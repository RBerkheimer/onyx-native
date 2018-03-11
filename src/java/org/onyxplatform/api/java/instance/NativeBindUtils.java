package org.onyxplatform.api.java.instance;

import clojure.java.api.Clojure;
import clojure.lang.IFn;
import clojure.lang.IPersistentMap;

import org.onyxplatform.api.java.OnyxNames;
import org.onyxplatform.api.java.OnyxMap;
import org.onyxplatform.api.java.NativeNames;
import org.onyxplatform.api.java.Catalog;
import org.onyxplatform.api.java.Task;
import org.onyxplatform.api.java.Job;
import org.onyxplatform.api.java.Lifecycle;

import org.onyxplatform.api.java.instance.INativeFn;
import org.onyxplatform.api.java.instance.IOnyxFnConstructor;

import org.onyxplatform.api.java.utils.MapFns;

/**
 * NativeBindUtils is a static utility class designed to work with User Classes
 * which extend the OnyxFn abstract class which are backed by native
 * libraries.
 * This utility provides a method which can add an object instance that is
 * derived from a native user class to a job.
 */
public class NativeBindUtils extends BindUtils implements OnyxNames, NativeNames {

	protected static IFn makeCatalogEntry;
    protected static IFn makeLifecycleEntry;

	/**
 	* Loads the clojure namespaces over-riding
	* the base classes
 	*/
	static {
		IFn requireFn = Clojure.var(CORE, Require);

		requireFn.invoke(Clojure.read(NATIVE_CATALOG));
		makeCatalogEntry = Clojure.var(NATIVE_CATALOG, MakeNativeInstanceTask);

        requireFn.invoke(Clojure.read(NATIVE_LIFECYCLES));
        makeLifecycleEntry = Clojure.var(NATIVE_LIFECYCLES, MakeNativeInstanceLifecycle);

	}

	/**
	 * Creates and adds an object instance to an existing Catalog object.
	 * The object instance is derived from a user class which extends
	 * the NativeOnyxFn abstract class. To use this method, a name for the object
	 * must be provided, along with the fully qualified user base class,
	 * a map of arguments to use as constructor args for the class,
	 * the library name, initialization parameters,
	 * and the environment parameters batchSize and batchTimeout.
	 * @param  catalog       the catalog object to which the new object instance will be added as a task
	 * @param  taskName      a string to use as a name for the object instance task in the Catalog
	 * @param  batchSize     an integer describing the number of segments that will be read at a time
	 * @param  batchTimeout  an integer describing the longest amount of time (ms) that a task will wait before reading segments
	 * @param  fqClassName   a string naming the fully qualified user class to use in object instance creation
	 * @param  ctrArgs       an IPersistentMap containing arguments to use in the user class constructor
	 * @param  libName   	a string naming the library to be loaded
	 * @return                returns the updated catalog which includes the added task
	 */

	public static void addFn(Job job, String taskName, int batchSize, int batchTimeout,
				                String fqClassName, IPersistentMap ctrArgs,
				                String libName) {
        IPersistentMap rawTaskMap = (IPersistentMap) makeCatalogEntry.invoke(taskName, batchSize, batchTimeout,
                                                                            fqClassName, ctrArgs,
                                                                            libName);
        OnyxMap taskMap = MapFns.toOnyxMap(rawTaskMap);
        Task task = new Task(taskMap);
        job.getCatalog().addTask(task);
        IPersistentMap rawLifecycleMap = (IPersistentMap) makeLifecycleEntry.invoke(taskName, "basic");
        OnyxMap lifecycleMap = MapFns.toOnyxMap(rawLifecycleMap);
        Lifecycle lifecycle = new Lifecycle(lifecycleMap);
        job.getLifecycles().addLifecycle(lifecycle);
	}

    /**
     * Creates and adds an object instance to an existing Catalog object.
     * The object instance is derived from a user class which extends
     * the NativeOnyxFn abstract class. To use this method, a name for the object
     * must be provided, along with the fully qualified user base class,
     * a map of arguments to use as constructor args for the class,
     * the library name, initialization parameters,
     * and the environment parameters batchSize and batchTimeout.
     * @param  catalog       the catalog object to which the new object instance will be added as a task
     * @param  taskName      a string to use as a name for the object instance task in the Catalog
     * @param  batchSize     an integer describing the number of segments that will be read at a time
     * @param  batchTimeout  an integer describing the longest amount of time (ms) that a task will wait before reading segments
     * @param  fqClassName   a string naming the fully qualified user class to use in object instance creation
     * @param  fqCtrClassName       a string naming the fully qualified constructor class used by the user class
     * @param  ctrArgs       an IPersistentMap containing arguments to use in the user class constructor
     * @param  libName   	a string naming the library to be loaded
     * @return                returns the updated catalog which includes the added task
     */
    public static void addFn(Job job, String taskName, int batchSize, int batchTimeout,
                             String fqClassName, String ctrClassName, IOnyxFnConstructor ctrArgs,
                             String libName) {
         IPersistentMap rawTaskMap = (IPersistentMap) makeCatalogEntry.invoke(taskName, batchSize, batchTimeout,
                                                                             fqClassName, ctrClassName, ctrArgs,
                                                                             libName);
         OnyxMap taskMap = MapFns.toOnyxMap(rawTaskMap);
         Task task = new Task(taskMap);
         job.getCatalog().addTask(task);
         IPersistentMap rawLifecycleMap = (IPersistentMap) makeLifecycleEntry.invoke(taskName, "user");
         OnyxMap lifecycleMap = MapFns.toOnyxMap(rawLifecycleMap);
         Lifecycle lifecycle = new Lifecycle(lifecycleMap);
         job.getLifecycles().addLifecycle(lifecycle);
    }

}

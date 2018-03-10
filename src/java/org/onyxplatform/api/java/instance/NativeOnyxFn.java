package org.onyxplatform.api.java.instance;

import clojure.lang.IPersistentMap;

import org.onyxplatform.api.java.utils.MapFns;
import org.onyxplatform.api.java.instance.Loader;
import org.onyxplatform.api.java.API;


/**
 *  NativeOnyxFn is the base class for all User type classes that a User wishes
 *  to use as an object instance as a task within an Onyx workflow.
 *  User classes must extend this NativeOnyxFn, and implement the consumeSegment method.
 */
public abstract class NativeOnyxFn extends OnyxFn implements INativeFn {


	public NativeOnyxFn(IPersistentMap m) {
		super(m);
	}

	/**
 	* Loads the native library.
	* <p>
	* This operation is per-instance and idempotent.
	*
 	* @param  libName The library name to load
 	* @param  args The arguments to use during loading
 	* @return      The loading response map
 	*/
	public void loadNativeResources(String libName)
		throws java.lang.UnsatisfiedLinkError {
			System.loadLibrary(libName);
		}

}

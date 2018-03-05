package onyxplatform.test;

import clojure.java.api.Clojure;
import clojure.lang.IFn;
import clojure.lang.IPersistentMap;

import org.onyxplatform.api.java.Catalog;
import org.onyxplatform.api.java.Task;
import org.onyxplatform.api.java.utils.MapFns;

import org.onyxplatform.api.java.instance.NativeBindUtils;

/**
 * SingleJavaTest tests a Job running with a single Java function, built
 * using the dynamic class loader. All basic behavior is set up using the
 * JobBuilder base class, while the pure Java object instance function is
 * added within this method itself.
 */
public class NativeSingleJavaTest extends NativeJobBuilder {

	public static final String PASS_FN = "onyxplatform.test.NativePassFn";
	public static final String EMPTY_FN = "onyxplatform.test.NativeEmptyFn";
	public static final String MERGE_FN = "onyxplatform.test.NativeMergeFn";
	public static final String DISSOC_FN = "onyxplatform.test.NativeDissocFn";
	public static final String ASSOC_FN = "onyxplatform.test.NativeAssocFn";
	public static final String GET_FN = "onyxplatform.test.NativeGetFn";

	private String className;
	private String libName;

    /**
     * Constructs a simple Job test that can run a pure java function
     * backed by the library name.
     * @param  onyxEnvConfig path to the EDN file specifying how to set up the job
     * @param  className The fully qualified class name to use
     * @param  libName The name of the backing library
     */
	public NativeSingleJavaTest(String onyxEnvConfig, String className, String libName) {
		super(onyxEnvConfig, 5, 50);
		this.className = className;
		this.libName = libName;
	}

    /**
     * Adds an Object instance of the test function to the Job catalog
     */
	public void configureCatalog() {
		NativeBindUtils.addFn(this.job, "pass", batchSize(), batchTimeout(),
				      this.className, MapFns.emptyMap(),
				      this.libName, 	 MapFns.emptyMap());
	}
}

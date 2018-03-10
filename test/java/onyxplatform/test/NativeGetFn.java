package onyxplatform.test;

import clojure.lang.IPersistentMap;

import org.onyxplatform.api.java.instance.NativeOnyxFn;
import org.onyxplatform.api.java.utils.MapFns;

/**
 * GetFn is a simple test class extending NativeOnyxFn which is used to test
 * the get map functions.
 */
public class NativeGetFn extends NativeOnyxFn {

	public NativeGetFn(IPersistentMap m) {
		super(m);
	}

	/**
 	* Calls the native getObj implementation
	* @param m Input map
	* @return Updated map
 	*/
	protected native IPersistentMap getObj(IPersistentMap m);

	/**
 	* Calls the native getInt implementation
	* @param m Input map
	* @return Updated map
 	*/
	protected native IPersistentMap getInt(IPersistentMap m);

	/**
 	* Calls the native getFloat implementation
	* @param m Input map
	* @return Updated map
 	*/
	protected native IPersistentMap getFloat(IPersistentMap m);

	/**
 	* Calls the native getDouble implementation
	* @param m Input map
	* @return Updated map
 	*/
	protected native IPersistentMap getDouble(IPersistentMap m);


	/**
 	* Calls the native getBool implementation
	* @param m Input map
	* @return Updated map
 	*/
	protected native IPersistentMap getBool(IPersistentMap m);

	/**
 	* Calls the native getStr implementation
	* @param m Input map
	* @return Updated map
 	*/
	protected native IPersistentMap getStr(IPersistentMap m);

	/**
	 * Takes a populated map like
	 *
	 * {:object {}
	 *  :int 1
	 *  :float 1.1
	 *  :double 2.2
	 *  :bool true
	 *  :str "TEST"
	 *  }
	 *
	 * Returns a map containing:
	 * {:object {}
     *  :object1 {}
     *  :int 1
     *  :int1 1
     *  :float 1.1
     *  :float1 1.1
     *  :double 2.2
     *  :double1 2.2
     *  :bool true
     *  :bool1 true
     *  :str "TEST"
     *  :str1 "TEST"
     *  }
	 * @param m The map to consume
	 * @return updated test map for comparison.
	 */
	public Object consumeSegment(IPersistentMap m) {

		m = getObj(m);
        m = getInt(m);
        m = getFloat(m);
        m = getDouble(m);
        m = getBool(m);
        m = getStr(m);
        return m;
    }
}

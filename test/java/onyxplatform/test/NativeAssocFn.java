package onyxplatform.test;

import clojure.lang.IPersistentMap;

import org.onyxplatform.api.java.instance.NativeOnyxFn;
import org.onyxplatform.api.java.utils.MapFns;

/**
 * Assoc is a simple test class extending NativeOnyxFn which is used to test
 * the native assoc functionality in an Onyx Job.
 */
public class NativeAssocFn extends NativeOnyxFn {

	public NativeAssocFn(IPersistentMap m) {
		super(m);
	}

	/**
 	* Calls the native assocObj implementation
	* @param m The coll
	* @param key The keyword
	* @param o The object value to assoc to the coll
 	*/
	protected native IPersistentMap assocObj(IPersistentMap m);

	/**
 	* Calls the native assocInt implementation
	* @param m The coll
	* @param key The keyword
	* @param v The int value to assoc to the coll
 	*/
	protected native IPersistentMap assocInt(IPersistentMap m);

	/**
 	* Calls the native assocFloat implementation
	* @param m The coll
	* @param key The keyword
	* @param f The float value to assoc to the coll
 	*/
	protected native IPersistentMap assocFloat(IPersistentMap m);

	/**
 	* Calls the native assocDouble implementation
	* @param m The coll
	* @param key The keyword
	* @param d The double value to assoc to the coll
 	*/
	protected native IPersistentMap assocDouble(IPersistentMap m);

	/**
 	* Calls the native assocBool implementation
	* @param m The coll
	* @param key The keyword
	* @param b The boolean value to assoc to the coll
 	*/
	protected native IPersistentMap assocBool(IPersistentMap m);

	/**
 	* Calls the native assocStr implementation
	* @param m The coll
	* @param key The keyword
	* @param s The String to assoc to the coll
 	*/
	protected native IPersistentMap assocStr(IPersistentMap m);

	/**
	 * Consumes an empty map and associates
	 * a key-value pair for each native
	 * type returning:
	 *
	 * {:object {}
	 *  :int 1
	 *  :float 1.1
	 *  :double 2.2
	 *  :bool true
	 *  :str "TEST"
	 *  }
	* @param m The map to consume
	* @return The map with the assoc'ed values
	 */
	public Object consumeSegment(IPersistentMap m) {
        //associates object = {}
		m = assocObj(m);
        //associates int = 1
        m = assocInt(m);
        //associates float = 1.1f
        m = assocFloat(m);
        //associates double = 2.2d
        m = assocDouble(m);
        //associates bool = true
        m = assocBool(m);
        //associates str = 'TEST'
        m = assocStr(m);
        return m;
	}
}

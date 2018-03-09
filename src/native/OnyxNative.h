
#ifndef _Included_OnyxNative
#define _Included_OnyxNative

#include <jni.h>
#include <stdbool.h>

#ifdef __cplusplus

#include <iostream>
#include <string>
using namespace std;

class OnyxNative {

	public:
		OnyxNative(JNIEnv *env);
		~OnyxNative();

		void init();

        jobject emptyMap();
        jobject mergeMaps(jobject, jobject);
        jobject assocObj(const char*, jobject, jobject);
        jobject assocInt(const char*, jobject, int);
        jobject assocFloat(const char*, jobject, float);
        jobject assocDouble(const char*, jobject, double);
        jobject assocBool(const char*, jobject, bool d);
        jobject assocStr(const char*, jobject, const char*);

		// JNI --------------------------
		//

		JNIEnv* getEnv();

		/**
		 * NOTE: All JNI objects are scoped to its calling context.
		 */
		jclass  getClass(std::string className);

		/**
 		* NOTE: jmethodID's have full runtime scope and can be re-used.
 		*/
		jmethodID getMethod(jclass clazz, std::string name, std::string decl, bool isStatic);


		// MapFns -----------------------
		//

		jobject merge(jobject a, jobject b);

			// Get
		jobject 	getObj(jobject ipmap, std::string key);
		int 		getInt(jobject ipmap, std::string key);
		long 		getLong(jobject ipmap, std::string key);
		float 		getFloat(jobject ipmap, std::string key);

		/**
		 * NOTE: This does NOT preserve precision.
		 *       adding 2.2 to the map, for example will
		 *       return a value of 2.200000047683716
		 */
		double 		getDouble(jobject ipmap, std::string key);
		bool 		getBool(jobject ipmap, std::string key);
		jstring 	getStr(jobject ipmap, std::string key);


			// Dissoc
		jobject dissoc(jobject ipmap, std::string key);


		// Utils -------------------------
		//

		void checkAndThrow(std::string msg);

		jstring toJavaString(std::string s);


	private:
		JNIEnv* m_env;

		// Map utilities
		jclass    m_mapClass;
		jmethodID m_mapEmptyId;
		jmethodID m_mapMergeId;
		jmethodID m_mapGetId;
		jmethodID m_mapAssocId;
		jmethodID m_mapDissocId;
};

extern "C" {

#endif

#ifdef __cplusplus
}
#endif

#endif

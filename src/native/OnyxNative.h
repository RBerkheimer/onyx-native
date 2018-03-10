
#ifndef _Included_OnyxNative
#define _Included_OnyxNative

#include <jni.h>
#include <stdbool.h>

#ifdef __cplusplus

#include <iostream>
#include <string>

class OnyxNative {

	public:
		OnyxNative(JNIEnv *env);
		~OnyxNative();

		void init();

        JNIEnv* getEnv();
        jclass  getClass(std::string className);
        jmethodID getMethod(jclass clazz, std::string name, std::string decl, bool isStatic);
        void checkAndThrow(std::string msg);
        jstring toJavaString(std::string s);

        jobject emptyMap();
        jobject mergeMaps(jobject, jobject);
        jobject dissoc(jobject, const char*);
        jobject assocObj(jobject, const char*, jobject);
        jobject assocInt(jobject, const char*, int);
        jobject assocFloat(jobject, const char*, float);
        jobject assocDouble(jobject, const char*, double);
        jobject assocBool(jobject, const char*, bool d);
        jobject assocStr(jobject, const char*, const char*);

        jobject 	getObj(jobject, const char*);
        int 		getInt(jobject, const char*);
        float 		getFloat(jobject, const char*);
        double 		getDouble(jobject, const char*);
        bool 		getBool(jobject, const char*);
        jstring 	getStr(jobject, const char*);

	private:
		JNIEnv* m_env;
};

extern "C" {

#endif

#ifdef __cplusplus
}
#endif

#endif

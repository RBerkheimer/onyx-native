#include <iostream>
#include <string>
using namespace std;
#include <jni.h>
#include "OnyxLib.h"
#include "OnyxNative.hpp"

extern "C"
{
    OnyxLib onyxlib_new(JNIEnv *env, jobject jobj) {
        OnyxLib onyx_native = new OnyxNative(env, jobj);
        onyx_native->init();
        return onyx_native;
    }

    void onyxlib_free(OnyxLib onyx_lib) {
        delete onyx_lib;
        onyx_lib = NULL;
    }

    void onyxlib_errorcheck(OnyxLib onyx_lib, const char* message){
        std::string m = message;
        onyx_lib->checkAndThrow(m);
    }

    JNIEnv* onyxlib_getenv(OnyxLib onyx_lib) {
        return onyx_lib->getEnv();
    }

    jobject onyxlib_getinstance(OnyxLib onyx_lib) {
        return onyx_lib->getInstance();
    }

    jclass onyxlib_getclass(OnyxLib onyx_lib, const char* classname) {
        std::string c = classname;
        return onyx_lib->getClass(c);
    }

    jmethodID onyxlib_getmethod(OnyxLib onyx_lib, const char* clas, const char* method,
                                const char* decl, bool is_static) {
        jmethodID id = NULL;
        std::string cname = clas;
        std::string mname = method;
        std::string sdecl = decl;

        jclass clazz = onyx_lib->getClass(cname);
        return onyx_lib->getMethod(clazz, mname, sdecl, is_static);
    }

    jstring onyxlib_tojavastring(OnyxLib onyx_lib, const char* cstr) {
        std::string s = cstr;
        return onyx_lib->toJavaString(s);
    }

    jobject onyxlib_emptymap(OnyxLib onyx_lib) {
        return onyx_lib->emptyMap();
    }

    jobject onyxlib_merge(OnyxLib onyx_lib, jobject jmap1, jobject jmap2) {
        return onyx_lib->merge(jmap1, jmap2);
    }

    jobject onyxlib_getobj(OnyxLib onyx_lib, jobject jmap, const char* jkey) {
        std::string k = jkey;
        return onyx_lib->getObj(jmap, k);
    }

    int onyxlib_getint(OnyxLib onyx_lib, jobject jmap, const char* jkey) {
        std::string k = jkey;
        return onyx_lib->getInt(jmap, k);
    }

    long onyxlib_getlong(OnyxLib onyx_lib, jobject jmap, const char* jkey) {
        std::string k = jkey;
        return onyx_lib->getLong(jmap, k);
    }

    float onyxlib_getfloat(OnyxLib onyx_lib, jobject jmap, const char* jkey) {
        std::string k = jkey;
        return onyx_lib->getFloat(jmap, k);
    }

    double onyxlib_getdouble(OnyxLib onyx_lib, jobject jmap, const char* jkey) {
        std::string k = jkey;
        return onyx_lib->getDouble(jmap, k);
    }

    bool onyxlib_getbool(OnyxLib onyx_lib, jobject jmap, const char* jkey) {
        std::string k = jkey;
        return onyx_lib->getBool(jmap, k);
    }

    jstring onyxlib_getstr(OnyxLib onyx_lib, jobject jmap, const char* jkey) {
        std::string k = jkey;
        return onyx_lib->getStr(jmap, k);
    }

    jobject onyxlib_assocobj(OnyxLib onyx_lib, jobject jmap, const char* jkey, jobject jobj) {
        std::string k = jkey;
        return onyx_lib->assocObj(jmap, k, jobj);
    }

    jobject onyxlib_assocint(OnyxLib onyx_lib, jobject jmap, const char* jkey, int jint) {
        std::string k = jkey;
        return onyx_lib->assocInt(jmap, k, jint);
    }

    jobject onyxlib_assoclong(OnyxLib onyx_lib, jobject jmap, const char* jkey, long jlong) {
        std::string k = jkey;
        return onyx_lib->assocLong(jmap, k, jlong);
    }

    jobject onyxlib_assocfloat(OnyxLib onyx_lib, jobject jmap, const char* jkey, float jfloat) {
        std::string k = jkey;
        return onyx_lib->assocFloat(jmap, k, jfloat);
    }

    jobject onyxlib_assocdouble(OnyxLib onyx_lib, jobject jmap, const char* jkey, double jdouble) {
        std::string k = jkey;
        return onyx_lib->assocDouble(jmap, k, jdouble);
    }

    jobject onyxlib_assocbool(OnyxLib onyx_lib, jobject jmap, const char* jkey, bool jbool) {
        std::string k = jkey;
        return onyx_lib->assocBool(jmap, k, jbool);
    }

    jobject onyxlib_assocstr(OnyxLib onyx_lib, jobject jmap, const char* jkey, const char* jstr) {
        std::string k = jkey;
        std::string str = jstr;
        return onyx_lib->assocStr(jmap, k, str);
    }

    jobject onyxlib_dissoc(OnyxLib onyx_lib, jobject jmap, const char* jkey) {
        std::string k = jkey;
        return onyx_lib->dissoc(jmap, k);
    }

}

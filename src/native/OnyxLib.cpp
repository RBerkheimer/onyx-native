#include <iostream>
#include <string>
using namespace std;
#include <jni.h>
#include "OnyxLib.h"
#include "OnyxNative.hpp"

extern "C"
{
    OnyxLib onyxlib_new(JNIEnv *env) {
        OnyxLib onyx_native = new OnyxNative(env);
        printf("inside onyxlib_new!\n");
        return onyx_native;
    }

    jobject onyxlib_emptymap(OnyxLib onyxlib) {
        return onyxlib->emptyMap();
    }

    jobject onyxlib_assocobj(OnyxLib onyxlib, const char* key, jobject jmap, jobject jobj) {
        return onyxlib->assocObj(key, jmap, jobj);
    }

    jobject onyxlib_assocint(OnyxLib onyxlib, const char* key, jobject jmap, int i) {
        return onyxlib->assocInt(key, jmap, i);
    }

    jobject onyxlib_assocfloat(OnyxLib onyxlib, const char* key, jobject jmap, float f) {
        return onyxlib->assocFloat(key, jmap, f);
    }

    jobject onyxlib_assocdouble(OnyxLib onyxlib, const char* key, jobject jmap, double d) {
        return onyxlib->assocDouble(key, jmap, d);
    }

    jobject onyxlib_assocbool(OnyxLib onyxlib, const char* key, jobject jmap, bool b) {
        return onyxlib->assocBool(key, jmap, b);
    }

    jobject onyxlib_assocstr(OnyxLib onyxlib, const char* key, jobject jmap, const char* s) {
        return onyxlib->assocStr(key, jmap, s);
    }


    void onyxlib_test(const char* teststr) {
        std::string k = teststr;
        printf("%s\n", teststr);
    }

    void onyxlib_free(OnyxLib onyx_lib) {
        delete onyx_lib;
    }

    void onyxlib_errorcheck(OnyxLib onyx_lib, const char* message){
        std::string m = message;
        onyx_lib->checkAndThrow(m);
    }

    JNIEnv* onyxlib_getenv(OnyxLib onyx_lib) {
        return onyx_lib->getEnv();
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

    jobject onyxlib_dissoc(OnyxLib onyx_lib, jobject jmap, const char* jkey) {
        std::string k = jkey;
        return onyx_lib->dissoc(jmap, k);
    }

}

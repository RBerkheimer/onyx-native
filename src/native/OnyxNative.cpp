#include "OnyxNative.h"
#include <iostream>
#include <string>
using namespace std;

#include <jni.h>


OnyxNative::OnyxNative(JNIEnv *env) {
    m_env = env;
}

OnyxNative::~OnyxNative() {}

void OnyxNative::init(){}

void OnyxNative::checkAndThrow(std::string msg) {
	if (m_env->ExceptionCheck()) {
		cout << "OnyxNative::checkAndThrow> msg=" << msg << endl;
	   	jclass Exception = m_env->FindClass("java/lang/Exception");
	   	m_env->ThrowNew(Exception,msg.c_str());
	}
}

JNIEnv* OnyxNative::getEnv() {
	return m_env;
}

jclass OnyxNative::getClass(std::string className) {
	jclass reqc = m_env->FindClass(className.c_str());
	std::string msg = "getClass> failed (" + className + ")";
	checkAndThrow(msg);
	return reqc;
}

jmethodID OnyxNative::getMethod(jclass clazz, std::string name, std::string decl, bool isStatic) {
	jmethodID id = NULL;
	if (isStatic) {
		id =  m_env->GetStaticMethodID(clazz, name.c_str(), decl.c_str());
	}
	else {
		id =  m_env->GetMethodID(clazz, name.c_str(), decl.c_str());
	}

	std::string msg = "getMethod> failed (name=" + name + ") (decl=" + decl + ")";
	checkAndThrow(msg);
	return id;
}

jstring OnyxNative::toJavaString(std::string s) {
	return 	m_env->NewStringUTF(s.c_str());
}

jobject OnyxNative::emptyMap() {
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID m_mapEmptyId = getMethod(mc, "emptyMap", "()Lclojure/lang/IPersistentMap;", true);
    jobject emptyMap = m_env->CallStaticObjectMethod(mc, m_mapEmptyId);
    return emptyMap;
}

jobject OnyxNative::mergeMaps(jobject map1, jobject map2) {
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID m_mapMergeId = getMethod(mc, "merge", "(Lclojure/lang/IPersistentMap;Lclojure/lang/IPersistentMap;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, m_mapMergeId, map1, map2);
    return updatedMap;
}

jobject OnyxNative::dissoc(jobject map, const char* key) {
	jstring objKey = m_env->NewStringUTF(key);
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID dissocId = getMethod(mc, "dissoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;)Lclojure/lang/IPersistentMap;", true);
	return m_env->CallStaticObjectMethod(mc, dissocId, map, objKey);
}

jobject OnyxNative::assocObj(jobject map, const char* key, jobject obj) {
    jstring objKey = m_env->NewStringUTF(key);
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID assocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, assocId, map, objKey, obj);
    return updatedMap;
}

jobject OnyxNative::assocInt(jobject map, const char* key, int i) {
    jstring intKey = m_env->NewStringUTF(key);
    jclass intClass = getClass("java/lang/Integer");
	jmethodID intMethodId =  m_env->GetMethodID(intClass, "<init>", "(I)V");
	jobject intObject = m_env->NewObject(intClass, intMethodId, (jint) i);
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID assocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, assocId, map, intKey, intObject);
    return updatedMap;
}

jobject OnyxNative::assocFloat(jobject map, const char* key, float f) {
    jstring floatKey = m_env->NewStringUTF(key);
    jclass floatClass = getClass("java/lang/Float");
	jmethodID floatMethodId =  m_env->GetMethodID(floatClass, "<init>", "(F)V");
	jobject floatObject = m_env->NewObject(floatClass, floatMethodId, (jfloat) f);
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID assocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, assocId, map, floatKey, floatObject);
    return updatedMap;
}

jobject OnyxNative::assocDouble(jobject map, const char* key, double d) {
    jstring doubleKey = m_env->NewStringUTF(key);
    jclass doubleClass = getClass("java/lang/Double");
	jmethodID doubleMethodId =  m_env->GetMethodID(doubleClass, "<init>", "(D)V");
	jobject doubleObject = m_env->NewObject(doubleClass, doubleMethodId, (jdouble) d);
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID assocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, assocId, map, doubleKey, doubleObject);
    return updatedMap;
}


jobject OnyxNative::assocBool(jobject map, const char* key, bool b) {
    jstring boolKey = m_env->NewStringUTF(key);
    jclass boolClass = getClass("java/lang/Boolean");
	jmethodID boolMethodId =  m_env->GetMethodID(boolClass, "<init>", "(Z)V");
	jobject boolObject = m_env->NewObject(boolClass, boolMethodId, (jboolean) b);
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID assocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, assocId, map, boolKey, boolObject);
    return updatedMap;
}


jobject OnyxNative::assocStr(jobject map, const char* key, const char* s) {
    jstring strKey = m_env->NewStringUTF(key);
	jobject strObject = m_env->NewStringUTF(s);
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID assocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, assocId, map, strKey, strObject);
    return updatedMap;
}


jobject OnyxNative::getObj(jobject map, const char* key) {
	jstring objKey = m_env->NewStringUTF(key);
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID getId = getMethod(mc, "get", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;)Ljava/lang/Object;", true);
    jobject returnObj = m_env->CallStaticObjectMethod(mc, getId, map, objKey);
    return returnObj;
}


int OnyxNative::getInt(jobject map, const char* key) {
	jobject intObj = getObj(map, key);
	jclass intClass = getClass("java/lang/Integer");
    jmethodID intId = m_env->GetMethodID(intClass, "intValue", "()I");
    int returnInt = (int) m_env->CallIntMethod(intObj, intId);
    return returnInt;
}


float OnyxNative::getFloat(jobject map, const char* key) {
	jobject floatObj = getObj(map, key);
	jclass floatClass = getClass("java/lang/Float");
    jmethodID floatId = m_env->GetMethodID(floatClass, "floatValue", "()F");
    float returnFloat = (float) m_env->CallFloatMethod(floatObj, floatId);
    return returnFloat;
}


double OnyxNative::getDouble(jobject map, const char* key) {
	jobject doubleObj = getObj(map, key);
	jclass doubleClass = getClass("java/lang/Double");
    jmethodID doubleId = m_env->GetMethodID(doubleClass, "doubleValue", "()D");
    double returnDouble = (double) m_env->CallDoubleMethod(doubleObj, doubleId);
    return returnDouble;
}


bool OnyxNative::getBool(jobject map, const char* key) {
	jobject boolObj = getObj(map, key);
	jclass boolClass = getClass("java/lang/Boolean");
    jmethodID boolId = m_env->GetMethodID(boolClass, "booleanValue", "()Z");
    bool returnBool = (bool) m_env->CallBooleanMethod(boolObj, boolId);
    return returnBool;
}

jstring OnyxNative::getStr(jobject map, const char* key) {
	jobject strObj = getObj(map, key);
	jclass strClass = getClass("java/lang/String");
    jstring jstr = (jstring) strObj;
    return jstr;

}

#include "OnyxNative.h"
#include <iostream>
#include <string>
using namespace std;

#include <jni.h>

/** Class encapsulating the runtime back pointer, affordances
 * for accessing utilities that live in Java-land.
 */

// Cnstr/Destr ----------------------------------
//

OnyxNative::OnyxNative (JNIEnv *env) {

    printf("OnyxNative constructor!\n");

    m_env = env;

	jclass mc = env->FindClass("org/onyxplatform/api/java/utils/MapFns");
	m_mapClass = (jclass) env->NewGlobalRef(mc);

	std::string msg = "OnyxNative::OnyxNative> failed to find MapFns";
	checkAndThrow(msg);
    printf("Finished construction!\n");
}

OnyxNative::~OnyxNative () {
    printf("Inside OnyxNative destructor!\n");
	m_env->DeleteGlobalRef(m_mapClass);
    printf("Finished Destruction!\n");
}

// Utils ---------------------------------------
//

void OnyxNative::checkAndThrow(std::string msg) {
	if (m_env->ExceptionCheck()) {
		cout << "OnyxNative::checkAndThrow> msg=" << msg << endl;
	   	jclass Exception = m_env->FindClass("java/lang/Exception");
	   	m_env->ThrowNew(Exception,msg.c_str());
	}
}

jobject OnyxNative::emptyMap() {
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID m_mapEmptyId = getMethod(mc, "emptyMap", "()Lclojure/lang/IPersistentMap;", true);
    jobject emptyMap = m_env->CallStaticObjectMethod(mc, m_mapEmptyId);
    return emptyMap;
}

jobject OnyxNative::assocObj(const char* key, jobject jmap, jobject jobj) {
    jstring test = m_env->NewStringUTF(key);
    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID m_mapAssocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, m_mapAssocId, jmap, test, jobj);

    return updatedMap;
}

jobject OnyxNative::assocInt(const char* key, jobject jmap, int i) {
    jstring intKey = m_env->NewStringUTF(key);

    jclass intClass = getClass("java/lang/Integer");
	jmethodID intMethodId =  m_env->GetMethodID(intClass, "<init>", "(I)V");
	jobject intObject = m_env->NewObject(intClass, intMethodId, (jint) i);

    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID m_mapAssocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, m_mapAssocId, jmap, intKey, intObject);

    return updatedMap;
}

jobject OnyxNative::assocFloat(const char* key, jobject jmap, float f) {
    jstring floatKey = m_env->NewStringUTF(key);

    jclass floatClass = getClass("java/lang/Float");
	jmethodID floatMethodId =  m_env->GetMethodID(floatClass, "<init>", "(F)V");
	jobject floatObject = m_env->NewObject(floatClass, floatMethodId, (jfloat) f);

    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID m_mapAssocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, m_mapAssocId, jmap, floatKey, floatObject);

    return updatedMap;
}

jobject OnyxNative::assocDouble(const char* key, jobject jmap, double d) {
    jstring doubleKey = m_env->NewStringUTF(key);

    jclass doubleClass = getClass("java/lang/Double");
	jmethodID doubleMethodId =  m_env->GetMethodID(doubleClass, "<init>", "(D)V");
	jobject doubleObject = m_env->NewObject(doubleClass, doubleMethodId, (jdouble) d);

    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID m_mapAssocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, m_mapAssocId, jmap, doubleKey, doubleObject);

    return updatedMap;
}


jobject OnyxNative::assocBool(const char* key, jobject jmap, bool b) {
    jstring boolKey = m_env->NewStringUTF(key);

    jclass boolClass = getClass("java/lang/Boolean");
	jmethodID boolMethodId =  m_env->GetMethodID(boolClass, "<init>", "(Z)V");
	jobject boolObject = m_env->NewObject(boolClass, boolMethodId, (jboolean) b);

    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID m_mapAssocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, m_mapAssocId, jmap, boolKey, boolObject);

    return updatedMap;
}


jobject OnyxNative::assocStr(const char* key, jobject jmap, const char* s) {
    jstring strKey = m_env->NewStringUTF(key);

	jobject strObject = m_env->NewStringUTF(s);

    jclass mc = m_env->FindClass("org/onyxplatform/api/java/utils/MapFns");
    jmethodID m_mapAssocId = getMethod(mc, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
    jobject updatedMap = m_env->CallStaticObjectMethod(mc, m_mapAssocId, jmap, strKey, strObject);

    return updatedMap;
}




// Accessors for runtime -----------------------
//

JNIEnv* OnyxNative::getEnv() {
	return m_env;
}

jclass OnyxNative::getClass(std::string className) {
	jclass reqc = m_env->FindClass(className.c_str());
	std::string msg = "getClass> failed (" + className + ")";
	checkAndThrow(msg);
	return reqc;
}

/**
 * NOTE: jmethodID's have full runtime scope and can be re-used.
 */
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


// JNI Entry point, Bootstrapping -------------------------------------
//

void OnyxNative::init(){}

/*void OnyxNative::init() {

	m_mapEmptyId = getMethod(m_mapClass, "emptyMap", "()Lclojure/lang/IPersistentMap;", true);
	std::string msg = "OnyxNative::init> emptyMap failed )";
	checkAndThrow(msg);

	m_mapMergeId = getMethod(m_mapClass, "merge", "(Lclojure/lang/IPersistentMap;Lclojure/lang/IPersistentMap;)Lclojure/lang/IPersistentMap;", true);
	msg = "OnyxNative::init> merge failed )";
	checkAndThrow(msg);

	m_mapGetId = getMethod(m_mapClass, "get", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;)Ljava/lang/Object;", true);
	msg = "OnyxNative::init> get failed )";
	checkAndThrow(msg);

	m_mapAssocId = getMethod(m_mapClass, "assoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;", true);
	msg = "OnyxNative::init> assoc failed )";
	checkAndThrow(msg);

	m_mapDissocId = getMethod(m_mapClass, "dissoc", "(Lclojure/lang/IPersistentMap;Ljava/lang/String;)Lclojure/lang/IPersistentMap;", true);
	msg = "OnyxNative::init> dissoc failed )";
	checkAndThrow(msg);

}*/


// IPersistentMap utilities -------------------------------------------
//


jobject OnyxNative::merge(jobject a, jobject b) {
	return m_env->CallStaticObjectMethod(m_mapClass, m_mapMergeId, a, b);
}


	// Get -------------------------
	//

jobject OnyxNative::getObj(jobject ipmap, std::string key) {
	jstring keyStr = toJavaString(key);
	return m_env->CallStaticObjectMethod(m_mapClass, m_mapGetId, ipmap, keyStr);
}

int OnyxNative::getInt(jobject ipmap, std::string key) {
	jobject v = getObj(ipmap, key);
	jclass clazz = getClass("java/lang/Integer");
	if (m_env->IsInstanceOf(v, clazz) == JNI_TRUE)
	{
		jmethodID mid   = m_env->GetMethodID(clazz, "intValue", "()I");
		return (int) m_env->CallIntMethod(v, mid);
	}
	else {
		return -1;
	}
}

long OnyxNative::getLong(jobject ipmap, std::string key) {
	jobject v = getObj(ipmap, key);
	jclass clazz = getClass("java/lang/Long");
	if (m_env->IsInstanceOf(v, clazz) == JNI_TRUE)
	{
		jmethodID mid   = m_env->GetMethodID(clazz, "longValue", "()J");
		return (long) m_env->CallLongMethod(v, mid);
	}
	else {
		return -1;
	}
}

float OnyxNative::getFloat(jobject ipmap, std::string key) {
	jobject v = getObj(ipmap, key);
	jclass clazz = getClass("java/lang/Float");
	if (m_env->IsInstanceOf(v, clazz) == JNI_TRUE)
	{
		jmethodID mid   = m_env->GetMethodID(clazz, "floatValue", "()F");
		return (float) m_env->CallFloatMethod(v, mid);
	}
	else {
		return -1.0f;
	}
}

double OnyxNative::getDouble(jobject ipmap, std::string key) {
	jobject v = getObj(ipmap, key);
	jclass clazz = getClass("java/lang/Double");
	if (m_env->IsInstanceOf(v, clazz) == JNI_TRUE)
	{
		jmethodID mid   = m_env->GetMethodID(clazz, "doubleValue", "()D");
		return (float) m_env->CallDoubleMethod(v, mid);
	}
	else {
		return -1.0f;
	}
}

bool OnyxNative::getBool(jobject ipmap, std::string key) {
	jobject v = getObj(ipmap, key);
	jclass clazz = getClass("java/lang/Boolean");
	if (m_env->IsInstanceOf(v, clazz) == JNI_TRUE)
	{
		jmethodID mid   = m_env->GetMethodID(clazz, "booleanValue", "()Z");
		return (bool) m_env->CallBooleanMethod(v, mid);
	}
	else {
		return false;
	}
}

jstring OnyxNative::getStr(jobject ipmap, std::string key){
	jobject v = getObj(ipmap, key);
	jclass clazz = getClass("java/lang/String");
	if (m_env->IsInstanceOf(v, clazz) == JNI_TRUE)
	{
		return (jstring)v;
	}
	else {
		return NULL;
	}
}


	// Dissoc ------------------------
	//
jobject OnyxNative::dissoc(jobject ipmap, std::string key) {
	jstring keyStr = toJavaString(key);
	return m_env->CallStaticObjectMethod(m_mapClass, m_mapDissocId, ipmap, keyStr);
}

#include <jni.h>

#include "OnyxNative.h"
#include "onyxplatform_test_NativeEmptyFn.h"
#include "onyxplatform_test_NativeMergeFn.h"
#include "onyxplatform_test_NativeAssocFn.h"
#include "onyxplatform_test_NativeDissocFn.h"
#include "onyxplatform_test_NativeGetFn.h"

/*
 * Class:     onyxplatform_test_NativeEmptyFn
 * Method:    createEmptyMap
 * Signature: ()Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeEmptyFn_createEmptyMap
  (JNIEnv *env, jobject obj)
{
	return onyx_emptyMap();
}

/*
 * Class:     onyxplatform_test_NativeMergeFn
 * Method:    mergeSimple
 * Signature: (Lclojure/lang/IPersistentMap;Lclojure/lang/IPersistentMap;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeMergeFn_merge
  (JNIEnv *env, jobject inst, jobject m1, jobject m2)
{
	return onyx_merge(m1, m2);
}


/*
 * Class:     onyxplatform_test_NativeDissocFn
 * Method:    dissoc
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeDissocFn_dissoc
  (JNIEnv *env, jobject inst, jobject m, jstring key)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jobject result = onyx_dissoc(m, k);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}


/** NativeAssocFn ---------------------------------------- */

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocObj
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/Object;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocObj
  (JNIEnv *env, jobject inst, jobject m, jstring key, jobject obj)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jobject result = onyx_assocObj(m, k, obj);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocInt
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;I)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocInt
  (JNIEnv *env, jobject inst, jobject m, jstring key, jint i)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jobject result = onyx_assocInt(m, k, i);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocFloat
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;F)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocFloat
  (JNIEnv *env, jobject inst, jobject m, jstring key, jfloat f)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jobject result = onyx_assocFloat(m, k, f);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocDouble
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;D)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocDouble
  (JNIEnv *env, jobject inst, jobject m, jstring key, jdouble d)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jobject result = onyx_assocDouble(m, k, d);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}


/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocBool
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;Z)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocBool
  (JNIEnv *env, jobject inst, jobject m, jstring key, jboolean b)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jobject result = onyx_assocBool(m, k, b);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocStr
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;Ljava/lang/String;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocStr
  (JNIEnv *env, jobject inst, jobject m, jstring key, jstring s)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	const char *str = (*env)->GetStringUTFChars(env, s, 0);
	jobject result = onyx_assocStr(m, k, str);
	(*env)->ReleaseStringUTFChars(env, key, k);
	(*env)->ReleaseStringUTFChars(env, s, str);
	return result;
}


/** NativeGetFn ----------------------------------------- */

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getObj
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeGetFn_getObj
  (JNIEnv *env, jobject inst, jobject m, jstring key)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jobject result = onyx_getObj(m, k);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getInt
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_onyxplatform_test_NativeGetFn_getInt
  (JNIEnv *env, jobject inst, jobject m, jstring key)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jint result = onyx_getInt(m, k);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getFloat
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)F
 */
JNIEXPORT jfloat JNICALL Java_onyxplatform_test_NativeGetFn_getFloat
  (JNIEnv *env, jobject inst, jobject m, jstring key)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jfloat result = onyx_getFloat(m, k);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getDouble
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)D
 */
JNIEXPORT jdouble JNICALL Java_onyxplatform_test_NativeGetFn_getDouble
  (JNIEnv *env, jobject inst, jobject m, jstring key)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jdouble result = onyx_getDouble(m, k);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getLong
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_onyxplatform_test_NativeGetFn_getLong
  (JNIEnv *env, jobject inst, jobject m, jstring key)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jlong result = onyx_getLong(m, k);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getBool
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_onyxplatform_test_NativeGetFn_getBool
  (JNIEnv *env, jobject inst, jobject m, jstring key)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	jboolean result = onyx_getBool(m, k);
	(*env)->ReleaseStringUTFChars(env, key, k);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getStr
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_onyxplatform_test_NativeGetFn_getStr
  (JNIEnv *env, jobject inst, jobject m, jstring key)
{
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
	return onyx_getStr(m, k);
}

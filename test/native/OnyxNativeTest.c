#include <jni.h>

#include "OnyxLib.h"
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
  (JNIEnv *env, jobject jobj) {
    OnyxLib olib = onyxlib_new(env, jobj);
	jobject newmap = onyxlib_emptymap(olib);
    onyxlib_free(olib);
    return newmap;
}

/*
 * Class:     onyxplatform_test_NativeMergeFn
 * Method:    mergeSimple
 * Signature: (Lclojure/lang/IPersistentMap;Lclojure/lang/IPersistentMap;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeMergeFn_merge
  (JNIEnv *env, jobject inst, jobject jmap1, jobject jmap2) {
      OnyxLib olib = onyxlib_new(env, inst);
      jobject newmap = onyxlib_merge(olib, jmap1, jmap2);
      onyxlib_free(olib);
      return newmap;
}

/*
 * Class:     onyxplatform_test_NativeDissocFn
 * Method:    dissoc
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeDissocFn_dissoc
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
      OnyxLib olib = onyxlib_new(env, inst);
      const char *k = (*env)->GetStringUTFChars(env, key, 0);
      jobject result = onyxlib_dissoc(olib, m, k);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return result;
}


/** NativeAssocFn ---------------------------------------- */

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocObj
 * Signature: (Lclojure/lang/IPersistentMap;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT void JNICALL Java_onyxplatform_test_NativeAssocFn_assocObj
  (JNIEnv *env, jobject inst, jobject m) {
      printf("obj!\n");
      OnyxLib olib = onyxlib_new(env, inst);
      //jobject obj = onyxlib_emptymap(olib);
      //onyxlib_assocobj(olib, m, "object", obj);
      onyxlib_free(olib);
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocInt
 * Signature: (Lclojure/lang/IPersistentMap;)V
 */
JNIEXPORT void JNICALL Java_onyxplatform_test_NativeAssocFn_assocInt
  (JNIEnv *env, jobject inst, jobject m) {
      printf("int!\n");
      OnyxLib olib = onyxlib_new(env, inst);
      //m = onyxlib_assocint(olib, m, "int", 1);
      onyxlib_free(olib);
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocFloat
 * Signature: (Lclojure/lang/IPersistentMap;)V
 */
JNIEXPORT void JNICALL Java_onyxplatform_test_NativeAssocFn_assocFloat
  (JNIEnv *env, jobject inst, jobject m) {
      printf("float!\n");
      OnyxLib olib = onyxlib_new(env, inst);
      //m = onyxlib_assocfloat(olib, m, "float", 1.1);
      onyxlib_free(olib);
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocDouble
 * Signature: (Lclojure/lang/IPersistentMap;)V
 */
JNIEXPORT void JNICALL Java_onyxplatform_test_NativeAssocFn_assocDouble
  (JNIEnv *env, jobject inst, jobject m) {
	/*const char *k = (*env)->GetStringUTFChars(env, key, 0);
    OnyxLib olib = onyxlib_new(env, inst);
	jobject result = onyxlib_assocdouble(olib, m, k, d);
	(*env)->ReleaseStringUTFChars(env, key, k);
    onyxlib_free(olib);
	return result;*/
}


/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocBool
 * Signature: (Lclojure/lang/IPersistentMap;)V
 */
JNIEXPORT void JNICALL Java_onyxplatform_test_NativeAssocFn_assocBool
  (JNIEnv *env, jobject inst, jobject m) {
      /*const char *k = (*env)->GetStringUTFChars(env, key, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jobject result = onyxlib_assocbool(olib, m, k, b);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return result;*/
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocStr
 * Signature: (Lclojure/lang/IPersistentMap;)V
 */
JNIEXPORT void JNICALL Java_onyxplatform_test_NativeAssocFn_assocStr
  (JNIEnv *env, jobject inst, jobject m) {
      /*const char *k = (*env)->GetStringUTFChars(env, key, 0);
      const char *str = (*env)->GetStringUTFChars(env, s, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jobject result = onyxlib_assocstr(olib, m, k, str);
      (*env)->ReleaseStringUTFChars(env, key, k);
      (*env)->ReleaseStringUTFChars(env, s, str);
      onyxlib_free(olib);
      return result;*/
}


/** NativeGetFn ----------------------------------------- */

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getObj
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeGetFn_getObj
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
      const char *k = (*env)->GetStringUTFChars(env, key, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jobject result = onyxlib_getobj(olib, m, k);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getInt
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_onyxplatform_test_NativeGetFn_getInt
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
    OnyxLib olib = onyxlib_new(env, inst);
	jint result = onyxlib_getint(olib, m, k);
	(*env)->ReleaseStringUTFChars(env, key, k);
    onyxlib_free(olib);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getFloat
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)F
 */
JNIEXPORT jfloat JNICALL Java_onyxplatform_test_NativeGetFn_getFloat
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
    OnyxLib olib = onyxlib_new(env, inst);
	jfloat result = onyxlib_getfloat(olib, m, k);
	(*env)->ReleaseStringUTFChars(env, key, k);
    onyxlib_free(olib);
	return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getDouble
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)D
 */
JNIEXPORT jdouble JNICALL Java_onyxplatform_test_NativeGetFn_getDouble
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
      const char *k = (*env)->GetStringUTFChars(env, key, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jdouble result = onyxlib_getdouble(olib, m, k);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getLong
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)J
 */
JNIEXPORT jlong JNICALL Java_onyxplatform_test_NativeGetFn_getLong
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
      const char *k = (*env)->GetStringUTFChars(env, key, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jlong result = onyxlib_getlong(olib, m, k);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getBool
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Z
 */
JNIEXPORT jboolean JNICALL Java_onyxplatform_test_NativeGetFn_getBool
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
      const char *k = (*env)->GetStringUTFChars(env, key, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jboolean result = onyxlib_getbool(olib, m, k);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return result;
}

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getStr
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_onyxplatform_test_NativeGetFn_getStr
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
      const char *k = (*env)->GetStringUTFChars(env, key, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jstring jstr = onyxlib_getstr(olib, m, k);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return jstr;
}

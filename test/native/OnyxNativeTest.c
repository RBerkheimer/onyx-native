#include <jni.h>

#include "OnyxLib.h"
#include "onyxplatform_test_NativeEmptyFn.h"
#include "onyxplatform_test_NativeMergeFn.h"
#include "onyxplatform_test_NativeAssocFn.h"
#include "onyxplatform_test_NativeDissocFn.h"
//#include "onyxplatform_test_NativeGetFn.h"

/*
 * Class:     onyxplatform_test_NativeEmptyFn
 * Method:    createEmptyMap
 * Signature: ()Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeEmptyFn_createEmptyMap
  (JNIEnv *env, jobject jobj) {
    OnyxLib olib = onyxlib_new(env);
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
  (JNIEnv *env, jobject inst) {
      OnyxLib olib = onyxlib_new(env);

      jobject emptymap1 = onyxlib_emptymap(olib);
      const char *k1 = "map1";
      int v1 = 1;
      jobject map1 = onyxlib_assocint(olib, emptymap1, k1, v1);

      jobject emptymap2 = onyxlib_emptymap(olib);
      const char *k2 = "map2";
      const char *v2 = "TEST";
      jobject map2 = onyxlib_assocstr(olib, emptymap2, k2, v2);

      jobject r = onyxlib_mergemaps(olib, map1, map2);
      onyxlib_free(olib);
      return r;
}

/*
 * Class:     onyxplatform_test_NativeDissocFn
 * Method:    dissoc
 * Signature: (Lclojure/lang/IPersistentMap;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeDissocFn_dissoc
  (JNIEnv *env, jobject inst, jobject m) {
      const char *k = "dissoc";
      OnyxLib olib = onyxlib_new(env);
      jobject result = onyxlib_dissoc(olib, m, k);
      onyxlib_free(olib);
      return result;
}


/** NativeAssocFn ---------------------------------------- */

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocObj
 * Signature: (Lclojure/lang/IPersistentMap;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocObj
  (JNIEnv *env, jobject inst, jobject m) {
      const char *k = "object";
      OnyxLib olib = onyxlib_new(env);
      jobject emptyMap = onyxlib_emptymap(olib);
      jobject r = onyxlib_assocobj(olib, m, k, emptyMap);
      onyxlib_free(olib);
      return r;
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocInt
 * Signature: (Lclojure/lang/IPersistentMap;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocInt
  (JNIEnv *env, jobject inst, jobject m) {
      const char *k = "int";
      int i = 1;
      OnyxLib olib = onyxlib_new(env);
      jobject r = onyxlib_assocint(olib, m, k, i);
      onyxlib_free(olib);
      return r;
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocFloat
 * Signature: (Lclojure/lang/IPersistentMap;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocFloat
  (JNIEnv *env, jobject inst, jobject m) {
      const char *k = "float";
      float f = 1.1;
      OnyxLib olib = onyxlib_new(env);
      jobject r = onyxlib_assocfloat(olib, m, k, f);
      onyxlib_free(olib);
      return r;
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocDouble
 * Signature: (Lclojure/lang/IPersistentMap;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocDouble
  (JNIEnv *env, jobject inst, jobject m) {
      const char *k = "double";
      double d = 2.2;
      OnyxLib olib = onyxlib_new(env);
      jobject r = onyxlib_assocdouble(olib, m, k, d);
      onyxlib_free(olib);
      return r;
}


/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocBool
 * Signature: (Lclojure/lang/IPersistentMap;)V
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocBool
  (JNIEnv *env, jobject inst, jobject m) {
      const char *k = "bool";
      bool b = true;
      OnyxLib olib = onyxlib_new(env);
      jobject r = onyxlib_assocbool(olib, m, k, b);
      onyxlib_free(olib);
      return r;
}

/*
 * Class:     onyxplatform_test_NativeAssocFn
 * Method:    assocStr
 * Signature: (Lclojure/lang/IPersistentMap;)V
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeAssocFn_assocStr
  (JNIEnv *env, jobject inst, jobject m) {
      const char *k = "str";
      const char *s = "TEST";
      OnyxLib olib = onyxlib_new(env);
      jobject r = onyxlib_assocstr(olib, m, k, s);
      onyxlib_free(olib);
      return r;
}


/** NativeGetFn ----------------------------------------- */

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getObj
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Lclojure/lang/IPersistentMap;
 */
/*JNIEXPORT jobject JNICALL Java_onyxplatform_test_NativeGetFn_getObj
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
      const char *k = (*env)->GetStringUTFChars(env, key, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jobject result = onyxlib_getobj(olib, m, k);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return result;
}*/

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getInt
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)I
 */
/*JNIEXPORT void JNICALL Java_onyxplatform_test_NativeGetFn_getInt
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
	/*const char *k = (*env)->GetStringUTFChars(env, key, 0);
    OnyxLib olib = onyxlib_new(env, inst);
	jint result = onyxlib_getint(olib, m, k);
	(*env)->ReleaseStringUTFChars(env, key, k);
    onyxlib_free(olib);
	return result;
}*/

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getFloat
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)F
 */
/*JNIEXPORT void JNICALL Java_onyxplatform_test_NativeGetFn_getFloat
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
	const char *k = (*env)->GetStringUTFChars(env, key, 0);
    OnyxLib olib = onyxlib_new(env, inst);
	jfloat result = onyxlib_getfloat(olib, m, k);
	(*env)->ReleaseStringUTFChars(env, key, k);
    onyxlib_free(olib);
	return result;
}*/

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getDouble
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)D
 */
/*JNIEXPORT void JNICALL Java_onyxplatform_test_NativeGetFn_getDouble
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
      const char *k = (*env)->GetStringUTFChars(env, key, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jdouble result = onyxlib_getdouble(olib, m, k);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return result;
}*/

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getLong
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)J
 */
/*JNIEXPORT void JNICALL Java_onyxplatform_test_NativeGetFn_getLong
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
      const char *k = (*env)->GetStringUTFChars(env, key, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jlong result = onyxlib_getlong(olib, m, k);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return result;
}*/

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getBool
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Z
 */
/*JNIEXPORT void JNICALL Java_onyxplatform_test_NativeGetFn_getBool
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
      /*const char *k = (*env)->GetStringUTFChars(env, key, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jboolean result = onyxlib_getbool(olib, m, k);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return result;
}*/

/*
 * Class:     onyxplatform_test_NativeGetFn
 * Method:    getStr
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Ljava/lang/String;
 */
/*JNIEXPORT jstring JNICALL Java_onyxplatform_test_NativeGetFn_getStr
  (JNIEnv *env, jobject inst, jobject m, jstring key) {
      const char *k = (*env)->GetStringUTFChars(env, key, 0);
      OnyxLib olib = onyxlib_new(env, inst);
      jstring jstr = onyxlib_getstr(olib, m, k);
      (*env)->ReleaseStringUTFChars(env, key, k);
      onyxlib_free(olib);
      return jstr;
}*/

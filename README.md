# Onyx Native - C Bindings and Utilities for Onyx Java

## Overview

Onyx Native was designed to support the use of native code, such as C, C++, and Fortran, in Onyx Java. Onyx Java provides Java bindings to Onyx, allowing [Onyx](http://www.onyxplatform.org) to process Java. So, through Onyx Java, users of Onyx Native can take advantage of having their code run in Onyx.

## Build Status

CircleCI Tests:  [![CircleCI](https://circleci.com/gh/RBerkheimer/onyx-native.svg?style=svg)](https://circleci.com/gh/RBerkheimer/onyx-native)

OnyxNative is currently supported for Onyx 0.9.15 with plans to migrate to the .12 series of Onyx in the near future.

## Architectural Approach

Onyx-native builds on the features of [onyx-java](https://github.com/rberkheimer/onyx-java) that provide support for the use of stateful Java instances in a workflow.
<br>
<br>
This packages provides two extensions to the Onyx Java BindUtils - allowing native tasks to be added to Onyx Java jobs by specifying a user DLL.
It also provides a standardized makefile to help users easily make cross-platform (OSX and UNIX flavor) DLLs that include the OnyxNative utils lib for IPersistentMap manipulation, called OnyxLib.
<br>
<br>

### Using Java Instances

Onyx-java provides affordances for inclusion of Java instances in a workflow via specialized catalog tools:<br>
<br>

```
import org.onyxplatform.api.java.instance.BindUtils;

Job job = new Job();

String taskName = "pass";
String fullyQualifiedJavaClass = "onyxplatform.test.PassFn";
IPersistentMap constructorArgs = MapFns.emptyMap();

int batchSize = 5; //batchSize specifies how many data segments to process together for this task
int batchTimeout = 50; //batchTimeout specifies how long onyx should wait on a hanging set of data segments before retrying

BindUtils.addFn(job, batchSize, batchTimeout, fullyQualifiedJavaClass, constructorArgs);
```
<br>
Which loads a pure Java class derived from *OnyxFn*

```
package onyxplatform.test;

import clojure.lang.IPersistentMap;

import org.onyxplatform.api.java.instance.OnyxFn;

public class PassFn extends OnyxFn {

        public PassFn(IPersistentMap m) {
                super(m);
        }

        public Object consumeSegment(IPersistentMap m) {
                return m;
        }
}
```

### Using Native-Backed Instances

Onyx-native provides additional support for native-backed instances by providing an extension BindUtils method (just specify the user DLL name in addition to the job instance, batch info, java class and constructor args). This will load the native library when the task is ready to run. Since the native library is idempotent at load, it stays loaded for use by any other tasks that may need to use it in the job.
The following sections demonstrate use of the native-specific features along with the interfaces and utilities at each level of abstraction.
<br>
<br>

#### Basic Usage

Onyx-native parallels onyx-java's approach offering additional native affordances to access runtime VM resources along with C/C++ utilities to directly manipulate Clojure maps in JNI functions.
<br>
<br>

#### Java

Onyx-native follows the same approach that onyx-java does (shown above) with additions to
specife the library along with initialization arguments. These are used along with native-specific
versions of the core API *NAPI* and *NativeOnyxEnv* to load and bootstrap your
native-backed instance at runtime.

<br>
<br>
As before, you use *NativeBindUtils* to generate a catalog entry:<br>
<br>

```
  Job j = new Job();
  NativeBindUtils.addFn(job, "pass", batchSize(), batchTimeout(),
                        fullyQualifiedJavaClassName, JavaClassConstructorArgs, "SomeLibrary");
```
<br>

The java class wraps your native code and includes the native function call -

```
public class DissocFn extends NativeOnyxFn {

 protected native IPersistentMap dissoc(IPersistentMap m);

 public Object consumeSegment(IPersistentMap m) {
   return dissoc(m);
 }
```

Note that all provided OnyxNative utilities in C/C++ work with immutable IPersistentMaps. The simplest use of this library would be to always pass only an IPersistentMap to the native function and return an IPersistentMap. Do all native manipulation inside native code. This ensures instance isolation.

#### Native

A simple implementation which proxies to the native map utility function:<br>

Javah generated header
```
/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class onyxplatform_test_DissocFn */

#ifndef _Included_onyxplatform_test_DissocFn
#define _Included_onyxplatform_test_DissocFn
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     onyxplatform_test_DissocFn
 * Method:    dissoc
 * Signature: (Lclojure/lang/IPersistentMap;Ljava/lang/String;)Lclojure/lang/IPersistentMap;
 */
JNIEXPORT jobject JNICALL Java_onyxplatform_test_DissocFn_dissoc
      (JNIEnv *, jobject, jobject, jstring);

#ifdef __cplusplus
}
#endif
#endif
```

Implementation
```
#include <jni.h>

#include "OnyxLib.h"
#include "onyxplatform_test_DissocFn.h"

JNIEXPORT jobject JNICALL Java_onyxplatform_test_DissocFn_dissoc
  (JNIEnv *env, jobject inst, jobject m) {
    const char* dissocKey = "dissoc";
    OnyxLib onyxlib = new OnyxLib(env);
    jobject result = onyxlib_dissoc(onyxlib, m, dissocKey);
    return result;
}

```

### Interop Utilities

OnyxLib is a native library written in C/C++ that allows easy manipulation of IPersistentMaps. Also, inside every user method called by Java, the user has access to their task instance. So the user can pass an IPersistentMap containing all of their task segment data, and also make calls against the task instance itself (to get things like task-wide properties or make log calls).
<br>
<br>

#### VM

Using JNI functions require some combination of parameters that include a jclass, and often a jmethodID.
Obtaining them from fully-qualified class name requires stereotyped boilerplate. These functions wrap
this functionality:

##### C++

```
JNIEnv* getEnv(); //holds the held JNIEnv pointer
jclass  getClass(const char* fullyQualifiedClassName);
jmethodID getMethod(const char* clazz, const char* name, const char* decl, bool isStatic);
jstring toJavaString(const char* s); //turns a const char* into a jstring
```

##### C

```
JNIEXPORT JNIEnv* onyxlib_getJNIEnv(OnyxLib olib);
JNIEXPORT jclass  onyxlib_getClass(OnyxLib olib, const char* pFqClassName);
JNIEXPORT jmethodID onyx_getMethod(OnyxLib olib, const char* clazz, const char* name, const char* decl, bool isStatic);
```

#### Map

<br>

The following methods are provided as part of the OnyxNative OnyxLib in C/C++:

##### C++

```
jobject emptyMap();
jobject mergeMap(jobject a, jobject b);

jobject         getObj(jobject ipmap, std::string key);
int             getInt(jobject ipmap, std::string key);
float           getFloat(jobject ipmap, std::string key);
double          getDouble(jobject ipmap, std::string key);
bool            getBool(jobject ipmap, std::string key);
jstring         getStr(jobject ipmap, std::string key);

jobject assocObj(jobject ipmap, std::string key, jobject value);
jobject assocInt(jobject ipmap, std::string key, int value);
jobject assocFloat(jobject ipmap, std::string key, float value);
jobject assocDouble(jobject ipmap, std::string key, double value);
jobject assocBool(jobject ipmap, std::string key, bool value);
jobject assocStr(jobject ipmap, std::string key, std::string value);

jobject dissoc(jobject ipmap, std::string key);
```

##### C

```

jobject       onyxlib_emptyMap(OnyxLib olib);
jobject       onyxlib_mergemaps(OnyxLib olib, jobject a, jobject b);

jobject       onyxlib_getObj(OnyxLib olib, jobject ipmap, const char* key);
int           onyxlib_getInt(OnyxLib olib, jobject ipmap, const char* key);
float         onyxlib_getFloat(OnyxLib olib, jobject ipmap, const char* key);
double        onyxlib_getDouble(OnyxLib olib, jobject ipmap, const char* key);
bool          onyxlib_getBool(OnyxLib olib, jobject ipmap, const char* key);
jstring       onyxlib_getStr(OnyxLib olib, jobject ipmap, const char* key);

jobject       onyxlib_assocObj(OnyxLib olib, jobject ipmap, const char* key, jobject value);
jobject       onyxlib_assocInt(OnyxLib olib, jobject ipmap, const char* key, int value);
jobject       onyxlib_assocLong(OnyxLib olib, jobject ipmap, const char* key, long value);
jobject       onyxlib_assocFloat(OnyxLib olib, jobject ipmap, const char* key, float value);
jobject       onyxlib_assocDouble(OnyxLib olib, jobject ipmap, const char* key, double value);
jobject       onyxlib_assocBool(OnyxLib olib, jobject ipmap, const char* key, bool value);
jobject       onyxlib_assocStr(OnyxLib olib, jobject ipmap, const char* key, std::string value);
jobject       onyxlib_dissoc(OnyxLib olib, jobject ipmap, const char*);
```

<br>
<br>

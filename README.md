# onyx-native - Affordances for native code in Onyx workflows

## Overview

The onyx-native package was designed to support the use of stateful,
native-backed Java objects in an [Onyx Platform](http://onyxplatform.org) workflow.

## Architectural Approach

Onyx-native builds on new features being added to [onyx-java](https://github.com/RBerkheimer/onyx-java) that 
provide support for the use of stateful Java instances in a workflow.<br>
<br>
This packages provides a simple and non-invasive matching set of Java and C 
interfaces that leverage Java's JNI and C++ to enable bootstrapping 
and memory management of native code in an Onyx workflow. <br>
<br>
This allows for the inclusion of native code in a way that requires few changes 
and that is a natural fit to an information-flow-based workflow 
system that is purely functional.<br>
<br>

### Using Java Instances

Onyx-java provides affordances for inclusion of Java instances in a workflow via specialized catalog tools:<br>
<br>

```
import org.onyxplatform.api.java.instance.BindUtils;

Catalog catalog = new Catalog();

String taskName = "pass";
String fullyQualifiedName = "onyxplatform.test.PassFn";
IPersistentMap ctrArgs = MapFns.emptyMap();

int batchSize = 5;
int batchTimeout = 50;

BindUtils.addFn(catalog, batchSize, batchTimeout, fullyQualifiedName, ctrArgs);
```
<br>
Which loads a pure Java class derived from *OnyxFn*:

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





### Expected initial publication May 2017, depends on ongoing work to upgrade [onyx-java](https://github.com/RBerkheimer/onyx-java)




package org.onyxplatform.api.java.instance;

import clojure.lang.IPersistentMap;

public interface INativeFn {

    public IPersistentMap loadNativeResources(String libName, IPersistentMap args);
    public void releaseNativeResources();
}

package org.onyxplatform.api.java.instance;

import clojure.lang.IPersistentMap;

public interface INativeFn {

    public void loadNativeResources(String libName);

    public void unloadNativeResources();
}

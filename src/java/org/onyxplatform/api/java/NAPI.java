package org.onyxplatform.api.java;

import clojure.java.api.Clojure;
import clojure.lang.IFn;
import org.onyxplatform.api.java.API;

public class NAPI extends API implements NativeNames  {

    static {
        IFn require = Clojure.var(CORE, Require);

        require.invoke(Clojure.read(NATIVE_CATALOG));
        require.invoke(Clojure.read(NATIVE_LIFECYCLES));

    }
}

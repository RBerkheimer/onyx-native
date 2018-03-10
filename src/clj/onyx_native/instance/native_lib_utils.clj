(ns onyx-native.instance.native-lib-utils
  (:gen-class))


(defn load-lib [instance lib-name]
    (.loadNativeResources instance lib-name))

(defn get-loaded-libs []
  (-> (doto (.getDeclaredField ClassLoader "loadedLibraryNames")
      (.setAccessible true))
      (.get (ClassLoader/getSystemClassLoader))))

(defn check-substr [substr str]
    (if (clojure.string/includes? str substr)
        true
        false))

(defn categorize-os [os-name]
    (cond
        (clojure.string/includes? os-name "win") "win"
        (clojure.string/includes? os-name "mac") "osx"
        (clojure.string/includes? os-name "nix") "unix"
        (clojure.string/includes? os-name "nux") "unix"
        (clojure.string/includes? os-name "aix") "unix"
        (clojure.string/includes? os-name "sunos") "solaris"
        :else "unix"))

(defn get-os []
    (let [os-name (.toLowerCase (System/getProperty "os.name"))]
        (categorize-os os-name)))

(defn get-lib-name [native-lib]
    (let [os (get-os)]
        (case os
            "win" nil
            "osx" (clojure.string/join ["lib" native-lib ".jnilib"])
            "unix" (clojure.string/join ["lib" native-lib ".so"])
            "solaris" (clojure.string/join ["lib" native-lib ".so"])
            "nil")))

(defn is-lib-loaded [native-lib]
  (let [loaded-libs (get-loaded-libs)
        check-lib (get-lib-name native-lib)]
          (check-substr check-lib loaded-libs)))

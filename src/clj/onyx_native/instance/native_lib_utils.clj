(ns onyx-native.instance.native-lib-utils
  (:gen-class))


(defn load-lib [lib-name]
    (System/loadLibrary lib-name))


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
        (.indexOf os-name "win") "win"
        (.indexOf os-name "mac") "osx"
        (.indexOf os-name "nix") "unix"
        (.indexOf os-name "nux") "unix"
        (.indexOf os-name "aix") "unix"
        (.indexOf os-name "sunos") "solaris"
        :else "unix"))

(defn get-os []
    (let [os-name (.toLowerCase (System/getProperty "os.name"))]
        (categorize-os os-name)))


(defn get-lib-name [native-lib]
    (let [os (get-os)]
        (println "os: " os)
        (case
            "win" nil
            "osx" (clojure.string/join ["lib" native-lib ".jnilib"])
            "unix" (clojure.string/join ["lib" native-lib ".so"])
            "solaris" (clojure.string/join ["lib" native-lib ".so"])
            nil)))

(defn is-lib-loaded [native-lib]
  (let [loaded-libs (get-loaded-libs)
        check-lib (get-lib-name native-lib)]
          (println "check lib: " check-lib)
          (check-substr check-lib loaded-libs)))

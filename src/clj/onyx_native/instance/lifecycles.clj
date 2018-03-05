(ns onyx-native.instance.lifecycles
  (:gen-class)
  (:require [onyx-java.instance.lifecycles :as jlcs]
            [onyx-native.instance.native-lib-utils :as native-lib]))


(defn before-native-task-ctr [event lifecycle]
    (let [user-class (str (:java-instance/class (:onyx.core/task-map event)))
          user-ctr (str (:java-instance/ctr (:onyx.core/task-map event)))
          ctr-args (:java-instance/args (:onyx.core/task-map event))
          class-factory (jlcs/make-user-factory user-class user-ctr)
          instance (class-factory ctr-args)
          instance-key (jlcs/keyname (:java-instance/id (:onyx.core/task-map event)))
          native-lib (str (:native/lib-name (:onyx.core/task-map event)))
          native-args (:native/init-args (:onyx.core/task-map event))]
            (.loadNativeResources instance native-lib native-args)
            (swap! jlcs/instances assoc instance-key instance)
            {}))

(defn before-native-task-basic [event lifecycle]
    (let [user-class (str (:java-instance/class (:onyx.core/task-map event)))
          ctr-args (:java-instance/args (:onyx.core/task-map event))
          class-factory (jlcs/make-basic-factory user-class)
          instance (class-factory ctr-args)
          instance-key (jlcs/keyname (:java-instance/id (:onyx.core/task-map event)))
          native-lib (str (:native/lib-name (:onyx.core/task-map event)))
          native-args (:native/init-args (:onyx.core/task-map event))]
            (print "loading native resources for: ")
            (println user-class)
            (println (native-lib/get-loaded-libs))
            (if-not (native-lib/is-lib-loaded native-lib)
                (native-lib/load-lib )
                (println "native library already loaded."))
            (print "loaded basic native resources for: ")
            (println user-class)
            (println (get-libs))
            (print "holding reference to: ")
            (println user-class)
            (swap! jlcs/instances assoc instance-key instance)
            (print "held reference to: ")
            (println user-class)
            {}))

(defn after-native-task [event lifecycle]
    (let [instance-key (jlcs/keyname (:java-instance/id (:onyx.core/task-map event)))
          instance (get @jlcs/instances instance-key)
          user-class (str (:java-instance/class (:onyx.core/task-map event)))]
          (swap! jlcs/instances dissoc instance-key)
          (print "removed held reference to: ")
          (println user-class)
          {}))
(def ctr-instance-calls
    {:lifecycle/before-task-start before-native-task-ctr
    :lifecycle/after-task-stop after-native-task})

(def basic-instance-calls
    {:lifecycle/before-task-start before-native-task-basic
    :lifecycle/after-task-stop after-native-task})

(defn make-instance-lifecycle [task-name task-type]
    (if (= task-type "basic")
    {:lifecycle/task (keyword task-name)
     :lifecycle/calls :onyx-native.instance.lifecycles/basic-instance-calls}
    {:lifecycle/task (keyword task-name)
     :lifecycle/calls :onyx-native.instance.lifecycles/ctr-instance-calls}))

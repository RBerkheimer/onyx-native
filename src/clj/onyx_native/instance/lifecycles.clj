(ns onyx-native.instance.lifecycles
  (:gen-class)
  (:import [org.onyxplatform.api.java.instance BindUtils Loader])
  (:require [onyx-java.instance.lifecycles :as jlcs]))


(defn before-native-task-ctr [event lifecycle]
    (let [classloader (Loader.)
          task-inst (BindUtils/loadFn classloader
                    (str (:java-instance/class (:onyx.core/task-map event)))
                    (str (:java-instance/ctr (:onyx.core/task-map event)))
                    (:java-instance/args (:onyx.core/task-map event)))
          k (jlcs/keyname (:java-instance/id (:onyx.core/task-map event)))
          native-lib (:native/lib-name (:onyx.core/task-map event))
          native-args (:native/init-args (:onyx.core/task-map event))]
            (swap! jlcs/classloaders assoc (jlcs/keyname (:java-instance/id (:onyx.core/task-map event))) classloader)
            (swap! jlcs/instances assoc (jlcs/keyname (:java-instance/id (:onyx.core/task-map event))) task-inst)
            (.loadNativeResources (get @jlcs/instances k) native-lib native-args)
            {}))

(defn before-native-task-basic [event lifecycle]
    (let [classloader (Loader.)
          task-inst (BindUtils/loadFn classloader
                    (str (:java-instance/class (:onyx.core/task-map event)))
                    (:java-instance/args (:onyx.core/task-map event)))
          k (jlcs/keyname (:java-instance/id (:onyx.core/task-map event)))
          native-lib (:native/lib-name (:onyx.core/task-map event))
          native-args (:native/init-args (:onyx.core/task-map event))]
            (swap! jlcs/classloaders assoc (jlcs/keyname (:java-instance/id (:onyx.core/task-map event))) classloader)
            (swap! jlcs/instances assoc (jlcs/keyname (:java-instance/id (:onyx.core/task-map event))) task-inst)
            (.loadNativeResources (get @jlcs/instances k) native-lib native-args)
            {}))

(defn after-native-task [event lifecycle]
    (if (contains? @jlcs/instances (jlcs/keyname (:java-instance/id (:onyx.core/task-map event))))
      (let [k (jlcs/keyname (:java-instance/id (:onyx.core/task-map event)))]
        (println "releasing native!")
        (println jlcs/classloaders)
        (println jlcs/instances)
        (.releaseNativeResources (get @jlcs/instances k))
        (swap! jlcs/classloaders dissoc k)
        (swap! jlcs/instances dissoc k)
        (println jlcs/classloaders)
        (println jlcs/instances)
        (println "returning!")
        {})))


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

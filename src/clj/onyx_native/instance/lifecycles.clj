(ns onyx-native.instance.lifecycles
  (:gen-class)
  (:import [org.onyxplatform.api.java.instance BindUtils NativeBindUtils Loader])
  (:require [onyx-java.instance.lifecycles :as jlcs]
            [onyx-java.instance.bind :as jbind]))

 (defn add-instance [id fq-class-name ctr-name ctr-args]
     (let [loader (Loader.)
            i (BindUtils/loadFn loader fq-class-name ctr-name ctr-args)]
            (swap! jlcs/classloaders assoc id loader)
            (swap! jlcs/instances assoc id i)
            i))

(defn before-native-task-ctr [event lifecycle]
    (let [k (jlcs/keyname (:java-instance/id (:onyx.core/task-map event)))
            i (add-instance k
                        (str (:java-instance/class (:onyx.core/task-map event)))
                        (str (:java-instance/ctr (:onyx.core/task-map event)))
                        (:java-instance/args (:onyx.core/task-map event)))]
            (println "Loading native task!")
            (.testme i)
            ;(.loadNativeResources i (str (:native/lib-name (:onyx.core/task-map event))) (:native/init-args (:onyx.core/task-map event)))
            (println i)
            (println (str (:native/lib-name (:onyx.core/task-map event))))
            (println (:native/init-args (:onyx.core/task-map event)))
            (println "loaded native resources!")
            {}))

(defn before-native-task-basic [event lifecycle]
    (let [classloader (Loader.)
          task-inst (BindUtils/loadFn classloader
                    (str (:java-instance/class (:onyx.core/task-map event)))
                    (:java-instance/args (:onyx.core/task-map event)))]
            (.loadNativeResources task-inst (str (:native/lib-name (:onyx.core/task-map event))) (:native/init-args (:onyx.core/task-map event)))
            (swap! jlcs/classloaders assoc (jlcs/keyname (:java-instance/id (:onyx.core/task-map event))) classloader)
            (swap! jlcs/instances assoc (jlcs/keyname (:java-instance/id (:onyx.core/task-map event))) task-inst))
            {})

(defn after-native-task [event lifecycle]
    (if (contains? @jlcs/instances (jlcs/keyname (:java-instance/id (:onyx.core/task-map event))))
      (let [k (jlcs/keyname (:java-instance/id (:onyx.core/task-map event)))]
      (println "releasing native resources!")
        (.releaseNativeResources (get @jlcs/instances k))
        (swap! jlcs/classloaders dissoc k)
        (swap! jlcs/instances dissoc k)))
        (println "Released native resources!")
        {})

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

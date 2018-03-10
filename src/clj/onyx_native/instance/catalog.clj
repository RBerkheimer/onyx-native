(ns onyx-native.instance.catalog
  (:gen-class)
  (:require [onyx-java.instance.catalog :as cat]))

(defn make-native-instance-task
    ([taskname batchsize batchtimeout fqclassname ctrargs libname]
        (let [entry (cat/make-instance-task taskname batchsize batchtimeout fqclassname ctrargs)
              native-entry (-> entry
                            (assoc :native/lib-name libname))]
                native-entry))
    ([taskname batchsize batchtimeout fqclassname ctrclass ctrargs libname]
        (let [entry (cat/make-instance-task taskname batchsize batchtimeout fqclassname ctrclass ctrargs)
              native-entry (-> entry
                            (assoc :native/lib-name libname))]
                native-entry)))

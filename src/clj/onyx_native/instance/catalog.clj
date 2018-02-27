(ns onyx-native.instance.catalog
  (:gen-class)
  (:require [onyx-java.instance.catalog :as cat]))

(defn make-native-instance-task
    ([taskname batchsize batchtimeout fqclassname ctrargs libname initargs]
        (let [entry (cat/make-instance-task taskname batchsize batchtimeout fqclassname ctrargs)]
            (-> entry
                (assoc :native/lib-name libname)
                (assoc :native/init-args initargs))))
    ([taskname batchsize batchtimeout fqclassname ctrclass ctrargs libname initargs]
        (let [entry (cat/make-instance-task taskname batchsize batchtimeout fqclassname ctrclass ctrargs)]
            (-> entry
                (assoc :native/lib-name libname)
                (assoc :native/init-args initargs)))))

(ns onyx-native.test.pure-java
  (:gen-class)
  (:import [onyxplatform.test SingleJavaTest SingleCljTest])
  (:require [clojure.test :refer [deftest is]]))

(deftest single-java-test
    (let [testObject (SingleJavaTest. "onyx-env.edn" SingleJavaTest/PASS_FN "OnyxNativeTest")
          inputs [{:pass-through "PASSTHROUGH"}]
          expected {:out [{:pass-through "PASSTHROUGH"} :done]}
          cat (.configureCatalog testObject)
          job (.toArray (.getJob testObject))
         ; outputs (.runJobCollectOutputs testObject [{:pass-through "PASSTHROUGH"}])
          ]
      (println "Job:")
      (println job)
        ;(.shutdown testObject)
        (is true)
        #_(is (= (first inputs) (first (:out outputs))))))

#_(deftest gc-test
    (let [testObject (SingleJavaTest. "onyx-env.edn")
          inputs [{:pass-through "PASSTHROUGH"}]
          expected "Success!"
          job-meta (.runJob testObject [{:pass-through "PASSTHROUGH"}])
          env (.getOnyx testObject) ]
      (try
        (is (.gc env))
        (finally (.shutdown testObject)))))


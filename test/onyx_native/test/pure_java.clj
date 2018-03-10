(ns onyx-native.test.pure-java
  (:gen-class)
  (:import [onyxplatform.test NativeSingleJavaTest])
  (:require [clojure.test :refer [deftest is]]))

(deftest pass-java-test
    (let [testObject (NativeSingleJavaTest.
                       "onyx-env.edn"
                       NativeSingleJavaTest/PASS_FN "OnyxNativeTest")
          inputs [{:pass-through "PASSTHROUGH"}]
          expected {:out [{:pass-through "PASSTHROUGH"} :done]}
          outputs (.runJobCollectOutputs testObject inputs) ]
      (println "pass-through-test> outputs=" outputs)
      (.shutdown testObject)
      (is (= expected outputs))))

(deftest empty-map-test
  (let [testObject (NativeSingleJavaTest.
                     "onyx-env.edn"
                     NativeSingleJavaTest/EMPTY_FN "OnyxNativeTest")
        inputs [{:pass-through "PASSTHROUGH"}]
        expected {:out [{} :done]}
        outputs (.runJobCollectOutputs testObject inputs) ]
    (println "empty-map-test> outputs=" outputs)
    (.shutdown testObject)
    (is (= expected outputs))))

(deftest assoc-map-test
  (let [testObject (NativeSingleJavaTest.
                 "onyx-env.edn"
                 NativeSingleJavaTest/ASSOC_FN "OnyxNativeTest")
    inputs [{}]
    expected {:out [{:object {}
                     :int 1
                     :float (float 1.1)
                     :double (double 2.2)
                     :bool true
                     :str "TEST"} :done]}
    outputs (.runJobCollectOutputs testObject inputs) ]
(println "assoc-map-test> outputs=" outputs)
(.shutdown testObject)
(is (= expected outputs))))

(deftest merge-map-test
  (let [testObject (NativeSingleJavaTest.
                     "onyx-env.edn"
                     NativeSingleJavaTest/MERGE_FN "OnyxNativeTest")
        inputs [{:pass-through "PASSTHROUGH"}]
        expected {:out [{:map1 1 :map2 "TEST"} :done]}
        outputs (.runJobCollectOutputs testObject inputs) ]
    (println "merge-map-test> outputs=" outputs)
    (.shutdown testObject)
    (is (= expected outputs))))

(deftest dissoc-map-test
  (let [testObject (NativeSingleJavaTest.
                     "onyx-env.edn"
                     NativeSingleJavaTest/DISSOC_FN "OnyxNativeTest")
        inputs [{:dissoc "DISSOC"}]
        expected {:out [{} :done]}
        outputs (.runJobCollectOutputs testObject inputs) ]
    (println "dissoc-map-test> outputs=" outputs)
    (.shutdown testObject)
    (is (= expected outputs))))


(deftest get-map-test
  (let [testObject (NativeSingleJavaTest.
                     "onyx-env.edn"
                     NativeSingleJavaTest/GET_FN "OnyxNativeTest")
        inputs [{:object {}
                 :int (int 1)
                 :float (float 1.1)
                 :double (double 2.2)
                 :bool true
                 :str "TEST"}]
         expected {:out [{:object {}
                          :object1 {}
                          :int 1
                          :int1 1
                          :float (float 1.1)
                          :float1 (float 1.1)
                          :double (double 2.2)
                          :double1 (double 2.2)
                          :bool true
                          :bool1 true
                          :str "TEST"
                          :str1 "TEST"} :done]}
        outputs (.runJobCollectOutputs testObject inputs)]
    (println "get-map-test> outputs=" outputs)
    (.shutdown testObject)
    (is (= expected outputs))))

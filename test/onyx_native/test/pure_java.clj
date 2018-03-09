(ns onyx-native.test.pure-java
  (:gen-class)
  (:import [onyxplatform.test NativeSingleJavaTest])
  (:require [clojure.test :refer [deftest is]]))

(comment (deftest get-map-test
  (let [testObject (NativeSingleJavaTest.
                     "onyx-env.edn"
                     NativeSingleJavaTest/GET_FN "OnyxNativeTest")
        inputs [{:object {}
                 :int (int 1)
                 :float (float 1.1)
                 :double (double 2.0)
                 :long (long 3.3)
                 :bool true
                 :str "TEST"}]
        expected {:out [{:passed true} :done]}
        outputs (.runJobCollectOutputs testObject inputs)]
    (println "get-map-test> outputs=" outputs)
    (.shutdown testObject)
    (is (= expected outputs)))))

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

(deftest assoc-map-test-2
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
(println "assoc-map-test2> outputs=" outputs)
(.shutdown testObject)
(is (= expected outputs))))


(comment (deftest pass-java-test
    (let [testObject (NativeSingleJavaTest.
                       "onyx-env.edn"
                       NativeSingleJavaTest/PASS_FN "OnyxNativeTest")
          inputs [{:pass-through "PASSTHROUGH"}]
          expected {:out [{:pass-through "PASSTHROUGH"} :done]}
          outputs (.runJobCollectOutputs testObject inputs) ]
      (.shutdown testObject)
      (is (= expected outputs))))

(deftest empty-map-test
  (let [testObject (NativeSingleJavaTest.
                     "onyx-env.edn"
                     NativeSingleJavaTest/EMPTY_FN "OnyxNativeTest")
        inputs [{:pass-through "PASSTHROUGH"}]
        expected {:out [{} :done]}
        outputs (.runJobCollectOutputs testObject inputs) ]
    (.shutdown testObject)
    (is (= expected outputs))))

(deftest merge-map-test
  (let [testObject (NativeSingleJavaTest.
                     "onyx-env.edn"
                     NativeSingleJavaTest/MERGE_FN "OnyxNativeTest")
        inputs [{:pass-through "PASSTHROUGH"}]
        expected {:out [{:pass-through "PASSTHROUGH" :test "A"} :done]}
        outputs (.runJobCollectOutputs testObject inputs) ]
    (.shutdown testObject)
    (is (= expected outputs))))

(deftest dissoc-map-test
  (let [testObject (NativeSingleJavaTest.
                     "onyx-env.edn"
                     NativeSingleJavaTest/DISSOC_FN "OnyxNativeTest")
        inputs [{:dissoc "DISSOC"}]
        expected {:out [{} :done]}
        outputs (.runJobCollectOutputs testObject inputs) ]
    (.shutdown testObject)
    (is (= expected outputs)))))

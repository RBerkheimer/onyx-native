(ns onyx-native.main
  (:gen-class)
  (:require [onyx-native.instance.catalog :as ic]
            [onyx-native.instance.lifecycles :as lcs]
            [onyx-java.instance.lifecycles :as jlcs]
            [onyx-native.instance.native-lib-utils as lib])
  (:import [org.onyxplatform.api.java
            API
            Catalog
            EnvConfiguration
            FlowCondition
            FlowConditions
            Job
            Lifecycle
            Lifecycles
            OnyxEnv
            OnyxMap
            OnyxNames
            OnyxVector
            TaskScheduler
            PeerConfiguration
            Task
            TaskScheduler
            Trigger
            Triggers
            Window
            Windows
            Workflow
            NativeOnyxEnv]
           [org.onyxplatform.api.java.utils
            AsyncCatalog
            AsyncLifecycles
            MapFns
            VectorFns]
           [org.onyxplatform.api.java.instance
            Loader
            BindUtils
            OnyxFn
            NativeBindUtils
            NativeOnyxFn ]))

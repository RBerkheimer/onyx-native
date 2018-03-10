struct OnyxNative
{
    OnyxNative(JNIEnv*);
    ~OnyxNative();

    JNIEnv* getEnv();

    void checkAndThrow(std::string);

    jobject emptyMap();
    jobject mergeMaps(jobject, jobject);
    jobject assocObj(jobject, const char*, jobject);
    jobject assocInt(jobject, const char*, int);
    jobject assocFloat(jobject, const char*, float);
    jobject assocDouble(jobject, const char*, double);
    jobject assocBool(jobject, const char*, bool d);
    jobject assocStr(jobject, const char*, const char*);

    jclass getClass(std::string);
    jmethodID getMethod(jclass, std::string, std::string, bool);
    jstring toJavaString(std::string);
    void init();
    jobject getObj(jobject, std::string);
    int getInt(jobject, std::string);
    long getLong(jobject, std::string);
    float getFloat(jobject, std::string);
    double getDouble(jobject, std::string);
    bool getBool(jobject, std::string);
    jstring getStr(jobject, std::string);
    jobject dissoc(jobject, std::string);
};

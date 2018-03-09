struct OnyxNative
{
    OnyxNative(JNIEnv*);
    ~OnyxNative();

    JNIEnv* getEnv();

    void checkAndThrow(std::string);

    jobject emptyMap();
    jobject mergeMaps(jobject, jobject);
    jobject assocObj(const char*, jobject, jobject);
    jobject assocInt(const char*, jobject, int);
    jobject assocFloat(const char*, jobject, float);
    jobject assocDouble(const char*, jobject, double);
    jobject assocBool(const char*, jobject, bool d);
    jobject assocStr(const char*, jobject, const char*);

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

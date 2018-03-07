struct OnyxNative
{
    OnyxNative(JNIEnv*, jobject);
    void checkAndThrow(std::string);
    JNIEnv* getEnv();
    jobject getInstance();
    jclass getClass(std::string);
    jmethodID getMethod(jclass, std::string, std::string, bool);
    jstring toJavaString(std::string);
    void init();
    jobject emptyMap();
    jobject merge(jobject, jobject);
    jobject getObj(jobject, std::string);
    int getInt(jobject, std::string);
    long getLong(jobject, std::string);
    float getFloat(jobject, std::string);
    double getDouble(jobject, std::string);
    bool getBool(jobject, std::string);
    jstring getStr(jobject, std::string);
    jobject assocObj(jobject, std::string, jobject);
    jobject assocInt(jobject, std::string, int);
    jobject assocLong(jobject, std::string, long);
    jobject assocFloat(jobject, std::string, float); //does not preserve precision
    jobject assocDouble(jobject, std::string, double);
    jobject assocBool(jobject, std::string, bool);
    jobject assocStr(jobject, std::string, std::string);
    jobject dissoc(jobject, std::string);
};

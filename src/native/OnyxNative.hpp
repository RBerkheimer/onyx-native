struct OnyxNative
{
    OnyxNative(JNIEnv*);
    ~OnyxNative();
    void init();

    JNIEnv* getEnv();
    jclass getClass(std::string);
    jmethodID getMethod(jclass, std::string, std::string, bool);
    jstring toJavaString(std::string);
    void checkAndThrow(std::string);

    jobject emptyMap();
    jobject mergeMaps(jobject, jobject);
    jobject dissoc(jobject, const char*);
    jobject assocObj(jobject, const char*, jobject);
    jobject assocInt(jobject, const char*, int);
    jobject assocFloat(jobject, const char*, float);
    jobject assocDouble(jobject, const char*, double);
    jobject assocBool(jobject, const char*, bool d);
    jobject assocStr(jobject, const char*, const char*);
    jobject getObj(jobject, const char*);
    int     getInt(jobject, const char*);
    long    getLong(jobject, const char*);
    float   getFloat(jobject, const char*);
    double  getDouble(jobject, const char*);
    bool    getBool(jobject, const char*);
    jstring getStr(jobject, const char*);
};

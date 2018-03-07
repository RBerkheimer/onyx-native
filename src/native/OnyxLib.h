struct OnyxNative;

#ifdef __cplusplus
extern "C" {
#endif

typedef OnyxNative * OnyxLib;
OnyxLib onyxlib_new(JNIEnv *, jobject);
void    onyxlib_free(OnyxLib);
void    onyxlib_errorcheck(OnyxLib, const char*);
JNIEnv* onyxlib_getenv(OnyxLib);
jobject onyxlib_getinstance(OnyxLib);
jclass onyxlib_getclass(OnyxLib, const char*);
jmethodID onyxlib_getmethod(OnyxLib, const char*, const char*, const char*, bool);
jstring onyxlib_tojavastring(OnyxLib, const char*);
jobject onyxlib_emptymap(OnyxLib);
jobject onyxlib_merge(OnyxLib, jobject, jobject);
jobject onyxlib_getobj(OnyxLib, jobject, const char*);
int onyxlib_getint(OnyxLib, jobject, const char*);
long onyxlib_getlong(OnyxLib,jobject, const char*);
float onyxlib_getfloat(OnyxLib, jobject, const char*);
double onyxlib_getdouble(OnyxLib, jobject, const char*);
bool onyxlib_getbool(OnyxLib, jobject, const char*);
jstring onyxlib_getstr(OnyxLib, jobject, const char*);
jobject onyxlib_assocobj(OnyxLib, jobject, const char*, jobject);
jobject onyxlib_assocint(OnyxLib, jobject, const char*, int);
jobject onyxlib_assoclong(OnyxLib, jobject, const char*, long);
jobject onyxlib_assocfloat(OnyxLib, jobject, const char*, float);
jobject onyxlib_assocdouble(OnyxLib, jobject, const char*, double);
jobject onyxlib_assocbool(OnyxLib, jobject, const char*, bool);
jobject onyxlib_assocstr(OnyxLib, jobject, const char*, const char*);
jobject onyxlib_dissoc(OnyxLib, const char*);

#ifdef __cplusplus
}
#endif

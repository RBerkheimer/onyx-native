struct OnyxNative;
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif
typedef struct OnyxNative * OnyxLib;
OnyxLib onyxlib_new(JNIEnv *);
void    onyxlib_free(OnyxLib);

jobject onyxlib_emptymap(OnyxLib);
jobject onyxlib_mergemaps(OnyxLib, jobject, jobject);
jobject onyxlib_assocobj(OnyxLib, const char*, jobject, jobject);
jobject onyxlib_assocint(OnyxLib, const char*, jobject, int);
jobject onyxlib_assocfloat(OnyxLib, const char*, jobject, float);
jobject onyxlib_assocdouble(OnyxLib, const char*, jobject, double);
jobject onyxlib_assocbool(OnyxLib, const char*, jobject, bool);
jobject onyxlib_assocstr(OnyxLib, const char*, jobject, const char*);

void    onyxlib_errorcheck(OnyxLib, const char*);
JNIEnv* onyxlib_getenv(OnyxLib);
jobject onyxlib_getinstance(OnyxLib);
jclass onyxlib_getclass(OnyxLib, const char*);
jmethodID onyxlib_getmethod(OnyxLib, const char*, const char*, const char*, bool);
jstring onyxlib_tojavastring(OnyxLib, const char*);
jobject onyxlib_getobj(OnyxLib, jobject, const char*);
int onyxlib_getint(OnyxLib, jobject, const char*);
long onyxlib_getlong(OnyxLib,jobject, const char*);
float onyxlib_getfloat(OnyxLib, jobject, const char*);
double onyxlib_getdouble(OnyxLib, jobject, const char*);
bool onyxlib_getbool(OnyxLib, jobject, const char*);
jstring onyxlib_getstr(OnyxLib, jobject, const char*);
jobject onyxlib_dissoc(OnyxLib, jobject, const char*);

#ifdef __cplusplus
}
#endif

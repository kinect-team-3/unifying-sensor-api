#include "UnifyingAPI.h"
#include "unifying_functions.h"
#include <jni.h>

/*
 * Class:     UnifyingAPI
 * Method:    convert_raw_to_unified
 * Signature: (Ljava/lang/String;IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_UnifyingAPI_convert_1raw_1to_1unified
  (JNIEnv *env, jobject obj, jstring data, jint offset, jint size, jstring type, jstring desc, jstring sensor)
  
{
	const char* cdata, ctype, cdesc, csensor;
	size_t coffset, csize;
}

/*
 * Class:     UnifyingAPI
 * Method:    convert_unified_to_raw
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_UnifyingAPI_convert_1unified_1to_1raw
  (JNIEnv *env, jobject obj, jstring data)

{
	const char* cdata = (*env)->GetStringUTFChars(env, data, NULL);
	
	uint8_t* result = convert_unified_to_raw(cdata);
	
	(*env)->ReleaseStringUTFChars(env, data, cdata);
	
	return (*env)->NewStringUTF(env, (char*) result);
}

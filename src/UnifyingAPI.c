#include "UnifyingAPI.h"
#include "unifying_functions.h"
#include <jni.h>

/*
 * Class:     UnifyingAPI
 * Method:    convert_raw_to_unified
 * Signature: (Ljava/lang/String;IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_UnifyingAPI_convert_1raw_1to_1unified
  (JNIEnv *, jobject, jstring, jint, jint, jstring, jstring, jstring)
  
{
}

/*
 * Class:     UnifyingAPI
 * Method:    convert_unified_to_raw
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_UnifyingAPI_convert_1unified_1to_1raw
  (JNIEnv *, jobject, jstring)


{
}

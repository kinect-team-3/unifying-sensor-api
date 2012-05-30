#include "UnifyingAPI.h"
#include "unifying_functions.h"
#include <jni.h>

/*
 * Class:     UnifyingAPI
 * Method:    convert_raw_to_unified
 * Signature: (Ljava/lang/String;IILjava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_UnifyingAPI_convert_1raw_1to_1unified
  (JNIEnv *env, jclass cla, jbyteArray data, jint offset, jint size, jstring type, jstring desc, jstring sensor)
  
{
	size_t coffset, csize;
	
	// Convert from Java data types to C types
	jbyte* b;
	jboolean isCopy;
	//int length = (*env)->GetArrayLength(env, data);
	//(*env)->GetByteArrayRegion(env, data, 0, length, b);
	b = (*env)->GetByteArrayElements(env, data, &isCopy);
	const char* cdata = b;
	
	const char* ctype = (*env)->GetStringUTFChars(env, type, NULL);
	const char* cdesc = (*env)->GetStringUTFChars(env, desc, NULL);
	const char* csensor = (*env)->GetStringUTFChars(env, sensor, NULL);
	
	coffset = offset;
	csize = size;
	
	// Run native C function
	char* result = convert_raw_to_unified(cdata, coffset, csize,
	ctype, cdesc, csensor);
	
	// Release the strings
	(*env)->ReleaseStringUTFChars(env, type, ctype);
	(*env)->ReleaseStringUTFChars(env, desc, cdesc);
	(*env)->ReleaseStringUTFChars(env, sensor, csensor);
	(*env)->ReleaseByteArrayElements(env, data, b, JNI_ABORT);
	
	// Create a new jstring from char*, return
	return (*env)->NewStringUTF(env, result);
}

/*
 * Class:     UnifyingAPI
 * Method:    convert_unified_to_raw
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jbyteArray JNICALL Java_UnifyingAPI_convert_1unified_1to_1raw
  (JNIEnv *env, jclass cla, jstring jsondata)

{
	// jstring -> char*
	const char* cdata = (*env)->GetStringUTFChars(env, jsondata, NULL);
	
	//printf("%s", cdata);
	
	// get size
	size_t* result_size;
	
	// native C call
	uint8_t* result = convert_unified_to_raw(cdata, result_size);
	
	// Release jstring, no longer needed
	(*env)->ReleaseStringUTFChars(env, jsondata, cdata);
	
	//create new jbytearray
	jbyteArray jb;
	jb = (*env)->NewByteArray(env, *result_size);
	
	(*env)->SetByteArrayRegion(env, jb, 0, *result_size, (jbyte *) result);
		
	// return a new jb from result
	return jb;
}

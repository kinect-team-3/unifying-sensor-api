#include "UnifyingAPI.h"
#include "unifying_functions.h"
#include <jni.h>


// ******************************
// Setup Code for process_unified
// ---------START----------------

char* process_unified (const char* jsondata, int(*process)(uint8_t *, size_t *));

JNIEnv *globalJavaEnv;
jclass globalJavaClass;
jmethodID globalMid;


/* This is the interface to the Java function */
int processFunc(uint8_t* bytestream, size_t* size)
{
	size_t i;
	// convert bytestream to jbyteArray
	// create new jbytearray
	jbyteArray jb;
	jb = (*globalJavaEnv)->NewByteArray(globalJavaEnv, *size);

	(*globalJavaEnv)->SetByteArrayRegion(globalJavaEnv, jb, 0, *size, (jbyte *) bytestream);
	/* Here's where we call back to the user's function in the Java code */
	jbyteArray res = (jbyteArray) (*globalJavaEnv)->CallObjectMethod(globalJavaEnv, globalJavaClass, globalMid, (jbyteArray) jb);
	
	*size = (*globalJavaEnv)->GetArrayLength(globalJavaEnv, res);
	
	jboolean isCopy;
	jbyte* b = (*globalJavaEnv)->GetByteArrayElements(globalJavaEnv, res, &isCopy);
	
	for (i = 0; i < *size; i++)
		bytestream[i] = b[i];
	
	
	return 0;
}

// ----------END------------------
// *******************************

/*
 * Class:     UnifyingAPI
 * Method:    process_unified_native
 * Signature: (Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_UnifyingAPI_process_1unified_1native
  (JNIEnv *env, jclass jcl, jstring funcName, jstring jsondata)
{
	int fail;
	const char* cjsondata;
	const char* functionName;
	jstring jresultJSON;
	jclass cls;
	jfieldID fid;

	/* Copy the Java env pointers to global space
	 so that processFunc can access them. */
	globalJavaEnv = env;
	globalJavaClass = jcl;
	
	/* Get hold of the name of the user's Java evaluation function. */
	functionName = (*env)->GetStringUTFChars(env, funcName, NULL);
	/* Get JSON data into jString */
	cjsondata = (*env)->GetStringUTFChars(env, jsondata, NULL);
	
	/* Now we have the Java evaluation function name we
     can use it to get hold of a handle (method ID) to the function.
     Once more, the method ID is stored globally so that processFunc
     can use it. Note that the Java function signature must be
     "([B)[B" (i.e. function with bytearray argument, returning bytearray). */
	//cls = (*env)->GetObjectClass(env, jcl);
	globalMid = (*env)->GetStaticMethodID(env, jcl, functionName, "([B)[B");
	
	// Release Strings
	(*env)->ReleaseStringUTFChars(env, funcName, functionName);
	
	if (globalMid == 0)
	{
		/* Cannot find method "functionName" with signature ([B)[B */
		
		// Release Strings
		(*env)->ReleaseStringUTFChars(env, jsondata, cjsondata);
		
		return -1;
	}
	else
	{
		/* Now call the function we're interested in from the unifying_functions.c C Library. */
		char* cresultJSON;
		cresultJSON = process_unified(cjsondata, processFunc);
		
		// Convert char* back to jString
		jresultJSON = (*env)->NewStringUTF(env, cresultJSON);

		/* Put the results back to Java. */
		/* Get the ID of the Java UnifyingAPI class member variable
		 "result" (which is of type String, hence the "Ljava/lang/String;" signature). */
		fid = (*env)->GetStaticFieldID(env, jcl, "result", "Ljava/lang/String;");
		/* Set the result value via the ID */
		(*env)->SetStaticObjectField(env, jcl, fid, jresultJSON);
		
		(*env)->ReleaseStringUTFChars(env, jresultJSON, cresultJSON);
	}
	
	// Release Strings
	(*env)->ReleaseStringUTFChars(env, jsondata, cjsondata);
	
	
	return 0;
}



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
	const uint8_t* cdata = b;
	
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

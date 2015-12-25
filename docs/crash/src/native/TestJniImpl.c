#include <jni.h>
#include "TestJniImpl.h"
#include <stdio.h>

JNIEXPORT void JNICALL
Java_TestClass_printHello(JNIEnv *env, jobject obj)
{

  int test = 0;
  test = 1/test;

  printf("Hello JNI World\n");
  return;
}

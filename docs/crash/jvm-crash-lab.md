# What's this

This lab will demonstrates:

* how native libraries cause JVM crash
* how use gcc compile c code in Linux X86_64 machine
* how to use java code call method in c library.

# Prerequisite

Get Source Code from Github

~~~
$ git clone git@github.com:kylinsoong/troubleshooting.git
$ cd troubleshooting/docs/crash/src/
$ tree
.
├── HelloJNI.java
├── native
│   ├── HelloJNI.c
│   ├── HelloJNI.h
│   ├── TestJniImpl.c
│   └── TestJniImpl.h
└── TestClass.java
~~~

Compile c code and use Java code call method in c library, use [HelloJNI.java](src/HelloJNI.java) and [HelloJNI.c](src/native/HelloJNI.c) as example:

~~~
$ cd native/
$ gcc -I"/usr/java/jdk1.8.0_25/include" -I"/usr/java/jdk1.8.0_25/include/linux" -fPIC -shared -o libhello.so HelloJNI.c
$ cd ..
$ javac HelloJNI.java
$ java -Djava.library.path=./native HelloJNI
Hello World JNI!
~~~

> NOTE: jdk installation path is /usr/java/jdk1.8.0_25, gcc compile [HelloJNI.c](src/native/HelloJNI.c) generate native library `libhello.so`, javac compile [HelloJNI.java](src/HelloJNI.java) generate `HelloJNI.class`. 


# Native library cause JVM crash example

[TestJniImpl.c](src/native/TestJniImpl.c) has the following code

~~~
Java_TestClass_printHello(JNIEnv *env, jobject obj)
{

  int test = 0;
  test = 1/test;
  return;
}
~~~

run above code will throw a exception in runtime, [TestClass.java](src/TestClass.java) will call `printHello()` method, which will cause JVM crash due to c code's exception. Use the following steps to reproduce native library cause JVM crash.

* Compile TestJniImpl.c

~~~
$ cd native/
$ gcc -I"/usr/java/jdk1.8.0_25/include" -I"/usr/java/jdk1.8.0_25/include/linux" -fPIC -shared -o libTestJniImpl.so TestJniImpl.c
~~~

`libTestJniImpl.so` will be generated once compile success.

* Compile TestClass.java

~~~
$ javac TestClass.java
~~~

* Run TestClass reproduce native library cause JVM Crash

~~~
$ java -Djava.library.path=./native TestClass
#
# A fatal error has been detected by the Java Runtime Environment:
#
#  SIGFPE (0x8) at pc=0x00007f255b2f36f5, pid=11816, tid=139798874932992
#
# JRE version: Java(TM) SE Runtime Environment (8.0_25-b17) (build 1.8.0_25-b17)
# Java VM: Java HotSpot(TM) 64-Bit Server VM (25.25-b02 mixed mode linux-amd64 compressed oops)
# Problematic frame:
# C  [libTestJniImpl.so+0x6f5]  Java_TestClass_printHello+0x1d
#
# Failed to write core dump. Core dumps have been disabled. To enable core dumping, try "ulimit -c unlimited" before starting Java again
#
# An error report file with more information is saved as:
# /home/kylin/src/troubleshooting/docs/crash/src/hs_err_pid11816.log
#
# If you would like to submit a bug report, please visit:
#   http://bugreport.sun.com/bugreport/crash.jsp
# The crash happened outside the Java Virtual Machine in native code.
# See problematic frame for where to report the bug.
#
Aborted (core dumped)
~~~

Note that, a crash log [hs_err_pid11816.log](samples/hs_err_pid005) generate under the same folder of TestClass. 


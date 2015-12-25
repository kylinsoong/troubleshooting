# What

JVM process crashes suddenly, a JVM hs_err_pidXXXX.log genereated.

# Why

Native libraries called via JNI(Java Native Interface)

* Type 2 JDBC driver
* User Application

JVM Issue

# How

* Analyze the JVM Log
* Analyze the Core File

# Labs

* [Lab - Native library cause JVM Crash](jvm-crash-lab.md)


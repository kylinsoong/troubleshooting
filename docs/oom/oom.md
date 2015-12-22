# What

Output the **java.lang.OutOfMemory** from server log or stdout/err log.

# Why

Run out of Memory at:

* Java heap area
* Permanent area
* Native memory area

Memory leakage 

* Increasing usage of memory and running out of memory finally
* If leakage is seen in Java heap, suspect: Non closure of JDBC object, Cached object or Long life object

JVM's bug (e.g. GC's compaction is a mess)

# How

* Analyze the GC log
* Analyze the Java process memory
* Analyze details of the Java process memory

# Labs

# Exploring the JVM Architecture

HotSpot JVM mainly contain 3 components:

* Class Loader Subsystem
* Runtime Data Areas
* Execution Engine

HotSpot JVM 3 components showed in below image:

![HotSpot JVM Architecture](img/hotspotjvm-1.PNG)

The key components of the JVM that relate to performance are highlighted in the following image:

![HotSpot JVM key comments](img/hotspotjvm-2.PNG)

There are three components of the JVM that are focused on when tuning performance. The heap is where your object data is stored. This area is then managed by the garbage collector selected at startup. Most tuning options relate to sizing the heap and choosing the most appropriate garbage collector for your situation. The JIT compiler also has a big impact on performance but rarely requires tuning with the newer versions of the JVM.

> NOTE: HotSpot JVM JIT compilers generate dynamic optimizations. In other words, they make optimization decisions while the Java application is running and generate high-performing native machine instructions targeted for the underlying system architecture.

# What is Automatic Garbage Collection?

Automatic garbage collection is the process of looking at heap memory, identifying which objects are in use and which are not, and deleting the unused objects. An in use object, or a referenced object, means that some part of your program still maintains a pointer to that object. An unused object, or unreferenced object, is no longer referenced by any part of your program. So the memory used by an unreferenced object can be reclaimed.

In a programming language like C, allocating and deallocating memory is a manual process. In Java, process of deallocating memory is handled automatically by the garbage collector. The basic process can be described as following 3 steps

* Step 1: Marking - The first step in the process is called marking. This is where the garbage collector identifies which pieces of memory are in use and which are not.

![Marking](img/gc-1.PNG)

Referenced objects are shown in blue. Unreferenced objects are shown in gold. All objects are scanned in the marking phase to make this determination. This can be a very time consuming process if all objects in a system must be scanned.

* Step 2: Normal Deletion - Normal deletion removes unreferenced objects leaving referenced objects and pointers to free space.

![Normal Deletion](img/gc-2.PNG)

The memory allocator holds references to blocks of free space where new object can be allocated.

* Step 3: Deletion with Compacting - To further improve performance, in addition to deleting unreferenced objects, you can also compact the remaining referenced objects. By moving referenced object together, this makes new memory allocation much easier and faster.

![Deletion with Compacting](img/gc-3.PNG)

# Why Generational Garbage Collection?

As stated earlier, having to mark and compact all the objects in a JVM is inefficient. As more and more objects are allocated, the list of objects grows and grows leading to longer and longer garbage collection time. However, empirical analysis of applications has shown that most objects are short lived.

Here is an example of such data. The Y axis shows the number of bytes allocated and the X access shows the number of bytes allocated over time.

![Generational Garbage Collection](img/gc-4.gif)

As you can see, fewer and fewer objects remain allocated over time. In fact most objects have a very short life as shown by the higher values on the left side of the graph.

# OBJECTIVE

* What's the java thread deadlock
* Illustrating Thread in `waiting for monitor entry` status
* Troubleshooting java thread deadlock
* Analysing java thread dump while thread deadlock occurring

# PREREQUISITE

* Maven 3.0 or latter.
* Eclipse
* threadDump analysing tools

# Java Thread Deadlock

Processing stops because two or more threads wait for release of Lock simultaneously. As below diagram: 

![java thread deadlock](img/eap5-hang-3.png)

Thread 1 locked Resource A while Thread 2 locked Resource B, at the same time, Thread 1 try to lock Resource B, Thread 2 try to lock Resource A. As a consequence, Thread 1 waiting for releasing of Thread 2 lock, Thread 2 waiting for releasing of Thread 1 lock, this is Java Threads Deadlock.

# Lab

We have 2 thread, lab-threaddump-thread-1 and lab-threaddump-thread-2,

* lab-threaddump-thread-1's action: 

*locked the Resource A* `->` *prepare lock the Resource B* `->` *locking the Resource B* `->` *locked Resource B*

* lab-threaddump-thread-2's action: 

*locked the Resource B* `->` *prepare lock the Resource A* `->` *locking the Resource A* `->` *locked Resource A*

* lab source code: .../jvm/thread/deadlock

## I - Build and generate executable jar

~~~
mvn clean install
~~~

thread-deadlock.jar will be generated.

## II - Show lab-threaddump-thread-1's action

~~~
java -jar thread-deadlock.jar 1
~~~

will show lab-threaddump-thread-1's action as below:

~~~
  lab-threaddump-thread-1 locked Resource A

  lab-threaddump-thread-1 prepare to lock Resource B

  lab-threaddump-thread-1 locking Resource B

  lab-threaddump-thread-1 locked Resource B
~~~

## III - Show lab-threaddump-thread-2's action

~~~
java -jar thread-deadlock.jar 2
~~~

will show lab-threaddump-thread-2's actions as below:

~~~
  lab-threaddump-thread-2 locked Resource B

  lab-threaddump-thread-2 prepare to lock Resource A

  lab-threaddump-thread-2 locking Resource A

  lab-threaddump-thread-2 locked Resource A
~~~

## IV - Show Java Thread Deadlock

~~~
java -jar thread-deadlock.jar a
~~~

will output the following:

~~~
  lab-threaddump-thread-1 locked Resource A

  lab-threaddump-thread-2 locked Resource B

  lab-threaddump-thread-2 prepare to lock Resource A

  lab-threaddump-thread-1 prepare to lock Resource B

  lab-threaddump-thread-1 locking Resource B

  lab-threaddump-thread-2 locking Resource A
~~~

We can find: It's impossible for lab-threaddump-thread-1 to lock the Resource B, and it's also impossible for lab-threaddump-thread-2 to lock Resource A, that because deadlock happened.

## V - Generate thread dump

~~~
jstack -l <PID> > deadlock.out
~~~

will generate thread dump file `deadlock.out`


# ANALYSING

* Both lab-threaddump-thread-1 and lab-threaddump-thread-2 are in `waiting for monitor entry` status

~~~
"lab-threaddump-thread-2" prio=10 tid=0xb6aec000 nid=0x176c waiting for monitor entry [0x6e97d000]
   java.lang.Thread.State: BLOCKED (on object monitor)
        at com.kylin.lab.threaddump.deadlock.Resource.lockInternal(Resource.java:28)
        - waiting to lock <0x9e3efa18> (a com.kylin.lab.threaddump.deadlock.Resource)
        at com.kylin.lab.threaddump.deadlock.Resource.lock(Resource.java:23)
        - locked <0x9e3efa08> (a com.kylin.lab.threaddump.deadlock.Resource)
        at com.kylin.lab.threaddump.deadlock.ResourceThread.run(ResourceThread.java:28)
        at java.lang.Thread.run(Thread.java:662)

   Locked ownable synchronizers:
        - None

"lab-threaddump-thread-1" prio=10 tid=0xb6aeac00 nid=0x176b waiting for monitor entry [0x6eb5c000]
   java.lang.Thread.State: BLOCKED (on object monitor)
        at com.kylin.lab.threaddump.deadlock.Resource.lockInternal(Resource.java:28)
        - waiting to lock <0x9e3efa08> (a com.kylin.lab.threaddump.deadlock.Resource)
        at com.kylin.lab.threaddump.deadlock.Resource.lock(Resource.java:23)
        - locked <0x9e3efa18> (a com.kylin.lab.threaddump.deadlock.Resource)
        at com.kylin.lab.threaddump.deadlock.ResourceThread.run(ResourceThread.java:26)
        at java.lang.Thread.run(Thread.java:662)

   Locked ownable synchronizers:
        - None
~~~

* Java-level deadlock be found

~~~
Found one Java-level deadlock:
=============================
"lab-threaddump-thread-2":
  waiting to lock monitor 0x6e802100 (object 0x9e3efa18, a com.kylin.lab.threaddump.deadlock.Resource),
  which is held by "lab-threaddump-thread-1"
"lab-threaddump-thread-1":
  waiting to lock monitor 0x6e8037a8 (object 0x9e3efa08, a com.kylin.lab.threaddump.deadlock.Resource),
  which is held by "lab-threaddump-thread-2"

Java stack information for the threads listed above:
===================================================
"lab-threaddump-thread-2":
        at com.kylin.lab.threaddump.deadlock.Resource.lockInternal(Resource.java:28)
        - waiting to lock <0x9e3efa18> (a com.kylin.lab.threaddump.deadlock.Resource)
        at com.kylin.lab.threaddump.deadlock.Resource.lock(Resource.java:23)
        - locked <0x9e3efa08> (a com.kylin.lab.threaddump.deadlock.Resource)
        at com.kylin.lab.threaddump.deadlock.ResourceThread.run(ResourceThread.java:28)
        at java.lang.Thread.run(Thread.java:662)
"lab-threaddump-thread-1":
        at com.kylin.lab.threaddump.deadlock.Resource.lockInternal(Resource.java:28)
        - waiting to lock <0x9e3efa08> (a com.kylin.lab.threaddump.deadlock.Resource)
        at com.kylin.lab.threaddump.deadlock.Resource.lock(Resource.java:23)
        - locked <0x9e3efa18> (a com.kylin.lab.threaddump.deadlock.Resource)
        at com.kylin.lab.threaddump.deadlock.ResourceThread.run(ResourceThread.java:26)
        at java.lang.Thread.run(Thread.java:662)

Found 1 deadlock.
~~~

* Full thread dump file view

[Deadlock thread dump file](deadlock.out)


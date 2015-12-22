* print java heap summary

~~~
jmap -heap <PID>
~~~

link:heap-summary-demo[Heap Summary Demo]

* generate heap dump(Linux 32)

~~~
jmap -dump:format=b,file=heap.hprof JAVA_PID
~~~

* generate heap dump(Linux 64)

~~~
jmap -J-d64 -dump:format=b,file=heap.hprof JAVA_PID
~~~

* generate heap dump(Windows)

~~~
jmap -dump:format=b,file=heap.hprof JAVA_PID
~~~


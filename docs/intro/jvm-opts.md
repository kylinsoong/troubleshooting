# Common Heap Related Switches

There are many different command line switches that can be used with Java. This section describes some of the more commonly used switches:

* *-Xms* - Sets the initial heap size for when the JVM starts
* *-Xmx* - Sets the maximum heap size
* *-Xmn* - Sets the size of the Young Generation
* *-XX:PermSize* - Sets the starting size of the Permanent Generation
* *-XX:MaxPermSize* - Sets the maximum size of the Permanent Generation

[Common Heap Related Switches Demo](../labs/lab-heap-usage.md)

# Enable GC log

~~~
-verbose:gc -Xloggc:gc.log
-verbose:gc -Xloggc:gc.log -XX:+PrintGCDetails
-verbose:gc -Xloggc:gc.log -XX:+PrintGCDetails -XX:+PrintGCDateStamps
~~~

## GC Log Example

~~~
2013-03-12T14:47:00.733+0800: 331.682: [Full GC [PSYoungGen: 2064K->0K(14656K)] [PSOldGen: 329172K->331173K(341376K)] 331236K->331173K(356032K) [PSPermGen: 1934K->1934K(16384K)], 0.0040140 secs] [Times: user=0.00 sys=0.00, real=0.01 secs]
~~~

* Full GC happened at 2013-03-12T14:47:00.733+0800, after JVM run 331.682 seconds
* Current heap size was changed by GC: 331236K->331173K
* Max heap size: 356032K
* Current permanent size was changed: 1934K->1934K
* Max permanent area size: 16384K
* Full GC took 0.0040140 secs

# Enable heap dump

~~~
-XX:+HeapDumpOnOutOfMemoryError
~~~

# Enable jconsole

* jconsole monitor j2se app(including JMX MBean monitor)

~~~
-Dcom.sun.management.jmxremote -Dcom.sun.management.jmxremote.port=9010 -Dcom.sun.management.jmxremote.local.only=false -Dcom.sun.management.jmxremote.authenticate=false -Dcom.sun.management.jmxremote.ssl=false
~~~

* jconsole monitor j2se app(Only monitor memory and threads)

~~~
-Dcom.sun.management.jmxremote
~~~


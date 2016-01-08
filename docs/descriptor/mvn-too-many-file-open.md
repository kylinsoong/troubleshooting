
# Too many open files - Maven assemble plugin

## Environment

* Linux Fedora 20

~~~
$ uname -a
Linux ksoong.xxx.com 3.11.10-301.fc20.x86_64 #1 SMP Thu Dec 5 14:01:17 UTC 2013 x86_64 x86_64 x86_64 GNU/Linux
~~~

* Java 1.8

~~~
$ java -version
java version "1.8.0_25"
Java(TM) SE Runtime Environment (build 1.8.0_25-b17)
Java HotSpot(TM) 64-Bit Server VM (build 25.25-b02, mixed mode)
~~~

* Maven 3.2.5

~~~
$ mvn --version
Apache Maven 3.2.5 (12a6b3acb947671f09b81f49094c53f426d8cea1; 2014-12-15T01:29:23+08:00)
Maven home: /home/kylin/tools/apache-maven-3.2.5
Java version: 1.8.0_25, vendor: Oracle Corporation
Java home: /usr/java/jdk1.8.0_25/jre
Default locale: en_US, platform encoding: UTF-8
OS name: "linux", version: "3.11.10-301.fc20.x86_64", arch: "amd64", family: "unix"
~~~

## Issue

Maven assemble plugin throw `Too many open files` Exception caused build failed

~~~
Caused by: org.codehaus.plexus.archiver.ArchiverException: Problem creating zip: ... (Too many open files)
	at org.codehaus.plexus.archiver.AbstractArchiver.createArchive(AbstractArchiver.java:1056)
	at org.apache.maven.plugin.assembly.archive.archiver.AssemblyProxyArchiver.createArchive(AssemblyProxyArchiver.java:437)
	at org.apache.maven.plugin.assembly.archive.DefaultAssemblyArchiver.createArchive(DefaultAssemblyArchiver.java:181)
~~~

## Resolution

Configuring /etc/security/limits.conf, add the following 2 lines

~~~
kylin soft    nofile           8192
kylin hard    nofile           8192
~~~

* kylin - the user name of mvn executed
* soft - for enforcing the soft limits
* hard - for enforcing hard limits
* nofile - max number of open files

Once configuration completed, exit and re-login for the change to take effect. To check the change take effect via ulimit command:

~~~
$ ulimit -n
8192
~~~


## Diagnostic Steps

* Check the max number of open files in current user, either `ulimit -a`, or `ulimit -n`

~~~
$ ulimit -a
core file size          (blocks, -c) 0
data seg size           (kbytes, -d) unlimited
scheduling priority             (-e) 0
file size               (blocks, -f) unlimited
pending signals                 (-i) 61431
max locked memory       (kbytes, -l) 64
max memory size         (kbytes, -m) unlimited
open files                      (-n) 1024
pipe size            (512 bytes, -p) 8
POSIX message queues     (bytes, -q) 819200
real-time priority              (-r) 0
stack size              (kbytes, -s) 8192
cpu time               (seconds, -t) unlimited
max user processes              (-u) 61431
virtual memory          (kbytes, -v) unlimited
file locks                      (-x) unlimited
~~~

~~~
$ ulimit -n
1024
~~~

* Change the max number of open files

* Verify the change take effect

~~~
$ ulimit -n
8192
~~~

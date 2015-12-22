If using OpenJDK or Sun JDK 1.6 or later, using jstack is an option. This is useful when redirecting standard out to a file is problematic for some reason (e.g. it is not desirable to restart the JVM just to redirect standard out). Execute the following, passing in the Java process ID:

~~~
jstack -l JAVA_PID > jstack.out
~~~

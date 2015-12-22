# What

Output the Too many open files from server log or stdout/err log

# Why

* The File Descriptor parameter is not suitable
* The file is not closed
* It remains, while socket connection has been in the state before TIME_WAIT

# How

* Find the files which are opened by the process
* Confirm resource limit on OS
* Confirm the socket state

Basic troubleshooting commands in Linux

~~~
ulimit -n
lsof -p <PID> | wc -l
lsof -p <PID>
~~~

# Labs

# What

* JBoss instance accepts no more new requests.
* Processing in-flight request becomes very slow or timed out.

# Why

Wrong design or implementation of customer's application / third party library or framework

* Infinite loop
* Too long SQL / WS out-band calls
* Thread deadlock

Wrong estimation of thread tuning 

* All available threads are busy and JBoss runs out of resources to execute new request
* Too long request processing
* Waiting for response from peer(e.g. RDBMS)
* Contention of resources
* Underestimation of peak load
* Too long JVM Full GC

Java VM or JBoss  bug

# How

* Get the Thread dump
* Get the GC log

# Labs

* [Java Threads Deadlock](../labs/lab-thread-deadlock.md)

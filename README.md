# Router operations

This repo is my solution to the mandatory assignment in the subject _IN2140 - Introduction to operating systems and data communication_ at the University of Oslo. This mandatory assignment was related to making router operations more effective. The program has been implemented in C.

## How to run

In the Makefile, there are a variety of calls that can be made to run the two example files.

First, run 

```
$ make all
```

This command will create the binary file needed to run the program.

After this, the command _run10_ and _run50_ will run based on specified files found in the _resources_ folder.

_run10_ contains a binary file with ten routers and ten edges with the respective command file.

_run50_ contains a binary file with fifty routers and one hundred and fifty edges with the respective command file.

## Compatibility ##

GCC 10.0 and above made some changes how it compiles _tentative definitions_. To ensure that the code will compile with GCC 10.0 and above, the _-fcommon_ flag has to be passed. If you are using a GCC version below 10.0, you can omit the _-fcommon_ flag

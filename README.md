# Router operations

This is my solution to the mandatory assignment in the subject _IN2140 - Introduction to operating systems and data communication_ at the University of Oslo. This mandatory assignment was related to making router operations more effective. The program is implemented in C.

## How to run

In the Makefile, there are to commands that run the two example files.

Firstly, compile the program with

```
$ make all
```

The commands _run10_ and _run50_ will run based on specified files found in the _resources_ folder.

```
$ make run10
```

```
$ make run50
```

_run10_ contains a binary file with ten routers and ten edges with the respective command file.

_run50_ contains a binary file with fifty routers and one hundred and fifty edges with the respective command file.

## Compatibility ##

GCC $\geq$ 10.0 made changes to how it compiles _tentative definitions_. For GCC $\geq$ 10.0, the _-fcommon_ has to be included.

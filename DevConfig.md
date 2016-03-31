# Introduction #
Several environment variables need to be defined to develop TREX or run TREX regression tests.

# EUROPA Environment Variables #
```
export PLASMA_HOME=/path/to/PLASMA
export PLASMA=$PLASMA_HOME/src/PLASMA
export LD_LIBRARY_PATH=$PLASMA_HOME/build/lib:$LD_LIBRARY_PATH
```

Note that for a Mac, the LD\_LIBRARY\_PATH setting is replaced with:
```
export DYLD_LIBRARY_PATH=$PLASMA_HOME/build/lib:$DYLD_LIBRARY_PATH
```
# TREX Environment Variables #
```
export TREX=/path/to/TREX
export TREX_LOG_DIR=$TREX/logs
```
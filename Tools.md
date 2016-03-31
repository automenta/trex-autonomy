

# Command Line Tools #
A set of command line tools are available once the proper configuration variables have been set up in the environment. If you followed the installation and environment setup steps in the [Getting Started](GetStarted.md) guide you are almost there. For some of these tools to work, the package must be built.
```
roscd your_working_package
make
```
## trexcreate ##
trexcreate will create an initial ROS package set up to use TREX. It will create a standard directory structure, and include all of the appropriate build and configuration files.
```
Usage:  trexcreate package_name  [--help] [--deps pkg1 pkg2 pkg3]
	package_name The ROS package name for the executive
	--deps a b c Optional ROS package dependencies of the package. In this example - a, b and c.
	--help       Produces this menu.
```
## trexfind ##
trexfind is a utility to locate a file in the [trex search path](SearchPath.md).
```
Usage:  trexfind file [--dir start_dir]  [--help] [--path]
  file   The file name to search for.
  --dir  Specify a start_dir in which to start the search from. If omitted, we will assume the search starts in the current directory.
  --help Produces this menu.
  --path Displays the search path.
```
## trexparse ##
trexparse is a utility to locate a file in the trex search path, and then parse it. It uses trexfind to locate the file.
```
Usage:  trexparse file [--dir start_dir]  [--help] [--path]
  file   The file name to parse.
  --dir  Specify a start_dir in which to start the search from. If omitted, we will assume the search starts in the current directory.
  --help Produces this menu.
  --path Displays the search path.
```
## trexdepends ##
trexdepends is a utility to enumerate all included files for a given nddl file.
```
Usage: trexdepends [file] [--help] [--dir start_dir]
 file   The nddl file to evaluate.
 --help Produces this menu.
 --dir  Indicates the start_dir to include in the search path.

```
## trexrun ##
trexrun launches a T-REX executive as a ROS node for batch or [interactive](TrexRun.md) execution.
```
Usage: trexrun [--help] [--debug] [--gtest] [--console] [--hyper | --playback] [--debug]
--help:     Provides this message!
--playback: Use if debugging a previous run. Expects an xml observation log file as input named <your_agent_name>.log
            and a clock log file names clock.log. In each tick, this will enforce that the Agent is allowed only as many
            execution steps that occured during the original run.
--hyper:    Run at 100% CPU for debugging. This enforces no limit on execution steps during each tick, and does not
            sleep if there is time left before the next tick.
--console:  Run in interactive mode. This will have no effect on the number of execution steps during each tick.
--gtest:    Apply validation tests on completion.
--debug:    Enables a debug version of the executive whichis slow, but provides alot of extra diagnostics.

TREX requires the following ROS parameters:
 trex/input_file: An xml file that defines the agent control configuration.
 trex/path:       A search path for locating input files. This should include a location for
                  the input configuration file, as well as locations for agent initialization files (nddl files)
 trex/start_dir   A directory from which to start the search for input files
 trex/log_dir:    An output directory for TREX log files.
```
## trexmonitor ##
[trexmonitor](TrexMonitor.md) is a runtime visualization tool for the trex executive.
```
Usage: trexmonitor [--help] [--dir log_dir]
 --help Produces this menu.
 --dir  Sets log_dir to be the source directory for reading executive output.
```

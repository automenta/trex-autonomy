# Create the project #
Create a working directory called trex\_tutorials:
```
mkdir trex_tutorials
cd trex_tutorials
```
This working directory must not be a subdirectory of any ROS package (it must not have a manifest.xml file in or above it). We will assume this is the working directory for remaining tutorials. Add this directory to the ROS\_PACKAGE\_PATH, if it is not already included:
```
ROS_PACKAGE_PATH=`pwd`:$ROS_PACKAGE_PATH
```
Create a project called **demo** using [trexcreate](Tutorials#trexcreate.md):
```
trexcreate demo
```
This will create a child directory of the current directory named **demo** with the following:
  * [manifest.xml](http://www.ros.org/wiki/Manifest) - A manifest file expected by ROS to delcare the new package.
  * [CMakeLists.txt](http://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/CMakeLists.txt) - A cmake file expected by ROS that will declare binaries required for _trexrun_ and _trexparse_.
  * [temp\_nddl\_gen.cfg](NddlConfig.md) - A NDDL configuration file used to set paths for file search, and binding implementation code to NDDL base classes.
  * src - A directory for source files. This directory will contain:
    * [demo\_components.cpp](http://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/src/trex_create_template_components.cpp) - A placeholder for any custom components you might wish to integrate in order to extend the capabilities of the executive
    * [temp\_init\_gen\_demo.cpp](http://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/src/temp_init_gen_demo.cpp) - A generated file providing a definition for a standard initialization package provided for all trex application packages.
    * [temp\_reg\_gen.cpp](http://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/src/temp_reg_gen.cpp) - A generated registartion file providing a registration function used in all trex application packages.
  * includes/package\_name - A directory for include files
  * nddl - A directory for NDDL model files. This directory includes a strawman model ([demo.nddl](https://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/nddl/demo.nddl)) to get you started:
  * cfg - A directory for T-REX agent configuration files.  To get started, this directory contains:
    * [demo.cfg](https://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/cfg/demo.cfg) which provides a 2-reactor configuration.
    * [debug.cfg](https://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/cfg/debug.cfg) which is used to set debug logging levels for T-REX.
  * test - A directory for test cases. A sample test case is provided. It includes:
    * [trex\_config.launch](http://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/test/trex_config.launch) - A ROS launch file used to set T-REX parameters. These will be used when running the executive.
    * [demo/demo.client.nddl](http://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/test/demo/demo.client.nddl) - The input nddl file for the **client** reactor of the **demo** agent.
    * [demo/demo.server.nddl](http://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/test/demo/demo.server.nddl) - The input nddl file for the **server** reactor of the **demo** agent.
    * [demo/demo.test](http://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/test/demo/demo.test) - A roslaunch file suitable for launching a roscore with required parameters and for use with rostest.
    * [demo/demo.valid](http://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core/trex_create_template/test/demo/demo.valid) - An event log populated with expected output as timeline changes are requested and as they are expected to occur. This is used as part of the regression testing framework.
# Try out some command line tools #
Using [command line tools](Tools.md) requires your new package to be built. To build the new project:
```
rosmake demo
```
You should now be able to apply [command line tools](Tools.md) now that your package has been built. To use these tools, you must be in the project's working directory, or bellow it. To get to the project easily, use roscd:
```
roscd demo
```
To find the configuration file `demo.cfg`:
```
trexfind demo.cfg
```
A success should generate the fully qualified path to the requested file. For example:
```
/u/mcgann/ros/ros-pkg/trex_tutorials/demo/cfg/demo.cfg
```
[trexdepends](Tools#trexdepends.md) can be used to get all the included nddl files for a given nddl target. if you type:
```
trexdepends test/demo/demo.client.nddl
```
You will see that this input file depends on a number of nddl files in this package and other packages:
```
/u/mcgann/ros/ros-pkg/wg-ros-pkg/stacks/trex/trex_core/TREX/agent/base/TREX.nddl
/u/mcgann/ros/ros-pkg/trex_tutorials/demo/nddl/demo.nddl
/wg/adw/mcgann/ros/ros-pkg/trex_tutorials/demo/test/demo/demo.client.nddl
```
# Execute an example scenario #
To run the executive for a sample scenario you will need to first launch a ROS core with suitable parameters:
```
roscd demo
roslaunch test/demo/demo.test
```
This will create a bunch of output indicating a successful startup:
```
SUMMARY
========

PARAMETERS
 * /trex/update_rate
 * /trex/input_file
 * /trex/log_dir
 * /trex/path
 * /trex/start_dir
 * /trex/time_limit
 * /trex/play_back

NODES

starting new master (master configured for auto start)
process[master]: started with pid [7020]
ROS_MASTER_URI=http://adw:11311/
setting /run_id to 4bf8eea0-c4a0-11de-a7b2-00301b81ce5d
+PARAM [/run_id] by /roslaunch
+PARAM [/roslaunch/uris/adw:59807] by /roslaunch
process[rosout-1]: started with pid [7035]
started core service [/rosout]
setting parameter [/trex/update_rate]
+PARAM [/trex/update_rate] by /roslaunch
setting parameter [/trex/input_file]
+PARAM [/trex/input_file] by /roslaunch
setting parameter [/trex/log_dir]
+PARAM [/trex/log_dir] by /roslaunch
setting parameter [/trex/path]
+PARAM [/trex/path] by /roslaunch
setting parameter [/trex/start_dir]
+PARAM [/trex/start_dir] by /roslaunch
setting parameter [/trex/time_limit]
+PARAM [/trex/time_limit] by /roslaunch
setting parameter [/trex/play_back]
+PARAM [/trex/play_back] by /roslaunch
+SERVICE [/rosout/get_loggers] /rosout http://adw:43147/
+SERVICE [/rosout/set_logger_level] /rosout http://adw:43147/
+SUB [/time] /rosout http://adw:43147/
+SUB [/clock] /rosout http://adw:43147/
+PUB [/rosout_agg] /rosout http://adw:43147/
+SUB [/rosout] /rosout http://adw:43147/
```

In order to run the executive, open up a new console window and:
```
roscd demo
trexrun
```
This will launch the executive and start executing in batch mode. The execute runs pretty quickly. The total test takes 10 ticks where each tick is 100ms, so once started, it should all happen in about a second. Here is what you should see:
```
[ INFO] 1256830560.655860000: Starting signal handler
[ INFO] 1256830560.678274000: Registering demo Schema
[ INFO] 1256830560.686118000: Registering demo Schema
[ INFO] 1256830560.690376000: Executive created.

[ INFO] 1256830560.690460000: Finished creating executive
[ INFO] 1256830560.690501000: Running the executive in nonstop mode.

[ INFO] 1256830561.610039000: Agent has finished running.

[ INFO] 1256830561.610117000: Deleting the executive
[ INFO] 1256830561.610167000: Shutting down at tick(10)

[ INFO] 1256830561.610207000: Terminating agent...

[ INFO] 1256830562.610285000: Resetting agent...

[ INFO] 1256830562.611953000: Destructing Executive...
```
It's OK to leave the core running for multiple executions of the executive as long as the test case parameters are the same. For now we will bring down ROS by simply switching to the console in which it was launched and typing **CTRL-C**.
# Inspect output #
There are a number of ways to see what is going on inside the executive. One of them is the [TREX.log](TrexLog.md) which is generated anew on every run. All executive log data is oupt to a directory designated by the TREX\_LOG\_DIR environment variable. This variable can also be set by the ros parameter trex/log\_dir. It is this mechanism that is used on the project structure you have just created.

Open up the trex\_config.launch file provided to see how trex configuration parameters are set:
```
roscd demo
cat test/trex_config.launch
```
You will see something like:
```
<launch>
  <!-- Automatically start roscore /-->
  <master auto="start"/>

  <!-- TREX Parameters /-->
  <param name="/trex/update_rate" value="10"/>
  <param name="/trex/path" value="$(find demo)/cfg:$(find trex_ros)/cfg"/>
  <param name="/trex/log_dir" value="$(find demo)/logs"/>
  <param name="/trex/play_back" value="0"/>
  <param name="/trex/time_limit" value="0"/>
  <param name="/trex/input_file" value="demo.cfg"/>
</launch>
```
Every time TREX executes, it creates a new working directory in the TREX\_LOG\_DIR. The current active directory is soft linked to **latest**. To inspect the log file generated:
```
cat logs/latest/TREX.log
```
Which should produce output of the form:
```
[0]ON hello ASSERT HelloWorldTimeline.Goodbye{}
[server][1]Request received: globalToken_0:HelloWorldTimeline.Hello(29)
[5]ON hello ASSERT HelloWorldTimeline.Hello{}
[server][7]Request received: HelloWorldTimeline.Goodbye(114)
[7]ON hello ASSERT HelloWorldTimeline.Goodbye{}
```
This log file tells you that:
  * At tick 0, the hello timeline has the value GoodBye
  * At tick 1, the server reactor received a request to transition the hello timeline to the value token of type Hello.
  * At tick 5, the hello timeline transitions to the requested value.
  * At tick 7, a second request is made, this time to transition to Goodbye. This transition occurs within the same tick.
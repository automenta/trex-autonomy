# Prerequisites #
T-REX requires Perforce Jam 2.5 or better. Under linux this can be obtained thus:
```
sudo apt-get install jam
```
The easiest way to build T-REX is through [ROS](http://www.ros.org/wiki/). Only the ROS build tools are required. These can be obtained by following the instructions in steps 1 and 2, for the ROS only install detailed [here](http://www.ros.org/wiki/ROS/Installation).
# Getting Required Sources and Building #
Make sure the [ROS\_PACKAGE\_PATH](http://www.ros.org/wiki/ROS/EnvironmentVariables#ROS_PACKAGE_PATH) environment variable is set to include the directory into which you check out T-REX. For example:
```
export ROS_PACKAGE_PATH=`pwd`:$ROS_PACKAGE_PATH
```
Check out the ROS package used to build TREX and all its external dependencies:
```
svn co https://code.ros.org/svn/wg-ros-pkg/trunk/stacks/trex/trex_core trex_core
```
Now you can build:
```
roscd trex_core
make
```
# Building and Running the Test Harness #
TREX has an extensive test harness consisting of small examples which exercise a range of different behaviors in the executive. To build all relevant libraries and execute the tests:
```
roscd trex_core
make test
```
If successful, you should see the following command line complete without complaint.
```
ExecuteTarget RUN_agent-module-tests_g_rt
```
Inspection of the output file:
```
cat TREX/agent/test/RUN_agent-module-tests_g_rt.output
```
should illustrate the set of tests that passed and will look something like this:
```
GamePlayTests::test***************
Running testPersonalRobots .... SUCCESS
Running testSynch .... SUCCESS
Running testExtensions .... SUCCESS
Running OrienteeringSolver .... SUCCESS
Running testRecall .... SUCCESS
Running testRepair .... SUCCESS
Running testLogging .... SUCCESS
Running testPersistence .... SUCCESS
Running testSimulationWithPlannerTimeouts .... SUCCESS
Running testScalability .... SUCCESS
Running testTestMonitor .... SUCCESS
Running testOneDeliberatorOneAdapter .... SUCCESS
Running bugFixes .... SUCCESS
Running testInconsistent .... SUCCESS
Running testOneStepAhead .... SUCCESS
Running testFileSearch .... SUCCESS
Running testDispatch .... SUCCESS
Running testSqueezeObserver .... SUCCESS
Running testSimulation .... SUCCESS
Running testUndefinedSingleTimeline .... SUCCESS
Running testUndefinedDerived .... SUCCESS
Running testActions .... SUCCESS
GamePlayTests::test PASSED.
AgentTests::test***************
Running testRealTimeClock .... SUCCESS
Running testForeverConfiguration .... SUCCESS
Running testTimelimitOverride .... SUCCESS
AgentTests::test PASSED.
```

# Setting up the environment #
There are a number of tools available from the command line, and a number of environment variables required for correct execution. It is convenient to set these up whenever you open up a new bash shell. To do this:
```
echo "source `rospack find trex_core`/bashrc.trex" >> ~/.bashrc
```
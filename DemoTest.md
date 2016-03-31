**Prerequisites:** We assume you have completed the tutorial for [creating a project](CreateProject.md).

# Test the demo project #
You can verify that the demo is working correctly by running a test case that is generated as part of a skeleton test harness for you:
```
roscd demo
make test
```
You should see output terminating with an indication of success such as:
```
[AGGREGATED TEST RESULTS SUMMARY]

PACKAGES: 
 * demo


SUMMARY
 * RESULT: SUCCESS
 * TESTS: 3
 * ERRORS: 0
 * FAILURES: 0
```

# Inspect test files #
The test harness includes a single executive test located in the test directory under test/demo. The nomenclature is standardised on test-case-name.test
```
roscd demo/test/demo
cat demo.test
```
The text displayed will be something like:
```
<launch>
  <!-- Include trex config -->
  <include file="$(find demo)/test/trex_config.launch" />
  <!-- Set TREX start dir. Trex starts looking for files here. -->
  <param name="/trex/start_dir" value="$(find demo)/test/demo"/>
  <!-- Create a test using trexfast. The test will compare with demo.valid to ensure correct operation. -->  
  <test test-name="test_demo_demo" pkg="demo" type="trexfast" time-limit="30.0" args="--hyper --gtest" />
</launch>
```

The success criteria for the test are defined in the .valid file test-case-name.valid. The file demo.valid contains:
```
0 NOTIFY  hello HelloWorldTimeline.Goodbye
1 REQUEST hello HelloWorldTimeline.Hello
5 NOTIFY  hello HelloWorldTimeline.Hello
7 REQUEST hello HelloWorldTimeline.Goodbye
7 NOTIFY  hello HelloWorldTimeline.Goodbye
```

The format for this [event log](EventLog.md) is a slim-down version of the contents of [TREX.log](TrexLog.md). It dispenses with some details that are useful for debugging but would make the test more brittle. In this exmple, observe that **NOTIFY** statements indicate a new value for a timeline (i.e. an observation) and **REQUEST** statements indicate a goal has been dispatched from a client to a server. This log file tells you that:
  * At tick 0, the hello timeline has the value GoodBye
  * At tick 1, a request was dispatched to transition the hello timeline to the value token of type Hello.
  * At tick 5, the hello timeline transitions to the requested value.
  * At tick 7, a second request is made, this time to transition to Goodbye. This transition occurs within the same tick.

# Force test to fail #
It is easy to force a test to fail. Simply modify the .valid file. For example, prepend a `!` to the start of the last line in demo.valid and save the file. Then:
```
roscd demo
make test
```
This time, you should see results indicating an error. This will look something like:
```
[ERROR] 1256828027.967000000: Invalid event stream. Compare .error and .valid files
testtest_demo_demo ... ok
[ROSTEST]-----------------------------------------------------------------------

[demo.test_demo_demo/validatEventLog][FAILURE]----------------------------------
/wg/adw/mcgann/ros/ros-pkg/wg-ros-pkg/stacks/trex/trex_ros/src/main.cpp:280
Value of: true
Expected: g_valid_event_log
Which is: false
--------------------------------------------------------------------------------

[demo.test_demo_demo/validateAssertions][passed]

SUMMARY
 * RESULT: FAIL
 * TESTS: 2
 * ERRORS: 0
 * FAILURES: 1
```

In the case of a discrepancy between the actual and expected event logs, the test harness will generate a file: test-case-name.error, in the test case directory, which will contain the actual event log for you to commpare against. The event log can be captured by simply promoting the .error file to a .valid status, or by generating a new .valid file. To regenerate the .valid file:
```
roscd demo
rm test/demo/demo.error
rm test/demo/demo.valid
make test
```
You should see that once again the test passes and now a new .valid file has been created.
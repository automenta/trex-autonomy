T-REX tools will search for named files of all kinds using a search path composed of 2 elements, defined by the following environment variables:
  * TREX\_PATH - This is a ':' delimited list of directories that will be searched.
  * TREX\_START\_DIR - This is the location from which to begin the search for a file.

T-REX will find the first available instance of a file. It searches according to the following scheme:
  1. Traverse up the directory tree from the start directory to a directory in the path.
  1. Traverse the path in the order in which the directories are listed.

The above environment variables can be set directly in the user environment. However, T-REX provides additional support for setting these properties. TREX\_PATH can be over-ridden by:
  * Setting trex/path as a ROS parameter before launching [trexrun](Tools#trexrun.md).
  * Setting the include path in [NDDL.cfg](NddlConfig.md), which will be obtained by searching the path based on the current environment variable settings.
  * Setting the include path in temp\_nddl\_gen.cfg, which will be obtained by searching the path based on the current environment variable settings. This is only used if  NDDL.cfg file is not found. Note that this file is auto-generated when using the [trexcreate](Tools#trexcreate.md) tool.

The TREX\_START\_DIR environment variable can be over-ridden by setting trex/start\_dir as a ROS parameter before launching [trexrun](Tools#trexrun.md).

For example, suppose the following files exist in the file system:
  * bar/a.foo
  * bar/bing/bing/a.foo
  * baz/b.foo

Assume TREX\_PATH = "foo:bar/cfg:bar:baz". This yields the following search examples:
  * If the start directory is bar/bing/bing/, then a search for a.foo will return: bar/bing/bing/a.foo.
  * If the start directory is bar/bing, then a search for a.foo will return: bar/a.foo.
  * If the start directory is bar/bing, then a search b.foo will return: baz/b.foo.





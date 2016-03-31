# The Challenges of Programming Autonomous Robots #
## Domain Characteristics ##
There are a wide variety of robots capable of a wide variety of tasks. For example, the PR2 is targetted at indoor service tasks. NOMAD is designed to autonomously explore the antarctic. Mars rovers operate as roving geologists on the planetary surface. Marine robots map the sea-floor and venture into uncharted underwater caves.
|![http://trex-autonomy.googlecode.com/svn/wiki/images/pr2.jpg](http://trex-autonomy.googlecode.com/svn/wiki/images/pr2.jpg)|![http://trex-autonomy.googlecode.com/svn/wiki/images/nomad.jpg](http://trex-autonomy.googlecode.com/svn/wiki/images/nomad.jpg)|![http://trex-autonomy.googlecode.com/svn/wiki/images/rover.jpg](http://trex-autonomy.googlecode.com/svn/wiki/images/rover.jpg)|![http://trex-autonomy.googlecode.com/svn/wiki/images/auv.jpg](http://trex-autonomy.googlecode.com/svn/wiki/images/auv.jpg)|![http://trex-autonomy.googlecode.com/svn/wiki/images/depthx.jpg](http://trex-autonomy.googlecode.com/svn/wiki/images/depthx.jpg)|
|:--------------------------------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------|:------------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------|:--------------------------------------------------------------------------------------------------------------------------------|
| [PR2 (Willow Garage)](http://www.willowgarage.com/pages/robots/pr2-overview)                                              | [NOMAD (CMU)](http://www.frc.ri.cmu.edu/projects/meteorobot2000/)                                                             |[Mars Rover (NASA)](http://marsrovers.nasa.gov/overview/)                                                                      |[Dorado AUV (MBARI)](http://www.mbari.org/auv/MappingAUV/)                                                                 | [DepthX (CMU/Stone Aerospace)](http://www.frc.ri.cmu.edu/depthx/)                                                               |

Despite the obvious differences in the types of robots, their tasks, and their environments, they have much in common:
  * **Complex machines** - They are all complex machines with many interacting components.
  * **Challenging environments** - They all operate in dynamic, unstructured and uncertain environments.
  * **Complex tasks** - Many applications of these robots require intricate combinations of a multitude of low-level behaviors.
  * **Resource constrained** - Autonomous robots, in the field, are usually constrained in resources such as energy, bandwidth, power, storage space, CPU.
  * **Time constrained** - Operators often impose time constraints on required tasks. For example, when an image must be taken, when a communication must occur, when a mission must be finished.

## Desirable Virtues ##
Despite these complexity factors, we would like our robots to embody some very important virtues:
  * **Safe** - Robots are expensive. They should not become lost or damged. Nor should they do harm to others.
  * **Goal-directed** - An operator can task a robot to achieve goals without having to detail precisely how they should be accomplished. This makes the robot easier to use.
  * **Efficient** - Completes given tasks with acceptable cost and quality.
  * **Adaptive** - Able to deal with situations as they occur. This is essential in dynamic and uncertain environments, which are most of the interesting environments.
  * **Robust** - Failure is inevitable. It should thus be recoverable.

## The Robot Programmer's Dilemna ##
![http://trex-autonomy.googlecode.com/svn/wiki/images/frazzled_programmer.jpg](http://trex-autonomy.googlecode.com/svn/wiki/images/frazzled_programmer.jpg)
If you have ever tried to program a sophisticated robot to achieve such high levels of performance, in such challenging environments, then you might empathize with the difficulties invoved:
  * There are many components to integrate and manage.
  * Often these components interact in intricate ways.
  * There can often be many alternatives to consider to achieve good behavior.
  * Choices about how things should be done must often be made in-situ, by the program rather than a-priori by the operator.
  * Murphy's Law is true - _Everything that can go wrong, will_.

[Learn More](http://code.google.com/p/trex-autonomy/wiki/LearnMore)
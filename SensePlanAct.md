# Sense - Plan - Act #



[Timelines](http://code.google.com/p/trex-autonomy/wiki/TimelinesAndExecution) are the first pillar of T-REX. Ubiquitous, embedded planning is the second.

## Goal-directed Feedback Control ##
We think of a control loop for an agent as having a goal to accomplish, in the face of feedback from the environment. T-REX calls such a control loop a **Teleo-Reactor** reflecting its goal-directed (_teleo_) and _reactive_ nature. A Teleo-Reactor encapsualtes three components of control:
  * Sensing - where observations from the environment are integrated into the internal state of the controller.
  * Planning - where a computation is used to determine actions to execute in order to achieve a given goal.
  * Acting - where planned actions are dispatched for execution.

The concept of control as a continual process of _Sense, Plan, Act_ is not new. It made its debut with [Shakey](http://www.ai.sri.com/shakey/) back in the 60s, but fell out of favor for a variety of reasons, including the fact that _planning_ was slow, and thus the robot was not very reactive. This evolution of robot control architectures is described [here](http://code.google.com/p/trex-autonomy/wiki/RelatedWork). Computers and planning technologies have come along way since then, making planning much faster, and more sophisticated.

## The Deliberative Reactor ##
T-REX includes a particular kind of Teleo-Reactor that is implemented with an embedded temporal planning system ([EUROPA](http://code.google.com/p/europa-pso/wiki/EuropaWiki)). We call this a **Deliberative Reactor** since it utilizes a deliberative planner (i.e. one that can look ahead in formulating a plan) at the core of its control loop. The figure below depicts the internal structure of a **Deliberative Reactor**.

![http://trex-autonomy.googlecode.com/svn/wiki/images/deliberative_reactor.png](http://trex-autonomy.googlecode.com/svn/wiki/images/deliberative_reactor.png)

The _Plan Database_ is the store for reactor state in the form of timelines and tokens as described [here](http://code.google.com/p/trex-autonomy/wiki/TimelinesAndExecution). This database actively propagates rules and constraints associated with a _partial plan_. The roles of sensing, planning and acting are played by the _Synchronizer_, the _Planner_, and the _Dispatcher_ respectively.  Keep in mind the notion of a timeline in the context of execution described [earlier](http://code.google.com/p/trex-autonomy/wiki/TimelinesAndExecution). **Observations** are input to the reactor from the external world, expressing new values arising on timelines. They are converted into tokens and inserted into the relevant timeline by the _Synchronizer_. **Goals** are desired values for timelines and again are expressed as tokens in the plan database. The _Planner_ tracks goal requests, and monitors the database for new flaws. It will activate whenever the plan is incomplete, and resolve the matter. The _Dispatcher_ is responsible for communicating planned timeline values to the responsible actors external to the reactor. If the timeline is internal, there is nothing to dispatch. The _Synchronizer_ publishes observations for any timelines _internal_ to the reactor.

## Benefits of the Deliberative Reactor ##
The _Deliberative Reactor_ is something of a wonder widget, since this basic building block can be applied in a wide variety of scenarios, customized by the set of timelines instantiated in the database, the time horizon over which it must plan, the model it uses, and on perhaps specialized plug-ins for the planner or the plan database as permitted by the EUROPA libraries modular design. This offers a great degree of software re-use in building a controller. In addition to the obvious advantages of software re-use, the planning centric control model implemented in the _Deliberative Reactor_ offers a number of benefits:
  * **Seamless integration of planning and execution**. It provides a seamless way to integrate planning and plan execution in a common representation, leveraging common run-time components. This removes some of the integration complexity that arises when a planner and an executive operate with different representations.
  * **Direct projection of execution impacts in the plan**. It enables the algorithms for temporal reasoning and constraint propagation used during planning to be directly applied for plan monitoring during execution, propagating effects of execution updates throughout the plan.
  * **Model-compliant execution**. It guarantee that any plans executed are model-compliant. Execution works directly on a plan. That plan is constructed through an automated process that is checked for compliance with a model as it goes. Hence there is no way for the executive to execute a plan that violates the model. This can provide important safety guarantees.
  * **High-level programming model**. It creates an agent programming model that is based on a very high-level language, making programs compact.
  * **Adjustable automated programming model**. It creates a programming model that allows prescriptive program specifications or models can be less prescriptive and exploit an automated planner to fill in the gaps. This can also make programs more compact and easier to maintain.
  * **High-impact of research advances**. It provides a technology infusion pathway for advances in planning to directly and substantially impact agent programming since the programming model heavily leverages these capabilities.

## Drawbacks ##
There are drawbacks. Chief among them are:
  * **Steep Learning Curve**. There is a steep learning curve to understand constraint-based temporal planning. Hopefully this is mitigated by [documentation](http://code.google.com/p/trex-autonomy/wiki/UserDocumentation) and [practical tutorials](http://code.google.com/p/trex-autonomy/wiki/Tutorials).
  * **Problems can be hard to debug**. Debugging problems can require careful analysis of partial plans. Hopefully this too is alleviated through the availablity of [execution monitoring and debugging tools](http://code.google.com/p/trex-autonomy/wiki/Tools).
  * **Heavyweight representation for some applications**. The timeline based representation is inappropariate for many forms of sensor data such as images, point clouds and other high-dimensional, high-volume data.
  * **Too slow for some applications**. There is a computational overhead to using a general-purpose planning framework that can often be avoided if a _Teleo-Reactor_ is carefully designed for the specific use case. This is a common critique of general purpose infrastructures vs. tailored solutions and the trade-off is very situationally dependent. We have managed to operate complex robots at control rates in the 10Hz range without a problem.
  * **Planning can be hard**. Automated planning often requires domain-dependent heuristics for problems of even moderate complexity. These heuristics can be challenging to develop, and brittle to maintain as models change, sometimes even for small changes. This is a subject for ongoing research.


[UP](http://code.google.com/p/trex-autonomy/wiki/LearnMore) [NEXT](http://code.google.com/p/trex-autonomy/wiki/DivideAndConquer)
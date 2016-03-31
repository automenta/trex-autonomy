# Why T-REX? #
[What would anybody want to use T-REX?](HardWork.md) Here are some of the benefits we hope to deliver with T-REX:
  * **Goal-directed Commanding**: Do you want to command a robot with goals telling it what to do, instead of detailing precisely how it should achieve them? If so, then a planning system is useful to turn goals into commands automatically, saving the robot operator alot of work, and reducing the possibility of error.
  * **Robust Execution**: Many real-world environments are highly uncertain. If your robot can decide how best to accomplish its objectives based on the situation at hand, then it can be robust to these uncertainties. A planner is a principled way to select suitable actions to achieve a goal, and it can leverage a plethora of work in automated reasoning to do so. Planners running during execution are handy because they can incrementally figure out what to do and/or they can re-plan if prior plans do not work out.
  * **Safe Execution**: Many sophisticated robots are expensive, complex machines that should be programmed with care. A _model_ can capture safety constraints that must be observed by all executions. Such a model is directly used by the planner and all plans produced are guaranteed to comply with these constraints. We call this _model compliant execution_. If the model is correct, this provides a powerful quality assurance mechanism for robot behavior.
  * **High-level Programming**: It's easy to get lost in details when programming a complex machine. A high-level modeling language raises the level of abstraction to the essential features of the robot mechanisms, available behaviors, and the task domain. This approach allows a programming model that can focus on the problem domain rather than worry about threads, memory management, and so forth.

# Key Ideas #
There are a few key ideas behind T-REX, and of course, the devil is in the details. Those details deeply involve [EUROPA-2](http://code.google.com/p/europa-pso/). However, as a first introduction, we present the key concepts.
## [Constraint-based Temporal Planning](CTP.md) ##
Constraint-based Temporal Planning is a paradigm for representing and reasoning about plans. It is a foundation of T-REX, and is presented here informally.
## [Timelines-based Execution](TimelinesAndExecution.md) ##
Many people are intuitively familiar with the notion of a timeline. In T-REX, a timeline is a core primitive for representing all state in the past, present and future. Check this out if you want to see more formally how this works.
## [Sense-Plan-Act](SensePlanAct.md) ##
Timelines are great, but what we really care about is how we fill them out. A long standing paradigm for robot control sees a control loop as a continuous cycle of Sensing, Planning, and Acting. T-REX applies this simple paradigm, thus placing planning at the core of a control loop in a systematic way. Check this out to learn more.
## [Divide-and-Conquer](DivideAndConquer.md) ##
An age old approach for tackling complexity is to _divide and conquer_. T-REX embraces this idea to enable a planning centric system to scale well, enabling a spectrum of variously reactive and deliberative behavior.

# [T-REX in the Scheme of Things](RelatedWork.md) #
People have been programming robots for quite some time. If you want to find out more about how approaches to programming robots have evolved, and how T-REX fits in to that work, then this is a good place to go.
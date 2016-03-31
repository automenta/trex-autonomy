# Timeline-based Execution #



Timelines are the representational foundation for T-REX. You should have some idea of what a timeline is and how it relates to planning by now. If not, read [this material](http://code.google.com/p/trex-autonomy/wiki/CTP) first. The mapping from timelines to execution is quite straightforward as we will now illustrate with a simple example.

## Moving a mobile robot to a goal ##
Suppose you have a mobile robot, perhaps something like a [PR2](http://www.willowgarage.com/pages/robots/pr2-overview). The robot can be commanded to a particular pose (x, y, theta). Robot navigation is implemented by a durative action called **MoveBase** which is **Active** while driving to the target location, and **Inactive** otherwise.  In particular, when such an action transitions to the **Inactive** state, it reports if it was successful or not, and provides feedback on the precise position and orientation on completion. An action in this sense is synonymous with a _skill_, or _behavior_, which are sometimes used in the literature.

An action with these semantics is readily represented by a timeline. The [NDDL model](http://code.google.com/p/trex-autonomy/wiki/CTP#Modeling) to describe the action is shown below. First, the class declaration shows a timeline with 2 possible predicates. Since each predicate has parameters whose domains are continuous, infinitely many values can be described with this structure. The details of the NDDL code, are not that important at this stage. The key thing to understand is that the basic timeline structure is described with 2 predicates, each suitably parameterized.

```

enum ResultStatus {
  UNDEFINED,  // Used when the action becomes inactive in an undefined state, such as when rebooting
  SUCCESS,    // Indicates the action terminated, accomplishing its goal. Or so it believes!
  ABORTED,    // Means the action aborted pursuit of its goal of its own volition
  PREEMPTED   // Means the action terminated on command from a client.
};

// Class declaration for MoveBase
class MoveBase extends AgentTimeline {
 predicate Active{
   float x;
   float y;
   float theta;
 }

 predicate Inactive{
   ResultStatus status;
   float x;
   float y;
   float theta;
 }

 MoveBase(Mode m) { super(m); }
};
```

## An Executive with a Plan ##
Think of an executive as an agent that contains a timeline. The NDDL code below shows how an instance of the **MoveBase** class is allocated. It is constructed with a marker indicating it is _External_. This means that the true source for that timeline value is outside of the agent. This makes sense since it captures the state of an external robot action. Also note that 2 predicate instances are allocated, each corresponding to a **goal token**. They are temporally ordered. These are simply desired values for the timeline to have. They become flaws for the planner to [resolve into a complete plan](http://code.google.com/p/trex-autonomy/wiki/CTP#Automated_Planning).

```
MoveBase movebase = new MoveBase(External);

// First goal
rejectable(movebase.Active goal_0);
goal_0.x = 1.0;
goal_0.y = 2.0;
goal_0.theta = 0.0;

// Second goal
rejectable(movebase.Active goal_1);
goal_1.x = 8.5;
goal_1.y = 9.0;
goal_1.theta = 0.4;

// goal 0 should be executed before goal_1
goal_0 before goal_1;
```

The executive will use a planner to plan the goals resulting in a timeline filled out as shown below. This is a planned trajectory for the _state_ of the external _movebase_ action. Actual values for the timeline will emerge during the course of execution. The _execution frontier_ marks the current clock position in the timeline - the point of current execution. The values at or before this point are considered _facts_ since they reflect actual world state. Notice that the goal parameters are bound to singletons while the feedback values of the Inactive values are not specified. These are left for resolution in execution. Also note that the time bounds marking the transitions from one value to another are represented as intervals. This reflects the uncertainty about actual start and finish times for action execution. The plan does not require precision here and so they are left as flexible as possible. This example assumes that all goals are to be accomplished within a mission time window of 1000 time units. Each time unit is called a _tick_.

|![http://trex-autonomy.googlecode.com/svn/wiki/images/timelines.a.png](http://trex-autonomy.googlecode.com/svn/wiki/images/timelines.a.png)|
|:------------------------------------------------------------------------------------------------------------------------------------------|

## Dispatching Goals and Receiving Observations ##
The executive must now execute this plan. Execution in this sense means to bring about the expected trajectory of values of its timeline. Since the timeline is external, it is not strictly up to the executive to make this happen. However, it can _task_ an external entity by _dispatching_ desired states (goals) to the responsible party in a timely fashion. We assume that as the receiver transitions states, it will notify the executive of the new value. So when the action becomes active, in pursuit of a goal defined by _x, y, theta_ it is manifest as an _observation token_ for the executive which is integrated into the timeline. An observation has the semantics of someting that has actually happened in the outside world (outside of the reactor that is). Where the data of the observation match a value in the timeline, the observation and the plan are merged. If they conflict, the plan becomes broken and a new plan will have to be created. Often, the planned value for a timeline will only stipulate bounds on expected values, in accordance with required tolerances for example, or reflecting uncertainty or ambivalence. The more flexibility retained in the plan, the more robust that plan will be when merging actual values in execution.

The figure below illustrates the _observation_ events in green and the _dispatch_ events in red. At the initial tick, an observation provides the initial timeline value. At _tick 1_ the executive dispatches the first goal. In this example we assume only one goal is dispatched at a time since the receiver (i.e. movebase action server) does not plan ahead for more than one goal. The executive gets an immediate response in the same tick indicating that the action has been activated in pursuit of the desired goal. At _tick 567_ the movebase action server achieves its goal and transitions to the **Inactive** state, generating a new observation for the executive.  The executive in turn can now dispatch the next goal, which follows the same process of observations.

|![http://trex-autonomy.googlecode.com/svn/wiki/images/timelines.b.png](http://trex-autonomy.googlecode.com/svn/wiki/images/timelines.b.png)|
|:------------------------------------------------------------------------------------------------------------------------------------------|

## Execution History ##
The execution history is shown in the timeline below. Here the execution frontier has advanced to _tick 977_. The action is in an **Inactive** state, with its end time being nudged by the advancing execution frontier. Notice that all the timepoints for state transitions are now ground to singleton values as are all parameters for all tokens. This reduction to singleton values occurs straightforwardly as observations are integrated with the plan during execution.

|![http://trex-autonomy.googlecode.com/svn/wiki/images/timelines.c.png](http://trex-autonomy.googlecode.com/svn/wiki/images/timelines.c.png)|
|:------------------------------------------------------------------------------------------------------------------------------------------|

[BACK](http://code.google.com/p/trex-autonomy/wiki/LearnMore)  [NEXT](http://code.google.com/p/trex-autonomy/wiki/SensePlanAct)
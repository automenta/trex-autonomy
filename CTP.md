

# Timelines and Tokens #
Consider a spacecraft traveling through deep space, tasked with taking pictures of specific targets. The spacecraft has an _engine_ which can be fired to alter its pose. It also has a _camera_ which is turned off when not in use. If the camera was previously off, it can require some warm up period before being ready. The spacecraft _attitude_ is either pointing at a specific target, thus having a steady pose, or transitioning from one pose to another. There are 3 state variables of interest in this spacecraft scenario: **Engine**, **Camera**, and **Attitude**.  A _timeline_ captures the values of a state variable over time. The figure below illustrates timelines for each of the above state variables. Both the **Camera** and the **Engine** are **Off** and the spacecraft is **PointingAt** a target given by _D12_. The value of a state variable, specified with a _Token_, has temporal extent, which means it persists for some period of time. The temporal scope for a value is bounded by a start and end time. In the figure below, the start time of each token  is fixed, but the end time is not. This indicates uncertainty and/or ambivalence about when the current value will end. A _token_ includes a [predicate](http://en.wikipedia.org/wiki/Predicate_(mathematical_logic)) with a possibly empty set of parameters, in keeping with conventional [first-order logic](http://en.wikipedia.org/wiki/First-order_logic) representations. The **Engine** can be **Off** or it can be **Thrusting** to a target pose. The **Camera** can be **Off**, **WarmingUp**, **Ready**, or **TakingPicture** at some target pose. The spacecraft **Attitude** is either **PointingAt** a target pose, or **TurningTo** a target pose.

![http://trex-autonomy.googlecode.com/svn/wiki/images/initial_state.png](http://trex-autonomy.googlecode.com/svn/wiki/images/initial_state.png)


# Constraints and Causal Links #
Suppose the spacecraft should take a picture of a specific asteroid. While it is taking a picture of the asteroid, it should be pointing at it. This can be said for any target pose. Also, in order to prevent jitter in the image, it is critical that the engine is **Off** while the shot is being taken. The figure below illustrates how the spacecraft timelines are filled out to accommodate this goal. It illustrates the values of timelines as they are expected to change, as well as the constraints between start times, end times and parameters. _Causal Links_ form a chain connecting goals to initial conditions. A _causal link_ is a directed edge from a _master token_ to a _slave token_.

![http://trex-autonomy.googlecode.com/svn/wiki/images/partial_plan.png](http://trex-autonomy.googlecode.com/svn/wiki/images/partial_plan.png)

Note that the requirement that _while taking a picture, the engine must be off_ is expressed as a constraint from the **Camera** timeline to the **Engine** timeline, with precedence constraints between timepoints capturing the _while_ semantics. Also note the transition of the **Camera** timeline from **Off** to **TakingPicture** must go through intermediate states to first warm up and then be ready. The goal also requires a change in vehicle attitude. The adjustment in attitude is co-temporal with thrusting the engine. This is expressed by equality constraints between the start and end times of the respective tokens.

# Modeling #
So far we have used informal language to describe the spacecraft domain. [NDDL](http://code.google.com/p/europa-pso/wiki/NDDLReference) is a formal modeling language used to specify a planning domain such that algorithms for search and inference can be applied to automatically fill out timelines as just described.
## Class Declarations ##
A **Target** is a structure defining a point in cartesian space:
```
class Target{
 float x;
 float y;
 float z;

 Target(float _x, _y, _z){
  x = _x;
  y = _y;
  z = _z;
 }
}
```
The **Engine** timeline is declared thus:
```
class Engine extends Timeline{
 predicate Off{}
 predicate Thrusting{
  Target target;
 }

 Engine(){super();}
}
```

Similarly, we can declare **Attitude** and **Camera** timelines.
```
class Camera extends Timeline {
 predicate Off{}
 predicate WarmingUp{}
 predicate Ready{}
 predicate TakingPicture{
  Target target;
 }
 Camera(){super();}
}

class Attitude extends Timeline {
 predicate PointingAt{
  Target target;
 }
 predicate TurningTo{
  Target target;
 }

 Attitude(){super();}
}
```
## Transition Constraints ##
There are a number of constraints governing transitions within a given timeline. For example, the engine will transition between **Off** and **Thrusting**. We can express this with rules constraining successor and predecessor values of each value:
```
Engine::Off{
 meets(Thrusting);
 met_by(Thrusting);
}
Engine::Thrusting{
 meets(Off);
 met_by(Off);
}
```
**Meets** and **met\_by** are examples of qualitative constraints between temporal intervals known as [Allen Relations](http://code.google.com/p/europa-pso/wiki/NDDLReference#Slave_Allocation_and_Temporal_Relations). If the **Camera** is **Off** its next state will always be **WarmingUp**:
```
Camera::Off{
 meets(WarmingUp);
}
```
Similarly, if it is **WarmingUp**, it will transition into **Ready**, and its prior value must be **Off**.
```
Camera::WarmingUp{
 meets(Ready);
 met_by(Off);
}
```
The Attitude state variable is also constrained to transition between **PointingAt** and **TurningTo**. In this case, we have to introduce a constraint between parameters of tokens:
```
Attitude::PointingAt{
 meets(TurningTo);
 // There is a parameter constraint equating parameters of the current and previous values.
 met_by(TurningTo pred);
 pred.target == target;
}
Attitude::TurningTo{
 meets(PointingAt succ);
 target == succ.target;
 met_by(PointingAt);
}
```
## Interaction Constraints ##
In addition to constraints on transitions within a timeline, we described a number of constraints between values across timelines. For example, the constraints holding on **TakingPicture** additionally include:
```
Camera::TakingPicture{
 contained_by(Engine.Off);
 contained_by(Attitude.PointingAt p);
 p.target == target;
}
```
Also, the interaction between **Attitude.TurningTo** and **Engine.Thrusting** can be stated simply:
```
Attitude::TurningTo{
 equals(Engine.Thrusting t);
 t.target == target;
}
```
# Automated Planning #
There is a very general notion that a plan might be flawed, and thus require fixing. The primary reasons why a plan is flawed are because it is _incomplete_ or _inconsistent_. If a plan is _incomplete_, it must be further refined. If it is _inconsistent_ it must be repaired. This section will illustrate the process of plan refinement using the spacecraft example, whereby an initial state and goal represent an _incomplete partial plan_ that which can be incrementally refined until there is a valid trajectory of all state variables to get from the initial state to the goal. Plan repair will not be discussed at this time. Suffice to say, it requires a relaxation of the plan in some fashion. The series of diagrams below illustrate how an initial partial plan is refined repeatedly until all flaws are resolved.

| ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.0.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.0.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.1.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.1.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.2.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.2.png) |
|:----------------------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------|
| The example begins with an initial state as previously described, and a goal to take a picture of the Asteroid. In this case, the goal represents a flaw since no decision has been made to put it in the plan. This is indicated by the yellow color and is called an _open condition_. The grey tokens indicate slaves entailed by the model. However, they are not considered flaws because their respective masters can continue indefinitely and thus no transition is actually required. In this case they are just constraints that any plan must not contradict, rather than states that must be achieved.| There is only one option available to resolve this first flaw - it must be _activated_. Activation means that the token exists as a new state transition in the plan. Alternatively one might be able to merge an open-condition with a preexisting token in the plan. We will see examples of that later. Once a token has been _activated_ we color it blue. The model is applied to _active_ tokens, generating slave tokens which are also flaws. Observe that the **TakingPicture** token has not been inserted  in the timeline yet. | A Timeline is like a unary resource in that there can be at most one value at a time.  Hence the plan is not complete until the token has been ordered with respect to other tokens on the same timeline. We call this ordering requirement a _threat_ since the potential overlap of unordered tokens on a timeline threatens the safe execution of the plan. The flaw is resolved by inserting the token after the initial value. Observe a side-effect of this insertion - the previously ignored slave of the **Camera.Off** token is now considered a flaw. Why is this? Because the plan now requires the camera to transition out of the **Off** state, and thus the _start time_ for the successor token is in the planning time horizon and must be dealt with in order to prove the plan complete.|
| ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.3.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.3.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.4.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.4.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.5.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.5.png) |
| The planner now has a choice of flaws to pursue. Choosing the next flaw is an important aspect of search-control and handled by _flaw selection heuristics_. Here we select the **Camera.Ready** token and once again _activate_ it. As before, once the model is applied to the newly activated token, more flaws appear. | The **Ready** token is inserted in the plan. Temporal constraints dictate that it is inserted before its master. Since there is an equality constraint between the timepoints, we show the timeline without gaps between them. | The next flaw is selected, and resolved via _activation_.                                                                         |
| ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.6.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.6.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.7.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.7.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.8.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.8.png) |
| As before, the threat is resolved by insertion. Once again, the point of insertion is highly constrained by temporal constraints from the model. | The successor to **Off** must be **WarmingUp**. The successor to **WarmingUp** must be **Ready**. This is reflected by the open conditions which can now be resolved by merging it with a pre-existing tokens, rather than activating it. Now the full trajectory for the **Camera** timeline is complete. | Next, the **Attitude.PointingAt** token is activated, generating a slave constraining its predecessor state as dictated by the model. It is worth pointing out that this token could not be merged with the existing **PointingAt** token since they disagree in their parameters. 2 tokens can only be merged if there is a consistent intersection for each corresponding temporal or parameter variable. When tokens are merged, the new bounds on the variables becomes the intersections of these corresponding domains. |
| ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.9.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.9.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.10.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.10.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.12.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.12.png) |
| Insertion of **PointingAt** in the plan once again changes the bounds on the initial value, forcing the successor state (i.e. **TurningTo**) to be in scope for planning. | Another open-condition is resolved by activation. Once again, the model entails new flaws.                                        | The token is inserted in the plan. Also, the outstanding slaves for this timeline can all be merged in immediately.               |
| ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.13.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.13.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.14.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.14.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.15.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.15.png) |
| Now the planner will work on the **Engine** timeline. The open-condition is activated.                                            | The **Engine.Thrusting** token is inserted in the timeline, placing the previously ignored token in scope.                        | The open-condition is resolved by merging, removing the gap between the first 2 tokens. The plan is still incomplete.             |
| ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.16.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.16.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.17.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.17.png) | ![http://trex-autonomy.googlecode.com/svn/wiki/images/plan.18.png](http://trex-autonomy.googlecode.com/svn/wiki/images/plan.18.png) |
|  Because of the temporal constraint structure arising from the model, and the planner ordering decisions made, it is not possible to merge the outstanding **Camera.Off** token with the initial state. Thus it must be activated. | The token is inserted at the end of the timeline. At this point gaps are still possible.                                          | Finally, outstanding tokens are merged, thus completing the plan.                                                                 |

[So how do timelines map to execution?](http://code.google.com/p/trex-autonomy/wiki/TimelinesAndExecution)
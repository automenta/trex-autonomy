# Introduction #

Conflict files are written do disk when an problems arise during planning or execution. They contain a brief description of the problem, as well as a thorough dump of relevant data.

# File Placement and Naming #

Conflict files are placed in a _conflicts_ directory inside of the reactor-specific log directory.

Files are named similarly to reactorstate files:
> _ticknum_._stepnum_.conflict
Where _ticknum_ is the tick at which the conflict occurred and _stepnum_ is the planning iteration number. This translates to a new conflict file being generated before each constraint relaxation. For example, if on tick 123 the plan enters a conflicted state and is relaxed twice, the following files would be generated in the conflicts directory:
> `123.0.conflict`<br>
<blockquote><code>123.1.conflict</code>
These conflicts would correspond the the reactorstate files:<br>
<code>123.0.reactorstate</code><br>
<code>123.1.reactorstate</code></blockquote>

<h1>Format</h1>
# Introduction #

TREX can be configured to write various amounts of information to disk, both with the built-in EUROPA logging system as well as additional TREX-specific information.

# Log Directory Location #
Unless otherwise specified at runtime, the base path in which TREX logs are placed is defined in `$TREX_LOG_DIR`. Inside of this directory, log directories for each run are created with the format:
> _year_._day_._run_
Additionally, a symbolic link named _latest_ is made at runtime which points to the latest log.

# Log Directory Contents #

Inside of each of these directories are several files and subdirectories:
| **File/Directory Name** | **Description** |
|:------------------------|:----------------|
|`TREX.log`               | Primary TREX event log |
|`clock.log`              | _deprecated_    |
|`cpuStat.log`            | Reports CPU usage for deliberation and synchronization for each reactor. |
|`Debug.log`              | PLASMA debugging output. |
|`cfg`                    | Flat directory which contains copies of all .nddl files and .cfg files that were loaded at runtime.  |
|_agentname_`.log`        | A history of all transactions between the agent and the world. |

For each reactor there is an additional sub-directory with the format:
> _agentname_._reactorname_
Each of these directories contains the files:

| **File/Directory Name** | **Description** |
|:------------------------|:----------------|
|`debug.log`              | General debugging information relevant to this reactor |
|`plan.log`               | A high-level log of all of the plans created by this reactor |
|`reactor_states`         | A Flat directory of .reactorstate files |
|`plans`                  | Directory of sub-directories from individual ticks with very fine plan information from the EUROPA subsystem.  |
|`conflicts`              | A flat directory of .conflict files |





# Details #
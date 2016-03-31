# Introduction #

# File format #

The `.reactorstate` files are meant to be dumped at each tick, so they represent the minimal amount of information necessary to describe the current timelines and active tokens in a reactor. They are still logged in an ascii format to ease portability.

Each line in the file is either a timeline description or a token description. A timeline is always followed by its constituent tokens. All fields are separated by tabs.

**Timeline format:**
```
[timeline key]\t[timeline name]\t['I'|'E']
```

**Token format:**
```
\t[token key]\t[token name]\t[start lower]\t[start upper]\t[end lower]\t[end upper]
```

# Details #

During normal (non-conflicting) execution, a .reactorstate file is written to disk by each deliberative reactor when `Agent::handleTickStart` calls `reactor->doHandleTickStart`. This means that the state in the file is the state **gong into** that tick. This will be the _ticknum_.0.reactorstate file. If failures occur during synchronization or planning, additional .reactorstate files will be written.
# About

A small program that simulates turing machines and outputs the time complexity and space complexity of the provided turing machine.

# Run

You have to provide a configuration to the program. 
This configuration is responsible for the logic of the Turing Machine. 

```bash
turing_machine "config.tm"
```

# Configuration

The configuration is done via ".tm" files (for - you guessed it - **T**uring **M**achines).

Configuration files have the following structure:

```
// Comments are done via double slashes.

// The start state and end states for the TM.
START: q0
FINAL: q1, q2, q5

// All transitions of the TM.
// One line represents one rule.
TRANS:
Q,A>Q',B,L
Q,C>Q',D,R
// Q is the original state whereas Q' is the new state.
// The character we are currently reading is A whereas writing is B.
// Either L, N, or R for left, right, or neutral movement of the head.

// Input alphabet and band alphabet will be figured out automatically.
// Blank symbols can be represented by underscores (_).
```
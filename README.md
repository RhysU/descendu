descendu
========

In-progress, slow-moving draft of a lousy game inspired by Greed Corp
[![Build Status](https://travis-ci.com/RhysU/descendu.svg?branch=master)](https://travis-ci.com/github/RhysU/descendu)

Work remaining
--------------

In no particular order:

 * Convert serialized data into some sort of dump for visualization/debug
     * Sort out representation for various tile elements
     * Sort out coloring for different player ownership
 * Make world generate/dump drivable via stdio
     * Use pstreams to invoke neato
     * Use linenoise?  Or just rlwrap
 * Input of S-expression commands/actions
 * Destruction of a hex due to its height being reduced by one (e.g. mining)
 * Output of S-expression commands/actions
 * Determination of whether or not a particular player has pieces remaining
 * Destruction of a hex with "splash" destroying linked marginal hexes
 * Process a player's start of turn, including height and resource per mining
 * Enumerate/label units/resources which have not "moved" yet this turn
 * Commands/actions represented as S-expressions
 * Tweak BFS into something a-star-ish
 * Command/action enumeration and then subsequent processing
     * Movement of walker, possibly with attack
     * Creation of base
     * Building of new walkers
     * And so on, which will require replaying the original game a bit
 * Clean up and refactor (e.g. split headers from implementation files)
 * Hashing functions could use some love.
 * Nicer backtraces? https://github.com/bombela/backward-cpp
 * Upgrade Catch to latest version, involving some breakage fix
 * Monkey around a bit and determine next steps

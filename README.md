descendu
========

In-progress, slow-moving draft of a lousy game inspired by Greed Corp: [![Build
Status](https://travis-ci.org/RhysU/descendu.svg?branch=master)](https://travis-ci.org/RhysU/descendu)

Work remaining
--------------

In no particular order:

 * Convert serialized data into some sort of dump for visualization/debug
 * Tweak BFS into something a-star-ish
 * Determination of whether or not a particular player has pieces remaining
 * Destruction of a hex due to its height being reduced by one (e.g. mining)
 * Destruction of a hex with "splash" destroying linked marginal hexes
 * Process a player's start of turn, including height and resource per mining
 * Enumerate/label units/resources which have not "moved" yet this turn
 * Commands/actions represented as S-expressions
 * Output of S-expression commands/actions
 * Input of S-expression commands/actions
 * Command/action enumeration and then subsequent processing
     * Movement of walker, possibly with attack
     * Creation of base
     * Building of new walkers
     * And so on, which will require replaying the original game a bit
 * Wire up a REPL along with the dotty wackiness to permit manual driving
     * Look into interacting via Guile
     * Look into rolling my own and wrap with rlwrap
 * Clean up and refactor (e.g. split headers from implementation files)
 * Hashing functions could use some love.
 * Nicer backtraces? https://github.com/bombela/backward-cpp
 * Monkey around a bit and determine next steps

Visualization
-------------

 * Graphviz undirected neato layout seems to do something sane (see below)
 * Should be able to use height to scale size
 * Should be able to output to SVG with minor piping work
 * Might be able to embed that SVG within an autoreloading web page
   (or some other 'live' viewer)

 ```
graph G {
    h00 -- he
    h00 -- hne
    h00 -- hnw
    h00 -- hw
    h00 -- hsw
    h00 -- hse

    he -- hne
    he -- hse

    hw -- hnw
    hw -- hsw

    hne -- hnw
    hse -- hsw
}
```

descendu
========

In-progress, slow-moving draft of a lousy game inspired by Greed Corp: [![Build
Status](https://travis-ci.org/RhysU/descendu.svg?branch=master)](https://travis-ci.org/RhysU/descendu)

Work remaining
--------------

In no particular order:

 * Upgrade Catch to latest version, involving some breakage fix
 * Convert serialized data into some sort of dump for visualization/debug
     * Sort out graphviz representation for tile height
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
 * Monkey around a bit and determine next steps

Visualization
-------------

 * Graphviz undirected neato layout seems to do something sane (see below)
 * Should be able to use height to scale size
 * Should be able to output to SVG with minor piping work
 * Might be able to embed that SVG within an autoreloading web page
   (or some other 'live' viewer)

```
strict graph G {
    graph [layout=neato overlap=true]
    node [shape=hexagon height=0.2 width=0.2 fontsize=10]

    hn  [fillcolor=red style=filled width=0.2 height=0.2]

    # Group1
    h00  --  hen
    h00  --  hes
    h00  --  hn
    h00  --  hs
    h00  --  hwn
    h00  --  hws
    hen  --  hes
    hn   --  hen
    hn   --  hwn
    hs   --  hes
    hs   --  hws
    hwn  --  hws

    # Group2
    ah00  --  ahen
    ah00  --  ahes
    ah00  --  ahn
    ah00  --  ahs
    ah00  --  ahwn
    ah00  --  ahws
    ahen  --  ahes
    ahn   --  ahen
    ahn   --  ahwn
    ahs   --  ahes
    ahs   --  ahws
    ahwn  --  ahws

    # Aux
    hen    --  henes  --  hes
    hwn    --  hwnws  --  hws
    hws    --  hwss   --  hs
    hwnws  --  foo    --  hws
    foo    --  hwss

    # Linkage
    hes -- ahwn
}
```

# stdlib
This repository contains a minimal stdlib for freestanding environments (like a Operating System), which is ISO C standard conform, just as usual.
Note that this stdlib just contains support for functions that are OS independent! So don't ask why you cant open a File, you must implement it!
## your work
In the header include/os-dep.h are all prototypes of functions YOU must provide. The rest is work of the stdlib.
# License
I choose GLPv2 because of I'm using a bit Linux Code in a few functions that aren't trivial to implement. So if you replace the Linux code (every Linux function I used is marked before as //XXX: Linux function at (file path) ), you can just use the stdlib free.
# TODO
I'm still working on things like dynamic memory management. So that feature will follow in a future release.
# Contributing
Contributors are welcome to fix errors or add more C stdlib functions. Just create a pull request for it.

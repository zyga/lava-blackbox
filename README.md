Android LAVA Wrapper
====================

This module contains a collection of tools that run on an Android system and
simplify the automation of tests. Android includes a lot of built-in tests
but they differ in output formats and a way of executing them.

This tool, runs on an Android device, consumees a list of tests to execute,
executs each test in succession and saves the result as a *Linaro Dashboard
Bundle*. The bundle is a JSON file with pre-defined elements that can be
consumed by the LAVA stack, specifically by the *LAVA Dashboard*. You can learn
more about the bundle format on http://lava-dashboard.rtfd.org/ and about the
LAVA Dashboard on http://lava-dashboard.rtfd.org/

How to use
==========

To use this software you need to incorporate it in your build. The best way to
do that is to augment the manifest to pull code from the official github
repository: git://github.com/zyga/android-lava-wrapper.git

Once this step is done your build should include a new executable
lava-gtest-wrapper. Usually you won't execute it directly but it is important
to remember why it is there. The point of lava-gtest-wrapper is to execute a
test using the google test framework. (http://code.google.com/p/googletest/)
and convert the output to a Dashboard Bundle. 

Typically you will want to run many tests and for that you will use a script called
lava-wrapper. It is a simple one-shot executable that does everything it can.

How to grab results
===================

TBD

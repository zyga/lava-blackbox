Black Box LAVA testing for Android
=================================

This module contains a collection of tools that run on an Android system and
simplify the automation of tests. Android includes a lot of built-in tests but
they differ in output formats and a way of executing them.

How to use
==========

To use this software you need to incorporate it in your build. The best way to
do that is to augment the manifest to pull code from the official github
repository: git://github.com/zyga/lava-blackbox.git

For instance, to add it to one of the Linaro builds all I had to do was to
patch the manifest with the following diff:

```diff
    diff --git a/landing-snowball.xml b/landing-snowball.xml
    index f3764b4..7d53aa1 100644
    --- a/landing-snowball.xml
    +++ b/landing-snowball.xml
    @@ -10,6 +10,8 @@
                fetch="git://git.linaro.org/" />
       <remote  name="android_input_bridge"
                fetch="git://github.com/rperier/" />
    +  <remote  name="zyga"
    +           fetch="git://github.com/zyga/" />
       <default revision="refs/tags/android-4.1.1_r4"
                remote="aosp"
                sync-j="4" />
    @@ -20,6 +22,7 @@
       <!-- External extras -->
       <project path="packages/apps/0xbench" name="platform/packages/apps/0xbench" revision="linaro-master" />
       <project path="external/android_input_bridge" name="android_input_bridge" remote="android_input_bridge" revision="master" />
    +  <project path="external/lava-blackbox" name="lava-blackbox" remote="zyga" revision="master" />
     
       <!-- Linaro extras -->
       <project path="packages/apps/DisableSuspend" name="platform/packages/apps/DisableSuspend" revision="master" />
```

Having done that run repo sync to fetch the new repository.

It is important to know that lava-blackbox runs _only_ in builds made with
*TARGET_BUILD_VARIANT=tests*. If in doubt have a look at my build scripts at
http://github.com/zyga/android-build-scripts The configurations ending with
-tests build the proper variant. 

Once you have a build transfer it onto your device (*make flash* if you have
used my build scripts) and get adb shell or direct serial shell to your device.
You will need to run as root so you may need to use su first. This is also
patched in Linaro builds.

To run all of the tests at once simply run:
    
    $ lava-blackbox --run-all-tests

Observe the output as tests fly by to know where each one gets saved but in
general all results will be saved to /sdcard/LAVA.

How to grab results
===================

You can fetch each result with adb pull but ideally you will use
lava-android-test to run this and obtain a single bundle directly. Support for
doing that has landed in trunk as of revision 205 (it will be released in the
next few days/weeks but feel free to grab that revision from trunk directly)

Having the proper code around  use lava-android-test to run the 'blackbox' test
and save the bundle by passing the -o option. Like this:

    $ lava-android-test run blackbox -o blackbox.json

Which tests are supported
=========================

All of the tests that use the Google test framework are supported. Support for
additional tests can be added in the future. You can add support for additional
tests by simply shipping a wrapper finder that will identify new tests.

How it works
============

This tool, runs on an Android device, once triggered it requires no outside
help to produce test results. It follows this simple algorithm to complete its
task:

 1. Any file named \*\_test or \*\-tests is considered a possible candidate
 2. Each candidate is offered to a subsequent wrapper-finders. Wrapper finders
    are small programs that are saved to /system/bin and follow a simple naming
    convention lava-wrapper-finder-\*
 3. The first wrapper finder that offers a non-empty response wins. The text
    returned by the last wrapper finder is used to know which wrapper should be
    used to run the specified test
 4. The wrapper is started with the test name as argument and the *-o* option,
    to select the output file with the test results. 
 5. The wrapper does whatever is needed to execute the tests, interpret the
    results and save the bundle to the requested file.
 6. The loop continues with subsequent test candidate to point 2

There are a few other things to know about:

 * The tool creates a directory to store all of the bundles. By default that is
   */sdcard/LAVA* but it can be overridden on the command line. Inside that
   directory, each time the script runs, a new unique directory is created.
   Inside that directory, in turn, are all of the bundles created by subsequent
   wrappers.

 * The tool passes *-r* option to each wrapper to produce human readable output.
 
 * There is no way for two wrapper finders to offer support for a single test,
   if that happens the result is not deterministic and depends on the ordering
   of file system traversal.

 * If a test or test wrapper hangs the whole tool will hang as well.

Glossary
========

*lava-blackbox*: Main executable of this projnect that should be launched (on
an Android device) to start testing.

*wrapper finders*: Small programs that help *lava-blackbox* to recognize valid
tests and suggests which *wrappers* should be used to process that test.
lava-blackbox ships with one wrapper finder by default,
lava-wrapper-finder-gtest that recognizes certain gtest-based tests. All
wrapper finders must be placed in /system/bin and must follow the naming
convention lava-wrapper-finder-\*

*wrappers*: Small utilities that can convert output of a certain kind of tests
into the *Linaro Dashboard Bundle* format. Each wrapper has a standardized
interface and must accept -o and -r options as well as a single argument that
points to the test to execute. The wrapper must execute the test in any means
necessary and create a bundle with the processed test results.
lava-blackbox ships with lava-gtest-wrapper that knows how to execute
and parse gtest-based tests.

*Linaro Dashboard Bundle*: A JSON-based data interchange format designed to
store test results and rich meta-data. This format is consumed by the LAVA
Dashboard. The format is documented at
http://linaro-dashboard-bundle.readthedocs.org/

*LAVA Dashboard*: Part of LAVA that stores displays test results. You can think
of it a big web-accessible archive. You can learn more about it at
http://lava-dashboard.rtfd.org/

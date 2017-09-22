========================================================================
    CONSOLE APPLICATION : EnigmaSimulator Project Overview
========================================================================

/////////////////////////////////////////////////////////////////////////////

Welcome to the Enigma-Simulator!

This console application simulates the cipher machine used in the second world
war by the Germans.

Wikipedia-article to the Enigma Machine:
https://en.wikipedia.org/wiki/Enigma_machine

The application lets you choose the type and number of rotators used in the
machine.
Each rotor type has a different mixed up order of the alphabet on it.

When you type a letter on the machine, the first rotor will rotate one step.
If a rotator has made a full rotation the next rotator will rotate one step
(like an old mileage counter)

The daily key and the message key are used to create a better encryption.

The daily key will be changed every day and the message key is individual for
every message.

These keys set up the rotators of the machine further:

For example, if the daily key is ABDC then:
the first rotator doesn’t rotate
the second rotates one time
the third rotates three times
and the fourth rotates two times

So, the daily key must be as long as the numbers of rotators used.

The message key will first be encrypted/decrypted with the daily key set up
and then set.

After that the machine is set up right and we can decode or encode the message.

After one round, you will be asked to continue or to quit.
On continuation, the machine will be reset and the daily key will be used again
(if you don't change it)

To check if the everything works right you can encrypt you message on the first round
and decrypt it on the second round with unchanged settings.

Happy encoding and decoding.

/////////////////////////////////////////////////////////////////////////////


EnigmaSimulator .vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

EnigmaSimulator .vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

EnigmaSimulator .cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named EnigmaSimulator.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////

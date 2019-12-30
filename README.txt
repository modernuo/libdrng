========================================================================
DRNG Library
========================================================================
Welcome to the DRNG Library. This is a simple library aimed at bringing 
suport for the rdrand and rdseed instructions feature of Intel 
processors, starting with the 3rd Generation Intel Core(tm) processor, 
to users with toolchains that do not support these new features. For 
more information on these instructions, please visit: 

https://software.intel.com/en-us/articles/intel-digital-random-number-generator-drng-software-implementation-guide 

These instructions are an innovative hardware approach to high-quality, 
high-performance entropy and random number generation.

Because not all compiler tool chains support these new
instructions, this library was created to facilitate easy access to it.
The idea is simple: link to a pre-built static library, provided in the
lib directory, and enjoy the new feature!

Documentation is stored in doc/--Point your browser to 
doc/html/index.html to get started.  

========================================================================
How to Build:
========================================================================

Windows
-------

You will need either:

	* Visual Studio* 2019
	-or-
	* The Intel compiler, if you plan on using an older version of VS
	
Steps:

1.	Open drng.sln in Visual Studio
2.	Build the drng project first to generate the library libdrng.dll
3.	Build the test project to generate test.exe
4.	Execute test.exe from Windows Command Prompt

Linux*
------
	
You will need either gcc* or the Intel compiler.

$ ./configure
$ make
$ make install

And then execute ./test

OS X*
-----

You will need to install Xcode*.

$ ./configure
$ make
$ make install

And then execute ./test

==========================================================================================

Copyright(C) 2015 Intel Corporation. All rights reserved.

*Other names and brands may be claimed as the property of others


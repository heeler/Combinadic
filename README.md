Combinadic
==========

CSet is a C++ class for generating a combinadic and converting a combinadic to the corresponding 
integer indexes. Follow the [link](https://en.wikipedia.org/wiki/Combinatorial_number_system) 
for an indepth discussion on Combinadics (Combinaatorial number systems).

As A Python Module
------------------

The project currently has a Jamfile (Boost::Build) that will use clang++ and the 
Boost::Python wrappers to build combinadic.so (shared library) that is loadable 
as a python module. The Jamfile can be use as a template for building other C++ 
projects to export to python. The command to build the module is:
> b2


Dependencies
------------

If you wish to run the unit tests you will need to install the googletest libraries and link 
against them in the compile. The makefile is currently setup to use a framework (OSX thing)
but for linux change the **-F (path to frameworks folder) -framework gtest** flags to **-L (path to lib folder) -lgtest**.

Useage in Code
--------------

The easiest way to understand how to call and use the Class is to look at the unit tests.

Googletest
----------

Unit tests for the C++ classes have been implemented in Googletest, 
 [Googletest library](http://code.google.com/p/googletest/) the latest
version of which can be downloaded
[here](http://code.google.com/p/googletest/downloads/list).

OSX:
Build the gtest.framework (remember to add the C++11 flags) and include it in your project.
The UIS_Gtest target should then build and the tests can be run

Unix:
Compiler options for C++11 are clang++ (Version >= 3.0) or g++ (Version >= 4.7).
In the Makefile set CXX_NAME to either CLANGPP or GPP and check the paths to the 
compiler tool to make sure a different version is not accidently being called.
Once the Makefile has the appropriate values entered then simply type make in the 
main project directory (where the Makefile lives).

Contact
-------

If you have any questions feel free to contact me. --Jamie
	* email: jamie.sherman@sciex.com



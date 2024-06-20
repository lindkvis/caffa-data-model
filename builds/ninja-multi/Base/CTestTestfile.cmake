# CMake generated Testfile for 
# Source directory: /home/glindkvist/Projects/caffa-data-model/Base
# Build directory: /home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/Base
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(caffaBase_UnitTests "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/bin/caffaBase_UnitTests")
set_tests_properties(caffaBase_UnitTests PROPERTIES  _BACKTRACE_TRIPLES "/home/glindkvist/Projects/caffa-data-model/Base/CMakeLists.txt;56;add_test;/home/glindkvist/Projects/caffa-data-model/Base/CMakeLists.txt;0;")
subdirs("Base_UnitTests")

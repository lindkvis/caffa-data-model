# CMake generated Testfile for 
# Source directory: /home/glindkvist/Projects/caffa-data-model
# Build directory: /home/glindkvist/Projects/caffa-data-model/builds/ninja-multi
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[caffaDataModel_UnitTests]=] "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/bin/caffaDataModel_UnitTests")
set_tests_properties([=[caffaDataModel_UnitTests]=] PROPERTIES  _BACKTRACE_TRIPLES "/home/glindkvist/Projects/caffa-data-model/CMakeLists.txt;104;add_test;/home/glindkvist/Projects/caffa-data-model/CMakeLists.txt;0;")
subdirs("Base")
subdirs("DataModel_UnitTests")

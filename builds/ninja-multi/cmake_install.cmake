# Install script for directory: /home/glindkvist/Projects/caffa-data-model

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/Base/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/DataModel_UnitTests/cmake_install.cmake")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    foreach(file
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1.0.0"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1"
        )
      if(EXISTS "${file}" AND
         NOT IS_SYMLINK "${file}")
        file(RPATH_CHECK
             FILE "${file}"
             RPATH "")
      endif()
    endforeach()
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
      "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/Debug/libcaffaDataModel.so.1.0.0"
      "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/Debug/libcaffaDataModel.so.1"
      )
    foreach(file
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1.0.0"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1"
        )
      if(EXISTS "${file}" AND
         NOT IS_SYMLINK "${file}")
        file(RPATH_CHANGE
             FILE "${file}"
             OLD_RPATH "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/Debug:"
             NEW_RPATH "")
        if(CMAKE_INSTALL_DO_STRIP)
          execute_process(COMMAND "/usr/bin/strip" "${file}")
        endif()
      endif()
    endforeach()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    foreach(file
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1.0.0"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1"
        )
      if(EXISTS "${file}" AND
         NOT IS_SYMLINK "${file}")
        file(RPATH_CHECK
             FILE "${file}"
             RPATH "")
      endif()
    endforeach()
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
      "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/Release/libcaffaDataModel.so.1.0.0"
      "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/Release/libcaffaDataModel.so.1"
      )
    foreach(file
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1.0.0"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1"
        )
      if(EXISTS "${file}" AND
         NOT IS_SYMLINK "${file}")
        file(RPATH_CHANGE
             FILE "${file}"
             OLD_RPATH "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/Release:"
             NEW_RPATH "")
        if(CMAKE_INSTALL_DO_STRIP)
          execute_process(COMMAND "/usr/bin/strip" "${file}")
        endif()
      endif()
    endforeach()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    foreach(file
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1.0.0"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1"
        )
      if(EXISTS "${file}" AND
         NOT IS_SYMLINK "${file}")
        file(RPATH_CHECK
             FILE "${file}"
             RPATH "")
      endif()
    endforeach()
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES
      "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/RelWithDebInfo/libcaffaDataModel.so.1.0.0"
      "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/RelWithDebInfo/libcaffaDataModel.so.1"
      )
    foreach(file
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1.0.0"
        "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so.1"
        )
      if(EXISTS "${file}" AND
         NOT IS_SYMLINK "${file}")
        file(RPATH_CHANGE
             FILE "${file}"
             OLD_RPATH "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/RelWithDebInfo:"
             NEW_RPATH "")
        if(CMAKE_INSTALL_DO_STRIP)
          execute_process(COMMAND "/usr/bin/strip" "${file}")
        endif()
      endif()
    endforeach()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so")
      file(RPATH_CHECK
           FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so"
           RPATH "")
    endif()
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/Debug/libcaffaDataModel.so")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so")
      file(RPATH_CHANGE
           FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so"
           OLD_RPATH "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/Debug:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so")
      file(RPATH_CHECK
           FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so"
           RPATH "")
    endif()
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/Release/libcaffaDataModel.so")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so")
      file(RPATH_CHANGE
           FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so"
           OLD_RPATH "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/Release:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so")
      endif()
    endif()
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so")
      file(RPATH_CHECK
           FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so"
           RPATH "")
    endif()
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/RelWithDebInfo/libcaffaDataModel.so")
    if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so" AND
       NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so")
      file(RPATH_CHANGE
           FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so"
           OLD_RPATH "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/lib/RelWithDebInfo:"
           NEW_RPATH "")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libcaffaDataModel.so")
      endif()
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "/home/glindkvist/Projects/caffa-data-model/cafAppEnum.h"
    "/home/glindkvist/Projects/caffa-data-model/cafChildArrayField.h"
    "/home/glindkvist/Projects/caffa-data-model/cafChildArrayField.inl"
    "/home/glindkvist/Projects/caffa-data-model/cafChildArrayFieldAccessor.h"
    "/home/glindkvist/Projects/caffa-data-model/cafChildFieldHandle.h"
    "/home/glindkvist/Projects/caffa-data-model/cafChildField.h"
    "/home/glindkvist/Projects/caffa-data-model/cafChildField.inl"
    "/home/glindkvist/Projects/caffa-data-model/cafChildFieldAccessor.h"
    "/home/glindkvist/Projects/caffa-data-model/cafDataFieldAccessor.h"
    "/home/glindkvist/Projects/caffa-data-model/cafDataField.h"
    "/home/glindkvist/Projects/caffa-data-model/cafField.h"
    "/home/glindkvist/Projects/caffa-data-model/cafFieldCapability.h"
    "/home/glindkvist/Projects/caffa-data-model/cafFieldHandle.h"
    "/home/glindkvist/Projects/caffa-data-model/cafObjectMacros.h"
    "/home/glindkvist/Projects/caffa-data-model/cafObjectCollector.h"
    "/home/glindkvist/Projects/caffa-data-model/cafObjectPerformer.h"
    "/home/glindkvist/Projects/caffa-data-model/cafObjectHandle.h"
    "/home/glindkvist/Projects/caffa-data-model/cafPortableDataType.h"
    "/home/glindkvist/Projects/caffa-data-model/cafFieldProxyAccessor.h"
    "/home/glindkvist/Projects/caffa-data-model/cafChildArrayFieldHandle.h"
    "/home/glindkvist/Projects/caffa-data-model/cafMethodHandle.h"
    "/home/glindkvist/Projects/caffa-data-model/cafDefaultObjectFactory.h"
    "/home/glindkvist/Projects/caffa-data-model/cafObjectFactory.h"
    "/home/glindkvist/Projects/caffa-data-model/cafObjectHandlePortableDataType.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/glindkvist/Projects/caffa-data-model/builds/ninja-multi/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

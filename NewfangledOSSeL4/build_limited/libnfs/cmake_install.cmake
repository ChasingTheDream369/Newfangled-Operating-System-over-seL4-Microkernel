# Install script for directory: /tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/libnfs

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_limited/staging")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/nfsc")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include" TYPE DIRECTORY FILES "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/libnfs/include/nfsc")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/nfsc/libnfs-raw-mount.h;/usr/local/include/nfsc/libnfs-raw-nfs.h;/usr/local/include/nfsc/libnfs-raw-nlm.h;/usr/local/include/nfsc/libnfs-raw-nsm.h;/usr/local/include/nfsc/libnfs-raw-portmap.h;/usr/local/include/nfsc/libnfs-raw-rquota.h")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/nfsc" TYPE FILE FILES
    "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/libnfs/mount/libnfs-raw-mount.h"
    "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/libnfs/nfs/libnfs-raw-nfs.h"
    "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/libnfs/nlm/libnfs-raw-nlm.h"
    "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/libnfs/nsm/libnfs-raw-nsm.h"
    "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/libnfs/portmap/libnfs-raw-portmap.h"
    "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/libnfs/rquota/libnfs-raw-rquota.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/cmake/libnfs/FindNFS.cmake;/usr/local/lib/cmake/libnfs/libnfs-config-version.cmake")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib/cmake/libnfs" TYPE FILE FILES
    "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/libnfs/cmake/FindNFS.cmake"
    "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_limited/libnfs/libnfs-config-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/pkgconfig/libnfs.pc")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib/pkgconfig" TYPE FILE FILES "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_limited/libnfs/libnfs.pc")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_limited/libnfs/mount/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_limited/libnfs/nfs/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_limited/libnfs/nfs4/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_limited/libnfs/nlm/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_limited/libnfs/nsm/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_limited/libnfs/portmap/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_limited/libnfs/rquota/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_limited/libnfs/lib/cmake_install.cmake")

endif()


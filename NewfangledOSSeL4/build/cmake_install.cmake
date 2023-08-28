# Install script for directory: /tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/staging")
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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/kernel/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/elfloader-tool/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/libsel4/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/projects/aos/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/projects/libcpio/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/projects/libelf/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/projects/libnfs/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/projects/libpicotcp/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/projects/libsel4sync/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/projects/libutils/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/projects/musllibc/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/projects/sel4runtime/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")

# Install script for directory: /tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/projects/aos

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/staging")
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
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/apps/tty_test/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/apps/sosh/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/apps/syscall_test/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/apps/malloc_test/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/apps/file_test/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/sos/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/libaos/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/libclock/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/libethernet/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/libsel4cspace/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/libserial/cmake_install.cmake")
  include("/tmp_amd/kamen/export/kamen/1/z5284381/comp9242/group-08/build_32/projects/aos/libsosapi/cmake_install.cmake")

endif()


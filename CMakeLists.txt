cmake_minimum_required(VERSION 3.14)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0005 NEW) 
  cmake_policy(SET CMP0003 NEW)   
endif(COMMAND cmake_policy)

project(iLaundry_hmi VERSION 0.1 LANGUAGES CXX)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)

IF ("${INSTALL_DIR}" STREQUAL "")
 MESSAGE ("[INSTALL] set install_dir to /usr")
 SET(CMAKE_INSTALL_PREFIX /usr)
ELSE ()
 MESSAGE ("[INSTALL] set install_dir to input ${INSTALL_DIR}")
 SET(CMAKE_INSTALL_PREFIX ${INSTALL_DIR})
ENDIF ()

IF (NOT CMAKE_BUILD_TYPE)
 SET(CMAKE_BUILD_TYPE "DEBUG")
 MESSAGE("FORCING DEBUG MODE!")
ENDIF (NOT CMAKE_BUILD_TYPE)

IF (CMAKE_BUILD_TYPE MATCHES RELEASE)
  add_definitions(-DNDEBUG)
  MESSAGE("-- ADDING NDEBUG FLAG!")
ENDIF()

SET(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -D_REENTRANT")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3 -D_REENTRANT")

ADD_SUBDIRECTORY(src)

IF (NOT "${CMAKE_SYSTEM_PROCESSOR}" MATCHES "arm")
  #ADD_SUBDIRECTORY(gtests)
ENDIF()

FIND_PACKAGE(Doxygen)

ADD_CUSTOM_TARGET (distclean @echo cleaning cmake files)

IF (UNIX)
  ADD_CUSTOM_COMMAND(
    COMMENT "distribution clean"
    COMMAND make ARGS clean
    COMMAND rm ARGS -rf ${CMAKE_SOURCE_DIR}/build/*

    TARGET  distclean
  )
ELSE(UNIX)
  ADD_CUSTOM_COMMAND(
    COMMENT "distclean only implemented in unix"
    TARGET  distclean
  )
ENDIF(UNIX)

ADD_CUSTOM_TARGET (uninstall @echo uninstall package)

IF (UNIX)
  ADD_CUSTOM_COMMAND(
    COMMENT "uninstall package"
    COMMAND xargs ARGS rm < install_manifest.txt

    TARGET  uninstall
  )
ELSE(UNIX)
  ADD_CUSTOM_COMMAND(
    COMMENT "uninstall only implemented in unix"
    TARGET  uninstall
  )
ENDIF(UNIX)

IF (UNIX)
 SET(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_DEBIAN_PACKAGE_ARCHITECTURE}")
 SET(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
 SET(CPACK_PACKAGING_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX})
 SET(CPACK_GENERATOR "DEB")
 SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "jsueprez@icloud.com")
 SET(CPACK_SET_DESTDIR "ON")  # Necessary because of the absolute install paths
 SET(CPACK_DEBIAN_PACKAGE_DEPENDS "")

 SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/control_extra/postinst")
 SET(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/control_extra/preinst")
 SET(CPACK_DEBIAN_PACKAGE_DEPENDS "lcms (>= 2.7), libfftw (>= 3.3.4), libtiff5 (>= 4.0.7), imagemagick (>= 7.0.2), redis (>= 3.0.2), libhiredis0.13 (>= 0.13.1-r0)")

 INCLUDE(CPack)
ELSE(UNIX)
 ADD_CUSTOM_COMMAND(
   COMMENT "packaging only implemented in unix"
   TARGET  uninstall
 )
ENDIF(UNIX)

# Copyright © 2022 Jason Stephenson
#
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.15)

project(unistdcpp VERSION 1.0.0 DESCRIPTION "C++ Support Library for POSIX")

file(GLOB UNISTD_SRC_FILES "src/*.cpp")
file(GLOB UNISTD_HDR_FILES "include/unistd/*.h")

add_library(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE "${UNISTD_SRC_FILES}")

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${UNISTD_HDR_FILES}")

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/unistd>
  )

include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/unistd
  )

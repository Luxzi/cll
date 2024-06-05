cmake_minimum_required(VERSION 3.16)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "gcc")
set(CMAKE_EXPORT_COMPILE_COMMANDS true)
project(LinkedList)

include(FetchContent)

if (CMAKE_VERSION VERSION_GREATER_EQUAL "3.24.0")
  cmake_policy(SET CMP0135 NEW)
endif()

FetchContent_Declare(
  unity
  URL https://github.com/ThrowTheSwitch/Unity/archive/refs/tags/v2.6.0.zip
)

FetchContent_MakeAvailable(unity)

set(CMAKE_MAKE_PROGRAM "make")
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_BUILD_TYPE Release)


option(BUILD_DOCS "Building documentation for ProjectAlpha and dependencies" ON)
if (BUILD_DOCS)
  message(STATUS "Building documentation is enabled")
  find_package(Doxygen REQUIRED doxygen)
  set(DOXYGEN_FILE_PATTERNS *.c,*.cpp,*.h,*.hpp,*.ipp)
  set(DOXYGEN_BUILTIN_STL_SUPPORT YES)
  set(DOXYGEN_DISTRIBUTE_GROUP_DOC YES)
  set(DOXYGEN_EXAMPLE_PATH "${PROJECT_SOURCE_DIR}/examples")
  set(DOXYGEN_EXCLUDE "${PROJECT_BINARY_DIR}")
  set(DOXYGEN_EXTRACT_ALL YES)
  set(DOXYGEN_GENERATE_TREEVIEW YES)
  set(DOXYGEN_QUIET YES)
  set(DOXYGEN_RECURSIVE YES)
  set(DOXYGEN_REFERENCED_BY_RELATION YES)
  set(DOXYGEN_REFERENCES_RELATION YES)
  set(DOXYGEN_SORT_BY_SCOPE_NAME YES)
  set(DOXYGEN_SORT_MEMBER_DOCS YES)
  set(DOXYGEN_SOURCE_BROWSER YES)
  set(DOXYGEN_STRIP_CODE_COMMENTS NO)
  set(DOXYGEN_GENERATE_LATEX YES)
  set(DOXYGEN_GENERATE_HTML YES)
  set(DOXYGEN_GENERATE_MAN YES)
  doxygen_add_docs(docs
                 "${PROJECT_SOURCE_DIR}/src"
                 "${PROJECT_SOURCE_DIR}/include"
                 ALL
                 COMMENT "Generate documentation")
else()
  message(STATUS "Building documentation is disabled")
endif()

file(GLOB SRC_FILES
  ${PROJECT_SOURCE_DIR}/src/*.c
  ${unity_SOURCE_DIR}/src/*.c)

include_directories(include)
include_directories(${unity_SOURCE_DIR}/src)

add_executable(cll_test
  tests/cll_test.c
  tests/log.c
  ${SRC_FILES}
)

target_compile_options(cll_test
  PUBLIC "-DLOG_USE_COLOR"
)
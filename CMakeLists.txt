cmake_minimum_required(VERSION 3.15.0)
project(pslib LANGUAGES CXX VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
include_directories("./include")

# Install Catch2
Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${catch2_SOURCE_DIR}/contrib/")
include(Catch)
include(CTest)

# Building a monolithic test executable does not work
# since there are duplicate variables all over the library.
# Instead, make one executable per each test.

file(GLOB_RECURSE testFiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cc)
foreach(file ${testFiles})
  if(${file} MATCHES ".*\.test\.cc$")
    string(REPLACE ".test.cc" "__test" testTarget ${file})
    string(REPLACE "/" "__" testTarget ${testTarget})

    add_executable(${testTarget} ${file})
    target_link_libraries(${testTarget} Catch2::Catch2)
    catch_discover_tests(${testTarget})
  else()
    # Deal with VS Code complaining about include error.
    string(REPLACE ".cc" "" sourceTarget ${file})
    string(REPLACE "/" "__" sourceTarget ${sourceTarget})

    add_library(${sourceTarget} ${file})
  endif()
endforeach()

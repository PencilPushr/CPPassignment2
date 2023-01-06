# CMakeList.txt : CMake project for CMake_Assignment2, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CMake_Assignment2")

# Add source to this project's executable.
add_executable (CMake_Assignment2 "CMake_Assignment2.cpp" "CMake_Assignment2.h" 
									"src/Manager.cpp" "src/Manager.h" 
									"src/User.cpp" "src/User.h" 
									"src/Person.cpp" "src/Person.h" 
									"src/ReadTweets.cpp" "src/ReadTweets.h"
									"util/MovingAverage.h"  "src/IteratorForTweets.h" "util/LineCounter.h" "src/Application.h" "src/Application.cpp")

#Forcing C++20
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMake_Assignment2 PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

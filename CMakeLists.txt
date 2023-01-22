# CMakeList.txt : CMake project for BadTwitter, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("BadTwitter")


file(GLOB source_files CONFIGURE_DEPENDS
            "*.h"
            "*.cpp"
            "src/*.cpp"
            "src/*.h"
            "util/*.cpp"
            "util/*.h"
)

# Add source to this project's executable.
# add_executable (BadTwitter "BadTwitter.cpp" "BadTwitter.h" "src/Manager.cpp" "src/Manager.h" )
add_executable (BadTwitter ${source_files} "src/FileHandler.h" "src/FileHandler.cpp"  "src/Interface/ManagerOptions.h" "src/Interface/UserOptions.h" "src/Interface/LoginOptions.h" "src/Interface/LoginOptions.cpp" "src/Interface/ManagerOptions.cpp" "src/Interface/UserOptions.cpp" "util/inputSanitiser.h" "util/inputSanitise.cpp" "util/MovingAverage.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BadTwitter PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

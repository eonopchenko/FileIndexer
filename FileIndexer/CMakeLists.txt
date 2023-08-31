# CMakeList.txt : CMake project for FileIndexer, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (FileIndexer "Main.cpp" "Main.h" "source/FileIndex.cpp" "include/FileIndex.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET FileIndexer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

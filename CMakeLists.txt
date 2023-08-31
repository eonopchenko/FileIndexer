# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("FileIndexer")

link_directories("FileIndexer/third_party/boost_1_83_0/bin/x64/lib")

# Include sub-projects.
add_subdirectory ("FileIndexer")
add_subdirectory ("UnitTests")

target_include_directories("FileIndexer" PRIVATE "FileIndexer/include")

SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "FileIndexer/third_party/boost_1_83_0/boost")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "FileIndexer/third_party/boost_1_83_0/bin/x64/lib")

target_include_directories("FileIndexer" PRIVATE "FileIndexer/third_party/boost_1_83_0")
target_include_directories("FileIndexer" PRIVATE "FileIndexer/third_party/cpp-text-table")

#find_package(Boost COMPONENTS regex system range filesystem REQUIRED)

target_link_libraries("FileIndexer"
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_RANGE_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_REGEX_LIBRARY}
)

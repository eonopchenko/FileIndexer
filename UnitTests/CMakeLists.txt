set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")

project ("UnitTests")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

link_directories("googletest-1.14.0/build/lib/Release")

add_executable("UnitTests" "pch.cpp" "test.cpp" "../FileIndexer/include/FileIndex.h" "../FileIndexer/source/FileIndex.cpp")

target_include_directories("UnitTests" PRIVATE "googletest-1.14.0/googletest/include")
target_include_directories("UnitTests" PRIVATE "../FileIndexer/include")

target_link_libraries("UnitTests" gtest gtest_main)

target_include_directories("UnitTests" PRIVATE "../FileIndexer/third_party/boost_1_83_0")
target_include_directories("UnitTests" PRIVATE "../FileIndexer/third_party/cpp-text-table")

target_link_libraries("UnitTests"
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_RANGE_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_REGEX_LIBRARY}
)

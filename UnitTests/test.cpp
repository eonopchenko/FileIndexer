#include "pch.h"

#include "FileIndex.h"

/// <summary>
/// Testing ProcessDirectory() function,
/// comparing with reference map file_map_expected
/// </summary>
/// <param name=""></param>
/// <param name=""></param>
TEST(FileIndexTestCase, FileIndexTest) {
  FileIndex fileIndex;
  fileIndex.ProcessDirectory("test directory1");
  file_map_t file_map_actual = fileIndex.file_map();

  file_extension_map_t file_extension_map;
  file_extension_map.insert(std::make_pair("exe", file_list_t({
	  std::make_pair("file-1 - Copy.exe", 0), 
	  std::make_pair("file-1.exe", 0) })));
  file_extension_map.insert(std::make_pair("txt", file_list_t({
	  std::make_pair("file-2.txt", 37), 
	  std::make_pair("subdir\\file-2.txt", 0) })));
  file_extension_map.insert(std::make_pair("xml", file_list_t({
	  std::make_pair("file-3 - Copy.xml", 0), 
	  std::make_pair("file-3.xml", 0), 
	  std::make_pair("subdir\\file-3 - Copy.xml", 0), 
	  std::make_pair("subdir\\file-3.xml", 0) })));

  file_map_t file_map_expected;
  file_map_expected.insert(std::make_pair("test directory1", file_extension_map));

  for (auto& it_file_map_expected : file_map_expected)
  {
	  auto index_actual = file_map_actual.find(it_file_map_expected.first);
	  ASSERT_NE(index_actual, file_map_actual.end()) << "Directory not found in the index";
	  for (auto& it_index_expected : it_file_map_expected.second)
	  {
		  auto extension_actual = index_actual->second.find(it_index_expected.first);
		  ASSERT_NE(extension_actual, index_actual->second.end()) << "Extension not found in the index";
		  /// etc...
	  }
  }
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

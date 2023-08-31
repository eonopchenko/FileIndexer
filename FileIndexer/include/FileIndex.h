#pragma once

#include <string>
#include <unordered_map>

typedef std::pair<std::string, size_t> file_name_size_pair_t;
typedef std::vector<file_name_size_pair_t> file_list_t;
typedef std::unordered_map<std::string, file_list_t> file_extension_map_t;
typedef std::unordered_map<std::string, file_extension_map_t> file_map_t;

/// <summary>
/// FileIndex class is intended to recursively 
/// build file index for the given target directory
/// </summary>
class FileIndex
{
public:
	FileIndex() = default;
	void ProcessDirectory(const std::string &path);
	void ListFiles(const std::string &extension);
	file_map_t file_map() const { return _file_map; }
private:
	/// Map [
	///		key->path, 
	///		value->Map [
	///			key->extension,
	///			value->vector (files list)
	///		]]
	file_map_t _file_map;
};

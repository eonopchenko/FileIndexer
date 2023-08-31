#include "FileIndex.h"

#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/regex.hpp>

#include <TextTable.h>

#include <iostream>

#define TEXTTABLE_ENCODE_MULTIBYTE_STRINGS
#define TEXTTABLE_USE_EN_US_UTF8

boost::regex fileExtensionPattern("[^.]+$");

/// <summary>
/// Recursively building file index 
/// in target directory specified by path
/// </summary>
/// <param name="path">Target directory path</param>
void FileIndex::ProcessDirectory(const std::string& path)
{
    /// Test if path exists, in the map index is already in
    /// Test if target is not directory (or directory doesn't exist)
    if ((_file_map.find(path) != _file_map.end()) || !boost::filesystem::is_directory(path))
    {
        return;
    }

    std::unordered_map<std::string, file_list_t> currentPathFileMap;
    /// Recursively iterate over the target directory
    for (auto& entry : boost::make_iterator_range(boost::filesystem::recursive_directory_iterator(path), {}))
    {
        if (boost::filesystem::is_regular_file(entry.path()))
        {
            std::string filePath = entry.path().string();

            std::string relativeFilePath = filePath.substr(path.length() + 1, filePath.length() - path.length());
            boost::smatch result;
            /// Get file extension using regex
            if (boost::regex_search(relativeFilePath, result, fileExtensionPattern))
            {
                std::string fileExtension(result[0].first, result[0].second);

                size_t fileSize = boost::filesystem::file_size(entry.path());

                file_name_size_pair_t filePathSizePair = std::make_pair(relativeFilePath, fileSize);

                if (currentPathFileMap.find(fileExtension) == currentPathFileMap.end())
                {
                    file_list_t fileList = { filePathSizePair };
                    currentPathFileMap.insert(std::make_pair(fileExtension, fileList));
                }
                else
                {
                    currentPathFileMap.at(fileExtension).push_back(filePathSizePair);
                }
            }
        }
    }

    _file_map.insert(std::make_pair(path, currentPathFileMap));
}

/// <summary>
/// Prints file index for target file extension
/// </summary>
/// <param name="extension">File extension</param>
void FileIndex::ListFiles(const std::string& extension)
{
    std::cout << "*." << extension << " files:" << std::endl;

    TextTable t('-', '|', '+');
    t.add("PATH");
    t.add("SIZE");
    t.endOfRow();

    for (auto pathIt = _file_map.begin(); pathIt != _file_map.end(); ++pathIt)
    {
        std::cout << pathIt->first << ":" << std::endl;
        if (pathIt->second.find(extension) != pathIt->second.end())
        {
            file_list_t& files = pathIt->second.at(extension);
            for (auto filesIt = files.begin(); filesIt != files.end(); ++filesIt)
            {
                t.add(filesIt->first);
                t.add(std::to_string(filesIt->second));
                t.endOfRow();
            }
        }
    }
    t.setAlignment(2, TextTable::Alignment::RIGHT);
    std::cout << t << std::endl;
}

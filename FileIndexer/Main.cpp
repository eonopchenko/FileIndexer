// FileIndexer.cpp : Defines the entry point for the application.
//

#include "Main.h"
#include "FileIndex.h"

/// <summary>
/// User-function just to demo FileIndex class
/// </summary>
/// <returns></returns>
int main()
{
	FileIndex fileIndex;
	fileIndex.ProcessDirectory("C:\\test directory1");
	fileIndex.ListFiles("exe");
	fileIndex.ListFiles("exa");
	fileIndex.ListFiles("xml");
	fileIndex.ListFiles("txt");
	return 0;
}

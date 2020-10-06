//This is a demonstration for getting full absolute paths for special directories in Windows
//There are more directories available to be found in the same manner as in this example
//only by switching a parameter in SHGetSpecialFolderPath
//refer to ShlObj_core.h for full parameter options available
//
//Ahn, Jeeho
//2020.10.6

//the following is needed if it is being built on Visual Studio
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <ShlObj.h>
#include <filesystem>
#include <string>
#include <iostream>

//converstion from TCHART to String
std::string TCHARToString(const TCHAR* ptsz)   //http://reedok.egloos.com/2186471
{
	int len = wcslen((wchar_t*)ptsz);
	char* psz = new char[2 * len + 1];
	wcstombs(psz, (wchar_t*)ptsz, 2 * len + 1);
	std::string s = psz;
	delete[] psz;
	return s;
}

std::string get_desktop_path()
{
	TCHAR buff[100] = { 0 };
	SHGetSpecialFolderPath(NULL, buff, CSIDL_DESKTOP, false);

	//return after converting the full path into a generic format
	//filessytem is under std::experimental below c++17
	//since c++17, filesystem is known to be under std like other members
	return std::experimental::filesystem::path(TCHARToString(buff)).generic_string();
}

std::string get_documents_path()
{
	TCHAR buff[100] = { 0 };
	SHGetSpecialFolderPath(NULL, buff, CSIDL_MYDOCUMENTS, false);

	//return after converting the full path into a generic format
	//filessytem is under std::experimental below c++17
	//since c++17, filesystem is known to be under std like other members
	return std::experimental::filesystem::path(TCHARToString(buff)).generic_string();	
}

std::string get_programfiles_path()
{
	TCHAR buff[100] = { 0 };
	SHGetSpecialFolderPath(NULL, buff, CSIDL_PROGRAM_FILES, false);

	//return after converting the full path into a generic format
	//filessytem is under std::experimental below c++17
	//since c++17, filesystem is known to be under std like other members
	return std::experimental::filesystem::path(TCHARToString(buff)).generic_string();
}


int main()
{
    std::cout << "Getting Windows Special Paths Demo" << std::endl;

	//Full Desktop Path
	std::string desktop_path = get_desktop_path();
	std::cout << "\nDesktop Path: \n" << desktop_path << std::endl;

	//Full Documents Path
	std::string documents_path = get_documents_path();
	std::cout << "\nDocuments Path: \n" << documents_path << std::endl;

	//Full Programs Files Path
	std::string programfiles_path = get_programfiles_path();
	std::cout << "\nProgram Files Path: \n" << programfiles_path << std::endl;

	return 0;
}
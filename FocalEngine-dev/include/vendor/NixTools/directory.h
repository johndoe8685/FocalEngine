#pragma once
#include <iostream>

//If NIXTOOLS_EXPORTS preprocessor defined. Then export the functions. Else import.

#ifdef NIXTOOLS_EXPORTS
#define NIXTOOLS_API __declspec(dllexport)
#else
#define NIXTOOLS_API __declspec(dllimport)
#endif

#ifdef __linux__
#include "unistd.h"
#endif

#ifdef _WIN64
#include <direct.h>
#define GetCurrentDir _getcwd
#endif

namespace NixTools
{
	class Directory
	{
	private:
		std::string m_path;
		std::string m_cwd;
		void processCwd();
	public:
		NIXTOOLS_API Directory(const std::string& path);
		NIXTOOLS_API Directory();

		NIXTOOLS_API void changePath(std::string path);
		NIXTOOLS_API std::string getPath();
		NIXTOOLS_API std::string getWorkDirectory();
		NIXTOOLS_API std::string getFileName();
	};
};

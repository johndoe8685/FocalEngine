#include "directory.h"
namespace NixTools
{
	Directory::Directory(const std::string& path)
		:m_path(path)
	{
		processCwd();
		changePath(m_path);
	}

	Directory::Directory()
	{
		processCwd();
	}

#ifdef __linux__
	void Directory::processCwd()
	{
		m_cwd = get_current_dir_name();
	}
#endif

#ifdef _WIN64
	void Directory::processCwd()
	{
		char buff[FILENAME_MAX];
		GetCurrentDir(buff, FILENAME_MAX);
		m_cwd = buff;
	}
#endif

	void Directory::changePath(std::string path)
	{
		m_path = m_cwd + path;
	}

	std::string Directory::getPath()
	{
		return m_path;
	}

	std::string Directory::getWorkDirectory()
	{
		return m_cwd;
	}

	std::string Directory::getFileName()
	{
		int index_of_last_slash = m_path.rfind("/");
		int index_of_last_dot = m_path.rfind(".");
		std::string result = m_path.substr(index_of_last_slash + 1, index_of_last_dot - index_of_last_slash - 1);
		return result;
	}
};

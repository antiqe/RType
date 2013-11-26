#ifndef __INIREADER_H__
#define __INIREADER_H__

#include <map>
#include <vector>
#include <string>

#include "INISection.hpp"

namespace Ultra
{
	class INIReader
	{
	private:
		std::string _filename;
		std::map<std::string, INISection *> _sects;
		bool _valid;
	public:
		INIReader(std::string const &filename);
		std::string getFilename() const;
		INISection *getSection(std::string const &name);
		bool isValid() const;
		bool load();
	private:
		std::string trim(std::string const &buffer);
		void parseLine(std::string const &str, std::vector<std::string> &v); 
	};
};

#endif
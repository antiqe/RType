#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstring>
#include <algorithm>

#include "INIReader.hpp"
#include "INISection.hpp"

namespace Ultra
{

	INIReader::INIReader(std::string const &filename)
		: _filename(filename), _valid(false)
	{ }

	std::string INIReader::getFilename() const
	{
		return (this->_filename);
	}

	INISection *INIReader::getSection(std::string const &name)
	{
		std::map<std::string, INISection *>::iterator	it = this->_sects.find(name);

		return (it != this->_sects.end() ? it->second : 0);
	}

	bool INIReader::isValid() const
	{
		return (this->_valid);
	}

	std::string INIReader::trim(std::string const &s)
	{
		long ep = 0;
		long sp = 0;
		std::string ret;
		char p[] = " \t\r\n\"";

		for (ep = s.length() - 1; ep >= 0; --ep)
			if (strchr(";", s[ep])) break;
		ret = s.substr(0, ep - 1);
		for (ep = ret.length() - 1; sp <= ep; ++sp)
			if (!strchr(p, ret[sp])) break;
		ret = ret.substr(sp, ep-sp+1);
		for (ep = ret.length() - 1; ep >= 0; --ep)
			if (!strchr(p, ret[ep])) break;
		ret = ret.substr(0, ep + 1);
		return ret;
	}

	bool INIReader::load()
	{
		INISection *e = 0;
		std::string line;
		std::vector<std::string> fields;
		std::ifstream f(this->_filename.c_str());

		if (!f)
			return (false);
		while (std::getline(f, line))
		{
			line = this->trim(line);
			if (line.length() > 2 && line[0] == '[' && line[line.length() - 1] == ']')
			{
				std::string sec = line.substr(1, line.length() - 2);
				e = new INISection(sec);
				this->_sects[sec] = e;
			}
			else if (e)
			{
				fields.clear();
				this->parseLine(line, fields);
				e->setField(fields[0], Ultra::Value(fields[1]));
			}
		}
		return (true);
	}

	void INIReader::parseLine(std::string const &str, std::vector<std::string > &v)
	{
		size_t start, end = 0;
		std::string delim = ":=";

		while (end < str.size())
		{
			start = end;
			while (start < str.size() && (delim.find(str[start]) != std::string::npos))
				start++;
			end = start;
			while (end < str.size() && (delim.find(str[end]) == std::string::npos))
				end++;
			if (end-start != 0)
				v.push_back(std::string(str, start, end-start));
		}
	}
}
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <istream>

namespace str
{

	class string
	{
	public:
		string(std::string str)
		{
			this->text = str;
		}
		string() = default;

		std::vector<str::string> split(const char* delimiter)
		{
			std::vector<str::string> ret;
			char* str = (char*)text.c_str();
			char* pch;

			pch = strtok(str, delimiter);
			while (pch != NULL)
			{
				str::string a;
				a() = pch;
				ret.push_back(a);
				pch = strtok(NULL, delimiter);
			}
			return ret;
		}

		bool startsWith(std::string expression)
		{
			return !text.compare(0, expression.size(), expression);
		}

		std::string& operator()()
		{
			return text;
		}

		char operator[](unsigned int i)
		{
			return text.at(i);
		}

	private:
		std::string text;
	};

}

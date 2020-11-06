#include "StringUtils.h"

std::vector<std::string> Split(std::string s, std::string regex)
{
    std::vector<std::string> res;

    size_t pos = 0;
    std::string token;

    while ((pos = s.find(regex)) != std::string::npos) {
        token = s.substr(0, pos);
        res.push_back(token);
        s.erase(0, pos + regex.length());
    }

    res.push_back(s);

    return res;
}

void split_recursive(int i, std::string* s, size_t size, char* splitter, std::vector<std::string>* res)
{
	if (i == size)
	{
		res->push_back(s->substr(0));
	}
	else
	{
		if (s->at(i) == *splitter)
		{
			res->push_back(s->substr(0, i));
			std::string newS = s->substr(i + 1);
			split_recursive(0, &newS, newS.length(), splitter, res);
		}
		else
		{
			split_recursive(i + 1, s, s->length(), splitter, res);
		}
	}
}

void split(std::vector<std::string>* res, std::string* s, char splitter)
{
	split_recursive(0, s, s->length(), &splitter, res);
}
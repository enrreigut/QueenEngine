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
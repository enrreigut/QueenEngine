#pragma once

#include <string>
#include <vector>

std::vector<std::string> Split(std::string s, std::string regex);

void split_recursive(int i, std::string* s, size_t size, char* splitter, std::vector<std::string>* res);

void split(std::vector<std::string>* res, std::string* s, char splitter);
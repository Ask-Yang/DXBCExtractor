#pragma once
#include <map>
#include <iostream>
#include <string>
#include <set>
#include <vector>
class ObjNameAdapter
{
public:
	ObjNameAdapter(std::string _initName);
	std::string swizzle(std::string swiz);
	std::string mask(std::string mask);
public:
	std::string initName;
	std::map<char, std::string> adapter;
	std::set<std::string> usedNames;
	std::map<char, int> letterChanged;
};
typedef std::shared_ptr<ObjNameAdapter> NameAdapterPtr;
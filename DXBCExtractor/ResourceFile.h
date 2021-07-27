#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "InstructionObject.h"
const size_t cSize = 8;
const size_t rSize = 8;
const size_t tSize = 8;
const size_t vSize = 8;
struct ResourceFile
{
	ResourceFile();
	std::map<std::string, InsObjPtr> res;
};


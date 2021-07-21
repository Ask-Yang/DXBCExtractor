#pragma once
#include <vector>
#include <iostream>
#include "InstructionObject.h"
const size_t cSize = 8;
const size_t rSize = 8;
const size_t tSize = 8;
const size_t vSize = 8;
class ResourceFile
{
	ResourceFile();
public:
	std::vector<std::shared_ptr<InstructionObject>> c; // constant
	std::vector<std::shared_ptr<InstructionObject>> r; // temporary
	std::vector<std::shared_ptr<InstructionObject>> t; // texture
	std::vector<std::shared_ptr<InstructionObject>> v; // color
};


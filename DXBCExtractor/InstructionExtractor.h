#pragma once
#include <iostream>
#include <string>
#include <set>
#include "Instruction.h"
#include "ResourceFile.h"

class InstructionExtractor
{
public:
	InstructionExtractor(std::shared_ptr<ResourceFile> _resFile);
	std::shared_ptr<Instruction> createInstruction(std::string line);
	std::set<std::string> instructionLibrary{
		"mad", "dp2", "sample_indexable", "sqrt", "lt", "movc", "dp3", "rsq",
		"mul", "mov", "add", "max", "log"
	};
private:
	std::shared_ptr<ResourceFile> resFile;
};


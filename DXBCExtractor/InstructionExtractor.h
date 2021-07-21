#pragma once
#include <iostream>
#include <string>
#include <set>
#include "Instruction.h"

class InstructionExtractor
{
public:
	std::shared_ptr<Instruction> createInstruction(std::string line);
	std::set<std::string> instructionLibrary{
		"mad", "dp2", "sample_indexable", "sqrt", "lt", "movc", "dp3", "rsq",
		"mul", "mov", "add", "max", "log"
	};
};


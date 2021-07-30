#pragma once
#include <iostream>
#include <string>
#include <set>
#include "Instruction.h"
#include "ResourceFile.h"
#include "InsNode.h"
class InstructionExtractor
{
public:
	InstructionExtractor(std::shared_ptr<ResourceFile> _resFile);
	void instructionObjectExtract(std::string line, std::vector<InsObjPtr>& sources, InsPtr& operation);
	InsObjPtr destObjExtract(std::string line);
	bool isObjectDest(std::string line, InsObjPtr dest);

	InsPtr createInstruction(std::string line);
	void createInsObject(std::string line, InsObjPtr& dest, std::vector<InsObjPtr>& sources);
	std::set<std::string> instructionLibrary{
		"mad", "dp2", "sample_indexable", "sqrt", "lt", "movc", "dp3", "rsq",
		"mul", "mov", "add", "max", "log"
	};
private:
	std::shared_ptr<ResourceFile> resFile;
	InsObjPtr createSingleInsObj(std::string str);
};


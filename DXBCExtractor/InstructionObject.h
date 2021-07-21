#pragma once
#include <string>
#include <vector>
class InstructionObject
{
public:
	InstructionObject();
	InstructionObject(std::string regName);
	
public:
	void setName(std::string regName);
	virtual bool isObjectLeft(std::string line);
	InstructionObject swizzle(std::string swizzle);
	void mask(std::string mask, InstructionObject& obj);
private:
	std::string name;
	std::vector<float> data;
};


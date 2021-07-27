#pragma once
#include <string>
#include <vector>
#include <iostream>
struct InstructionObject
{
	InstructionObject();
	InstructionObject(std::string regName);
	
	void setName(std::string regName);
	virtual bool isObjectLeft(std::string line);
	InstructionObject swizzle(std::string swizzle);
	void mask(std::string mask, InstructionObject& obj);
	bool operator==(const std::string str) {
		return name == str;
	}

	std::string name;
	std::vector<float> data;
};
InstructionObject operator+(const InstructionObject& left, const InstructionObject& right);
InstructionObject operator*(const InstructionObject& left, const InstructionObject& right);
InstructionObject operator-(const InstructionObject& left, const InstructionObject& right);


typedef std::shared_ptr<InstructionObject> InsObjPtr;
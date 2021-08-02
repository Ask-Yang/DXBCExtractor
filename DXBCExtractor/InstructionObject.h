#pragma once
#include <string>
#include <vector>
#include <iostream>

struct InsNode;
typedef std::shared_ptr<InsNode> InsNodePtr;
typedef std::weak_ptr<InsNode> InsNodeWeak;
struct Vec4f;
struct InstructionObject;
typedef std::shared_ptr<InstructionObject> InsObjPtr;
struct InstructionObject
{
	InstructionObject();
	InstructionObject(std::string regName);
	
	void setName(std::string regName);
	virtual bool isObjectLeft(std::string line);
	InstructionObject swizzle(std::string swizzle);
	void mask(std::string mask, InstructionObject& obj);
	InsNodePtr getCurrentNode();
	void setNewNode(InsNodePtr next);
	void setInitNodeValue(Vec4f val);
	void setInitNode(InsNodePtr initNode);
	bool operator==(const std::string str) {
		return name == str;
	}
	
	void print();
	InsNodePtr objRoot;
	InsNodePtr currentNode;
	InsObjPtr CalcuObj;

	std::string name;
	std::vector<float> data;
};
InstructionObject operator+(const InstructionObject& left, const InstructionObject& right);
InstructionObject operator*(const InstructionObject& left, const InstructionObject& right);
InstructionObject operator-(const InstructionObject& left, const InstructionObject& right);
InstructionObject operator*(const InstructionObject& left, const int& right);

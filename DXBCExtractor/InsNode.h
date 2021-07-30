#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include "Instruction.h"
struct InsNode;
typedef std::shared_ptr<InsNode> InsNodePtr;

struct InstructionObject;
typedef std::shared_ptr<InstructionObject> InsObjPtr;

struct Vec4f {
	float x, y, z, w;
	Vec4f();
	Vec4f(float a, float b, float c, float d);
	explicit Vec4f(const InsObjPtr pInsObj);
	friend std::ostream& operator<<(std::ostream& os, const Vec4f& v);
};
std::ostream& operator<<(std::ostream& os, const Vec4f& v);

struct InsNode {
	Vec4f destValue;
	InsObjPtr destObj;
	InsNodePtr pre;
	InsNodePtr next;
	std::vector<InsNodePtr> sources;
	InsPtr instruction;
	std::string line;
	InsNode(Vec4f val) {
		destValue = val;
	}
	InsNode(std::string _line, InsObjPtr _destObj, std::vector<InsNodePtr> _sources, InsPtr _instruction) {
		line = _line;
		destObj = _destObj;
		sources = _sources;
		instruction = _instruction;
	}
	void exec();
	void print() {
		std::cout << line;
	}
};
void connectTwoNode(InsNodePtr pre, InsNodePtr next);
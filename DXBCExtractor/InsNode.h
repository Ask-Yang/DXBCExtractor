#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <sstream>
#include <set>
#include "Instruction.h"
struct InsNode;
typedef std::shared_ptr<InsNode> InsNodePtr;

struct InstructionObject;
typedef std::shared_ptr<InstructionObject> InsObjPtr;
typedef std::weak_ptr<InstructionObject> InsObjWeak;

struct Vec4f {
	float x, y, z, w;
	Vec4f();
	Vec4f(float a, float b, float c, float d);
	explicit Vec4f(const InsObjPtr pInsObj);
	friend std::ostream& operator<<(std::ostream& os, const Vec4f& v);
};
std::ostream& operator<<(std::ostream& os, const Vec4f& v);

struct InsNode {
	static int printMode; // 0是所有输入变量只要接触了这个寄存器就会被保留，1是只有上一次直接接触才会被保留
	int lineNumber;
	Vec4f destValue;
	InsObjWeak destObj;
	InsNodePtr pre;
	InsNodePtr next;
	std::vector<InsNodePtr> sources;
	std::set<std::string> signs;
	InsPtr instruction;
	std::string line;
	std::string transformLine;
	InsNode(Vec4f val);
	InsNode(std::string _line, InsObjPtr _destObj, std::vector<InsNodePtr> _sources, InsPtr _instruction, size_t _lineNumber);
	void exec();
	std::string print();
	std::string print2();
	bool isObjShield(std::string str);
	InsObjPtr getDest();
};

void connectTwoNode(InsNodePtr pre, InsNodePtr next);
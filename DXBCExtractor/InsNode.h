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

struct Vec4f {/// 辅助的4值类，用的比较少。
	float x, y, z, w;
	Vec4f();
	Vec4f(float a, float b, float c, float d);
	explicit Vec4f(const InsObjPtr pInsObj);
	friend std::ostream& operator<<(std::ostream& os, const Vec4f& v);
};
std::ostream& operator<<(std::ostream& os, const Vec4f& v);

struct InsNode {
	static int printMode; /// 0是所有输入变量只要接触了这个寄存器就会被保留，1是只有上一次直接接触才会被保留
						  /// 2是带后缀的mode1
						  /// printMode要在创建节点之前更改
public:
	int lineNumber; /// 对应指令行号
	Vec4f destValue; /// 该节点的dest寄存器在运算后拥有的值
	InsObjWeak destObj; /// 对应的dest节点
	InsNodePtr pre; 
	InsNodePtr next;
	std::vector<InsNodePtr> sources; /// 该节点对应指令的source寄存器在该指令执行时对应的currentNode。在构造函数中构建。
	std::set<std::string> signs; /// 为print()服务，存储相应的obj符号
	InsPtr instruction; /// 该节点对应指令
	std::string line; /// 该节点对应指令的原始行
	std::string transformLine; /// 为print2()服务，记录变化后的寄存器。在构造函数中构建。
public:
	InsNode(Vec4f val);
	InsNode(std::string _line, InsObjPtr _destObj, std::vector<InsNodePtr> _sources, InsPtr _instruction, size_t _lineNumber);
	void exec();	/// 执行node中存储的calcu
	std::string print(); /// 输出相关资源，和printMode关联
	std::string print2();  /// 输出寄存器随操作变化
	bool isObjShield(std::string str);
	InsObjPtr getDest();
};

void connectTwoNode(InsNodePtr pre, InsNodePtr next);
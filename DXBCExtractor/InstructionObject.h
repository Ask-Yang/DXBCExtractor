#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "ObjNameAdapter.h"
struct InsNode;
typedef std::shared_ptr<InsNode> InsNodePtr;
typedef std::weak_ptr<InsNode> InsNodeWeak;
struct Vec4f;
struct InstructionObject;
typedef std::shared_ptr<InstructionObject> InsObjPtr;
struct InstructionObject
{
public:
	InstructionObject();
	InstructionObject(std::string regName);
	
	void setName(std::string regName);
	virtual bool isObjectLeft(std::string line); /// 判断该寄存器是不是dest
	InstructionObject swizzle(std::string swizzle); /// 将该寄存器的值按swizzle创建一个新的obj
	void mask(std::string mask, InstructionObject& obj); /// 将obj的值按mask写入到该寄存器中
	InsNodePtr getCurrentNode(); 
	void setNewNode(InsNodePtr next); /// 寄存器作为指令dest时被调用，设置新节点
	void setInitNodeValue(Vec4f val); /// 为用户执行calcu时设置初始值
	void setInitNode(InsNodePtr initNode); /// 设置初始节点，因为需要此寄存器的指针所以无法放在构造函数中，具体调用由InstructionExtractor执行
	bool operator==(const std::string str) {
		return name == str;
	}
	
public:
	void print(); /// 输出这个寄存器连接的节点的print，表示这个寄存器被修改的哪些操作
	InsNodePtr objRoot; /// 最开始的初始节点
	InsNodePtr currentNode; /// 如果寄存器被（资源同）改变（写入，作为指令dest），那么对应的currentNode会更新
	InsObjPtr CalcuObj; /// 对应的计算单元，被InsNode连接，防止循环引用
	NameAdapterPtr adapter; /// 对应的ObjNameAdapter对象，用于存储变化的名字

	std::string name; /// 寄存器的名字
	std::vector<float> data; ///四个通道对应的变量
};
InstructionObject operator+(const InstructionObject& left, const InstructionObject& right);
InstructionObject operator*(const InstructionObject& left, const InstructionObject& right);
InstructionObject operator-(const InstructionObject& left, const InstructionObject& right);
InstructionObject operator*(const InstructionObject& left, const int& right);

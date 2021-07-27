#pragma once
#include "ResourceFile.h"
#include <iostream>
#include <vector>
#include <string>
class Instruction
{
public:
	Instruction(std::shared_ptr<ResourceFile> file, std::string line);
	virtual void calu(InsObjPtr dest, std::vector<InsObjPtr> sources) = 0;
protected:
	void build(std::string line);
	std::shared_ptr<ResourceFile> resFile;
	std::string name;
	std::string mask;
	std::vector<std::string> swizzleList;
	std::string rawLine;
};
typedef std::shared_ptr<Instruction> InsPtr;
// SetUp û��Ҫ���򣬿���һ��ʼ������
// Arithmetic, Texture ��������
// Flow control ����һ��ʼ�Ͱ�flow control�������Ȼ��͵��������ļ���������shader control��

class InsMad : public Instruction {
	void calu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsDp2 : public Instruction {

};

class InsSample_indexable : public Instruction {

};

class InsSqrt : public Instruction {

};

class InsLt : public Instruction {

};

class InsMovc : public Instruction {

};

class InsDp3 : public Instruction {

};

class InsRsq : public Instruction {

};

class InsMul : public Instruction {

};

class InsMov : public Instruction {

};

class InsAdd : public Instruction {
	void calu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsMax : public Instruction {

};

class InsLog : public Instruction {

};
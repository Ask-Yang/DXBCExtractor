#pragma once
#include "ResourceFile.h"
#include <iostream>
#include <vector>
#include <string>
class Instruction
{
public:
	Instruction(std::shared_ptr<ResourceFile> file, std::string line);
	virtual void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) = 0;
protected:
	void build(std::string line);
	std::shared_ptr<ResourceFile> resFile;
	std::string name;
	std::string mask;
	std::vector<std::string> swizzleList;
	std::vector<int> minusList; // calcuʱ�ǵö�Ӧ���
	std::string rawLine;
};
typedef std::shared_ptr<Instruction> InsPtr;
// SetUp û��Ҫ���򣬿���һ��ʼ������
// Arithmetic, Texture ��������
// Flow control ����һ��ʼ�Ͱ�flow control�������Ȼ��͵��������ļ���������shader control��

class InsMad : public Instruction {
public:
	InsMad(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsDp2 : public Instruction {
public:
	InsDp2(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsSample_indexable : public Instruction {
public:
	InsSample_indexable(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsSqrt : public Instruction {
public:
	InsSqrt(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsLt : public Instruction {
public:
	InsLt(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsMovc : public Instruction {
public:
	InsMovc(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsDp3 : public Instruction {
public:
	InsDp3(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsRsq : public Instruction {
public:
	InsRsq(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsMul : public Instruction {
public:
	InsMul(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsMov : public Instruction {
public:
	InsMov(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsAdd : public Instruction {
public:
	InsAdd(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsMax : public Instruction {
public:
	InsMax(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};

class InsLog : public Instruction {
public:
	InsLog(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};
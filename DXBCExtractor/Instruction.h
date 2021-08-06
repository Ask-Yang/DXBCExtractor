#pragma once
#include "ResourceFile.h"
#include <iostream>
#include <vector>
#include <string>
class Instruction
{
public:
	Instruction(std::shared_ptr<ResourceFile> file, std::string line);
	virtual void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources);
public:
	void build(std::string line); /// 构建寄存器
	std::shared_ptr<ResourceFile> resFile; 
	std::string name;  /// 指令的名字，如add，mul等
	std::string mask;  /// 形如reg.xyz 中的xyz，mask就是字符串"xyz" 
	std::vector<std::string> swizzleList;
	std::vector<int> minusList; /// calcu时记得对应相乘，1就是系数为1，-1就是系数为-1
	std::string rawLine; /// 指令对应的行的
};
typedef std::shared_ptr<Instruction> InsPtr;
/// SetUp 没必要逆向，可以一开始解析完
/// Arithmetic, Texture 可以逆向
/// Flow control 可以一开始就把flow control拆出来，然后就当成两个文件处理，反正shader control少

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

class InsExp : public Instruction {
public:
	InsExp(std::shared_ptr<ResourceFile> file, std::string line);
	void calcu(InsObjPtr dest, std::vector<InsObjPtr> sources) override;
};
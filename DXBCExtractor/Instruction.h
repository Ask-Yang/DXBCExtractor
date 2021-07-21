#pragma once
#include "ResourceFile.h"
#include <iostream>
#include <vector>
#include <string>
class Instruction
{
public:
	Instruction(std::shared_ptr<ResourceFile> file, std::string line);
	virtual void calu(std::shared_ptr<InstructionObject> dest, std::vector<std::shared_ptr<InstructionObject>> sources) = 0;
private:
	void build(std::string line);
	std::shared_ptr<ResourceFile> resFile;
	std::string name;
	std::string mask;
	std::vector<std::string> swizzleList;
	std::string rawLine;
};
// SetUp 没必要逆向，可以一开始解析完
// Arithmetic, Texture 可以逆向
// Flow control 可以一开始就把flow control拆出来，然后就当成两个文件处理，反正shader control少

class InsMad : public Instruction {

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

};

class InsMax : public Instruction {

};

class InsLog : public Instruction {

};
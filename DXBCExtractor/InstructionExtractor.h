#pragma once
#include <iostream>
#include <string>
#include <set>
#include "Instruction.h"
#include "ResourceFile.h"
#include "InsNode.h"
class InstructionExtractor
{
public:
	InstructionExtractor(std::shared_ptr<ResourceFile> _resFile); /// 构造函数，需要一个寄存器文件对象，存储相应的寄存器
	void instructionObjectExtract(std::string line, std::vector<InsObjPtr>& sources, InsPtr& operation); /// 从完整的文本中提取该指令的source对象，还有指令
	InsObjPtr destObjExtract(std::string line);	/// 从完整的指令文本line中单独提取destObj
	bool isObjectDest(std::string line, InsObjPtr dest);  /// 判断输入的dest参数在这个指令中是否是dest 

	InsPtr createInstruction(std::string line); /// 创建指令
	void createInsObject(std::string line, InsObjPtr& dest, std::vector<InsObjPtr>& sources);
	std::set<std::string> instructionLibrary{ /// 添加需要翻译的指令，如果不需要计算则不需要动
		"mad", "dp2", "sample_indexable(texture2d)(float,float,float,float)", "sqrt", "lt", "movc", "dp3", "rsq",
		"mul", "mov", "add", "max", "log", "exp"
	};
private:
	std::shared_ptr<ResourceFile> resFile;
	InsObjPtr createSingleInsObj(std::string str); /// 根据只包含了寄存器对象和对应后缀（.xyz）的字符串创建对象
};


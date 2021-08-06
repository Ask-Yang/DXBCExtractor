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
	InstructionExtractor(std::shared_ptr<ResourceFile> _resFile); /// ���캯������Ҫһ���Ĵ����ļ����󣬴洢��Ӧ�ļĴ���
	void instructionObjectExtract(std::string line, std::vector<InsObjPtr>& sources, InsPtr& operation); /// ���������ı�����ȡ��ָ���source���󣬻���ָ��
	InsObjPtr destObjExtract(std::string line);	/// ��������ָ���ı�line�е�����ȡdestObj
	bool isObjectDest(std::string line, InsObjPtr dest);  /// �ж������dest���������ָ�����Ƿ���dest 

	InsPtr createInstruction(std::string line); /// ����ָ��
	void createInsObject(std::string line, InsObjPtr& dest, std::vector<InsObjPtr>& sources);
	std::set<std::string> instructionLibrary{ /// �����Ҫ�����ָ��������Ҫ��������Ҫ��
		"mad", "dp2", "sample_indexable(texture2d)(float,float,float,float)", "sqrt", "lt", "movc", "dp3", "rsq",
		"mul", "mov", "add", "max", "log", "exp"
	};
private:
	std::shared_ptr<ResourceFile> resFile;
	InsObjPtr createSingleInsObj(std::string str); /// ����ֻ�����˼Ĵ�������Ͷ�Ӧ��׺��.xyz�����ַ�����������
};


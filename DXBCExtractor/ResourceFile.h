#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "InstructionObject.h"

struct ResourceFile
{
	ResourceFile();
	std::map<std::string, InsObjPtr> res; /// �����õ���Դ�ͼĴ����ͻᱻ����������
};


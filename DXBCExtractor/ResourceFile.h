#pragma once
#include <vector>
#include <map>
#include <iostream>
#include "InstructionObject.h"

struct ResourceFile
{
	ResourceFile();
	std::map<std::string, InsObjPtr> res; /// 创建好的资源和寄存器就会被保存在这里
};


#pragma once
#include <map>
#include <iostream>
#include <string>
#include <set>
#include <vector>
class ObjNameAdapter
{
public:
	ObjNameAdapter(std::string _initName);
	std::string swizzle(std::string swiz); /// 指寄存器作为source时，使用dst.xyz，会输出存储在adapter中的之前变化的名字，
										   /// 如果相邻的通道名字相同会被合并，同时输出float#()来表示此时变量的size
	std::string mask(std::string mask); /// 指寄存器作为dest时，使用下标dst.xyz时创建的新名字dst_xyz_#_#_#
public:
	std::string initName; /// 寄存器最开始的名字（资源也是一样）如r0
	std::map<char, std::string> adapter; /// 对应的x,y,z,w通道存储的名字
	std::map<char, int> letterChanged;  /// 记录xyzw通道被改变的次数，创建新名字时需要
};
typedef std::shared_ptr<ObjNameAdapter> NameAdapterPtr;
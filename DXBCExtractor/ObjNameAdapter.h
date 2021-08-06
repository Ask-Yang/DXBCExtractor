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
	std::string swizzle(std::string swiz); /// ָ�Ĵ�����Ϊsourceʱ��ʹ��dst.xyz��������洢��adapter�е�֮ǰ�仯�����֣�
										   /// ������ڵ�ͨ��������ͬ�ᱻ�ϲ���ͬʱ���float#()����ʾ��ʱ������size
	std::string mask(std::string mask); /// ָ�Ĵ�����Ϊdestʱ��ʹ���±�dst.xyzʱ������������dst_xyz_#_#_#
public:
	std::string initName; /// �Ĵ����ʼ�����֣���ԴҲ��һ������r0
	std::map<char, std::string> adapter; /// ��Ӧ��x,y,z,wͨ���洢������
	std::map<char, int> letterChanged;  /// ��¼xyzwͨ�����ı�Ĵ���������������ʱ��Ҫ
};
typedef std::shared_ptr<ObjNameAdapter> NameAdapterPtr;
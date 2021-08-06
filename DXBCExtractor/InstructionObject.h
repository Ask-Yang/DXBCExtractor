#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "ObjNameAdapter.h"
struct InsNode;
typedef std::shared_ptr<InsNode> InsNodePtr;
typedef std::weak_ptr<InsNode> InsNodeWeak;
struct Vec4f;
struct InstructionObject;
typedef std::shared_ptr<InstructionObject> InsObjPtr;
struct InstructionObject
{
public:
	InstructionObject();
	InstructionObject(std::string regName);
	
	void setName(std::string regName);
	virtual bool isObjectLeft(std::string line); /// �жϸüĴ����ǲ���dest
	InstructionObject swizzle(std::string swizzle); /// ���üĴ�����ֵ��swizzle����һ���µ�obj
	void mask(std::string mask, InstructionObject& obj); /// ��obj��ֵ��maskд�뵽�üĴ�����
	InsNodePtr getCurrentNode(); 
	void setNewNode(InsNodePtr next); /// �Ĵ�����Ϊָ��destʱ�����ã������½ڵ�
	void setInitNodeValue(Vec4f val); /// Ϊ�û�ִ��calcuʱ���ó�ʼֵ
	void setInitNode(InsNodePtr initNode); /// ���ó�ʼ�ڵ㣬��Ϊ��Ҫ�˼Ĵ�����ָ�������޷����ڹ��캯���У����������InstructionExtractorִ��
	bool operator==(const std::string str) {
		return name == str;
	}
	
public:
	void print(); /// �������Ĵ������ӵĽڵ��print����ʾ����Ĵ������޸ĵ���Щ����
	InsNodePtr objRoot; /// �ʼ�ĳ�ʼ�ڵ�
	InsNodePtr currentNode; /// ����Ĵ���������Դͬ���ı䣨д�룬��Ϊָ��dest������ô��Ӧ��currentNode�����
	InsObjPtr CalcuObj; /// ��Ӧ�ļ��㵥Ԫ����InsNode���ӣ���ֹѭ������
	NameAdapterPtr adapter; /// ��Ӧ��ObjNameAdapter�������ڴ洢�仯������

	std::string name; /// �Ĵ���������
	std::vector<float> data; ///�ĸ�ͨ����Ӧ�ı���
};
InstructionObject operator+(const InstructionObject& left, const InstructionObject& right);
InstructionObject operator*(const InstructionObject& left, const InstructionObject& right);
InstructionObject operator-(const InstructionObject& left, const InstructionObject& right);
InstructionObject operator*(const InstructionObject& left, const int& right);

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <ostream>
#include <sstream>
#include <set>
#include "Instruction.h"
struct InsNode;
typedef std::shared_ptr<InsNode> InsNodePtr;

struct InstructionObject;
typedef std::shared_ptr<InstructionObject> InsObjPtr;
typedef std::weak_ptr<InstructionObject> InsObjWeak;

struct Vec4f {/// ������4ֵ�࣬�õıȽ��١�
	float x, y, z, w;
	Vec4f();
	Vec4f(float a, float b, float c, float d);
	explicit Vec4f(const InsObjPtr pInsObj);
	friend std::ostream& operator<<(std::ostream& os, const Vec4f& v);
};
std::ostream& operator<<(std::ostream& os, const Vec4f& v);

struct InsNode {
	static int printMode; /// 0�������������ֻҪ�Ӵ�������Ĵ����ͻᱻ������1��ֻ����һ��ֱ�ӽӴ��Żᱻ����
						  /// 2�Ǵ���׺��mode1
						  /// printModeҪ�ڴ����ڵ�֮ǰ����
public:
	int lineNumber; /// ��Ӧָ���к�
	Vec4f destValue; /// �ýڵ��dest�Ĵ����������ӵ�е�ֵ
	InsObjWeak destObj; /// ��Ӧ��dest�ڵ�
	InsNodePtr pre; 
	InsNodePtr next;
	std::vector<InsNodePtr> sources; /// �ýڵ��Ӧָ���source�Ĵ����ڸ�ָ��ִ��ʱ��Ӧ��currentNode���ڹ��캯���й�����
	std::set<std::string> signs; /// Ϊprint()���񣬴洢��Ӧ��obj����
	InsPtr instruction; /// �ýڵ��Ӧָ��
	std::string line; /// �ýڵ��Ӧָ���ԭʼ��
	std::string transformLine; /// Ϊprint2()���񣬼�¼�仯��ļĴ������ڹ��캯���й�����
public:
	InsNode(Vec4f val);
	InsNode(std::string _line, InsObjPtr _destObj, std::vector<InsNodePtr> _sources, InsPtr _instruction, size_t _lineNumber);
	void exec();	/// ִ��node�д洢��calcu
	std::string print(); /// ��������Դ����printMode����
	std::string print2();  /// ����Ĵ���������仯
	bool isObjShield(std::string str);
	InsObjPtr getDest();
};

void connectTwoNode(InsNodePtr pre, InsNodePtr next);
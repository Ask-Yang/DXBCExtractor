#include "InsNode.h"
#include "InstructionObject.h"
using namespace std;
ostream& operator<<(ostream& os, const Vec4f& v)
{
	cout << "(" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")";
	return os;
}
void connectTwoNode(InsNodePtr pre, InsNodePtr next)
{
	pre->next = next;
	next->pre = pre;
}

void InsNode::exec()
{
	vector<InsObjPtr> sourceObjs;
	for (auto& node : sources)
	{
		sourceObjs.push_back(node->destObj);
	}
	if (destObj)
	{
		instruction->calcu(destObj, sourceObjs);
		destValue = Vec4f(destObj);
	}
}

Vec4f::Vec4f()
{
	x = 0; y = 0; z = 0; w = 0;
}

Vec4f::Vec4f(float a, float b, float c, float d)
{
	x = a; y = b; z = c; w = d;
}

Vec4f::Vec4f(const InsObjPtr pInsObj)
{
	x = pInsObj->data[0];
	y = pInsObj->data[1];
	z = pInsObj->data[2];
	w = pInsObj->data[3];
}

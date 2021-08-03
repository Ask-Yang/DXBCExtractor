#include "InsNode.h"
#include "InstructionObject.h"
using namespace std;

extern set<string> shieldList;

int InsNode::printMode = 0;
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
		sourceObjs.push_back(node->getDest());
	}
	if (InsObjPtr dest = destObj.lock())
	{
		instruction->calcu(dest, sourceObjs);
		destValue = Vec4f(dest);
	}
}

string InsNode::print()
{
	stringstream out;
	out << lineNumber << ": ";
	out << line;

	for (int i = line.size() + to_string(lineNumber).size(); i < 120; i++)
		out << " ";
	out << lineNumber << ": ";
	for (auto str : signs)
	{
		if(!isObjShield(str))
			out << str << " ";
	}
	out << endl;
	string outLine = out.str();
	cout<<outLine;
	return out.str();
}
InsNode::InsNode(Vec4f val)
	:lineNumber(-1)
{
	destValue = val;
}
InsNode::InsNode(std::string _line, InsObjPtr _destObj, std::vector<InsNodePtr> _sources, InsPtr _instruction, size_t _lineNumber)
{
	lineNumber = _lineNumber;
	line = _line;
	destObj = _destObj;
	sources = _sources;
	instruction = _instruction;
	for (auto& obj : sources)
	{
		if (printMode == 0)
		{
			for (auto s : obj->signs)
				signs.insert(s);
		}
		else if (printMode == 1)
		{
			if (auto p = obj->destObj.lock())
				signs.insert(p->name);
		}
	}
}
InsObjPtr InsNode::getDest()
{
	if (InsObjPtr dest = destObj.lock())
		return dest;
	else
		return nullptr;
}

bool InsNode::isObjShield(string str)
{
	if (str.size() > 3 && str[0] == 'l' && str[1] == '(')
		return true;// Á¢¼´Êý
	for (auto s:shieldList)
	{
		if (s.size() != str.size())
			continue;
		bool isShield = true;
		for (int i=0;i<s.size();i++)
		{
			if (s[i] == '#')
				continue;
			else if (s[i] != str[i])
			{
				isShield = false;
				break;
			}				
		}
		if (isShield)
			return true;
	}
	return false;
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

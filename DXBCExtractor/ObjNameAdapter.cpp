#include "ObjNameAdapter.h"
using namespace std;
char index2letter[4]= { 'x','y','z','w' };

ObjNameAdapter::ObjNameAdapter(std::string _initName)
{
	initName = _initName;
	adapter['x'] = initName;
	adapter['y'] = initName;
	adapter['z'] = initName;
	adapter['w'] = initName;
	letterChanged['x'] = 0;
	letterChanged['y'] = 0;
	letterChanged['z'] = 0;
	letterChanged['w'] = 0;

}

std::string ObjNameAdapter::swizzle(std::string swiz)
{
	if (initName.size() > 2 && initName[0] == 'l' && initName[1] == '(')
		return initName;
	vector<string> temp;

	if (swiz.size() != 0)
	{
		temp.resize(swiz.size());
		for (int i = 0; i < swiz.size(); i++)
		{
			if (swiz[i] == 'x')
				temp[i] = adapter['x'];
			else if (swiz[i] == 'y')
				temp[i] = adapter['y'];
			else if (swiz[i] == 'z')
				temp[i] = adapter['z'];
			else if (swiz[i] == 'w')
				temp[i] = adapter['w'];
		}
	}
	else
	{
		for (auto str : adapter)
			temp.push_back(str.second);
	}

	vector<int> perSufix;
	int p = 0;
	while (p < temp.size())
	{
		while (p + 1 < temp.size() && temp[p] == temp[p + 1])
			++p;

		perSufix.push_back(p);
		++p;
	}

	string out;
	out = "float" + to_string(swiz.size()) + "(";
	p = 0;
	for(int i=0;i<perSufix.size();i++)
	{
		string sufix;
		
		for (;p <= perSufix[i]; p++)
		{
			sufix.push_back(swiz[p]);
		}
		out += temp[p-1] + "." + sufix + ", ";
	}

	out.pop_back();
	out.pop_back();
	out += ")";
	return out;
}

std::string ObjNameAdapter::mask(std::string mask)
{
	if (initName.size() > 2 && initName[0] == 'l' && initName[1] == '(')
		return initName;
	string newName = initName + "_" + mask + "_";
	for (int i = 0; i < mask.size(); i++)
		newName += to_string(++letterChanged[mask[i]]) + "_";
	newName.pop_back();
	for (int i = 0; i < mask.size(); i++)
		adapter[mask[i]] = newName;
	return newName;
}

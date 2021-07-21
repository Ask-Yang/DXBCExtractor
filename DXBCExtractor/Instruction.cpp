#include "Instruction.h"
using namespace std;
Instruction::Instruction(std::shared_ptr<ResourceFile> file, std::string line)
	:resFile(file)
{
	build(line);
}

// 有三种情况 
// 第一种是只有一个命令 类似 ps_2_2 / nop
// 第二种是只有一个命令和一个dst 类似 texkill dst
// 第三种是有sources的 类似 abs dst, src

// 然后可能有mask、swizzle可能没有，mask swizzle是命令的一部分
void Instruction::build(std::string line)
{
	rawLine = line;
	const string under_point = ".";
	const string space = " ";
	unsigned int next = 0, last = 0, point = 0;
	string token;
	if ((next = line.find(space, last)) != string::npos)
		name = line.substr(last, next);
	else
	{
		name = line;
		return;
	}

	last = next + 1;
	if ((point = line.find(under_point, last)) == string::npos)
		return;
	if ((next = line.find(space, last)) != string::npos)
	{
		if(point < next) // for preventing the case: ins dst, src.xyz
			mask = line.substr(point + 1, next - 1); 
	}
	else
	{
		mask = line.substr(point + 1); // ins dst.xyz 
		return;
	}

	last = next + 1;
	point = last; // for preventing the case: ins dst, src.xyz
	while ((next = line.find(space, last)) != string::npos)
	{
		point = line.substr(last, next).find(under_point);
		if (point == string::npos)
			swizzleList.push_back("");
		else
			swizzleList.push_back(line.substr(point + 1, next - 1));
		last = next + 1;
	}
	point = line.find(under_point, last);
	if (point == string::npos)
		swizzleList.push_back("");
	else
		swizzleList.push_back(line.substr(point + 1));
}

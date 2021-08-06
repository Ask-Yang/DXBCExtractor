#include "Instruction.h"
using namespace std;
Instruction::Instruction(std::shared_ptr<ResourceFile> file, std::string line)
	:resFile(file)
{
	build(line);
}

void Instruction::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

/// 有三种情况 
/// 第一种是只有一个命令 类似 ps_2_2 / nop
/// 第二种是只有一个命令和一个dst 类似 texkill dst
/// 第三种是有sources的 类似 abs dst, src

/// 然后可能有mask、swizzle可能没有，mask swizzle是命令的一部分
void Instruction::build(std::string line)
{
	rawLine = line;
	const string under_point = ".";
	const string space = " ";
	size_t next = 0, last = 0, point = 0;
	string token;
	if ((next = line.find(space, last)) != string::npos)
		name = line.substr(last, next - last);
	else
	{
		name = line;
		return;
	}
	/// 抽取mask
	last = next + 1;
	if ((point = line.find(under_point, last)) == string::npos)
		return;
	if ((next = line.find(space, last)) != string::npos)
		mask = line.substr(point + 1, next - 1 - point - 1); 
	else
	{
		mask = line.substr(point + 1); /// ins dst.xyz 
		return;
	}
	/// 抽取swizzle
	last = next + 1;
	point = last; /// for preventing the case: ins dst, src.xyz
	while ((next = line.find(space, last)) != string::npos)
	{
		if (line[last] == '-') /// 计算ins dst, -src0的情况
		{
			++last;
			minusList.push_back(-1);
		} 
		else
			minusList.push_back(1);
		point = line.substr(last, next - last).find_last_of(under_point);
		if (point == string::npos)
			swizzleList.push_back("");
		else
			swizzleList.push_back(line.substr(last + point + 1, next - 1 - (last + point + 1)));
		last = next + 1;
	}
	if (line[last] == '-')
	{
		++last;
		minusList.push_back(-1);
	}
	else
		minusList.push_back(1);
	point = line.find_last_of(under_point);
	if (point == string::npos)
		swizzleList.push_back("");
	else
		swizzleList.push_back(line.substr(point + 1));
}

InsMad::InsMad(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsMad::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
	InstructionObject res;
	res = (sources[0]->swizzle(swizzleList[0])) * minusList[0] 
		* (sources[1]->swizzle(swizzleList[1])) * minusList[1]
		+ (sources[2]->swizzle(swizzleList[2])) * minusList[2];
	dest->mask(mask, res);
}

InsAdd::InsAdd(std::shared_ptr<ResourceFile> file, std::string line)
	: Instruction(file, line)
{
}

void InsAdd::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
	InstructionObject res;
	res = (sources[0]->swizzle(swizzleList[0])) * minusList[0]
		+ (sources[1]->swizzle(swizzleList[1])) * minusList[1];
	dest->mask(mask, res);
}

InsDp2::InsDp2(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsDp2::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

InsSample_indexable::InsSample_indexable(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsSample_indexable::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

InsSqrt::InsSqrt(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsSqrt::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

InsLt::InsLt(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsLt::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

InsMovc::InsMovc(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsMovc::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

InsDp3::InsDp3(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsDp3::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

InsRsq::InsRsq(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsRsq::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

InsMul::InsMul(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsMul::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
	InstructionObject res;
	res = (sources[0]->swizzle(swizzleList[0])) * minusList[0]
		* (sources[1]->swizzle(swizzleList[1])) * minusList[1];
	dest->mask(mask, res);
}

InsMov::InsMov(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsMov::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

InsMax::InsMax(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsMax::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

InsLog::InsLog(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsLog::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

InsExp::InsExp(std::shared_ptr<ResourceFile> file, std::string line)
	:Instruction(file, line)
{
}

void InsExp::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
}

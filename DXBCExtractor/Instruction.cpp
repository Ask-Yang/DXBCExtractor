#include "Instruction.h"
using namespace std;
Instruction::Instruction(std::shared_ptr<ResourceFile> file, std::string line)
	:resFile(file)
{
	build(line);
}

// ��������� 
// ��һ����ֻ��һ������ ���� ps_2_2 / nop
// �ڶ�����ֻ��һ�������һ��dst ���� texkill dst
// ����������sources�� ���� abs dst, src

// Ȼ�������mask��swizzle����û�У�mask swizzle�������һ����
void Instruction::build(std::string line)
{
	rawLine = line;
	const string under_point = ".";
	const string space = " ";
	size_t next = 0, last = 0, point = 0;
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
			mask = line.substr(point + 1, next - 1 - point - 1); 
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
		if (line[last] == '-')
			minusList.push_back(-1);
		else
			minusList.push_back(1);
		point = line.substr(last, next).find(under_point);
		if (point == string::npos)
			swizzleList.push_back("");
		else
			swizzleList.push_back(line.substr(point + 1, next - 1 - point - 1));
		last = next + 1;
	}
	if (line[last] == '-')
		minusList.push_back(-1);
	else
		minusList.push_back(1);
	point = line.find(under_point, last);
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

}

InsAdd::InsAdd(std::shared_ptr<ResourceFile> file, std::string line)
	: Instruction(file, line)
{
}

void InsAdd::calcu(InsObjPtr dest, std::vector<InsObjPtr> sources)
{
	InstructionObject res;
	for (int i = 0; i < sources.size(); i++)
	{
		InstructionObject temp;
		temp = (sources[i]->swizzle(swizzleList[i])) * minusList[i];
		res = res + temp;
	}
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

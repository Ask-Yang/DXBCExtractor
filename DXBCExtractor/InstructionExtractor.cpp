#include "InstructionExtractor.h"
using namespace std;
InstructionExtractor::InstructionExtractor(std::shared_ptr<ResourceFile> _resFile)
{
    resFile = _resFile;
}
void InstructionExtractor::instructionObjectExtract(string line, std::vector<InsObjPtr>& sources, InsPtr& operation)
{
    operation = createInstruction(line);
    InsObjPtr dest;
    createInsObject(line, dest, sources);
}
InsObjPtr InstructionExtractor::destObjExtract(std::string line)
{
    vector<InsObjPtr> vec;
    InsObjPtr dest;
    createInsObject(line, dest, vec);
    return dest;
}
bool InstructionExtractor::isObjectDest(string line, InsObjPtr dest)
{
    string delimiter = " ";
    size_t last = 0, next = 0;
    if ((next = line.find(delimiter)) != string::npos)
    {
        last = next + 1;
        string destStr;
        if ((next = line.find(delimiter, last)) != string::npos)
            destStr = line.substr(last, next - last);
        else
            destStr = line.substr(last);
        size_t point = 0;
        if ((point = destStr.find(".")) != string::npos)
            destStr = destStr.substr(0, point);
        return destStr == dest->name;
    }
    else
        return false;
}
InsPtr InstructionExtractor::createInstruction(std::string line)
{
    string delimiter = " ";
    size_t pos = 0;
    string insStr;
    if ((pos = line.find(delimiter)) != string::npos)
        insStr = line.substr(0, pos);
    else
        return nullptr;

    if (instructionLibrary.find(insStr) != instructionLibrary.end())
    {
        if (insStr == "mad")
            return make_shared<InsMad>(resFile, line);
        else if (insStr == "dp2")
            return make_shared<InsDp2>(resFile, line);
        else if (insStr == "sample_indexable(texture2d)(float,float,float,float)")
            return make_shared<InsSample_indexable>(resFile, line);
        else if (insStr == "sqrt")
            return make_shared<InsSqrt>(resFile, line);
        else if (insStr == "lt")
            return make_shared<InsLt>(resFile, line);
        else if (insStr == "movc")
            return make_shared<InsMovc>(resFile, line);
        else if (insStr == "dp3")
            return make_shared<InsDp3>(resFile, line);
        else if (insStr == "rsq")
            return make_shared<InsRsq>(resFile, line);
        else if (insStr == "mul")
            return make_shared<InsMul>(resFile, line);
        else if (insStr == "mov")
            return make_shared<InsMov>(resFile, line);
        else if (insStr == "add")
            return make_shared<InsAdd>(resFile, line);
        else if (insStr == "max")
            return make_shared<InsMax>(resFile, line);
        else if (insStr == "log")
            return make_shared<InsLog>(resFile, line);
        else if (insStr == "exp")
            return make_shared<InsExp>(resFile, line);
        else
            return make_shared<Instruction>(resFile, line);
    }
    else
        return make_shared<Instruction>(resFile, line);
}

void InstructionExtractor::createInsObject(std::string line, InsObjPtr& dest, std::vector<InsObjPtr>& sources)
{
    string delimiter = " ";
    size_t last = 0, next = 0;
    if((next = line.find(delimiter)) != string::npos)
    {
        last = next + 1;
        string destStr;
        if ((next = line.find(delimiter, last)) != string::npos)
            destStr = line.substr(last, next - last);
        else
            destStr = line.substr(last);
        dest = createSingleInsObj(destStr);
    }
    else
    {
        dest = nullptr;
        return;
    }

    last = next + 1;
    if (line[last] == '-')
        ++last;
    InsObjPtr source;
    while ((next = line.find(delimiter, last)) != string::npos)
    {
        if (line[last] == '-')
            ++last;
        string objStr;
        if (line[last] == 'l' && line[last + 1] == '(')
        {
            next = line.find(")", last);
            ++next;
            objStr = line.substr(last, next - last);
            ++next;
        }
        else
            objStr = line.substr(last, next - last);
        source = createSingleInsObj(objStr);
        sources.push_back(source);
        last = next + 1;
    }
    if (last > line.size())
        return;
    if (line[last] == '-')
        ++last;
    source = createSingleInsObj(line.substr(last));                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
    sources.push_back(source);
}

InsObjPtr InstructionExtractor::createSingleInsObj(std::string objStr)
{
    if (objStr == "")
        return nullptr;
    size_t point = 0;
    InsObjPtr obj;
    if (((point = objStr.find(".")) != string::npos) && objStr[0] != 'l' && objStr[1] != '(')
        objStr = objStr.substr(0, point);
    if (resFile->res.find(objStr) != resFile->res.end())
        obj = resFile->res[objStr];
    else
    {
        // 为了防止循环引用，使用一个Calcu的obj作为对应的计算单元，所有计算将会对这个单元进行，而绑定到resFile上的则是另一个
        // 作为和指令对应的绑定单元
        obj = make_shared<InstructionObject>(objStr);
        InsNodePtr node = make_shared<InsNode>(Vec4f(0, 0, 0, 0));
        InsObjPtr objCalcu = make_shared<InstructionObject>(objStr);
        objCalcu->setName(objStr);
        node->destObj = objCalcu;
        //node->signs.insert(objStr);
        NameAdapterPtr adapter = make_shared<ObjNameAdapter>(objStr);
        objCalcu->adapter = adapter;
        // node->line = "Object Start Here: ";
        obj->CalcuObj = objCalcu;
        obj->setInitNode(node);
        resFile->res[objStr] = obj;
    }
    return obj;
}

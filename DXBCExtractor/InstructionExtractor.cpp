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
        if ((next = line.find(delimiter)) != string::npos)
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
    if ((pos = line.find(delimiter) != string::npos))
        insStr = line.substr(0, pos);
    else
        return nullptr;

    if (instructionLibrary.find(insStr) != instructionLibrary.end())
    {
        if (insStr == "mad")
            return make_shared<InsMad>(resFile, insStr);
        else if (insStr == "dp2")
            return make_shared<InsDp2>(resFile, insStr);
        else if (insStr == "sample_indexable")
            return make_shared<InsSample_indexable>(resFile, insStr);
        else if (insStr == "sqrt")
            return make_shared<InsSqrt>(resFile, insStr);
        else if (insStr == "lt")
            return make_shared<InsLt>(resFile, insStr);
        else if (insStr == "movc")
            return make_shared<InsMovc>(resFile, insStr);
        else if (insStr == "dp3")
            return make_shared<InsDp3>(resFile, insStr);
        else if (insStr == "rsq")
            return make_shared<InsRsq>(resFile, insStr);
        else if (insStr == "mul")
            return make_shared<InsMul>(resFile, insStr);
        else if (insStr == "mov")
            return make_shared<InsMov>(resFile, insStr);
        else if (insStr == "add")
            return make_shared<InsAdd>(resFile, insStr);
        else if (insStr == "max")
            return make_shared<InsMax>(resFile, insStr);
        else if (insStr == "log")
            return make_shared<InsLog>(resFile, insStr);
        else
            return nullptr;
    }
    else
        return nullptr;
}

void InstructionExtractor::createInsObject(std::string line, InsObjPtr& dest, std::vector<InsObjPtr>& sources)
{
    string delimiter = " ";
    size_t last = 0, next = 0;
    if((next = line.find(delimiter)) != string::npos)
    {
        last = next + 1;
        string destStr;
        if ((next = line.find(delimiter)) != string::npos)
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
    InsObjPtr source;
    while ((next = line.find(delimiter)) != string::npos)
    {
        string objStr = line.substr(last, next - last);
        source = createSingleInsObj(objStr);
        sources.push_back(source);
        last = next + 1;
    }
    source = createSingleInsObj(line.substr(last));
    sources.push_back(source);
}

InsObjPtr InstructionExtractor::createSingleInsObj(std::string objStr)
{
    size_t point = 0;
    InsObjPtr obj;
    if ((point = objStr.find(".")) != string::npos)
        objStr = objStr.substr(0, point);
    if (resFile->res.find(objStr) != resFile->res.end())
        obj = resFile->res[objStr];
    else
    {
        obj = make_shared<InstructionObject>(objStr);
        resFile->res[objStr] = obj;
    }
    return obj;
}

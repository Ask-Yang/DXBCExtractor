#include "InstructionExtractor.h"
using namespace std;
std::shared_ptr<Instruction> InstructionExtractor::createInstruction(std::string line)
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
        if()
    }
}

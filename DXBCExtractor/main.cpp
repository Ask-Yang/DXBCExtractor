// 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Instruction.h"
#include "InstructionObject.h"
#include "InstructionExtractor.h"
using namespace std;

struct InstructionTreeNode{
    shared_ptr<InstructionObject> dest;
    shared_ptr<Instruction> operation;
    vector<shared_ptr<InstructionTreeNode>> children;
    shared_ptr<InstructionTreeNode> parent;
    InstructionTreeNode(shared_ptr<InstructionObject> dest, shared_ptr<Instruction> operation);
    InstructionTreeNode(shared_ptr<InstructionObject> dest);
};
void readTXTtoVec(vector<string>& src, string filepath);
bool isDesInstructionObjectLeft(string line, shared_ptr<InstructionObject> dest);
void instructionObjectExtractor(string line, vector<shared_ptr<InstructionObject>>& sources, shared_ptr<Instruction> operation);
void  findInstructionObject(int lineNumber, shared_ptr<InstructionTreeNode> destNode);

vector<string> dxbcSrc;
InstructionExtractor insExtractor;

int main()
{
    readTXTtoVec(dxbcSrc, "dxbc.txt");

}

void readTXTtoVec(vector<string>& src, string filepath)
{
    ifstream fin;
    fin.open(filepath);
    string str;
    while (!fin.eof())
    {
        getline(fin, str);
        src.push_back(str);
    }
    fin.close();
}

bool isDesInstructionObjectLeft(string line, shared_ptr<InstructionObject> dest)
{
    return dest->isObjectLeft(line);
}

void instructionObjectExtractor(string line, vector<shared_ptr<InstructionObject>>& sources, shared_ptr<Instruction> operation)
{

}

void  findInstructionObject(int lineNumber, shared_ptr<InstructionTreeNode> destNode)
{
    int findLine = lineNumber;
    while (findLine>=0 && !isDesInstructionObjectLeft(dxbcSrc[findLine--], destNode->dest));
    if (findLine < 0)
        return;
    vector<shared_ptr<InstructionObject>> sources;
    shared_ptr<Instruction> operation;
    instructionObjectExtractor(dxbcSrc[++findLine], sources, operation);
    destNode->operation = operation;
    for (auto& object : sources)
    {
        shared_ptr<InstructionTreeNode> sourceTreeNode = make_shared<InstructionTreeNode>(object);
        findInstructionObject(--findLine, sourceTreeNode);
        sourceTreeNode->parent = destNode;
        destNode->children.push_back(sourceTreeNode);
    }
}

InstructionTreeNode::InstructionTreeNode(shared_ptr<InstructionObject> dest, shared_ptr<Instruction> operation)
{
}

InstructionTreeNode::InstructionTreeNode(shared_ptr<InstructionObject> dest)
{
}

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
struct InstructionTreeNode;
typedef shared_ptr<InstructionTreeNode> InsTreeNodePtr;
struct InstructionTreeNode{
    InsObjPtr dest;
    InsPtr operation;
    vector<InsTreeNodePtr> children;
    InsTreeNodePtr parent;
    InstructionTreeNode(InsObjPtr dest, InsPtr operation);
    InstructionTreeNode(InsObjPtr dest);
};
void readTXTtoVec(vector<string>& src, string filepath);
void findInstructionObject(int lineNumber, InsTreeNodePtr destNode, vector<string>& dxbcSrc, InstructionExtractor& insExtractor);



int main()
{
    shared_ptr<ResourceFile> resFile = make_shared<ResourceFile>();
    InstructionExtractor insExtractor(resFile);
    vector<string> dxbcSrc;
    readTXTtoVec(dxbcSrc, "dxbc.txt");
    int srcFinal = dxbcSrc.size() - 2;
    InsObjPtr finalObj = insExtractor.destObjExtract(dxbcSrc[srcFinal--]);
    InsTreeNodePtr root = make_shared<InstructionTreeNode>(finalObj);
    findInstructionObject(srcFinal, root, dxbcSrc, insExtractor);
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

void findInstructionObject(int lineNumber, InsTreeNodePtr destNode, vector<string>& dxbcSrc, InstructionExtractor& insExtractor)
{
    int findLine = lineNumber;
    while (findLine>=0 && !insExtractor.isObjectDest(dxbcSrc[findLine--], destNode->dest));
    if (findLine < 0)
        return;
    vector<InsObjPtr> sources;
    InsPtr operation;
    insExtractor.instructionObjectExtract(dxbcSrc[++findLine], sources, operation);
    destNode->operation = operation;
    for (auto& object : sources)
    {
        InsTreeNodePtr sourceTreeNode = make_shared<InstructionTreeNode>(object);
        findInstructionObject(--findLine, sourceTreeNode, dxbcSrc, insExtractor);
        sourceTreeNode->parent = destNode;
        destNode->children.push_back(sourceTreeNode);
    }
}

InstructionTreeNode::InstructionTreeNode(InsObjPtr dest, InsPtr operation)
{
    this->dest = dest;
    this->operation = operation;
}

InstructionTreeNode::InstructionTreeNode(InsObjPtr dest)
{
    this->dest = dest;
}

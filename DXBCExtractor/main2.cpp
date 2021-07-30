#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Instruction.h"
#include "InstructionObject.h"
#include "InstructionExtractor.h"
#include "InsNode.h"
using namespace std;

void readTXTtoVec2(vector<string>& src, string filepath)
{
    ifstream fin;
    fin.open(filepath);
    if (!fin.is_open())
    {
        cout << "File Opening Failed!" << endl;
        return;
    }
    string str;
    while (!fin.eof())
    {
        getline(fin, str);
        src.push_back(str);
    }
    fin.close();
}

void setInitNodes(vector<InsNodePtr>& sourceNodes) {

}

int main() {
    shared_ptr<ResourceFile> resFile = make_shared<ResourceFile>();
    InstructionExtractor insExtractor(resFile);
    vector<string> dxbcSrc;
    readTXTtoVec2(dxbcSrc, "D:\\DXBCExtractor_github\\DXBCExtractor\\dxbc.txt");
    vector<InsNodePtr> nodes;
    for (int i = 0; i < dxbcSrc.size(); i++)
    {
        InsObjPtr dest;
        vector<InsObjPtr> sources;
        InsPtr instruction;
        insExtractor.createInsObject(dxbcSrc[i], dest, sources);
        instruction = insExtractor.createInstruction(dxbcSrc[i]);
        vector<InsNodePtr> sourceNodes;
        for (auto& insObj : sources)
            sourceNodes.push_back(insObj->getCurrentNode());
        InsNodePtr current = make_shared<InsNode>(dxbcSrc[i], dest, sourceNodes, instruction);
        if(dest)
            dest->setNewNode(current);
        nodes.push_back(current);
    }
    setInitNodes(nodes);
    for (auto& node : nodes)
        node->exec();
    for (auto& objPair : resFile->res)
        objPair.second->print();
	return 0;
}
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "Instruction.h"
#include "InstructionObject.h"
#include "InstructionExtractor.h"
#include "InsNode.h"
using namespace std;

size_t findFirstLetter(string str) {
    size_t pos = 10000;
    for (int i = 0; i < 26; i++) {
        pos = min(pos, str.find('a' + i));
    }
    return pos;
}

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
    getline(fin, str);
    getline(fin, str);
    getline(fin, str); 
    // SKIP
    //Shader hash 0d39dcc8-6939aba8-f3773300-c06d1865
    //
    //ps_5_0
    while (!fin.eof())
    {
        getline(fin, str);
        if (str.size() != 0)
        {
            str = str.substr(findFirstLetter(str));
            if(str.find("dcl_") == string::npos) // skip dcl_ÉùÃ÷
                src.push_back(str);
        }
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
    for (int i = 0; i < dxbcSrc.size() - 1; i++) // skip ret
    {
        //if (i == 10)
        //    cout << "debug" << endl;
        InsObjPtr dest;
        vector<InsObjPtr> sources;
        InsPtr instruction;
        insExtractor.createInsObject(dxbcSrc[i], dest, sources);
        instruction = insExtractor.createInstruction(dxbcSrc[i]);
        vector<InsNodePtr> sourceNodes;
        for (auto& insObj : sources)
            sourceNodes.push_back(insObj->getCurrentNode());
        InsNodePtr current = make_shared<InsNode>(dxbcSrc[i], dest->CalcuObj, sourceNodes, instruction);
        if(dest)
            dest->setNewNode(current);
        nodes.push_back(current);
    }
    setInitNodes(nodes);
    for (int i=0;i<nodes.size();i++)
        nodes[i]->exec();
    for (auto& objPair : resFile->res)
        objPair.second->print();
	return 0;
}
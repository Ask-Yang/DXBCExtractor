#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <set>

#include "Instruction.h"
#include "InstructionObject.h"
#include "InstructionExtractor.h"
#include "InsNode.h"
#include "ObjNameAdapter.h"
using namespace std;

set<string> shieldList = { /// 增加print()的屏蔽词
    "r#", "t#"
};

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
    /// SKIP
    ///Shader hash 0d39dcc8-6939aba8-f3773300-c06d1865
    ///
    ///ps_5_0
    while (!fin.eof())
    {
        getline(fin, str);
        if (str.size() != 0)
        {
            str = str.substr(findFirstLetter(str));
            if(str.find("dcl_") == string::npos) /// skip dcl_声明
                src.push_back(str);
        }
    }
    fin.close();
}
void writeVecToTXT(vector<string>& src, string filepath)
{
    ofstream outFile(filepath);
    for (int i = 0; i < src.size(); i++)
    {
        outFile << src[i];
    }
    outFile.close();
}

void setInitNodes(shared_ptr<ResourceFile> resFile) {
    /// 如果需要计算，需要在这里设置初值。
    resFile->res["r0"]->setInitNodeValue(Vec4f(0, 0, 0, 0));
}

int main() {
    shared_ptr<ResourceFile> resFile = make_shared<ResourceFile>();
    InstructionExtractor insExtractor(resFile);
    vector<string> dxbcSrc;
    readTXTtoVec2(dxbcSrc, "D:\\DXBCExtractor_github\\DXBCExtractor\\dxbc.txt");
    vector<InsNodePtr> nodes;
    // InsNode::printMode = 2; /// printMode要在创建节点之前更改
    for (int i = 0; i < dxbcSrc.size() - 1; i++) /// skip ret
    {
        if (i == 34)
            cout << "debug" << endl;
        InsObjPtr dest;
        vector<InsObjPtr> sources;
        InsPtr instruction;
        insExtractor.createInsObject(dxbcSrc[i], dest, sources);
        instruction = insExtractor.createInstruction(dxbcSrc[i]);
        vector<InsNodePtr> sourceNodes;
        for (auto& insObj : sources)
            sourceNodes.push_back(insObj->getCurrentNode());
        InsNodePtr current = make_shared<InsNode>(dxbcSrc[i], dest->CalcuObj, sourceNodes, instruction, i); 
        if(dest)
            dest->setNewNode(current);
        nodes.push_back(current);
    }
    vector<string> outFile;
    setInitNodes(resFile);
    for (int i=0;i<nodes.size();i++)
        nodes[i]->exec();
    
    for (auto& node : nodes)
        outFile.push_back(node->print());
    writeVecToTXT(outFile, "out.txt");
    ///for (auto& objPair : resFile->res) /// 按寄存器输出
        ///objPair.second->print();
	return 0;
}

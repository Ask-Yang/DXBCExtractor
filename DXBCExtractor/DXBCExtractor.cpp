// DXBCExtractor.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
#include <string>

#include "Operation.h"
#include "OperationObject.h"
using namespace std;

struct OperationTreeNode{
    OperationObject dest;
    Operation operation;
    vector<shared_ptr<OperationTreeNode>> children;
    shared_ptr<OperationTreeNode> parent;
    OperationTreeNode(OperationObject dest, Operation operation);
    OperationTreeNode(OperationObject dest);
};
bool isDestOperationObjectLeft(string line,const OperationObject& dest);
void operationObjectExtractor(string line, vector<shared_ptr<OperationObject>>& sources, Operation& operation);
void  findOperationObject(int lineNumber, shared_ptr<OperationTreeNode> destNode);
vector<string> dxbcSrc;


void  findOperationObject(int lineNumber, shared_ptr<OperationTreeNode> destNode)
{
    int findLine = lineNumber;
    while (findLine>=0 && !isDestOperationObjectLeft(dxbcSrc[findLine--], destNode->dest));
    if (findLine < 0)
        return;
    vector<shared_ptr<OperationObject>> sources;
    Operation operation;
    operationObjectExtractor(dxbcSrc[++findLine], sources, operation);
    destNode->operation = operation;
    for (auto& object : sources)
    {
        shared_ptr<OperationTreeNode> sourceTreeNode = make_shared<OperationTreeNode>(object);
        findOperationObject(--findLine, sourceTreeNode);
        sourceTreeNode->parent = destNode;
        destNode->children.push_back(sourceTreeNode);
    }
}

int main()
{
    
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

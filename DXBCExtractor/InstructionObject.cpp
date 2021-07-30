#include "InstructionObject.h"
#include "InsNode.h"
using namespace std;
InstructionObject::InstructionObject()
    :data(4)
{
}

InstructionObject::InstructionObject(std::string regName)
    :name(regName),
    data(4)
{
    int num = count(regName.begin(), regName.end(), ',');
    if (regName[0] == 'l' && regName[1]=='(')
    {
        string numStr = regName.substr(2, regName.size() - 3);
        string delimiter = " ";
        size_t last = 0, next = 0;
        for (int i = 0; i < num; i++)
        {
            next = numStr.find(delimiter, last);
            data[i] = stof(numStr.substr(last, next - 1 - last));
            last = next + 1;
        }
        if(num == 3)
            data[3] = stof(numStr.substr(last));
        else
        {
            for (int i = num; i < 4; i++)
                data[i] = 0;
        }
    }
}

void InstructionObject::setName(std::string regName)
{
    this->name = regName;
}

bool InstructionObject::isObjectLeft(std::string line)
{
    return false;
}

InstructionObject InstructionObject::swizzle(std::string swizzle)
{
    InstructionObject obj;
    for (int i = 0; i < swizzle.size(); i++)
    {
        if (swizzle[i] == 'x' || swizzle[i] == 'r')
            obj.data[i] = data[0];
        else if (swizzle[i] == 'y' || swizzle[i] == 'g')
            obj.data[i] = data[1];
        else if (swizzle[i] == 'z' || swizzle[i] == 'b')
            obj.data[i] = data[2];
        else if (swizzle[i] == 'w' || swizzle[i] == 'a')
            obj.data[i] = data[3];
    }
    if (swizzle == "")
        obj = *this;
    return obj;
}

void InstructionObject::mask(std::string mask, InstructionObject& obj)
{
    if (mask == "")
    {
        data = obj.data;
        return;
    }
    for (int i = 0; i < mask.size(); i++)
    {
        if (mask[i] == 'x' || mask[i] == 'r')
            data[0] = obj.data[i];
        else if (mask[i] == 'y' || mask[i] == 'g')
            data[1] = obj.data[i];
        else if (mask[i] == 'z' || mask[i] == 'b')
            data[2] = obj.data[i];
        else if (mask[i] == 'w' || mask[i] == 'a')
            data[3] = obj.data[i];
    }
       
}

InsNodePtr InstructionObject::getCurrentNode()
{
    return currentNode;
}

void InstructionObject::setNewNode(InsNodePtr next)
{
    currentNode->next = next;
    next->pre = currentNode;
    currentNode = currentNode->next;
}

void InstructionObject::setInitNodeValue(Vec4f val)
{
    objRoot->destValue = val;
}

void InstructionObject::setInitNode(InsNodePtr initNode)
{
    objRoot = initNode;
    currentNode = objRoot;
}

void InstructionObject::print()
{
    Vec4f initVal = objRoot->destValue;
    cout << "Object Name: " << name << " " << "Init Value: " << initVal << endl;
    InsNodePtr cur = objRoot;
    while (cur) {
        cur->print();
        cur = cur->next;
    }
}

InstructionObject operator+(const InstructionObject& left, const InstructionObject& right)
{
    InstructionObject obj;
    obj.data[0] = left.data[0] + right.data[0];
    obj.data[1] = left.data[1] + right.data[1];
    obj.data[2] = left.data[2] + right.data[2];
    obj.data[3] = left.data[3] + right.data[3];
    return obj;
}

InstructionObject operator*(const InstructionObject& left, const InstructionObject& right)
{
    InstructionObject obj;
    obj.data[0] = left.data[0] * right.data[0];
    obj.data[1] = left.data[1] * right.data[1];
    obj.data[2] = left.data[2] * right.data[2];
    obj.data[3] = left.data[3] * right.data[3];
    return obj;
}

InstructionObject operator-(const InstructionObject& left, const InstructionObject& right)
{
    InstructionObject obj;
    obj.data[0] = left.data[0] - right.data[0];
    obj.data[1] = left.data[1] - right.data[1];
    obj.data[2] = left.data[2] - right.data[2];
    obj.data[3] = left.data[3] - right.data[3];
    return obj;
}

InstructionObject operator*(const InstructionObject& left, const int& right)
{
    InstructionObject obj;
    obj.data[0] = left.data[0] * right;
    obj.data[1] = left.data[1] * right;
    obj.data[2] = left.data[2] * right;
    obj.data[3] = left.data[3] * right;
    return obj;
}

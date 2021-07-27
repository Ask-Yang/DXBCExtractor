#include "InstructionObject.h"

InstructionObject::InstructionObject()
    :data(4)
{
}

InstructionObject::InstructionObject(std::string regName)
    :name(regName),
    data(4)
{
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
    return obj;
}

void InstructionObject::mask(std::string mask, InstructionObject& obj)
{
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

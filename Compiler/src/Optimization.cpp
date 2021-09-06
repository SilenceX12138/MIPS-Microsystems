#include "../include/IntermediateCode.h"
#include "../include/Optimization.h"
#include "../include/utils.h"

void Optmization::startOptimize()
{
    peep();
    moveImm();
}

void Optmization::peep()
{
    vector<IntermediateCode> newList;
    IntermediateCode currentCode;
    for (int i = 0; i < (int)IntermediateCode::intermediateCodeList.size(); i++)
    {
        currentCode = IntermediateCode::intermediateCodeList[i];
        if (currentCode.type == GOTO && IntermediateCode::intermediateCodeList[i + 1].type == Label)
        {
            string toLabel = currentCode.itemList[3].getLabel();
            string nextLabel = IntermediateCode::intermediateCodeList[i + 1].itemList[3].getLabel();
            if (toLabel == nextLabel)
            {
                continue;
            }
        }
        newList.push_back(currentCode);
    }
    IntermediateCode::intermediateCodeList = newList;
}

void Optmization::moveImm()
{
    vector<IntermediateCode> newList;
    IntermediateCode currentCode;
    for (int i = 0; i < (int)IntermediateCode::intermediateCodeList.size(); i++)
    {
        currentCode = IntermediateCode::intermediateCodeList[i];
        if (currentCode.type == Add || currentCode.type == Mult)
        {
            int tempVal1, tempVal2;
            bool isVal1 = currentCode.itemList[0].getVal(tempVal1);
            bool isVal2 = currentCode.itemList[1].getVal(tempVal2);
            if (isVal1 && !isVal2)
            {
                swap(currentCode.itemList[0], currentCode.itemList[1]);
            }
        }
        newList.push_back(currentCode);
    }
    IntermediateCode::intermediateCodeList = newList;
}

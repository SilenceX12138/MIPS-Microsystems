#include "../include/IntermediateCode.h"
#include "../include/Optimization.h"
#include "../include/utils.h"

void Optmization::startOptimize()
{
    peep();
    moveImm();
    omitAssign();
    omitMult();
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

void Optmization::omitAssign()
{
    vector<IntermediateCode> newList;
    IntermediateCode currentCode;
    for (int i = 0; i < (int)IntermediateCode::intermediateCodeList.size(); i++)
    {
        currentCode = IntermediateCode::intermediateCodeList[i];
        if (currentCode.type == Assign)
        {
            // a = a
            IntermediateCodeItem item = currentCode.itemList[0];
            IntermediateCodeItem targetItem = currentCode.itemList[2];
            if (item.isTypeof(SymItem) && item.getSym().getId() == targetItem.getSym().getId())
            {
                continue;
            }
        }
        newList.push_back(currentCode);
    }
    IntermediateCode::intermediateCodeList = newList;
}

void Optmization::omitMult()
{
    vector<IntermediateCode> newList;
    IntermediateCode currentCode;
    for (int i = 0; i < (int)IntermediateCode::intermediateCodeList.size(); i++)
    {
        currentCode = IntermediateCode::intermediateCodeList[i];
        if (currentCode.type == Mult)
        {
            // a = 0 * x = 0
            // a = b * 1 = b
            // a = b * -1 = -b
            // a = b * 0 = 0
            IntermediateCodeItem item1 = currentCode.itemList[0];
            IntermediateCodeItem item2 = currentCode.itemList[1];
            IntermediateCodeItem targetItem = currentCode.itemList[2];
            int tempVal = -10101;
            if (item2.getVal(tempVal))
            {
                if (tempVal == 1)
                {
                    currentCode = IntermediateCode(Assign, {item1, targetItem});
                }
                else if (tempVal == 0)
                {
                    currentCode = IntermediateCode(Assign, {IntermediateCodeItem::create(RegItem, "0"), targetItem});
                }
                else if (tempVal == -1)
                {
                    currentCode = IntermediateCode(Sub, {IntermediateCodeItem::create(RegItem, "0"), item1, targetItem});
                }
            }
            if (item1.getVal(tempVal))
            {
                if (tempVal == 0)
                {
                    currentCode = IntermediateCode(Assign, {IntermediateCodeItem::create(RegItem, "0"), targetItem});
                }
            }
        }
        else if (currentCode.type == Div)
        {
            // a = 0 / x = 0
            // a = b / 1 = b
            // a = b / -1 = -b
            IntermediateCodeItem item1 = currentCode.itemList[0];
            IntermediateCodeItem item2 = currentCode.itemList[1];
            IntermediateCodeItem targetItem = currentCode.itemList[2];
            int tempVal = -1;
            if (item2.getVal(tempVal))
            {
                if (tempVal == 1)
                {
                    currentCode = IntermediateCode(Assign, {item1, targetItem});
                }
                else if (tempVal == -1)
                {
                    currentCode = IntermediateCode(Sub, {IntermediateCodeItem::create(RegItem, "0"), item1, targetItem});
                }
            }
            if (item1.getVal(tempVal))
            {
                if (tempVal == 0)
                {
                    currentCode = IntermediateCode(Assign, {IntermediateCodeItem::create(RegItem, "0"), targetItem});
                }
            }
        }
        newList.push_back(currentCode);
    }
    IntermediateCode::intermediateCodeList = newList;
}

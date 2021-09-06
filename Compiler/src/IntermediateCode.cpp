#include <iomanip>

#include "../include/IntermediateCode.h"
#include "../include/StreamManager.h"

using namespace std;

vector<IntermediateCode> IntermediateCode::intermediateCodeList;

const string INTERMEDIATECODE_TABLE[] = {
    "UndefCode",
    // I/O
    "Read", "Write", "WriteOver",
    // calculate
    "Assign", "Add", "Sub", "Mult", "Div", "LoadArr", "SaveArr",
    // function
    "PushArg", "Call", "Ret", "Label",
    // branch
    "BGT", "BGE", "BLT", "BLE", "BEQ", "BNE", "GOTO"};

IntermediateCode::IntermediateCode()
{
    this->type = UndefCode;
    this->itemList.clear();
}

IntermediateCode::IntermediateCode(IntermediateCodeType type, vector<IntermediateCodeItem> itemList)
{
    this->type = type;
    this->itemList = vector<IntermediateCodeItem>(5, nullItem);
    switch (type)
    {
    case Read:
    case Write:
        this->itemList[0] = itemList[0];
        break;
    case WriteOver:
        break;
    case Assign:
        this->itemList[0] = itemList[0];
        this->itemList[2] = itemList[1];
        break;
    case Add:
    case Sub:
    case Mult:
    case Div:
    case LoadArr:
    case SaveArr:
        this->itemList[0] = itemList[0];
        this->itemList[1] = itemList[1];
        this->itemList[2] = itemList[2];
        break;
    case Label:
        this->itemList[3] = itemList[0];
        break;
    case Ret:
        this->itemList[0] = itemList.empty() ? nullItem : itemList[0];
        break;
    case Call:
        this->itemList[3] = itemList[0];
        break;
    case PushArg:
        this->itemList[0] = itemList[0];
        this->itemList[1] = itemList[1];
        this->itemList[3] = itemList[2];
        break;
    case BGT:
    case BGE:
    case BLT:
    case BLE:
    case BEQ:
    case BNE:
        this->itemList[0] = itemList[0];
        this->itemList[1] = itemList[1];
        this->itemList[3] = itemList[2];
        break;
    case GOTO:
        this->itemList[3] = itemList[0];
    default:
        break;
    }
}

IntermediateCode::IntermediateCode(const IntermediateCode &o)
{
    this->type = o.type;
    this->itemList = o.itemList;
}

void IntermediateCode::insert(IntermediateCodeType type, vector<IntermediateCodeItem> itemList)
{
    intermediateCodeList.push_back(IntermediateCode(type, itemList));
}

void IntermediateCode::dup(int start, int end)
{
    for (int i = start; i < end; i++)
    {
        intermediateCodeList.push_back(intermediateCodeList[i]);
    }
}

void IntermediateCode::startIntermediateCodeGenerate()
{
    for (int i = 0; i < (int)intermediateCodeList.size(); i++)
    {
        intermediatefileStringStream << intermediateCodeList[i] << endl;
    }
}

ostream &operator<<(ostream &output, const IntermediateCode &t)
{
    output << setw(15) << left << INTERMEDIATECODE_TABLE[t.type] << t.itemList[0] << t.itemList[1] << t.itemList[2] << t.itemList[3];
    return output;
}

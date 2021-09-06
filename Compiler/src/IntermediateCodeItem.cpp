#include <iomanip>
#include <string>

#include "../include/IntermediateCodeItem.h"
#include "../include/SymbolTable.h"

using namespace std;

IntermediateCodeItem nullItem = IntermediateCodeItem();

IntermediateCodeItem::IntermediateCodeItem()
{
    this->type = UndefItem;
    this->index = -1;
    this->immInt = 18373531;
    this->reg = -1;
    this->label.clear();
}

IntermediateCodeItem::IntermediateCodeItem(const IntermediateCodeItem &o)
{
    this->type = o.type;
    this->index = o.index;
    this->immInt = o.immInt;
    this->reg = o.reg;
    this->label = o.label;
}

int IntermediateCodeItem::getSymIndex()
{
    return this->index - 1;
}

Symbol IntermediateCodeItem::getSym()
{
    return SymbolTable::globalSymTable[this->index - 1];
}

bool IntermediateCodeItem::getVal(int &val)
{
    if (type == ImmIntItem || type == ImmCharItem)
    {
        val = immInt;
        return true;
    }
    else if (type == SymItem && getSym().getKind() == ConstSym)
    {
        val = getSym().getConstIntValue();
        return true;
    }
    return false;
}

int IntermediateCodeItem::getImmInt()
{
    return this->immInt;
}

int IntermediateCodeItem::getReg()
{
    return this->reg;
}

string IntermediateCodeItem::getLabel()
{
    return this->label;
}

IntermediateCodeItem IntermediateCodeItem::create(IntermediateCodeItemType type, string strText)
{
    IntermediateCodeItem tempItem;
    tempItem.type = type;
    switch (type)
    {
    case ImmIntItem:
        tempItem.immInt = stoi(strText);
        break;
    case ImmCharItem:
        tempItem.immInt = (int)strText[0];
        break;
    case RegItem:
        tempItem.reg = stoi(strText);
        break;
    case LabelItem:
        tempItem.label = strText;
        break;
    case StrItem:
    case SymItem:
        tempItem.index = stoi(strText);
        break;
    default:
        tempItem.index = -1;
    }
    return tempItem;
}

int IntermediateCodeItem::getType()
{
    return this->type;
}

bool IntermediateCodeItem::isTypeof(IntermediateCodeItemType expectedType)
{
    if (expectedType == ImmItem)
    {
        return (this->type == ImmIntItem) || (this->type == ImmCharItem);
    }
    return (this->type == expectedType);
}

ostream &operator<<(ostream &output, const IntermediateCodeItem &t)
{
    output << setw(15);
    switch (t.type)
    {
    case ImmIntItem:
        output << t.immInt;
        break;
    case ImmCharItem:
        output << "'" + string(1, (char)t.immInt) + "'";
        break;
    case RegItem:
        output << "$" + to_string(t.reg);
        break;
    case LabelItem:
        output << t.label;
        break;
    case StrItem:
    case SymItem:
        output << "sym_" + to_string(t.index);
        break;
    default:
        output << "\"\"";
    }
    return output;
}

#include <fstream>
#include <iostream>
#include <sstream>

#include "../include/Error.h"
#include "../include/IntermediateCode.h"
#include "../include/LexicalAnalysis.h"
#include "../include/GlobalConst.h"
#include "../include/Optimization.h"
#include "../include/StreamManager.h"
#include "../include/SyntaxAnalysis.h"
#include "../include/TargetCode.h"
#include "../include/utils.h"

using namespace std;

stringstream logfileStringstream;
stringstream errorfileStringstream;
stringstream lexicalfileStringstream;
stringstream syntaxfileStringstream;
stringstream intermediatefileStringStream;
stringstream targetfileStringStream;

ofstream logfile;
ofstream errorfile;
ofstream lexicalfile;
ofstream syntaxfile;
ofstream intermediatefile;
ofstream targetfile;

void createAnalyzefile()
{
    initialStream();
    LexicalAnalysis::readFile();
    if (Token::tokenList.empty())
    {
        cout << "Colpiler Feedback: Source code file is empty, Compilation aborted." << endl;
        return;
    }
    try
    {
        LexicalAnalysis::startLexicalAnalyze();
        SyntaxAnalysis::startSyntaxAnalyze();
        SymbolTable::display();
        createLogfile();
    }
    catch (exception e)
    {
        if (Error::hasError)
        {
            createErrorfile();
            cout << "Compiler Feedback: Error occurs, Compilation aborted." << endl;
        }
        return;
    }
    if (Error::hasError)
    {
        createErrorfile();
        cout << "Compiler Feedback: Error occurs, Compilation aborted." << endl;
        return;
    }
    IntermediateCode::startIntermediateCodeGenerate();
    // Optmization::startOptimize();
    createProcfile();
    TargetCode::startTargetCodeGenerate();
    createMipsfile();
}

void initialStream()
{
    logfileStringstream.clear();
    errorfileStringstream.clear();
    lexicalfileStringstream.clear();
    syntaxfileStringstream.clear();
}

void createLogfile()
{
    logfile.open("log.txt");
    logfile << logfileStringstream.str();
    logfile.close();
}

void createErrorfile()
{
    errorfile.open("error.txt");
    errorfile << errorfileStringstream.str();
    errorfile.close();
}

void createMipsfile()
{
    targetfile.open("mips.txt");
    targetfile << targetfileStringStream.str();
    targetfile.close();
}

void createProcfile()
{
    if (LOG_MODE)
    {
        lexicalfile.open("lex.txt");
        lexicalfile << lexicalfileStringstream.str();
        lexicalfile.close();
        syntaxfile.open("syntax.txt");
        syntaxfile << syntaxfileStringstream.str();
        syntaxfile.close();
        intermediatefile.open("intermediate.txt");
        intermediatefile << intermediatefileStringStream.str();
        intermediatefile.close();
    }
}

bool isLegalCharacter(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '_' || isalnum(c))
    {
        return true;
    }
    return false;
}

bool isLegalString(string s)
{
    for (int i = 0; i < (int)s.size(); i++)
    {
        int charOrder = (int)s[i];
        if (charOrder == 32 || charOrder == 33 || (charOrder >= 35 && charOrder <= 126))
        {
            continue;
        }
        return false;
    }
    return true;
}

SymbolType tokenType2SymbolType(Token t)
{
    if (t.isTypeof(INTTK))
    {
        return IntSym;
    }
    else if (t.isTypeof(CHARTK))
    {
        return CharSym;
    }
    return UndefSymType;
}

FunctionRetType tokenType2RetType(Token t)
{
    if (t.isTypeof(INTTK))
    {
        return IntRet;
    }
    else if (t.isTypeof(CHARTK))
    {
        return CharRet;
    }
    return UndefRetType;
}

IntermediateCodeType revLogic(IntermediateCodeType raw)
{
    switch (raw)
    {
    case BGT:
        return BLE;
    case BGE:
        return BLT;
    case BLT:
        return BGE;
    case BLE:
        return BGT;
    case BEQ:
        return BNE;
    case BNE:
        return BEQ;
    default:
        return UndefCode;
    }
}

IntermediateCodeType token2RelaCode(Token t)
{
    switch (t.getCategory())
    {
    case LSS:
        return BLT;
    case LEQ:
        return BLE;
    case GRE:
        return BGT;
    case GEQ:
        return BGE;
    case NEQ:
        return BNE;
    case EQL:
        return BEQ;
    default:
        return UndefCode;
    }
}

string omitEscape(string str)
{
    string newStr = "";
    for (int i = 0; i < (int)str.length(); i++)
    {
        if (str[i] == '\\')
        {
            newStr.append("\\\\");
        }
        else
        {
            newStr.append(string(1, str[i]));
        }
    }
    return newStr;
}

int log2(int num)
{
    if (num & (num - 1))
    {
        return -1;
    }
    int x = 0;
    while (num > 1)
    {
        num >>= 1;
        x++;
    }
    return x;
}

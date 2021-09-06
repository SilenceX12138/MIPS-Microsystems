#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "../include/GlobalConst.h"
#include "../include/LexicalAnalysis.h"
#include "../include/StreamManager.h"
#include "../include/utils.h"

using namespace std;

string LexicalAnalysis::fileString = "";
Token LexicalAnalysis::currentToken = Token();
int LexicalAnalysis::currentLineNumber = 1;
int LexicalAnalysis::currentPosition = 0;
bool LexicalAnalysis::finish = false;

void LexicalAnalysis::readFile()
{
    ifstream t("testfile.txt");
    stringstream buffer;
    buffer << t.rdbuf();
    fileString = buffer.str();
    t.close();
    Token::tokenList.clear();
    while (getNextToken())
    {
        Token::tokenList.push_back(currentToken);
        lexicalfileStringstream << currentToken << endl;
    }
    return;
}

void LexicalAnalysis::startLexicalAnalyze()
{
    if (!finish)
    {
        logfileStringstream << "The lexical analysis terminated unexpectedly." << endl;
    }
    return;
}

char LexicalAnalysis::getChar()
{
    if (currentPosition == (int)fileString.size())
    {
        return EOF;
    }
    char nextChar = fileString[currentPosition];
    if (nextChar == '\r')
    {
        if (currentPosition + 1 < (int)fileString.size() && fileString[currentPosition + 1] == '\n')
        {
            currentPosition++;
        }
        currentLineNumber++;
    }
    else if (nextChar == '\n')
    {
        currentLineNumber++;
    }
    currentPosition++;
    return nextChar;
}

void LexicalAnalysis::ungetChar()
{
    currentPosition--;
    if (fileString[currentPosition] == '\n')
    {
        if (currentPosition - 1 > 0 && fileString[currentPosition - 1] == '\r')
        {
            currentPosition--;
        }
        currentLineNumber--;
    }
    else if (fileString[currentPosition] == '\r')
    {
        currentLineNumber--;
    }
    return;
}

bool LexicalAnalysis::isAlphaOrUnderscore(char c)
{
    if (c == '_' || isalpha(c))
    {
        return true;
    }
    return false;
}

bool LexicalAnalysis::getNextToken()
{
    char tempChar;
    tempChar = getChar();
    while (isspace(tempChar))
    {
        tempChar = getChar();
    }
    if (tempChar == EOF)
    {
        finish = true;
        return false;
    }
    if (tempChar == '!')
    {
        tempChar = getChar();
        if (tempChar == '=')
        {
            currentToken = Token(NEQ, "!=", currentLineNumber);
            return true;
        }
        return false;
    }
    if (tempChar == '(')
    {
        currentToken = Token(LPARENT, "(", currentLineNumber);
        return true;
    }
    if (tempChar == ')')
    {
        currentToken = Token(RPARENT, ")", currentLineNumber);
        return true;
    }
    if (tempChar == '*')
    {
        currentToken = Token(MULT, "*", currentLineNumber);
        return true;
    }
    if (tempChar == '+')
    {
        currentToken = Token(PLUS, "+", currentLineNumber);
        return true;
    }
    if (tempChar == ',')
    {
        currentToken = Token(COMMA, ",", currentLineNumber);
        return true;
    }
    if (tempChar == '-')
    {
        currentToken = Token(MINU, "-", currentLineNumber);
        return true;
    }
    if (tempChar == '/')
    {
        currentToken = Token(DIV, "/", currentLineNumber);
        return true;
    }
    if (tempChar == ':')
    {
        currentToken = Token(COLON, ":", currentLineNumber);
        return true;
    }
    if (tempChar == ';')
    {
        currentToken = Token(SEMICN, ";", currentLineNumber);
        return true;
    }
    if (tempChar == '<')
    {
        tempChar = getChar();
        if (tempChar != '=')
        {
            ungetChar();
            currentToken = Token(LSS, "<", currentLineNumber);
            return true;
        }
        else if (tempChar == '=')
        {
            currentToken = Token(LEQ, "<=", currentLineNumber);
            return true;
        }
        return false;
    }
    if (tempChar == '=')
    {
        tempChar = getChar();
        if (tempChar != '=')
        {
            ungetChar();
            currentToken = Token(ASSIGN, "=", currentLineNumber);
            return true;
        }
        else if (tempChar == '=')
        {
            currentToken = Token(EQL, "==", currentLineNumber);
            return true;
        }
        return false;
    }
    if (tempChar == '>')
    {
        tempChar = getChar();
        if (tempChar != '=')
        {
            ungetChar();
            currentToken = Token(GRE, ">", currentLineNumber);
            return true;
        }
        else if (tempChar == '=')
        {
            currentToken = Token(GEQ, ">=", currentLineNumber);
            return true;
        }
        return false;
    }
    if (tempChar == '[')
    {
        currentToken = Token(LBRACK, "[", currentLineNumber);
        return true;
    }
    if (tempChar == ']')
    {
        currentToken = Token(RBRACK, "]", currentLineNumber);
        return true;
    }
    if (tempChar == '{')
    {
        currentToken = Token(LBRACE, "{", currentLineNumber);
        return true;
    }
    if (tempChar == '}')
    {
        currentToken = Token(RBRACE, "}", currentLineNumber);
        return true;
    }
    if (tempChar == '\'')
    {
        string tempStr = "";
        while (true)
        {
            tempChar = getChar();
            if (tempChar == '\'')
            {
                break;
            }
            tempStr += tempChar;
        }
        if (!isLegalCharacter(tempStr[0]) || tempStr.empty())
        {
            Error::outputError(currentLineNumber, IllegalToken);
        }
        currentToken = Token(CHARCON, tempStr, currentLineNumber);
        return true;
    }
    if (tempChar == '"')
    {
        string tempStr = "";
        while (true)
        {
            tempChar = getChar();
            if (tempChar == '"')
            {
                break;
            }
            tempStr += tempChar;
        }
        if (!isLegalString(tempStr) || tempStr.empty())
        {
            Error::outputError(currentLineNumber, IllegalToken);
        }
        currentToken = Token(STRCON, tempStr, currentLineNumber);
        return true;
    }
    if (isdigit(tempChar))
    {
        string tempStr(1, tempChar);
        while (true)
        {
            tempChar = getChar();
            if (!isdigit(tempChar))
            {
                break;
            }
            tempStr += tempChar;
        }
        ungetChar();
        currentToken = Token(INTCON, tempStr, currentLineNumber);
        currentToken.setValue(stoi(tempStr));
        return true;
    }
    if (isAlphaOrUnderscore(tempChar))
    {
        string rawStr(1, tempChar);
        while (true)
        {
            tempChar = getChar();
            if (!isAlphaOrUnderscore(tempChar) && !isdigit(tempChar))
            {
                break;
            }
            rawStr += tempChar;
        }
        ungetChar();
        string tempStr = rawStr;
        transform(tempStr.begin(), tempStr.end(), tempStr.begin(), ::tolower);
        if (tempStr == "case")
        {
            currentToken = Token(CASETK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "char")
        {
            currentToken = Token(CHARTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "const")
        {
            currentToken = Token(CONSTTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "default")
        {
            currentToken = Token(DEFAULTTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "else")
        {
            currentToken = Token(ELSETK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "for")
        {
            currentToken = Token(FORTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "if")
        {
            currentToken = Token(IFTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "int")
        {
            currentToken = Token(INTTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "main")
        {
            currentToken = Token(MAINTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "printf")
        {
            currentToken = Token(PRINTFTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "return")
        {
            currentToken = Token(RETURNTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "scanf")
        {
            currentToken = Token(SCANFTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "switch")
        {
            currentToken = Token(SWITCHTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "void")
        {
            currentToken = Token(VOIDTK, rawStr, currentLineNumber);
            return true;
        }
        if (tempStr == "while")
        {
            currentToken = Token(WHILETK, rawStr, currentLineNumber);
            return true;
        }
        currentToken = Token(IDENFR, rawStr, currentLineNumber);
        return true;
    }
    return false;
}
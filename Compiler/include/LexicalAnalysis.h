#ifndef _LEXICALANALYSIS_H_
#define _LEXICALANALYSIS_H_

#include <string>

#include "Error.h"
#include "Token.h"

using namespace std;

// Analyse the lex of source file.
class LexicalAnalysis
{
private:
    static string fileString;
    static Token currentToken;
    static int currentLineNumber;
    static int currentPosition;
    static bool finish;

    static char getChar();
    static void ungetChar();
    static bool getNextToken();
    static bool isAlphaOrUnderscore(char c);

public:
    static void readFile();
    static void startLexicalAnalyze();
};

#endif
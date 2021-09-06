#ifndef _ERROR_H_
#define _ERROR_H_

#include <string>

using namespace std;

extern const string ERRORCODE_TABLE[];

enum ErrorType
{
    IllegalToken,           // a
    DuplicateName,          // b
    UndefinedName,          // c
    ArgCountMismatch,       // d
    ArgTypeMismatch,        // e
    IllegalConditionType,   // f
    IllegalNonRetFunc,      // g
    IllegalRetFunc,         // h
    IllegalArrayIndex,      // i
    ConstModification,      // j
    SemicnMissing,          // k
    RparentMissing,         // l
    RbrackMissing,          // m
    ArrayInitMismatch,      // n
    ConstTypeMismatch,      // o
    DefaultStatementMissing // p
};

class Error
{
public:
    static bool hasError;

    Error();
    static void outputError(int lineNumber, ErrorType errorType);
};

#endif
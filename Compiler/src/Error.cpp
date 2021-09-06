#include <iostream>
#include <sstream>
#include <fstream>

#include "../include/Error.h"
#include "../include/StreamManager.h"

using namespace std;

const string ERRORCODE_TABLE[] = {
    "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p"};

bool Error::hasError = false;

void Error::outputError(int lineNumber, ErrorType errorType)
{
    hasError = true;
    errorfileStringstream << lineNumber << " " << ERRORCODE_TABLE[errorType] << endl;
}
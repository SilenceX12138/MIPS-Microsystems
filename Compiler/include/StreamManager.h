#ifndef _STREAMMANAGER_H_
#define _STREAMMANAGER_H_

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

extern stringstream logfileStringstream;
extern stringstream errorfileStringstream;
extern stringstream lexicalfileStringstream;
extern stringstream syntaxfileStringstream;
extern stringstream intermediatefileStringStream;
extern stringstream targetfileStringStream;

extern ofstream logfile;
extern ofstream errorfile;
extern ofstream lexicalfile;
extern ofstream syntaxfile;
extern ofstream intermediatefile;
extern ofstream targetfile;

#endif
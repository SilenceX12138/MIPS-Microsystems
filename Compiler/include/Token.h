#ifndef _TOKEN_H_
#define _TOKEN_H_

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Hold token's basic information.
class Token
{
private:
	string text;
	string lowerText;
	int category;
	int lineNumber;
	int value; // default -1 except INTCON

public:
	static vector<Token> tokenList;
	static int currentTokenPos;

	Token();
	Token(int category, string text, int lineNumber);
	Token(const Token &t);
	friend ostream &operator<<(ostream &output, const Token &t);
	// 返回token的原始形式
	string getText();
	string getLowerText();
	int getCategory();
	int getLineNumber();
	int getValue();
	void setValue(int value);
	bool isTypeof(int expectedCategory);
};

extern const string CATEGORY_TABLE[];

#define NEQ 0
#define LPARENT 1
#define RPARENT 2
#define MULT 3
#define PLUS 4
#define COMMA 5
#define MINU 6
#define DIV 7
#define COLON 8
#define SEMICN 9
#define LSS 10
#define LEQ 11
#define ASSIGN 12
#define EQL 13
#define GRE 14
#define GEQ 15
#define LBRACK 16
#define RBRACK 17
#define CASETK 18
#define CHARTK 19
#define CONSTTK 20
#define DEFAULTTK 21
#define ELSETK 22
#define FORTK 23
#define IFTK 24
#define INTTK 25
#define MAINTK 26
#define PRINTFTK 27
#define RETURNTK 28
#define SCANFTK 29
#define SWITCHTK 30
#define VOIDTK 31
#define WHILETK 32
#define LBRACE 33
#define RBRACE 34
#define IDENFR 35
#define INTCON 36
#define CHARCON 37
#define STRCON 38

#endif

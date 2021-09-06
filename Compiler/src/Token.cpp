#include <algorithm>

#include "../include/Token.h"

using namespace std;

int Token::currentTokenPos = -1;
vector<Token> Token::tokenList;

// Sequence of the table is the same as MACRO definition in Token.h.
const string CATEGORY_TABLE[] = {
	// 0-4
	"NEQ", "LPARENT", "RPARENT", "MULT", "PLUS",
	// 5-9
	"COMMA", "MINU", "DIV", "COLON", "SEMICN",
	// 10-14
	"LSS", "LEQ", "ASSIGN", "EQL", "GRE",
	// 15-19
	"GEQ", "LBRACK", "RBRACK", "CASETK", "CHARTK",
	// 20-24
	"CONSTTK", "DEFAULTTK", "ELSETK", "FORTK", "IFTK",
	// 25-29
	"INTTK", "MAINTK", "PRINTFTK", "RETURNTK", "SCANFTK",
	// 30-34
	"SWITCHTK", "VOIDTK", "WHILETK", "LBRACE", "RBRACE",
	// 35-38
	"IDENFR", "INTCON", "CHARCON", "STRCON"};

Token::Token()
{
	this->text = "";
	this->lowerText = "";
	this->category = -1;
	this->lineNumber = 0;
	this->value = -1;
}

Token::Token(int category, string text, int lineNumber)
{
	this->text = text;
	this->lowerText = text;
	this->category = category;
	transform(this->lowerText.begin(), this->lowerText.end(), this->lowerText.begin(), ::tolower);
	this->lineNumber = lineNumber;
	this->value = -1;
}

Token::Token(const Token &t)
{
	this->text = t.text;
	this->lowerText = t.lowerText;
	this->category = t.category;
	this->lineNumber = t.lineNumber;
	this->value = t.value;
}

ostream &operator<<(ostream &output, const Token &t)
{
	output << CATEGORY_TABLE[t.category] << " " << t.text;
	return output;
}

string Token::getText()
{
	return this->text;
}

string Token::getLowerText()
{
	return this->lowerText;
}

int Token::getCategory() 
{
	return this->category;
}

int Token::getLineNumber()
{
	return this->lineNumber;
}

int Token::getValue()
{
	return this->value;
}

void Token::setValue(int value)
{
	this->value = value;
}

bool Token::isTypeof(int expectedCategory)
{
	return this->category == expectedCategory;
}

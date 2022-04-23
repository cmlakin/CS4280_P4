#ifndef SCANNER_h
#define SCANNER_h

#include <iostream>
#include <stdlib.h>
#include <string>
#include <cctype>
#include "token.h"

using namespace std;

// #define KW 1000;
// #define ID 1001;
// #define EOF 1002;
// #define NUM 1003;
// #define OP 1004;
// #define CMT 1005;
#define ERR -1
#define INITIAL 0
#define FINAL 1000

Token scanner(string&, int);
char look(string&);
char getChar(string&);
int getCol(char);
bool kwCheck(string&);
Token FSDriver(string&, int);

#endif

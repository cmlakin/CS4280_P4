// scan in and return one token
#include "scanner.h"

// store string and call getchar();
string tokenNames[] = {"Keyword", "Identifier", "EOF", "Number", "Operator",
                        "Comment"};

// declare FSA table here
const int statesRow = 9;
const int tokensCol = 10;                //   0    1     2     3     4     5     6    7      8    9
                                        //  a-z  A-Z   op[]   <     -    0-9    *    EOF    ws   ERR
const int table[statesRow][tokensCol] = { {   1,    3,    4,    5,   -1,    6,    7, 1003,  500,   -1},  //0(s0)
                                          {   2,    2,   -1,   -1,   -1,    2,   -1,   -1,   -1,   -1},  //1(s1)
                                          {   2,    2, 1002, 1002, 1002,    2, 1002, 1002, 1002, 1002},  //2(s2)
                                          {   3, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001, 1001},  //3(s3)
                                          {1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005},  //4(s4)
                                          {  -1,   -1,   -1,    4,    4,   -1,   -1,   -1,   -1,   -1},  //5(s5)
                                          {1004, 1004, 1004, 1004, 1004,    6, 1004, 1004, 1004, 1004},  //6(s6)
                                          {   7,    7,    7,    7,    7,    7,    8,   -1,    7,   -1},  //7(s7)
                                          {1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006}}; //8(s8)

// pass 2 arguemnts - string and line number
Token scanner(string& fileString, int lineN)  {
  //cout << "*** In scanner.cpp *** \n";
  //cout << "filestring = " << fileString << endl;
  Token temp;

  temp = FSDriver(fileString, lineN);

  // cout << "*** In scanner.cpp after FSDriver call *** \n";

  return temp;

}

char look(string& str){
  // cout << "--- in look\n";
  char lookAhead = '\0';

  if(str.length() > 0) {
    lookAhead = str.at(0);
    // cout << "lookAhead = " << lookAhead << endl;
  }
  else {
    // do something here
  }

  return lookAhead;
}

// site for string.at() https://www.geeksforgeeks.org/string-at-in-cpp/
// stie for string.end() https://www.javatpoint.com/cpp-string-end-function
char getChar(string& str) {
  // cout << "--- in getCahr\n";
  char next = '\0';
  // parse string for nextChar
  next = str.at(0);
  str.erase(0, 1);
  //cout << "remaining string = " << str << endl;

  return next;
}

int getCol(char currentChar){
  // cout << "--- in get col\n";
  int colNum = 0;
  // find FSA column

  if (currentChar == ' '){
    colNum = 8;
  }
  else if (isalpha(currentChar)){
    if (isupper(currentChar)){
      colNum = 1;
    }
    else {
      colNum = 0;
    }
  }
  else if (isdigit(currentChar)){
    colNum = 5;
  }
  else {
    for(int i = 0; i < 7; i++){
      if (currentChar == operator1[i].at(0)) {
        colNum = 2;
      }
    }
    if (colNum != 2) {
      if(currentChar == operator2){
        colNum = 3;
      }
      else if (currentChar == operator3) {
        colNum = 4;
      }
      else if (currentChar == comment){
        colNum = 6;
      }
      else if (currentChar == '\0') {
        colNum = 7;
      }
      else {
        //error - unknown character error
        colNum = 9;
      }
    }
  }

  return colNum;

}

bool kwCheck(string& str) {
  int counter = 0;
  for (int i = 0; i < 14; i++){
    if (str == keyword[i]) {
      return true;
    }
    else {
      counter++;
    }
  }
  if (counter == 13){
    return false;
  }
  ;
}

Token FSDriver(string& fileString, int line) // assume nextChar set, and used as column index
{
  int state = 0; //INITIAL; // (0 = S1 here)
  int nextState;
  Token token;
  string s = "";
  char nextChar = '\0';
  int fsaCol = 0;

  token.line = line;

  while (fileString.length() > 0 && isspace(look(fileString))) {
    char ws = '\0';
    ws = getChar(fileString);
  }
  if (fileString.length() == 0){
    // end of string
  }

  while (state != FINAL) {
    //cout << "state = " << state << endl;
    nextChar = look(fileString);
    fsaCol = getCol(nextChar);
    nextState = table[state][fsaCol];
    //cout << "next state = " << nextState << endl;
    if (nextState < 0) {
      //Error(); // report error and exit
      token.ID = nextState;
      token.chars = nextChar;
      return token;
    }
    else if (nextState >= 1000) { // put switch here instead of if statement
      if (nextState == KW_tk) { // need reserved keyword loop
        //cout << "in FSDriver keyword state\n";
        int check = kwCheck(s);
        if (check) {
          //cout << "KW_TK\n";
          token.ID = nextState;
          token.chars = s;
          return token; // or specific keyword
        }
        else if (s == "Done"){
          token.ID = 1007;
          return token;
        }
        else {
          //error
          token.ID = -2;
          token.chars = s;
          return token;
        }

      }
      else if (nextState >= ID_tk && nextState <= CMT_tk){
        token.ID = nextState;
        token.chars = s;

        return token;
      }

    }
    else if (nextState == 500) {
      fileString.erase(0);
      token.ID = 500;
      return token;
    }
    else {  // not FINAL
      state = nextState;
      char addChar = getChar(fileString);
      //cout << "addChar = " << addChar << endl;
      s = s + addChar;
      //cout << "s = " << s << endl;

    }
  }
  return token;
}

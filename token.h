#ifndef TOKEN_h
#define TOKEN_h

#include <iostream>
#include <string>


using namespace std;
// enum is going to return a value
enum tokenId {KW_tk = 1001, ID_tk = 1002, EOF_tk = 1003, NUM_tk = 1004,
              OP_tk = 1005, CMT_tk = 1006};

// tokenNames[EOF_tk] -> this will print EOF
extern string tokenNames[];


struct Token {
  int ID;  // type of token
  string chars;   // characters in token
  int line;      // line number
};


static std::string keyword[] = {"Again", "If", "Assign", "Move", "Show",
                                "Flip", "Name", "Home", "Do", "Spot",
                                "Place", "Here", "There"};
static std::string operator1[] = {"&", "+", "/", "%", ".", "{", "}"};
static char operator2 = '<';
static char operator3 = '-';
static char comment = '*';


#endif

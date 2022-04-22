#ifndef PARSER_h
#define PARSER_h

#include <iostream>
#include <fstream>
#include "node.h"
#include "token.h"
using namespace std;

node_t* getRoot();
node_t * parser(istream&);
Token getNextToken(istream&);

node_t* S(istream&, Token&);
node_t* R(istream&, Token&);
node_t* E(istream&, Token&);
node_t* A(istream&, Token&);
node_t* B(istream&, Token&);
node_t* C(istream&, Token&);
node_t* D(istream&, Token&);
node_t* F(istream&, Token&);
node_t* G(istream&, Token&);
node_t* T(istream&, Token&);
node_t* V(istream&, Token&);
node_t* H(istream&, Token&);
node_t* J(istream&, Token&);
node_t* K(istream&, Token&);
node_t* L(istream&, Token&);
node_t* W(istream&, Token&);
node_t* Z(istream&, Token&);

# endif

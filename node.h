#ifndef NODE_h
#define NODE_h

#include <list>
#include "token.h"


using std::list;
using std::string;

struct node_t {
  char label; // node label
  Token token;
  list<node_t> children; // list of words each node holds
  int level;


  // parent constructor
  node_t(char value) {
    this->label = value;
  }

  // token constructor
  node_t(Token tk) {
    token = tk;
    //this->label = '\0';
  }

  // copy constructor
  node_t(const node_t& rhs) {
    this->label  = rhs.label;
    this->children = rhs.children;
    this->token.chars = rhs.token.chars;
    this->token.ID = rhs.token.ID;
    this->level = rhs.level;
  }

  // copy constructor
  //node_t(const node_t& rhs) { }

}; // end of struct node_t

#endif

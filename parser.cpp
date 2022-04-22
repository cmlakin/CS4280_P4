#include <iostream>
#include <fstream>
#include "scanner.h"
#include "node.h"
#include "token.h"
#include "statSem.h"
#include "parser.h"

using namespace std;

string fileLine;
int lineNum = 0;
int levelNum = 0;
node_t* root = nullptr;

node_t* getRoot() {
  return root;
}

node_t * parser(istream& in) {
  Token tk;

  if (in.eof()) {
    cout << "Error: Empty file, no content.\n";
    cout << "Exiting program.\n";
  }

  tk = getNextToken(in);
  root = S(in, tk);

  return root;
}

Token getNextToken(istream& in) {
  //cout << "In getNextToken\n";
  if (fileLine.length() == 0){

    getline(in, fileLine);
    if (in.eof()){
      // return eof token - get code from p1
    }
    lineNum++;
    //cout << "fileLine = " << fileLine << endl;
  }
  return scanner(fileLine, lineNum);
}

//individual functions written out.
node_t* S(istream& in, Token& tk){
  node_t* p= new node_t('S');
  //cout << "in S token.chars = " << tk.chars << endl;
  p->level = levelNum;
  if (tk.chars == "Name") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in S token.chars = " << tk.chars << endl;
    // check if valid identifier token
    if (tk.ID == 1002) {
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in S token.chars = " << tk.chars << endl;
      // check for specific keyword token
      if (tk.chars == "Spot") {
        node_t t(tk);
        p->children.push_back(t);
        tk = getNextToken(in);
        // cout << "in S token.chars = " << tk.chars << endl;
        // check if valid identifier token
        if (tk.ID == 1002) {
          node_t t(tk);
          p->children.push_back(t);
          tk = getNextToken(in);
          // cout << "calling R\n";

          node_t* foo = R(in, tk);
          p->children.push_back(*foo);
          // cout << "-- in s after r\n";
          // cout << "calling E\n";
          foo = E(in, tk);
          p->children.push_back(*foo);
          // cout << "-- in s after e\n";
        }
        else {
          cout << "Error. Invalid entry in S(), exiting program.\n";
          exit(-1);
        }
      }
      else {
        cout << "Error. Invalid entry in S(), exiting program.\n";
        exit(-1);
      }
    }
    else {
      cout << "Error. Invalid entry in S(), exiting program.\n";
      exit(-1);
    }
  }
  else {
    cout << "Error. Invalid entry in S(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* R(istream& in, Token& tk) {
  node_t* p = new node_t('R');
  p->level = ++levelNum;
  // cout << "in R token.chars = " << tk.chars << endl;
  if (tk.chars == "Place") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "calling A\n";
    node_t* foo = A(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in r after  a\n";
    // cout << "calling B\n";
    node_t* foo1 = B(in, tk);
    p->children.push_back(*foo1);
    // cout << "-- in r after b\n";
    // cout << "in R token.chars = " << tk.chars << endl;
    if (tk.chars == "Home"){
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in R token.chars = " << tk.chars << endl;
    }
  }
  else {
    cout << "Error. Invalid entry in R(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* E(istream& in, Token& tk) {
  node_t* p= new node_t('E');
  p->level = ++levelNum;
  // cout << "in E token.chars = " << tk.chars << endl;
  if (tk.chars == "Show") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);

    // cout << "in E token.chars = " << tk.chars << endl;
    if (tk.ID == 1002) {
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in E token.chars = " << tk.chars << endl;
    }
    else {
      cout << "Error. Invalid entry in E(), exiting program.\n";
      exit(-1);
    }
  }
  else {
    cout << "Error. Invalid entry in E(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* A(istream& in, Token& tk) {
  node_t* p= new node_t('A');
  p->level = ++levelNum;
  // cout << "in A token.chars = " << tk.chars << endl;

  if (tk.chars == "Name") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in A token.chars = " << tk.chars << endl;

    if (tk.ID == 1002) {
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in A token.chars = " << tk.chars << endl;
    }
    else {
      cout << "Error. Invalid entry in A(), exiting program.\n";
      exit(-1);
    }
  }
  else {
    cout << "Error. Invalid entry in A(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* B(istream& in, Token& tk) {
  node_t* p= new node_t('B');
  p->level = ++levelNum;
  if (tk.chars == ".") {
    node_t t(tk);
    p->children.push_back(t);
    // cout << "in B token.chars = " << tk.chars << endl;
    tk = getNextToken(in);
    // cout << "in B token.chars = " << tk.chars << "\n calling C\n";
    node_t* foo = C(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in b  after <C>\n";
    // cout << "in B token.chars = " << tk.chars << endl;
    if (tk.chars == ".") {
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in B token.chars = " << tk.chars << "\n calling B\n";
      node_t* foo = B(in, tk);
      p->children.push_back(*foo);
      // cout << "-- in b after .<B>\n";
      // cout << "in B token.chars = " << tk.chars << "\n calling B\n";
    }
    else {
      cout << "Error. Invalid entry in B(), exiting program.\n";
      exit(-1);
    }
  }
  else if (tk.chars == "/") {
    // cout << "calling D /\n";
    node_t* foo = D(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in b after D /\n";
    // cout << "in B token.chars = " << tk.chars << endl;
  }
  else if (tk.chars == "Assign") {
    // cout << "calling D Assign\n";
    node_t* foo = D(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in b after D Assign\n";
    // cout << "in B token.chars = " << tk.chars << endl;

  }
  else if (tk.chars == "Spot" || tk.chars == "Move") {
    // cout << "calling D Spot/Move\n";
    node_t* foo = D(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in b after D Spot/Move\n";
    // cout << "in B token.chars = " << tk.chars << endl;

  }
  else if (tk.chars == "Flip") {
    // cout << "calling D Flip\n";
    node_t* foo = D(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in b after D Flip\n";
    // cout << "in B token.chars = " << tk.chars << endl;

  }
  else if (tk.chars == "Show") {
    // cout << "calling D Show\n";
    node_t* foo = D(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in b after D Show\n";
  }
  else if (tk.chars == "{") {
    // cout << "calling D {\n";
    node_t* foo = D(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in b after D {\n";
  }
  else {  // predicts B->(epslon)
    // I need to print empty in here for tk.chars
    Token temp = tk;
    temp.chars = "Empty";
    node_t t(temp);
    p->children.push_back(t);

  }
  --levelNum;
  return p;
}

node_t* C(istream& in, Token& tk) {
  node_t* p= new node_t('C');
  p->level = ++levelNum;
  // cout << "in C token.chars = " << tk.chars << endl;
  if (tk.chars == "{") {
    // cout << "calling F\n";
    node_t* foo = F(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in c after f\n";
    // cout << "in C token.chars = " << tk.chars << endl;

  }
  else if (tk.chars == "Here") {
    // cout << "calling G\n";
    node_t* foo = G(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in c after g\n";
    // cout << "in C token.chars = " << tk.chars << endl;
  }
  else {
    cout << "Error. Invalid entry in C(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}


node_t* D(istream& in, Token& tk) {
  node_t* p= new node_t('D');
  p->level = ++levelNum;
  // cout << "in D token.chars = " << tk.chars << endl;
  if (tk.chars == "/") {
    // cout << "calling H\n";
    node_t* foo = H(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in d after H\n";
    // cout << "in D after H token.chars = " << tk.chars << endl;
  }
  else if (tk.chars == "Assign") {
    // cout << "calling J\n";
    node_t* foo = J(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in d after j\n";
    // cout << "in D after J token.chars = " << tk.chars << endl;

  }
  else if (tk.chars == "Spot" || tk.chars == "Move") {
    // cout << "calling K\n";
    node_t* foo = K(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in d after k\n";
    // cout << "in D token.chars = " << tk.chars << endl;
  }
  else if (tk.chars == "Flip") {
    // cout << "calling L\n";
    node_t* foo = L(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in d after l\n";
    // cout << "in D token.chars = " << tk.chars << endl;
  }
  else if (tk.chars == "Show") {
    // cout << "calling E\n";
    node_t* foo = E(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in d after e\n";
    // cout << "in D token.chars = " << tk.chars << endl;
  }
  else if (tk.chars == "{") {
    // cout << "calling F\n";
    node_t* foo = F(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in d after f\n";
    // cout << "in D token.chars = " << tk.chars << endl;
  }
  else {
    cout << "Error. Invalid entry in D(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* F(istream& in, Token& tk) {
  node_t* p= new node_t('F');
  p->level = ++levelNum;
  // cout << "in F token.chars = " << tk.chars << endl;
  if (tk.chars == "{") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in F token.chars = " << tk.chars << endl;
    if (tk.chars == "If") {
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in F token.chars = " << tk.chars << endl;

      if (tk.ID == 1002) {
        node_t t(tk);
        p->children.push_back(t);
        tk = getNextToken(in);
        // cout << "in F token.chars = " << tk.chars << "\n calling T\n";
        node_t* foo = T(in, tk);
        p->children.push_back(*foo);
        // cout << "-- in f after t\n calling W\n";
        foo = W(in, tk);
        p->children.push_back(*foo);
        // cout << "-- in f after w\ncalling D\n";
        foo = D(in, tk);
        p->children.push_back(*foo);
        // cout << "-- in f after d\n";
        // cout << "in F token.chars = " << tk.chars << endl;

        if (tk.chars == "}") {
          node_t t(tk);
          p->children.push_back(t);
          tk = getNextToken(in);
          //cout << "in F token.chars = " << tk.chars << endl;
        }
        else {
          cout << "Error. Invalid entry in F(), exiting program.\n";
          exit(-1);
        }
      }
      else {
        cout << "Error. Invalid entry in F(), exiting program.\n";
        exit(-1);
      }
    }
    else if (tk.chars  == "Do") {
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in F token.chars = " << tk.chars << endl;

      if (tk.chars == "Again") {
        node_t t(tk);
        p->children.push_back(t);
        tk = getNextToken(in);
        // cout << "in F token.chars = " << tk.chars << "\ncalling D\n";
        node_t* foo = D(in, tk);
        p->children.push_back(*foo);
        // cout << "-- in f after d\ncalling T\n";
        foo = T(in, tk);
        p->children.push_back(*foo);
        // cout << "-- in f after t\ncalling W\n";
        foo = W(in, tk);
        p->children.push_back(*foo);
        // cout << "-- in f after w\n";
        // cout << "in F token.chars = " << tk.chars << endl;

        if (tk.chars == "}") {
          node_t t(tk);
          p->children.push_back(t);
          tk = getNextToken(in);
          // cout << "in F token.chars = " << tk.chars << endl;
        }
        else {
          cout << "Error. Invalid entry in F(), exiting program.\n";
          exit(-1);
        }
      }
      else {
        cout << "Error. Invalid entry in F(), exiting program.\n";
        exit(-1);
      }
    }
  }
  else {
    cout << "Error. Invalid entry in F(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* G(istream& in, Token& tk) {
  node_t* p= new node_t('G');
  p->level = ++levelNum;
  // cout << "in G token.chars = " << tk.chars << endl;
  if (tk.chars == "Here") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in G token.chars = " << tk.chars << endl;

    if (tk.ID == 1004) {
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in G token.chars = " << tk.chars << endl;

      if (tk.chars == "There") {
        node_t t(tk);
        p->children.push_back(t);
        tk = getNextToken(in);
        // cout << "in G token.chars = " << tk.chars << endl;
      }
      else {
        cout << "Error. Invalid entry in G(), exiting program.\n";
        exit(-1);
      }
    }
    else {
      cout << "Error. Invalid entry in G(), exiting program.\n";
      exit(-1);
    }
  }
  else {
    cout << "Error. Invalid entry in G(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* T(istream& in, Token& tk) {
  node_t* p= new node_t('T');
  p->level = ++levelNum;
  // cout << "in T token.chars = " << tk.chars << endl;
  if (tk.chars == "<<") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in T token.chars = " << tk.chars << endl;

  }
  else if (tk.chars == "<-") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in T token.chars = " << tk.chars << endl;
  }
  else {
    cout << "Error. Invalid entry in T(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* V(istream& in, Token& tk) {
  node_t* p= new node_t('V');
  p->level = ++levelNum;
  // cout << "in V token.chars = " << tk.chars << endl;
  if (tk.chars == "+") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in V token.chars = " << tk.chars << endl;
  }
  else if (tk.chars == "%") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in V token.chars = " << tk.chars << endl;
  }
  else if (tk.chars == "&") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in V token.chars = " << tk.chars << endl;
  }
  else {
    cout << "Error. Invalid entry in V(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* H(istream& in, Token& tk) {
  node_t* p= new node_t('H');
  p->level = ++levelNum;
  // cout << "in H token.chars = " << tk.chars << endl;
  if (tk.chars == "/") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in H token.chars = " << tk.chars << "\ncalling Z\n";

    node_t* foo = Z(in, tk);
    p->children.push_back(*foo);
    // cout << "-- in h after z\n";
    // cout << "in H token.chars = " << tk.chars << endl;
  }
  else {
    cout << "Error. Invalid entry in H(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* J(istream& in, Token& tk) {
  node_t* p= new node_t('J');
  p->level = ++levelNum;
  // cout << "in J token.chars = " << tk.chars << endl;
  if (tk.chars == "Assign") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in J token.chars = " << tk.chars << endl;

    if (tk.ID == 1002) {
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in J token.chars = " << tk.chars << "\ncalling D()\n";
      node_t* foo = D(in, tk);
      p->children.push_back(*foo);
      // cout << "-- in j after D\n";
      tk = getNextToken(in);
      // cout << "in J token.chars = " << tk.chars << endl;
    }
    else {
      cout << "Error. Invalid entry in J(), exiting program.\n";
      exit(-1);
    }
  }
  else {
    cout << "Error. Invalid entry in J(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* K(istream& in, Token& tk) {
  node_t* p= new node_t('K');
  p->level = ++levelNum;
  // cout << "in K token.chars = " << tk.chars << endl;
  if (tk.chars == "Spot") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in K token.chars = " << tk.chars << endl;

    if (tk.ID == 1004) {
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in K token.chars = " << tk.chars << endl;

      if (tk.chars == "Show") {
        node_t t(tk);
        p->children.push_back(t);
        tk = getNextToken(in);
        // cout << "in K token.chars = " << tk.chars << endl;

        if (tk.ID == 1004) {
          node_t t(tk);
          p->children.push_back(t);
          tk = getNextToken(in);
          // cout << "in K token.chars = " << tk.chars << endl;
        }
        else {
          cout << "Error. Invalid entry in K(), exiting program.\n";
          exit(-1);
        }
      }
      else {
        cout << "Error. Invalid entry in K(), exiting program.\n";
        exit(-1);
      }
    }
  }
  else   if (tk.chars == "Move") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in K token.chars = " << tk.chars << endl;

      if (tk.ID == 1002) {
        node_t t(tk);
        p->children.push_back(t);
        tk = getNextToken(in);
        // cout << "in K token.chars = " << tk.chars << endl;

        if (tk.chars == "Show") {
          node_t t(tk);
          p->children.push_back(t);
          tk = getNextToken(in);
          // cout << "in K token.chars = " << tk.chars << endl;

          if (tk.ID == 1002) {
            node_t t(tk);
            p->children.push_back(t);
            tk = getNextToken(in);
            // cout << "in K token.chars = " << tk.chars << endl;
          }
          else {
            cout << "Error. Invalid entry in K(), exiting program.\n";
            exit(-1);
          }
        }
        else {
          cout << "Error. Invalid entry in K(), exiting program.\n";
          exit(-1);
        }
      }
      else {
        cout << "Error. Invalid entry in K(), exiting program.\n";
        exit(-1);
      }
  }
  else {
    cout << "Error. Invalid entry in K(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* L(istream& in, Token& tk) {
  node_t* p= new node_t('L');
  p->level = ++levelNum;
  // cout << "in L token.chars = " << tk.chars << endl;
  if (tk.chars == "Flip") {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in L token.chars = " << tk.chars << endl;

    if (tk.ID == 1002) {
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in L token.chars = " << tk.chars << endl;
    }
    else {
      cout << "Error. Invalid entry in L(), exiting program.\n";
      exit(-1);
    }
  }
  else {
    cout << "Error. Invalid entry in L(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* W(istream& in, Token& tk) {
  node_t* p= new node_t('W');
  p->level = ++levelNum;
  // cout << "in W token.chars = " << tk.chars << endl;
  if (tk.ID == 1004) {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in W token.chars = " << tk.chars << endl;

    if (tk.chars == ".") {
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in W token.chars = " << tk.chars << endl;
    }
    else if (tk.chars == "+" || tk.chars == "%" || tk.chars == "&"){
      node_t t(tk);
      p->children.push_back(t);
      tk = getNextToken(in);
      // cout << "in W token.chars = " << tk.chars << "\ncalling V()\n";
      node_t* foo = V(in, tk);
      p->children.push_back(*foo);
      // cout << "-- in w after v\n";
      tk = getNextToken(in);
      // cout << "in W token.chars = " << tk.chars << endl;
      if (tk.ID == 1004) {
        node_t t(tk);
        p->children.push_back(t);
        tk = getNextToken(in);
        // cout << "in W token.chars = " << tk.chars << endl;
      }
      else {
        cout << "Error. Invalid entry in W(), exiting program.\n";
        exit(-1);
      }

    }
    else {
      cout << "Error. Invalid entry in W(), exiting program.\n";
      exit(-1);
    }
  }
  else {
    cout << "Error. Invalid entry in W(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

node_t* Z(istream& in, Token& tk) {
  node_t* p= new node_t('Z');
  p->level = ++levelNum;
  // cout << "in Z token.chars = " << tk.chars << endl;
  if (tk.ID == 1002) {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in Z token.chars = " << tk.chars << endl;
  }
  else if (tk.ID == 1004) {
    node_t t(tk);
    p->children.push_back(t);
    tk = getNextToken(in);
    // cout << "in Z token.chars = " << tk.chars << endl;
  }
  else {
    cout << "Error. Invalid entry in Z(), exiting program.\n";
    exit(-1);
  }
  --levelNum;
  return p;
}

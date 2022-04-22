#include <iostream>
#include <stdlib.h>
#include <string>
#include <iterator>
#include <list>
#include "node.h"
#include "statSem.h"
#include "codeGen.h"


using namespace std;

extern string currentIdent;
string prevIdent;

void codeGen(node_t* p, ofstream& out) {
  if (p == nullptr) {
    return;
  }
  else {
    // cout << p->label << endl;

    string entry;
    //cout << "label " << p->label << endl;
    for (list<node_t>::iterator iter = std::begin(p->children); iter!=std::end(p->children); ++iter){

      // cout << "iter " << (*iter).token.chars << endl;

      entry = (*iter).token.chars;

      if (entry == "Name") {
        ++iter;
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
        out << "LOAD 0\n";
        out << "STORE " << currentIdent << endl;

      }
      else if (entry == "Spot") {
        ++iter;
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
        if ((*iter).token.ID == 1002) {
          out << "READ " << currentIdent << endl;
        }
        else if ((*iter).token.ID == 1004){
          out << "LOAD " << currentIdent << endl;
        }
      }
      else if (entry == "Show") {
        ++iter;
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
        if ((*iter).token.ID == 1002) {
          out << "WRITE " << currentIdent << endl;
        }
        else if ((*iter).token.ID == 1004){
          out << "WRITE " << currentIdent << endl;
        }
      }
      else if (entry == "If") {
        ++iter;
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
      }
      else if (entry == "Assign") {
        ++iter;
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
        prevIdent = currentIdent;
      }
      else if (entry == "Flip") {
        ++iter;
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
        out << "LOAD " << currentIdent << endl;
        out << "MULT -1\n";
        out << "STORE " << currentIdent << endl;
      }
      else if (entry == "Here"){
        ++iter;
        currentIdent = (*iter).token.chars;
        out << "READ T4\n";
        out << "BRZNEG OUT\n";
        out << "REPEAT: WRITE T4\n";
        out << "SUB 1\n";
        out << "BRPOS NOREPEAT\n";
        out << "NOREPEAT: NOOP\n";
      }
      else if (entry == "Move") {
        ++iter;
        currentIdent = (*iter).token.chars;
        out << "LOAD " << currentIdent << endl;
      }
      else if (entry == "/") {
        ++iter;
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
        if ((*iter).token.ID == 1002) {
          out << "LOAD " << currentIdent << endl;
          out << "SUB 1\n";
          out << "STORE " << currentIdent << endl;
        }
        else {
          out << "READ T3\n";
          out << "SUB 1\n";
          out << "STORE " << currentIdent << endl;
        }
      }
      else {
        codeGen(&(*iter), out);
      }

      // statSem(&(*iter));
    }
  }
}

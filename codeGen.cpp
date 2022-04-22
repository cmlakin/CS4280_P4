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
extern list<string> symTab;
list<string> temps;
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
      cout << "entry =  " << (*iter).token.chars << endl;

      if (entry == "Name") {
        ++iter;
        currentIdent = (*iter).token.chars;
        cout << "current ident = " << currentIdent << endl;
        out << "LOAD 0\n";
        out << "STORE " << currentIdent << endl;

      }
      else if (entry == "Spot") {
        iter++;
        currentIdent = (*iter).token.chars;
        cout << "current ident = " << currentIdent << endl;
        if ((*iter).token.ID == 1002) { // Identifer
          out << "READ " << currentIdent << endl;
        }
        else if ((*iter).token.ID == 1004){ // Number
          out << "LOAD " << currentIdent << endl;
        }
      }
      else if (entry == "Show") {
        ++iter;
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
        if ((*iter).token.ID == 1002) { // Identifier
          out << "WRITE " << currentIdent << endl;
        }
        else if ((*iter).token.ID == 1004){ // Number
          out << "WRITE " << currentIdent << endl;
        }
      }
      else if (entry == "If") {
        ++iter;
        string ident = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
        ++iter;
        string next = (*iter).token.chars;
        if (next == "<-") {
          out << "READ T1\n";
          out << "SUB " << ident << endl;
          out << "BRPOS OUT\n";
          // call separate function for d
          out << "OUT: NOOP\n";

        }
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
        temps.push_back("T4");
        out << "READ T4\n";
        out << "BRZNEG NOREPEAT\n";
        out << "REPEAT: WRITE T4\n";
        out << "SUB 1\n";
        out << "BRPOS REPEAT\n";
        out << "NOREPEAT: NOOP\n";
      }
      else if (entry == "Move") {
        ++iter;
        currentIdent = (*iter).token.chars;
        out << "LOAD " << currentIdent << endl;
      }
      else if (entry == "/") {
        //cout << "/ current ident = " << currentIdent << endl;
        ++iter;
        currentIdent = (*iter).token.chars;
        cout << "/ current ident = " << currentIdent << endl;

        if ((*iter).token.ID == 1002) { // Identifer
          out << "LOAD " << currentIdent << endl;
          out << "SUB 1\n";
          out << "STORE " << currentIdent << endl;
        }
        else if ((*iter).token.ID == 1004){ // Number
          temps.push_back("T3");
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



void printVars(ofstream& out) {

  for (list<string>::iterator iter = std::begin(symTab); iter!=std::end(symTab); ++iter){
    out << (*iter) << " 0\n";
  }

  for (list<string>::iterator iter = std::begin(temps); iter!=std::end(temps); ++iter){
    out << (*iter) << " 0\n";
  }
}

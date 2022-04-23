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
char printOut = 'n';

void codeGen(node_t* p, ofstream& out) {
  if (p == nullptr) {
    return;
  }
  else {
    // cout << p->label << endl;
    int count = 0;
    string entry;
    //cout << "label " << p->label << endl;
    for (list<node_t>::iterator iter = std::begin(p->children); iter!=std::end(p->children); ++iter){

      // cout << "iter " << (*iter).token.chars << endl;
      cout << "label = " << p->label << endl;
      cout << "count =  " << ++count << endl;
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
        cout << "show - current ident = " << currentIdent << endl;
        cout << "show - tk.ID = " << (*iter).token.ID << endl;
        out << "WRITE " << currentIdent << endl;
        if (printOut == 'y'){
          out << "DONE: NOOP\n";
          printOut = 'n';
        }
      }
      else if (entry == "If") {
        ++iter;
        prevIdent = (*iter).token.chars;
        cout << "current ident = " << currentIdent << endl;
        // call separate function for d
        codeGen(&(*iter), out);
      }
      else if (entry == "<-") {
        temps.push_back("T1");
        out << "READ T1\n";
        out << "SUB " << prevIdent << endl;
        out << "BRNEG DONE\n";
        printOut = 'y';
        codeGen(&(*iter), out);
      }
      else if (entry == "<<") {
        temps.push_back("T2");
        out << "READ T2\n";
        out << "SUB " << prevIdent << endl;
        out << "BRNEG DONE\n";
        printOut = 'y';
        codeGen(&(*iter), out);
      }
      else if (entry == "Assign") {
        ++iter;
        currentIdent = (*iter).token.chars;
        cout << "current ident = " << currentIdent << endl;
        prevIdent = currentIdent;
      }
      else if (entry == "Flip") {
        ++iter;
        currentIdent = (*iter).token.chars;
        cout << "current ident = " << currentIdent << endl;
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
        prevIdent = entry;
        codeGen(&(*iter), out);
      }
      else if (prevIdent == "/" && (*iter).token.ID == 1002) {
        currentIdent = (*iter).token.chars;
        cout << "1002 / current ident = " << currentIdent << endl;
        out << "LOAD " << currentIdent << endl;
        out << "SUB 1\n";
        out << "STORE " << currentIdent << endl;
        prevIdent = "";
        codeGen(&(*iter), out);
      }
      else if (prevIdent == "/" && (*iter).token.ID == 1004){ // Number
        currentIdent = (*iter).token.chars;
        cout << "1004 / current ident = " << currentIdent << endl;
        temps.push_back("T3");
        out << "READ T3\n";
        out << "SUB 1\n";
        out << "STORE " << currentIdent << endl;
        prevIdent = "";
      }
      else {
        codeGen(&(*iter), out);
      }
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

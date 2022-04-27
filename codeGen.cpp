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
string prevIdent = "";
string prevLabelIdent = "";
string prevLabel = "";
string prevOp = "";
string prevNumber = "";
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
      // else if (!prevOp.empty() && !prevNumber.empty() && !prevIdent.empty()){
      //
      //
      // }
      // else if ((*iter).token.ID == 1004){
      //   prevNumber = (*iter).token.chars;
      //   ++iter;
      //   codeGen(&(*iter), out);
      //
      //
      // }
      else if (entry == "<-") {
        temps.push_back("T1");
        out << "READ T1\n";
        out << "SUB " << prevIdent << endl;
        out << "BRNEG DONE\n";
        printOut = 'y';
        prevOp = entry;
        codeGen(&(*iter), out);
      }
      else if (entry == "<<") {
        temps.push_back("T2");
        out << "READ T2\n";
        out << "SUB " << prevIdent << endl;
        out << "BRNEG DONE\n";
        printOut = 'y';
        prevOp = entry;
        codeGen(&(*iter), out);
      }
      else if (entry == "Assign") {
        ++iter;
        prevLabel = "Assign";
        currentIdent = (*iter).token.chars;
        cout << "current ident = " << currentIdent << endl;
        prevLabelIdent = currentIdent;
      }
      else if (entry == "Flip") {
        ++iter;
        currentIdent = (*iter).token.chars;
        cout << "current ident = " << currentIdent << endl;
        out << "LOAD " << currentIdent << endl;
        out << "MULT -1\n";
        out << "STORE " << currentIdent << endl;
        if (prevLabel == "Assign"){
          out << "STORE " << prevLabelIdent << endl;
          prevLabel = "";
          prevLabelIdent = "";
        }
      }
      else if (entry == "Here"){
        ++iter;
        currentIdent = (*iter).token.chars;
        temps.push_back("T4");
        temps.push_back("T5");
        out << "READ T4\n";
        out << "LOAD T4\n";
        out << "STORE T5\n";
        out << "BRZNEG NOREPEAT\n";
        out << "REPEAT: WRITE T5\n";
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
        if (prevLabel == "Assign"){
          out << "STORE " << prevLabelIdent << endl;
          prevLabel = "";
          prevLabelIdent = "";
        }
        codeGen(&(*iter), out);
      }
      else if (prevIdent == "/" && (*iter).token.ID == 1004){ // Number
        currentIdent = (*iter).token.chars;
        cout << "1004 / current ident = " << currentIdent << endl;
        temps.push_back("T3");
        out << "READ T3\n";
        out << "SUB 1\n";
        out << "STORE T3\n";
        if (prevLabel == "Assign"){
          out << "STORE " << prevLabelIdent << endl;
          prevLabel = "";
          prevLabelIdent = "";
        }
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

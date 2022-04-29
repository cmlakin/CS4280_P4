#include <iostream>
#include <stdlib.h>
#include <string>
#include <iterator>
#include <list>
#include "node.h"
#include "statSem.h"
#include "genCode.h"


using namespace std;

extern string currentIdent;
extern list<string> symTab;
extern int numberCount;
list<string> temps;
string prevIdent = "";
string prevLabelIdent = "";
string prevLabel = "";
string prevOp = "";
string prevNumber = "";
string tOp = ""; // operator from <T>
char printOut = 'n';

void genCode(node_t* p, ofstream& out) {
  if (p == nullptr) {
    return;
  }
  else {
    // cout << p->label << endl;
    // int count = 0;
    string entry;
    //cout << "label " << p->label << endl;
    for (list<node_t>::iterator iter = std::begin(p->children); iter!=std::end(p->children); ++iter){

      // cout << "iter " << (*iter).token.chars << endl;
      // cout << "label = " << p->label << endl;
      // cout << "count =  " << ++count << endl;
      entry = (*iter).token.chars;
      // cout << "entry =  " << (*iter).token.chars << endl;

      if (entry == "Name") {
        ++iter;
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
        out << "LOAD 0\n";
        out << "STORE " << currentIdent << endl;

      }
      else if (entry == "Spot") {
        iter++;
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
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
        // cout << "show - current ident = " << currentIdent << endl;
        // cout << "show - tk.ID = " << (*iter).token.ID << endl;

        if (printOut == 'y'){
          if (prevLabel == "Do" && tOp == "<-"){
            out << "BRNEG LOOP\n";
          }
          else if (prevLabel == "Do" && tOp == "<<"){
            out << "BRPOS LOOP\n";
          }
          out << "DONE: NOOP\n";
          printOut = 'n';
        }
        out << "WRITE " << currentIdent << endl;
      }
      else if (entry == "If") {
        ++iter;
        prevIdent = (*iter).token.chars;
        prevLabel = "If";
        // cout << "current ident = " << prevIdent << endl;
        // call separate function for d
        genCode(&(*iter), out);
      }
      else if (entry == "Do") {
        // ++iter;
        // prevIdent = (*iter).token.chars;
        prevLabel = "Do";
        // cout << "current ident = " << prevIdent << endl;
        // call separate function for d
        genCode(&(*iter), out);
      }
      else if ((*iter).token.ID == 1004 && numberCount == 1 && prevLabel == "If") {
        if (tOp == "<-") {
         temps.push_back("T1");
         out << "READ T1\n";
         out << "SUB " << prevIdent << endl;
         out << "BRPOS DONE\n";
         printOut = 'y';
         tOp = "";
         prevOp = "";
         prevLabel = "";
        }
        else if (tOp == "<<"){
          temps.push_back("T1");
          out << "READ T1\n";
          out << "SUB " << prevIdent << endl;
          out << "BRZNEG DONE\n";
          printOut = 'y';
          tOp = "";
          prevOp = "";
          prevLabel = "";
        }
      }
      else if ((*iter).token.ID == 1004 && numberCount == 2 && prevLabel == "If") {
        if (prevNumber.empty()) {
          prevNumber = (*iter).token.chars;
        }
        else {
          if (tOp == "<-") {
            if (prevOp == "+") {
              temps.push_back("T2");
              temps.push_back("T3");
              out << "READ T2\n";
              out << "READ T3\n";
              out << "LOAD T2\n";
              out << "ADD T3\n";
              out << "SUB " << prevIdent << endl;
              out << "BRPOS DONE\n";
              printOut = 'y';
            }
            else if (prevOp == "%") {
              temps.push_back("T2");
              temps.push_back("T3");
              out << "READ T2\n";
              out << "READ T3\n";
              out << "LOAD T2\n";
              out << "DIV T3\n";
              out << "STORE T2\n";
              out << "ABS T2\n";
              out << "SUB " << prevIdent << endl;
              out << "BRPOS DONE\n";
              printOut = 'y';
            }
            else if (prevOp == "&") {
              temps.push_back("T2");
              temps.push_back("T3");
              out << "READ T2\n";
              out << "READ T3\n";
              out << "LOAD T2\n";
              out << "MULT T3\n";
              out << "SUB " << prevIdent << endl;
              out << "BRPOS DONE\n";
              printOut = 'y';
            }
            tOp = "";
            prevOp = "";
            prevLabel = "";
          }
          else if (tOp == "<<") {
            if (prevOp == "+") {
              temps.push_back("T4");
              temps.push_back("T5");
              out << "READ T4\n";
              out << "READ T5\n";
              out << "LOAD T4\n";
              out << "ADD T5\n";
              out << "SUB " << prevIdent << endl;
              out << "BRZNEG DONE\n";
              printOut = 'y';
            }
            else if (prevOp == "%") {
              temps.push_back("T4");
              temps.push_back("T5");
              out << "READ T4\n";
              out << "READ T5\n";
              out << "LOAD T4\n";
              out << "DIV T5\n";
              out << "STORE T4\n";
              out << "ABS T1\n";
              out << "SUB " << prevIdent << endl;
              out << "BRZNEG DONE\n";
              printOut = 'y';
            }
            else if (prevOp == "&") {
              temps.push_back("T4");
              temps.push_back("T5");
              out << "READ T4\n";
              out << "READ T5\n";
              out << "LOAD T4\n";
              out << "MULT T5\n";
              out << "SUB " << prevIdent << endl;
              out << "BRZNEG DONE\n";
              printOut = 'y';
            }
          }
          tOp = "";
          prevOp = "";
          prevLabel = "";
        }
        genCode(&(*iter), out);
      }
      else if ((*iter).token.ID == 1004 && numberCount == 1 && prevLabel == "Do") {
        if (tOp == "<-") {
         temps.push_back("T1");
         out << "LOOP: NOOP\n";
         out << "READ T1\n";
         out << "LOAD T1\n";
         out << "BRPOS DONE\n";
         printOut = 'y';
         // tOp = "";
         // prevOp = "";
         // prevLabel = "";

         // genCode(&(*iter), out);

         // out << "BRNEG LOOP\n";

        }
        else if (tOp == "<<"){
          temps.push_back("T1");
          out << "READ T1\n";
          out << "SUB " << prevIdent << endl;
          out << "BRZNEG DONE\n";
          printOut = 'y';
          tOp = "";
          prevOp = "";
          prevLabel = "";
        }
      }
      else if ((*iter).token.ID == 1004 && numberCount == 2 && prevLabel == "Do") {
        if (prevNumber.empty()) {
          prevNumber = (*iter).token.chars;
        }
        else {
          if (tOp == "<-") {
            if (prevOp == "+") {
              temps.push_back("T2");
              temps.push_back("T3");
              out << "READ T2\n";
              out << "READ T3\n";
              out << "LOAD T2\n";
              out << "ADD T3\n";
              out << "SUB " << prevIdent << endl;
              out << "BRPOS DONE\n";
              printOut = 'y';
            }
            else if (prevOp == "%") {
              temps.push_back("T2");
              temps.push_back("T3");
              out << "READ T2\n";
              out << "READ T3\n";
              out << "LOAD T2\n";
              out << "DIV T3\n";
              out << "STORE T2\n";
              out << "ABS T2\n";
              out << "SUB " << prevIdent << endl;
              out << "BRPOS DONE\n";
              printOut = 'y';
            }
            else if (prevOp == "&") {
              temps.push_back("T2");
              temps.push_back("T3");
              out << "READ T2\n";
              out << "READ T3\n";
              out << "LOAD T2\n";
              out << "MULT T3\n";
              out << "SUB " << prevIdent << endl;
              out << "BRPOS DONE\n";
              printOut = 'y';
            }
            tOp = "";
            prevOp = "";
            prevLabel = "";
          }
          else if (tOp == "<<") {
            if (prevOp == "+") {
              temps.push_back("T4");
              temps.push_back("T5");
              out << "READ T4\n";
              out << "READ T5\n";
              out << "LOAD T4\n";
              out << "ADD T5\n";
              out << "SUB " << prevIdent << endl;
              out << "BRZNEG DONE\n";
              printOut = 'y';
            }
            else if (prevOp == "%") {
              temps.push_back("T4");
              temps.push_back("T5");
              out << "READ T4\n";
              out << "READ T5\n";
              out << "LOAD T4\n";
              out << "DIV T5\n";
              out << "STORE T4\n";
              out << "ABS T1\n";
              out << "SUB " << prevIdent << endl;
              out << "BRZNEG DONE\n";
              printOut = 'y';
            }
            else if (prevOp == "&") {
              temps.push_back("T4");
              temps.push_back("T5");
              out << "READ T4\n";
              out << "READ T5\n";
              out << "LOAD T4\n";
              out << "MULT T5\n";
              out << "SUB " << prevIdent << endl;
              out << "BRZNEG DONE\n";
              printOut = 'y';
            }
          }
          tOp = "";
          prevOp = "";
          prevLabel = "";
        }
        genCode(&(*iter), out);
      }
      else if (entry == "<-" || entry == "<<") {
        tOp = entry;
        genCode(&(*iter), out);
      }
      else if ((*iter).token.ID == 1005) {
        if (entry == "+" || entry == "%" || entry == "&") {
          prevOp = (*iter).token.chars;
          // out << "prevOp " << prevOp << endl;
        }
        genCode(&(*iter), out);
      }
      else if (entry == "Assign") {
        ++iter;
        prevLabel = "Assign";
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
        prevLabelIdent = currentIdent;
      }
      else if (entry == "Flip") {
        ++iter;
        currentIdent = (*iter).token.chars;
        // cout << "current ident = " << currentIdent << endl;
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
        temps.push_back("T6");
        temps.push_back("T7");
        out << "READ T6\n";
        out << "LOAD T6\n";
        out << "STORE T7\n";
        out << "BRZNEG NOREPEAT\n";
        out << "REPEAT: WRITE T7\n";
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
        genCode(&(*iter), out);
      }
      else if (prevIdent == "/" && (*iter).token.ID == 1002) {
        currentIdent = (*iter).token.chars;
        // cout << "1002 / current ident = " << currentIdent << endl;
        out << "LOAD " << currentIdent << endl;
        out << "SUB 1\n";
        out << "STORE " << currentIdent << endl;
        prevIdent = "";
        if (prevLabel == "Assign"){
          out << "STORE " << prevLabelIdent << endl;
          prevLabel = "";
          prevLabelIdent = "";
        }
        genCode(&(*iter), out);
      }
      else if (prevIdent == "/" && (*iter).token.ID == 1004){ // Number
        currentIdent = (*iter).token.chars;
        // cout << "1004 / current ident = " << currentIdent << endl;
        temps.push_back("T8");
        out << "READ T8\n";
        out << "SUB 1\n";
        out << "STORE T8\n";
        if (prevLabel == "Assign"){
          out << "STORE " << prevLabelIdent << endl;
          prevLabel = "";
          prevLabelIdent = "";
        }
        prevIdent = "";
      }
      else {
        genCode(&(*iter), out);
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

/***************************************************************
 * Corrina Lakin
 * CS4280 P1
 * Description:
    Lexical Analyzer
 *************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <fstream>
#include <type_traits>
#include "parser.h"
// #include "treePrint.h"
#include "statSem.h"
#include "codeGen.h"

using namespace std;




int main(int argc, char * argv[]) {
  //cout << "*** in main\n";
  char* filenameIn;
  ifstream inFile;
  ofstream outFile;

  // parse commandline arguements
  if (argc == 2) {
    filenameIn = argv[1];

    inFile.open(filenameIn);
    parser(inFile);
    inFile.close();
  }
  else if (argc > 2){
    cout << "ERROR: Too many arguements entered.\n";
    cout << "USAGE: ./scanner [filename]\n";
  }
  else {
    cout << "Enter string to check for tokens.\n";
    cout << "Enter 'Done' when finished to exit program.\n";
    parser(cin);
  }

  // here is where I will call semantics file
  statSem(getRoot());
  // cout << "\nIn Main:\n";
  printSymTab();

  outFile.open("P4.asm");
  codeGen(getRoot(), outFile);
  outFile << "STOP\n";
  printVars(outFile);
  outFile.close();

  // treePrint(getRoot());
  return 0;
}

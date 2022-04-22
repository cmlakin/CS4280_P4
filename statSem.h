#ifndef STATSEM_h
#define STATSEM_h

#include <fstream>

using std::ofstream;

void statSem(node_t*);
void insertIdent(string);
void verifyIdent(string);
void printSymTab();

#endif

#include <iostream>
#include <stdlib.h>
#include <string>
#include "node.h"
#include "treeprint.h"


using namespace std;

void treePrint(node_t* p) {
  if (p == nullptr) {
    return;
  } else {
      // temp will be used to format spacing of levels
      int temp;
      temp = p->level + 1;
      cout << p->label << endl;

      for (node_t s: p->children) {
        for(int i = 0; i < temp; i++) {
          cout << "  ";
        }
        if (s.children.size() == 0) {
          if (s.token.ID == 1002){
            cout << "Identifier " << s.token.chars << endl;
          }
          else if (s.token.ID == 1004) {
            cout << "Number " << s.token.chars << endl;
          }
          else {
            cout << s.token.chars << endl;
          }
        }
        else {
          treePrint(&s);
        }
      }

  }
}

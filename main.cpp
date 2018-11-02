#include "GenNode.h"
#include "GenDlinkedlist.h"
#include "GenQueue.h"
#include "Simulate.h"
#include <iostream>
using namespace std;

string nameoffile;

int main () {
  cout << "Please enter the exact name of the file along with the extension" << endl;
  getline(cin, nameoffile);

  Simulate object;
  object.startSimulate (nameoffile);
}

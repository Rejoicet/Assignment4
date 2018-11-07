#include <iostream>
#include <fstream>
using namespace std;

class Simulate {
public:
  Simulate();
  ~Simulate();
  int startSimulate(string filename);

private:
  ifstream registrarFile;
  int a, b, f, numwindows, timer, idle, numtwindows, nstudents;
  int nswaittime, sum, median, medi, nten, l, widle, idl;
  double mean, total, wmean, tot;
};

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
  int a, b, f, numwindows, timer, idle, numtwindows, nstudents, nswaittime, sum, median, medi, nten, l, widle;
  double mean, total, wmean, tot;
};

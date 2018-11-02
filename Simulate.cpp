#include "GenNode.h"
#include "GenDlinkedlist.h"
#include "GenQueue.h"
#include "Simulate.h"
using namespace std;

Simulate::Simulate()
{
  timer = 0;
  numtwindows = 0;
  idle = widle = 0;
  nstudents = 0;
  nswaittime = 0;
  f = l = 0;
  sum = 0;
  mean = wmean = 0.0;
  total = tot = 0.0;
  median = medi = nten = 0;
}

Simulate::~Simulate() {}

int Simulate::startSimulate (string filename)
{
  registrarFile.open (filename);

  if (!registrarFile) {             //Exception if error in opening file
    cout << "Unable to open the file. Please check the following and enter the file name again -" << endl;
    cout << "1 - File is not open already" << endl;
    cout << "2 - Check some other program is not using it" << endl;
    cout << "3 - File name and its extension is correct" << endl;
    exit(1);
  }

  GenQueue <int> arrival;   //at what time are the students ought to arrive
  GenQueue <int> numstudents; //number of students in the queue
  GenQueue <int> stime;     //time each student needs
  GenQueue <int> numarrival;  //how many studens arrive at a particular time
  GenQueue <int> stimer;    //capture the start time when student enters a queue
  GenDlinkedlist <int> swaittime; //capture each student's wait time in the queue
  GenDlinkedlist <int> twindows;  //windows busy-idle time

  registrarFile >> a;
  numwindows = a;
  int myWindow[numwindows] = {};

  while (!registrarFile.eof()) {
    registrarFile >> a;
    arrival.enqueue(a);
    registrarFile >> a;
    numarrival.enqueue(a);
    for (int i = 0; i < numarrival.front(); i++) {
      registrarFile >> a;
      stime.enqueue(a);
    }
  }

  //stime.remove();

  while (true) {

    while (twindows.contains(0) == true)	{  //removing all 0's from twindows
      twindows.remove(0);
      --numtwindows;
    }

    if (timer == arrival.front()) {
      for (int i = 1; i <= numarrival.front(); i++) { //put the students in the queue
        numstudents.enqueue(i);
        stimer.enqueue(timer);
        ++nstudents;
      }
      arrival.dequeue();
      numarrival.dequeue();
    }

    idle = numwindows - numtwindows;	//check the number of windows that are free

    if (idle != 0) {
      if (numstudents.isEmpty() != true) {
        b = nstudents;
        if (idle > nstudents) {
          for (int j = 0; j < b; j++) {		//remove the students from the queue and
                                                  //take them to the idle windows as applicable
             numstudents.dequeue();
             swaittime.sort (timer, stimer.front(), sum, medi);
             median = medi;
             medi = 0;
             if (timer - stimer.front() > 10) {
               ++nten;
             }
             //swaittime.addBack (timer - stimer.front());
             twindows.addBack (stime.front());
             stime.dequeue();
             stimer.dequeue();
             ++numtwindows;
             --nstudents;
             ++nswaittime;
           }
        }
        else if ((idle < nstudents) || (idle == nstudents)) {
          for (int j = 0; j < idle; j++) {		//remove the students from the queue and
                                       //take them to the idle windows as applicable
             numstudents.dequeue();
             swaittime.sort (timer, stimer.front(), sum, medi);
             median = medi;
             medi = 0;
             if (timer - stimer.front() > 10) {
               ++nten;
             }
             //swaittime.addBack (timer - stimer.front());
             twindows.addBack (stime.front());
             stime.dequeue();
             stimer.dequeue();
             ++numtwindows;
             --nstudents;
             ++nswaittime;
           }
        }
       }
    }

    if (twindows.isEmpty() != true) {	//reducing all the elements in twindows by 1
      twindows.reduce();
    }

    for (int i = 0; i < idle; i++) {
      myWindow[i] = myWindow[i] + 1;
    }

    /*cout << timer << endl;
    cout << idle << endl;*/

    if (arrival.isEmpty() == true) {	//if twindows is empty at the end of timer i,
                                  //exit the simulation as there is nothing more to simulate
      if (twindows.isEmpty() == true) {
        break;
      }
    }

    ++timer;
  }

  for (int i = 0; i < numwindows; i++) {
    tot = tot + myWindow[i];
    if (l < myWindow[i]) {
      l = myWindow[i];
    }
    if (myWindow[i] > 5) {
      ++widle;
    }
  }

  total = sum;
  mean = total/nswaittime;
  wmean = tot/numwindows;

  cout << "The mean student wait time is " << mean << endl;
  cout << "The median student wait time is " << median << endl;
  cout << "The longest student wait time is " << swaittime.back() << endl;
  cout << "The number of students waiting over 10 minutes is " << nten << endl;
  cout << "The mean window idle time is " << wmean << endl;
  cout << "The longest window idle time is " << l << endl;
  cout << "Number of windows idle for over 5 minutes is " << widle << endl;

  registrarFile.close();
}

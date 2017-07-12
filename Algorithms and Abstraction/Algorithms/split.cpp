#include <cstdlib>
#include <queue>


using std::priority_queue;

int numCells(double endTime, double minSplit, double maxSplit){
  priority_queue<double> times;
  double mySplitTime = 0;
  int counter = 0;
  times.push(mySplitTime);
  times.push(mySplitTime);

  while ((-1)*mySplitTime <= endTime && !times.empty()){
    mySplitTime = times.top();
    times.pop();
    double newSplit = mySplitTime - (minSplit + rand()*(maxSplit-minSplit)/RAND_MAX);
    if ((-1)*newSplit > endTime){
      ++counter;
    } else {
      times.push(newSplit);
      times.push(newSplit);
    }
  }
  return times.size()+counter;
}
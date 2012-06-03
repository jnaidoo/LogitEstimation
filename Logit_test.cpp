// Logit_test.cpp
// Verify that we can initialize data, compute score and information matrix

#include "Logit.hpp"
using namespace std;

int main(int argc, char* argv[]){
  if(argc < 2){
    return(EXIT_FAILURE);
  }

  char *theData;     // character array for 
  theData = argv[1]; // name of data file

  Logit myLogit(theData);
  //readInData(theData); // want to pass by reference; can I put in a pointer?
  myLogit.printNumObs();

  ifstream inTmp;
  inTmp.open(theData, ios::in);
  if (!inTmp){
    exit(EXIT_FAILURE);
  }
  string firstObs;
  getline(inTmp,firstObs);
  //cout << firstObs << endl;
  myLogit.convertSplit(firstObs);
  
  //covariateVector4d_t v1;
  //v1 << 1,2,3,4;
  //SquareMatrix4d_t A = v1.transpose()*v1; 
  //cout << A << endl;


  return 0;
}

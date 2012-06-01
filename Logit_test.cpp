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

  return 0;
}

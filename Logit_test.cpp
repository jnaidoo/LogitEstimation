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
  //myLogit.printAttributes();
  coefficientVector4d_t testBeta;
  testBeta << 0,0,0,0;
  cout << "at beta = " << testBeta << "likelihood is " << myLogit.calcObjective(testBeta) << endl;
  cout << "at beta = " << testBeta << "score is " << myLogit.calcScore(testBeta) << endl;
  cout << "at beta = " << testBeta << "Hessian is " << myLogit.calcHessian(testBeta) << endl;

  return 0;
}

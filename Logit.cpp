//Logit.cpp - implementation of Logit class

#include "Logit.hpp"



using namespace std;
using namespace boost;

//------------------------
// public member functions
//------------------------

Logit::Logit(char* filename) // have to pass character array with filename to instantiate Logit
{
  numObservations = getNumObservations(filename);
  // initialize data members to empty
  
  // preallocate size of lists
  covariates.reserve(numObservations);
  outcomes.reserve(numObservations);

} // end constructor definition

Logit::~Logit()
{} // empty destructor

void Logit::printAttributes()
{
  cout << "number of observations: " << (*this).numObservations << endl;
  cout << "number of covariates: " << (*this).numCovariates << endl;

} // end of printAttributes

void Logit::printNumObs()
{
  cout << "Number of observations for this Logit = " << (*this).numObservations << endl;   
}


//------------------------
// private member functions
//------------------------

int Logit::getNumObservations(char* filename)
{
  ifstream in;
  in.open(filename, ios::in);
  if (!in){
    exit(EXIT_FAILURE);
  }
  
  // adapted from recipe 4.17 in C++ Cookbook
  //int numObs = 0;
  int chars = 0;
  int lines = 0;


  char cur = '\0';
  char last = '\0';
   
  while (in.get(cur)){
    if(cur == '\n' || (cur == '\f' && last == '\r')){
      lines++;
    }
    else{
      chars++;
    }

    last = cur;
     
  } // end of while loop
  
  if (chars > 0){ // need to count final line 
    if (isalnum(last)){
     // words++;
      lines++;
    }
  }

  return lines;   
} // end getNumObservations




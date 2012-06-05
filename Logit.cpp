//Logit.cpp - implementation of Logit class

#include "Logit.hpp"

using namespace std;
using namespace boost;

//------------------------
// public member functions
//------------------------

Logit::Logit(const char* filename) // have to pass character array with filename to instantiate Logit
{
  numObservations = getNumObservations(filename);

  // initialize data members to empty
  // preallocate size of lists
  covariates.reserve(numObservations);
  outcomes.reserve(numObservations);

  //for(int ix = 0; ix<numObservations); ++ix){
  ifstream data;
  data.open(filename, ios::in);
  if (data.is_open())
  {
    string line;
    int ix = 0; 
      while ( data.good() && ix<numObservations)
      {
       getline (data,line); // this fills the string 'line' with the next line of data
       // now we fill up the vectors of      
       convertSplit(line,outcomes[ix],covariates[ix]);
       ix++;
      } // end while loop
      data.close();
  } // end if statement
  else{
   cout << "ERROR: could not open file: " << filename << ". Stop." << endl;
   exit(EXIT_FAILURE);
  }
} // end constructor definition

Logit::~Logit()
{} // empty destructor

void Logit::printAttributes()
{
  cout << "number of observations: " << (*this).numObservations << endl;
  
  cout << "***" << endl;
  cout << "First 5 observations" << endl;
  for(int ix = 0; ix < 5; ++ix){
    cout << "---" << endl;
    cout << "y[" << ix << "]" << " = " << outcomes[ix] << endl;
    cout << "x[" << ix << "]" << " = " << covariates[ix] << endl;
    cout << "x'x[" << ix << "]" << " = " << endl;
    cout << covariates[ix].transpose()*covariates[ix] << endl;
  } // end for loop

} // end of printAttributes

double Logit::calcObjective(const coefficientVector4d_t& beta)
{
//for_each (myvector.begin(), myvector.end(), myfunction);
  double tmpSum = 0;
  for(int ix = 0; ix<numObservations; ++ix){
    // use if statement to avoid multiplications
    if(outcomes[ix] == 1){
      tmpSum += logLogitCDF(getIndex(beta,covariates[ix]));
    }
    else{
      // recall, log(1-G(a)) = log(G(-a))
      tmpSum += logLogitCDF(-getIndex(beta,covariates[ix]));
    }
  } // end for
  return -tmpSum; // minimize -likelihood
} // end calcObjective

scoreVector4d_t Logit::calcScore(const coefficientVector4d_t& beta)
{
  scoreVector4d_t tmpSum;
  tmpSum.setZero(); // initialize to zero

  for(int ix = 0; ix<numObservations; ++ix){
      tmpSum += (outcomes[ix]-exp(logLogitCDF(getIndex(beta,covariates[ix]))))*covariates[ix];
    } // end for 
  return -tmpSum; // minimize -likelihood
} // end calcScore



SquareMatrix4d_t Logit::calcHessian(const coefficientVector4d_t& beta)
{
  SquareMatrix4d_t tmpSum;
  tmpSum.setZero(); // initialize to zero

  for(int ix = 0; ix<numObservations; ++ix){
      tmpSum += exp(logHessianWeight(getIndex(beta,covariates[ix])))*(covariates[ix].transpose()*covariates[ix]);
  } // end for 
  return tmpSum; // Hessian of -L is positive definite

} // end calcHessian














//------------------------
// private member functions
//------------------------

double Logit::getIndex(const coefficientVector4d_t& beta, const covariateVector4d_t& x)
{
  return x*beta.transpose();
}



double Logit::logLogitCDF(double index) // pass by value; worry about temporary values changing
{
  // returns log of Logit CDF
  return -log(1+exp(-index));
}//end logitCDF

double Logit::logHessianWeight(double index)
{
  // returns log of G()*[1-G()]
  return -index + 2*logLogitCDF(index);
} // end logHessianWeight


int Logit::getNumObservations(const char* filename)
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
  // initialize to 
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

void Logit::convertSplit(const string observationString, outcome_t& response, covariateVector4d_t& regressors)
{
  vector<string> splitStringList; 
  split(splitStringList, observationString, is_any_of(" ,")); // tokenize s

  // extract LHS variable
  response = getOutcomeFromString(splitStringList.front());
  
  // discard first element = LHS variable
  // remaining elements are covariates
  splitStringList.erase(splitStringList.begin());
  
  double myTmpArray[splitStringList.size()];
  for(int ix = 0; ix<splitStringList.size(); ++ix){
    myTmpArray[ix] = convertStringToDouble(splitStringList[ix]); 
  }
  regressors = Eigen::Map<covariateVector4d_t>(myTmpArray);
} // end convertSplit

// private method to convert string --> double
double Logit::convertStringToDouble(const string s){
   try{
      return boost::lexical_cast<double>(s);
    }
    catch(bad_lexical_cast &){
      return -999; 
    }
} // end of convertStringToDouble

// private method to convert string --> int
int Logit::getOutcomeFromString(const string s)
{
  int y;
  try{
      return boost::lexical_cast<int>(s);
   }
  catch(bad_lexical_cast &){
      return -999; 
  }
  return y;
} // end of getOutcomeFromString



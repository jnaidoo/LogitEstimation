// Jesse Naidoo (jnaidoo@uchicago.edu)
// Logit.hpp - header file for Logit class
// 
// NOTES FOR USE:
// -- uses std and Eigen namespaces, which will be inherited by
//    all code which #includes Logit.hpp
//
/** VERSION HISTORY:
  * ----------------
  * 29/5/12 first version
  * 4/6/12 hook interface into Ipopt
  *
  *
  *
  *
  *
  */

// for now, we unfortunately have to hard-code in the number of covariates (k = 4)
// though it may be possible to change the typedefs to have size Dynamic
// to allow for different numbers of covariates

//======================================================
// #include guards
#ifndef __LOGIT_HPP__
#define __LOGIT_HPP__

//======================================================
// included dependencies

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <Eigen/Dense>
#include <cmath>
//#include <cctype>
//#include <cstdlib>
//======================================================
// typedefs
typedef Eigen::Matrix<double,1,4> covariateVector4d_t; // row vector of covariates
typedef Eigen::Matrix<double,1,4> coefficientVector4d_t; // row of coefficients
typedef int outcome_t; 
typedef Eigen::Matrix<double,1,4> scoreVector4d_t;
typedef Eigen::Matrix<double,4,4> SquareMatrix4d_t; // to be populated with analytic Hessian

//======================================================
// namespace declarations
using namespace std;
//======================================================
// class definition
class Logit
  {
  public:
    Logit(const char* filename);  //ctor
    ~Logit(); // dtor
    void printAttributes(); // prints out numObservations, properties of first 5 obs
    double calcObjective(const coefficientVector4d_t& beta);
    scoreVector4d_t calcScore(const coefficientVector4d_t& beta);
    SquareMatrix4d_t calcHessian(const coefficientVector4d_t& beta);

  private:
    //** member functions
    double getIndex(const coefficientVector4d_t& beta, const covariateVector4d_t& x); // inner product
  
    double logLogitCDF(const double index); // log(G()) for likelihood and score
    double logHessianWeight(const double index); // log(G()[1-G()]) for Hessian
    int getNumObservations(const char* filename); // argument = data filename
    // convertSplit takes a line and enters y and x data into its arguments
    void convertSplit(const string observationString, int& response, covariateVector4d_t& regressors);
    double convertStringToDouble(const string s); // simple type-recast
    int getOutcomeFromString(const string s);
    
    //** member data
    int numObservations;
    //int numCovariates; --> redundant because I don't know how to pass a variable-dim argument to likelihood yet
    vector<outcome_t> outcomes;
    vector<covariateVector4d_t> covariates;
     
  }; // end of Logit class definition

#endif


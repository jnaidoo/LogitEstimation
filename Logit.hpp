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
  *
  *
  *
  *
  *
  *
  */

// for now, we unfortunately have to hard-code in the number of covariates (k = 4)

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
//#include <cctype>
//#include <cstdlib>
//======================================================
// typedefs
typedef Eigen::Matrix<double,1,4> covariateVector4d_t;
typedef int outcome_t; 
typedef Eigen::Matrix<double,1,4> scoreVector4d_t;
typedef Eigen::Matrix<double,4,4> SquareMatrix4d_t;

//======================================================
// namespace declarations
using namespace std;
//======================================================
// class definition
class Logit
  {
  public:
    Logit(char* filename);  //ctor
    ~Logit(); // dtor
    void printAttributes(); // prints out numObservations, properties of first 5 obs
    double calcObjective(const Number)

  private:
    //** member functions
    int getNumObservations(char*);
    double convertStringToDouble(const string s);
    int getOutcomeFromString(const string s);
    // convertSplit takes a line and enters y and x data into its arguments
    void convertSplit(string observationString, int& response, covariateVector4d_t& regressors);
    
    //** member data
    int numObservations;
    //int numCovariates; --> redundant because I don't know how to pass a variable-dim argument to likelihood yet
    vector<outcome_t> outcomes;
    vector<covariateVector4d_t> covariates;
     
  }; // end of Logit class definition

#endif


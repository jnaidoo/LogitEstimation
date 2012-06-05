// Logit_NLP.cpp
// implementation of Logit_NLP interface
//
/** VERSION HISTORY:
  * ----------------
  * 28/5/12 first version
  *
  *
  *
  *
  *
  *
  */

// for now, we unfortunately have to hard-code in the number of covariates (k = 4)


#include "Logit_NLP.hpp"
#include "Logit.hpp"

#include <cassert>
#include <iostream>

using namespace Ipopt;

// constructor
Logit_NLP::Logit_NLP()
{}

//destructor
Logit_NLP::~Logit_NLP()
{}

// returns the size of the problem
bool Logit_NLP::get_nlp_info(Index& n, Index& m, Index& nnz_jac_g,
                             Index& nnz_h_lag, IndexStyleEnum& index_style)
{
  n = 4;
  m = 0;
  nnz_jac_g = 0;
  nnz_h_lag = 10; // Hessian is 4x4 and symmetric --> 10 elements in upper triangle
  index_style = TNLP::C_STYLE;

  Logit myLogit("LogitData.txt"); // initialize Logit object with data
                                  // hopefully this only happens once??
  return true;
}

// returns the variable bounds
bool Logit_NLP::get_bounds_info(Index n, Number* x_l, Number* x_u,
                                Index m, Number* g_l, Number* g_u)
{
  assert(n==4);
  assert(m==0);
  
  // box constraints on parameters (x's) are trivial
  for(Index i=0; i<n; ++i){
    x_l[i] = -2e19;
    x_u[i] = 2e19;
  }
  
  return true;
}

// returns the initial point for the problem
bool Logit_NLP::get_starting_point(Index n, bool init_x, Number* x,
                                   bool init_z, Number* z_L, Number* z_U,
                                   Index m, bool init_lambda,
                                   Number* lambda)
{
  assert(init_x == true);
  assert(init_z == false);
  assert(init_lambda == false);

  // initialize parameter estimates (Stata: (.6151037  .54470695  1.0954129   .2425786))
  x[0] = 1;
  x[1] = 1;
  x[2] = 1;
  x[3] = 1;

  return true;
}

// returns the value of the objective function
bool Logit_NLP::eval_f(Index n, const Number* x, bool new_x, Number& obj_value)
{
  assert(n == 4);
  // to be altered later: is Number* a C-style array?
  // if so, can we simply use Eigen::Map calcObjective?
  coefficientVector4d_t tmpBeta << x[0], x[1], x[2], x[3];
  obj_value = myLogit.calcObjective(tmpBeta); 
  return true;
}

// return the gradient of the objective function grad_{x} f(x)
bool Logit_NLP::eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f)
{
  assert(n == 4);
  coefficientVector4d_t tmpBeta << x[0], x[1], x[2], x[3];

  // create temporary vector for output so we only have to evaluate the score once
  scoreVector4d_t tmpScore = myLogit.calcScore(tmpBeta);
  grad_f[0] = tmpScore(0);
  grad_f[1] = tmpScore(1);
  grad_f[2] = tmpScore(2);
  grad_f[3] = tmpScore(3);

  // interesting: in Philip Barrett's code, he has the one-liner
  // thisLogit.evalGradient(x,grad_f);  
  // what is he passing by reference to evalGradient? and what data types are x, grad_f?

  return true;
}

// return the value of the constraints: g(x)
bool Logit_NLP::eval_g(Index n, const Number* x, bool new_x, Index m, Number* g)
{
  // leave this empty as there are no constraints
  return true;
}

// return the structure or values of the jacobian
bool Logit_NLP::eval_jac_g(Index n, const Number* x, bool new_x,
                           Index m, Index nele_jac, Index* iRow, Index *jCol,
                           Number* values)
{
  // leave this empty as there are no constraints
  return true;
}

//return the structure or values of the hessian
bool Logit_NLP::eval_h(Index n, const Number* x, bool new_x,
                       Number obj_factor, Index m, const Number* lambda,
                       bool new_lambda, Index nele_hess, Index* iRow,
                       Index* jCol, Number* values)
{
  if(values == NULL){
  // don't know what this code does. appears to fill in H with
  // H[i,j] = some function of (i,j)
  // where is the fact that the hessian is symmetric flagged?
    Index idx=0;
    for (Index row = 0; row < 4; row++) {
      for (Index col = 0; col <= row; col++) {
        iRow[idx] = row;
        jCol[idx] = col;
        idx++;
      }
    }  
   assert(idx == nele_hess);   
   } //end if
   else{
    assert(n == 4);
    coefficientVector4d_t tmpBeta << x[0], x[1], x[2], x[3];
    SquareMatrix4d_t tmpHessian = myLogit.calcHessian(tmpBeta);  

    // fill the objective portion
    values[0] = tmpHessian(0,0); // 0,0

    values[1] = tmpHessian(1,0); // 1,0
    values[2] = tmpHessian(1,1); // 1,1

    values[3] = tmpHessian(2,0); // 2,0
    values[4] = tmpHessian(2,1); // 2,1
    values[5] = tmpHessian(2,2); // 2,2

    values[6] = tmpHessian(3,0); // 3,0
    values[7] = tmpHessian(3,1); // 3,1
    values[8] = tmpHessian(3,2); // 3,2
    values[9] = tmpHessian(3,3); // 3,3

    // no assert statement here (see if this works?) 
  } // end else


  return true;
}

void Logit_NLP::finalize_solution(SolverReturn status,
                                  Index n, const Number* x, const Number* z_L, const Number* z_U,
                                  Index m, const Number* g, const Number* lambda,
                                  Number obj_value,
				  const IpoptData* ip_data,
				  IpoptCalculatedQuantities* ip_cq)
{
  // here is where we would store the solution to variables, or write to a file, etc
  // so we could use the solution.

  // For this example, we write the solution to the console
  std::cout << std::endl << std::endl << "Solution of the primal variables, x" << std::endl;
  for (Index i=0; i<n; i++) {
     std::cout << "x[" << i << "] = " << x[i] << std::endl;
  }

  std::cout << std::endl << std::endl << "Solution of the bound multipliers, z_L and z_U" << std::endl;
  for (Index i=0; i<n; i++) {
    std::cout << "z_L[" << i << "] = " << z_L[i] << std::endl;
  }
  for (Index i=0; i<n; i++) {
    std::cout << "z_U[" << i << "] = " << z_U[i] << std::endl;
  }

  std::cout << std::endl << std::endl << "Objective value" << std::endl;
  std::cout << "f(x*) = " << obj_value << std::endl;

  std::cout << std::endl << "Final value of the constraints:" << std::endl;
  for (Index i=0; i<m ;i++) {
    std::cout << "g(" << i << ") = " << g[i] << std::endl;
  }
}

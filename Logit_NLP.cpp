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
//#include "auxFunctions.hpp"

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

  return true;
}

// returns the variable bounds
bool Logit_NLP::get_bounds_info(Index n, Number* x_l, Number* x_u,
                                Index m, Number* g_l, Number* g_u)
{

  return true;
}

// returns the initial point for the problem
bool Logit_NLP::get_starting_point(Index n, bool init_x, Number* x,
                                   bool init_z, Number* z_L, Number* z_U,

                                   Index m, bool init_lambda,
                                   Number* lambda)
{

  return true;
}

// returns the value of the objective function
bool Logit_NLP::eval_f(Index n, const Number* x, bool new_x, Number& obj_value)
{
  // obj_value = calcObjective(x); 
  return true;
}

// return the gradient of the objective function grad_{x} f(x)
bool Logit_NLP::eval_grad_f(Index n, const Number* x, bool new_x, Number* grad_f)
{

  return true;
}

// return the value of the constraints: g(x)
bool Logit_NLP::eval_g(Index n, const Number* x, bool new_x, Index m, Number* g)
{

 return true;
}

// return the structure or values of the jacobian
bool Logit_NLP::eval_jac_g(Index n, const Number* x, bool new_x,
                           Index m, Index nele_jac, Index* iRow, Index *jCol,
                           Number* values)
{

  return true;
}

//return the structure or values of the hessian
bool Logit_NLP::eval_h(Index n, const Number* x, bool new_x,
                       Number obj_factor, Index m, const Number* lambda,
                       bool new_lambda, Index nele_hess, Index* iRow,
                       Index* jCol, Number* values)
{

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

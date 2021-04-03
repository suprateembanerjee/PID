#include "PID.h"

PID::PID() 
{
  Kp = 0;
  Ki = 0;
  Kd = 0;

  total_cte = 0;
  prev_cte = 0;

  p_error = 0;
  i_error = 0;
  d_error = 0;
}

PID::PID(double Kp_, double Ki_, double Kd_) 
{
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
  
  total_cte = 0;
  prev_cte = 0;

  p_error = 0;
  i_error = 0;
  d_error = 0;
}

PID::~PID() {}


void PID::set_coeffs(double Kp_, double Ki_, double Kd_) {
  
  // Set PID coefficients
   
  Kp = Kp_;
  Ki = Ki_;
  Kd = Kd_;
}


void PID::UpdateError(double cte) 
{
  // Update PID errors based on cte

  total_cte += cte;
  p_error = Kp * cte;
  d_error = Kd * (cte - prev_cte);
  i_error = Ki * total_cte;
  prev_cte = cte;
}

double PID::TotalError() 
{
  // Calculate and return the Total Error

  return -1.0 * (p_error + d_error + i_error);
}
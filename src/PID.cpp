#include "PID.h"
#include <assert.h>
#include <iostream>
#include <math.h>

//using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double tol, int chunk_size) {
  this->tol = tol;
  this->chunk_size = 100;
  p[0] = 0.10;
  p[1] = 5.0;
  p[2] = 0.10;
  
  /*dp[0] = 0.0;
  dp[1] = 0.0;
  dp[2] = 0.0;*/
}

void PID::UpdateError(double cte) {
  this->cte = cte;
  if(prev_cte == -1) {
    prev_cte = cte;
  }
}

double PID::CalculateThrottle(double steer_value, double speed) {
  double throttle;
  
  if(fabs(steer_value) < 0.03 && speed < 30) {
    throttle = 1.0;
  } else if(fabs(steer_value) < 0.30 )  {
    throttle = 0.3;
  } else {
    throttle = 0;
  }
  return throttle;
}
double PID::CalculateSteer(double speed) {

  count++; //counter used to reset Integral portion
  
  double tolerance_cte = 0.50; // If we are close enough don't steer, adds stability
  if(fabs(cte) < tolerance_cte) {
    return 0;
  }
  if(cte > 0) {
    cte -= tolerance_cte;
  } else {
    cte += tolerance_cte;
  }
  diff_cte = cte - prev_cte;
  prev_cte = cte;
  int_cte += cte;
  
  //We used a modified P where P is propotional to square of CTE. This makes sure we steer more if cte if higher.
  double steer = -p[0] * cte * fabs(cte) - p[1] * diff_cte - p[2] * int_cte/count;
  //std::cout << " steer = " << steer << " p= " << p[0] << "," << p[1] << "," << p[2] << std::endl;
  
  //adjust steer for speed
  /*
  double good_speed = 50;
  if(speed > good_speed) {
    steer = steer * (good_speed/speed) * (good_speed/speed);
  }*/
   
  if(steer < -1.0) {
    steer = -1;
  } else if (steer > 1.0) {
    steer = 1.0;
  }
  
  if(count >= chunk_size) {
    //reinitialize the I error
    count = 0;
    int_cte = 0;
  }
  return steer;
}

void PID::Twiddle() {
 /* Not Used
  double p_i, dp_i;
  double sum_dp = dp[0]+dp[1]+dp[2];
  int occur = count/chunk_size;
  
  if(count == 0) {
    best_error = fabs(cte);
    best_diff_cte = fabs(cte);
  }
  if(tol > sum_dp) {
    //We have reached the tolerance we need.
    std::cout << " count = " << count << " tol= " << tol << " sum_dp = " << sum_dp << std::endl;
    return;
  }
  
  if(count >= 0 && count%chunk_size == 0) {
    //for every even chunk adjust the params
    //for every odd occurance check if adjustment worked else reset param and change dp.
    //decide which params to work on
    switch (occur % 4) {
      case 0:
        p[0] += dp[0];
        break;
      case 1:
        if(fabs(cte) < fabs(best_error)) {
          //looks like param worked, try to increase param next.
          best_error = cte;
          dp[0] *= 1.1; //increase param by 10% next time.
        } else {
          //param failed, lower the param.
          p[0] -= dp[0]; //rollback to original value;
          if(p[0] < 0) {
            p[0] = 0;
          }
          dp[0] *= 0.9; //reduce param by 10% next time.
          //p[0] += dp[0];
        }
        break;
      case 2:
        p[1] += dp[1];
        break;
      case 3:
        if(best_diff_cte < diff_cte) {
          //best_diff_cte = diff_cte;
          dp[1] *= 1.1; //increase param by 10% next time.
        } else {
          best_diff_cte = diff_cte;
          //param failed, lower the param.
          p[1] -= dp[1]; //rollback to original value;
          if(p[1] < 0) {
            p[1] = 0;
          }
          dp[1] *= 0.9; //reduce param by 10% next time.
        }
        break;
      case 4:
        p[2] += dp[2];
        break;
      case 5:
        if(fabs(cte) < fabs(best_error)) {
          //looks like param worked, try to increase param next.
          best_error = cte;
          dp[2] *= 1.1; //increase param by 10% next time.
        } else {
          //param failed, lower the param.
          p[2] -= dp[2]; //rollback to original value;
          if(p[2] < 0) {
            p[2] = 0;
          }
          dp[2] *= 0.9; //reduce param by 10% next time.
        }
        break;
      default:
        std::cerr << "Abort: We should not be here" << std::endl;
        assert(0);
        break;
    }
    std::cout << "cte = " << cte << " best_error = " << best_error << " count = " << count  ;
    std::cout << " diff_cte = " << diff_cte << " best_diff_cte = " << best_diff_cte << " int_cte = " << int_cte;
    std::cout << " occur = " << occur << " p= " << p[0] << "," << p[1] << "," << p[2] ;
    std::cout << " dp = " << dp[0] << "," << dp[1] << "," << dp[2] << std::endl;
  }
  return;
  */
}

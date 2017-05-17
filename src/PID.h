#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double p[3];
  double dp[3];
  double tol;
  
  /*
  * other variables
  */
  double prev_cte = -1; //uninitialized
  double cte;
  double int_cte = 0;
  int chunk_size;
  int count = 0;
  double best_error;
  double diff_cte;
  double best_diff_cte;
  
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double tol, int chunk_size);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
    
  /*
   * Calculate the steering angle.
   */
  double CalculateSteer(double speed);

  /*
   * Calculate throttle.
   */
  double CalculateThrottle(double steer_value, double speed);
  
  /*
   * twiddle will reset the coefficients.
   */
  void Twiddle();
};

#endif /* PID_H */

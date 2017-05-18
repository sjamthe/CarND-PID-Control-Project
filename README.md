# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---

## Demonstrate the use of PID controller algo to stabilize the car

The steering angle is controlled by the PID controller. The following additional modifications to the controller were introduced here.

1. The controller is not just proportional to CTE but to CTE*abs(CTE). This allows the controller to take faster action as the tracking error increases (> 1). That means as the car deviates from the center more the steering is turned more in the opposite direction. 
2. As we want to avoid car steering shaking too much we have introduced a tracking tolerance (+- 0.5). If the CTE is between this range then steering wheel is not adjusted. 
3. The throttle is controlled by simple reasoning for now. If the are not steering a lot (< 0.03) and speed is less than 30 mph then we go full throttle (1.0). If the steering is > .03 but < .3 the throttle is 0.3 (which maintains speed at about 30mph) else throttle is set to zero.

Note: We tried to implement twiddle but found it difficult to stabilize and also not necessary after we found the coefficients for P,I,D.

Following is a [video](https://www.youtube.com/watch?v=gajd7TQmusk&t=21s) of a full run.


# PID ControllerProject
Self-Driving Car Engineer Nanodegree Program
   

## Reflections

This project implements a very simple PID controller that controls the steering angle of the vehicle in a simulated environment. 
The values for coefficients has been hard coded and are obviously not computationally optimal. The project meets the rubric, and since I am behind schedule and in a crunch to
complete the final project in under 3 weeks, I am submitting this for evaluation even though it is unsatisfactory to me. I could not wait 3 days for a mentor to respond to
my questions in Knowledge hub, and all previous answers to others' questions regarding my queries were unsatisfactory, so waiting would probably not make any sense anyway.

### Overall Workflow

The PID controller takes in a few hard coded static coefficients that I have manually tuned to optimize it for the intended behavior in the Simulator provided by Udacity.
The PID class contained overloaded constructors to initialize the objects, and a set_coeffs() method to specifically set coefficients. My initial plan was to use set_coeffs() to
use the result from Coordinate Ascent (Twiddle) to initialize my PID controllers, but since it never got implemented, it remained unused. The object has access to a few variables 
such as the coefficients themselves, along with errors, previous CTE (used for differential calculations) and total CTE (used for integral calculations). The throttle has been 
hardcoded to simulate constant velocity.

### Possible Improvements

* Calculating Optimal Coefficients

The hard-coded coefficients are not only inefficient and time consuming, but are also sub-optimal. When I faced difficulties implementing Genetic Algorithm based techniques such
as Coordinate Ascent (Twiddle), I looked at some other techniques to optimize PID coefficients, such as Ant Colony Optimizations (ACO), but I was unable to implement that as well.
My gripe is, Twiddle was actually covered in the lectures, but the implementation was so simplistic that implementing the algorithm in this context was much more convoluted. Not
being able to implement Twiddle feels like I could not properly learn the material I was expected to learn, even though I implemented the project.


* Using another PID controller for throttle

Throttle has been set to a constant velocity, which is inefficient and lazy. Ideally I would want to implement a PID controller for throttle as well, and my efforts in implementing
it may be visible from the commented code in _main.cpp_. Intuitively, it makes sense to use CTE because it is a parameter that tells how far the car is from the center of the lane.
Intuitively, it would make sense if speed was higher when the car is in the center of the lane and decrease as the car deviates from the center. This does not work because the
compiler throws a weird error. Then I tried to use _speed_ instead of _cte_.Trying to implement this resulted in an ever-increasing speed, that eventually throws the car 
off-path after sharp turns. With increased speed the car's steering also becomes extremely unstable which I do not understand why.


### Issues with the current project

* Steering instability seems to explode

As the car moves forward, at low speeds, a P-controller seems to oscillate a little. Then, as speed increases, the P-Controller starts oscillating much more with time, almost
like exploding gradients. This was not the speed simply amplifying the steering, the steering measurement itself explodes, regardless of speed, throwing the car off track.
When we talk about a full PID controller, any value in the I component also makes the car oscillate, where this same issue from the P-Controller exists. This forced me to 
essentially implement a PD Controller and not a PID controller to simulate desired working.

* PID Controller did not meet theoretical expectations

Theoretically, the PID controller does converge, even though slightly later than a PD Controller. Implementing the PID controller produced very different results. Any value 
for the integral coefficient makes the vehicle oscillate almost like a P-Controller, even when differential is weighted heavily. This creates a knowledge gap which remains 
unaddressed.


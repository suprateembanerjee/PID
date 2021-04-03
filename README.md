# PID Controller
Udacity Self-Driving Car Engineer Nanodegree Program

This project involves the a Simulator developed by Udacity which can be downloaded [here](https://github.com/udacity/self-driving-car-sim/releases).

## Dependencies

* **cmake 3.5** [Installation Instructions](https://cmake.org/install/)
* **Ubuntu Terminal** for running UNIX Terminal on Windows. [download](https://aka.ms/wslubuntu2004) 
* **make 4.1 (Linux and Mac), 3.81 (Windows)**  Installation Instructions : [Mac](https://developer.apple.com/xcode/features/) [Windows](http://gnuwin32.sourceforge.net/packages/make.html)
* **g++ 9.3** Installation Instructions: [Mac](https://developer.apple.com/xcode/features/) [Windows](http://www.mingw.org/) 
* **uWebSocketIO** for smooth data flow between simulator and code. [download](https://github.com/uWebSockets/uWebSockets)  
    ```
    <Navigate to the project folder using Ubuntu terminal>
    chmod u+x install-ubuntu.sh
    ./install-ubuntu.sh
    ./install-linux.sh
    ```

## Installation and Usage

With uWebSocketIO installed, navigate to the project directory, and execute the following commands:
```
mkdir build && cd build
cmake .. && make
./pid
```
On the Ubuntu Terminal, we can observe that the program is listening to a port. Now, if the Simulator is launched, it should automatically connect and execute.

## Overall Workflow

The PID controller takes in a few hard coded static coefficients that I have manually tuned to optimize it for the intended behavior in the Simulator provided by Udacity.
The PID class contained overloaded constructors to initialize the objects, and a set_coeffs() method to specifically set coefficients. The object has access to a few variables 
such as the coefficients themselves, along with errors, previous CTE (used for differential calculations) and total CTE (used for integral calculations). The throttle has been 
hardcoded to simulate constant velocity.

Essentially, as the project currently stands, it is a P Controller, as both I and D coefficients have been tuned to negligible or null values. I plan to update this code in the future where I would use the following possible improvements.

## Possible Improvements

* Calculating Optimal Coefficients

The hard-coded coefficients are not only inefficient and time consuming, but are also sub-optimal. Genetic Algorithm based techniques such as Coordinate Ascent (Twiddle), or other techniques such as Ant Colony Optimizations (ACO) can be used to optimize coefficients.

* Using another PID controller for throttle

Throttle has been set to a constant velocity. Ideally a PID controller can be used for throttle as well. Intuitively, it makes sense to use CTE because it is a parameter that tells how far the car is from the center of the lane. Intuitively, it would also make sense if speed was higher when the car is in the center of the lane and decrease as the car deviates from the center. 

## Output

A video titled **Output.mp4** can be found in the repository showcasing the working of the PID Controller in the simulator.

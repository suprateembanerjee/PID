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
cd build
cmake .. && make
./pid
```
On the Ubuntu Terminal, we can observe that the program is listening to a port. Now, if the Simulator is launched, it should automatically connect and execute.

## Output

A video titled **Output.mp4** can be found in the repository showcasing the working of the PID Controller in the simulator.

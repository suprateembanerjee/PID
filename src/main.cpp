#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include "json.hpp"
#include "PID.h"

// for convenience
using nlohmann::json;
using std::string;
using std::cin;
using std::cout;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }



string hasData(string s) 
{
  /** Checks if the SocketIO event has JSON data.
    * If there is data the JSON object in string format will be returned,
    * else the empty string "" will be returned.
    */

  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");

  if (found_null != string::npos)
    return "";

  else if (b1 != string::npos && b2 != string::npos)
    return s.substr(b1, b2 - b1 + 1);

  return "";
}

void changemode(int);
int    kbhit(void);

void changemode(int dir)
{
  static struct termios oldt, newt;

  if ( dir == 1 )
  {
    tcgetattr( STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  }
  else
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

int kbhit (void)
{
  struct timeval tv;
  fd_set rdfs;

  tv.tv_sec = 0;
  tv.tv_usec = 0;

  FD_ZERO(&rdfs);
  FD_SET (STDIN_FILENO, &rdfs);

  select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
  return FD_ISSET(STDIN_FILENO, &rdfs);

}

int main() {
  uWS::Hub h;

  // Initialize the PID variable
  PID steer_pid(0.2, 0.0001, 5.0);

  h.onMessage([&steer_pid/*, &throttle_pid*/](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, 
                     uWS::OpCode opCode) 
  {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event

    if (length && length > 2 && data[0] == '4' && data[1] == '2') 
    {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") 
      {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") 
        {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());
          double steer_value;
          double throttle_value = 0.3;
          
          // Calculate steering value [-1, 1]

          steer_pid.UpdateError(cte);
          steer_value = steer_pid.TotalError();
          
          char ch; 
          changemode(1);

          if ( kbhit() )
          {
          	cin >> ch;
            cout << ch << " From: P: " << steer_pid.Kp << " I: " << steer_pid.Ki <<  " D: " << steer_pid.Kd;
            
            switch (ch)
            {
                case 'P':
                    steer_pid.Kp += steer_pid.Kp*0.1; // Or += 0.01; 
                    break;
                case 'p':
                    steer_pid.Kp -= steer_pid.Kp*0.1; // Or -= 0.01;
                    break;
                case 'I':
                    steer_pid.Ki += steer_pid.Ki*0.1; // Or += 0.001; 
                    break;
                case 'i':
                    steer_pid.Ki -= steer_pid.Ki*0.1; // Or -= 0.001; 
                    break;
                case 'D':
                    steer_pid.Kd += steer_pid.Kd*0.1; // Or += 0.1; 
                    break;
                case 'd':
                    steer_pid.Kd -= steer_pid.Kd*0.1; // Or -=0.1;
                    break;
            }
            cout << ch << " To: P: " << steer_pid.Kp << " I: " << steer_pid.Ki <<  " D: " << steer_pid.Kd;
          }

          changemode(0);

          json msgJson;
          msgJson["steering_angle"] = steer_value;
          msgJson["throttle"] = throttle_value;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } 
      else 
      {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) 
  {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, 
                         char *message, size_t length) 
  {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  
  if (h.listen(port)) 
  {
    std::cout << "Listening to port " << port << std::endl;
  } 
  else 
  {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }
  
  h.run();
}
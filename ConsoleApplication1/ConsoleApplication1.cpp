#include <stdio.h>
#include <iostream>
#include <windows.h>
#define _USE_MATH_DEFINES
#include <math.h>

enum valve_control_t
{
    HI=1, LO=-1, ZO=0
};


// Bang-bang control function with hysteresis
int8_t bangBangControl(float setpoint, float feedback, float hysteresis, float deadband)
{
    static int8_t output = 0;

    float lh = 0.0;
    float hh = 0.0;
   
    switch (output)
    {
    case -1:
        lh = -deadband;     
        hh =  hysteresis + deadband;
        break;
    case 1:
        lh = -(hysteresis + deadband);  
        hh =  deadband;
        break;
    case 0:
        lh = -(hysteresis + deadband);
        hh =  hysteresis + deadband;
        break;
    default:
        break;
    }


    float error = setpoint - feedback;

    if ((error > lh) && (error < hh))       output =  0;
    else if (error > hh)                    output =  1;
    else if (error < lh)                    output = -1; 

    return output;
}



int main()
{
    int u_valve = 0;
    float yr = 0.0;
    double t = 0.0;
    while (true)
    {

        yr = sin(2 * M_PI * 0.1 * t);

        u_valve = bangBangControl(yr, 0, 0.2, 0.3);
        Sleep(10);
        t += 0.1;

        std::cout << "yr: " << yr << "\t u: " << u_valve << std::endl;
    }

    return 0;
}
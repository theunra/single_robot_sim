#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <string>

// Position and Orientation
struct Pose
{
    double x;
    double y;
    double w;

    Pose(){
        x = y = w = 0.0;
    }
};

// Robot properties
struct Robot
{
    Pose pos;
};

// Encoder
struct Encoder
{
    double encoder_pulse;
    double encoder_ppr;
    double encoder_ratio;
};

#endif
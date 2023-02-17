#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <array>
#include <map>
#include <vector>

#define N_LINEAR_SPEED 8
#define N_ROTATION_SPEED 8
#define N_MAX_MOTOR 3

namespace fukuro 
{

enum MotorIndex // Motor Index
{
    motor1,
    motor2,
    motor3
};

enum speed_t
{
    Speed025 = 0, //speed = 25 cm per sec
    Speed050 = 1,
    Speed075 = 2,
    Speed100 = 3,
    Speed125 = 4,
    Speed150 = 5,
    Speed175 = 6,
    Speed200 = 7 //speed = 200 cm per sec
};

enum rotation_speed_t
{
    SpeedPhi6 = 0, //speed = phi/6 per sec
    SpeedPhi5 = 1,
    SpeedPhi4 = 2,
    SpeedPhi3 = 3,
    SpeedPhi2 = 4,
    SpeedPhi1 = 5 //speed = phi per sec
};

typedef std::map<speed_t, double> MotorLinearSpeedMap;
typedef std::vector<MotorLinearSpeedMap> MotorLinearSpeedMaps;
typedef std::vector<double> PIParam;

struct Motor
{
    double m1;
    double m2;
    double m3;

    Motor(){
        m1 = m2 = m3 = 0.0;
    }
};

struct Speed
{
    double _025;
    double _050;
    double _075;
    double _100;
    double _125;
    double _150;
    double _175;
    double _200;
};

struct MotorRatio
{
    Speed cw;
    Speed ccw;
};

struct MotorStep
{
    Motor cw_motor;
    Motor ccw_motor;
};

struct PIParameter
{
    PIParam k_param;
    
    PIParameter()
    {
        k_param.resize(9);
    }
};

struct MotorParameter
{
    static constexpr std::array<speed_t, N_LINEAR_SPEED> linear_speeds{
    {
        speed_t::Speed025,
        speed_t::Speed050,
        speed_t::Speed075,
        speed_t::Speed100,
        speed_t::Speed125,
        speed_t::Speed150,
        speed_t::Speed175,
        speed_t::Speed200
    } };

    static constexpr std::array<rotation_speed_t, N_ROTATION_SPEED> rotation_speeds{
    {
        rotation_speed_t::SpeedPhi6,
        rotation_speed_t::SpeedPhi5,
        rotation_speed_t::SpeedPhi4,
        rotation_speed_t::SpeedPhi3,
        rotation_speed_t::SpeedPhi2,
        rotation_speed_t::SpeedPhi1
    }};

    MotorParameter()
    {
        linear_map_cw.resize(N_MAX_MOTOR);
        linear_map_ccw.resize(N_MAX_MOTOR);

        auto ccw = linear_map_ccw.begin();
        auto ccw_end = linear_map_ccw.end();
        for (auto &cw : linear_map_cw)
        {
            for (size_t i = 0; i < 8; i++)
            {
                auto s = static_cast<speed_t>(i);
                auto pair = std::make_pair(s, 0.0);
                cw.insert(pair);
                ccw->insert(pair);
            }
            ccw++;
        }
    }

    MotorLinearSpeedMaps linear_map_cw;
    MotorLinearSpeedMaps linear_map_ccw;
    std::map<rotation_speed_t, double> rotation_map_cw;
    std::map<rotation_speed_t, double> rotation_map_ccw;
    double linear(double speed);
    double rotation(double speed);
};

}
#endif // MOTOR_HPP
#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include <eigen3/Eigen/Core>
#include <eigen3/Eigen/Dense>
#include <random>
#include <stdio.h>
#include <iostream>

namespace fukuro
{
    class KalmanFilter;
}

class KalmanFilter
{
private:
    Eigen::Vector3d x, x_, u, e, z;
    Eigen::Matrix3d A, B, P, P_, Q, R, H, K;

    double T;
    double rv, qv;
    double X, Y, Theta;
    bool first_update;
    void estimate();
    void measure();

public:
    KalmanFilter();
    ~KalmanFilter();

    void setX(double x);
    void setY(double y);
    void setT(double T_);
    void setState(double x1, double x2, double x3);
    void setControl(double u1, double u2, double u3);
    void setMeasurement(double z1, double z2, double z3);
    void update(double T, double u1, double u2, double u3, double z1, double z2, double z3);
    double getTheta();
    double getX();
    double getY();
    double getVx();
    double getVy();

};


#endif // KALMANFILTER_H
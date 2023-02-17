#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include <vector>
#include <fukuro/field.hpp>
#include <fukuro/Point.hpp>

namespace fukuro
{

    #define STATIC_OBSTACLE 1

    enum Shape
    {
        CIRCLE,
        SQUARE,
        CLEARCIRCLE,
        CLEARSQUARE
    };

    struct Obstacle
    {
        fukuro::Point2d pos;
        double r;
        int shape;

        Obstacle() : 
            pos(fukuro::Point2d(0.0, 0.0)),
            r(OBSTACLE_RADIUS),
            shape(CIRCLE)
        {}

        Obstacle(double _x, double _y, double r_ = OBSTACLE_RADIUS, int shape_ = CIRCLE)
        {
            pos = fukuro::Point2d(_x, _y);
            r = r_;
            shape = shape_;
        }

        Obstacle(fukuro::Point2d &pt, double r_ = OBSTACLE_RADIUS, int shape_ = CIRCLE)
        {
            pos = pt;
            r = r_;
            shape = shape_;
        }
    };

    typedef std::vector<Obstacle> Obstacles;

    // Static Obstacles
    struct StaticObstacle
    {
        fukuro::Point2d pos;
        bool status;
        double r;
        int shape = CIRCLE;

        StaticObstacle() : 
            pos(0.0, 0.0), r(0.0), status(false)
        {}

        StaticObstacle(double _x, double _y, double _r = OBSTACLE_RADIUS, bool _status = false, int _shape = CIRCLE)
        {
            pos = fukuro::Point2d(_x, _y);
            r = _r;
            status = _status;
            shape = _shape;
        }

        StaticObstacle(fukuro::Point2d _pos, double _r = OBSTACLE_RADIUS, bool _status = false, int _shape = CIRCLE)
        {
            pos = _pos;
            r = _r;
            status = _status;
            shape = _shape;
        }
    };

    typedef std::vector<StaticObstacle> StaticObstacles; 
}

#endif
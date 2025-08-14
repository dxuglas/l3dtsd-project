#ifndef ANGLE_H
#define ANGLE_H

#include <cmath>

/** 
 * @brief wrap angle from -pi to pi
 * 
 * @param angle angle to be wrapped (in radians)
 * 
 * @return double wrapped angle
 */
inline double wrap_angle(double angle) {
    while (angle > M_PI) angle -= 2*M_PI;
    while (angle < -M_PI) angle += 2*M_PI;
    return angle;
}


/**
 * @brief convert angle from degrees to radians
 * 
 * @param angle angle in degrees
 * 
 * @return double anlge in radians
 */
inline double to_radians(double angle) {
    return angle * M_PI / 180.0;
}

#endif
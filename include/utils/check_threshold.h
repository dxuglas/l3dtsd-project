#ifndef CHECK_THRESHOLD_H
#define CHECK_THRESHOLD_H

#include <cstdlib>

/**
 * @brief checks value is above a min value, otherwise sets to 0
 * 
 * @param value the value to be checked
 * @param min_value the minimum value allowed
 * 
 * @return float the value or 0
 */
inline float check_threshold(float value, float min_value) {
    return std::abs(value) > min_value ? value : 0.0f;
}

#endif
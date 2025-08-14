#ifndef POSE_H
#define POSE_H

/**
 @brief a struct representing the pose of the robot
 */
struct Pose {
    float x;
    float y;
    float heading;

    Pose (float x, float y, float heading);
};

#endif // POSE_H
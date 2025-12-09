#ifndef CAMERA_H
#define CAMERA_H

#include "common.hpp"

// Camera position (Y offset for scrolling)
extern float cameraY;
extern float targetCameraY;

// Function declarations
void updateCamera(float playerPixelY);
float getCameraOffset();
void resetCamera();

#endif
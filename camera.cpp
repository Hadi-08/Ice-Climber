#include "camera.hpp"

// Camera position (Y offset for scrolling)
float cameraY = 0.0f;
float targetCameraY = 0.0f;

// Update camera to follow player vertically
void updateCamera(float playerPixelY) {
    // Convert board Y to pixel Y
    float screenY = playerPixelY - cameraY;

    // If player is in upper portion of screen, scroll up
    if (screenY < CAMERA_THRESHOLD) {
        targetCameraY = playerPixelY - CAMERA_THRESHOLD;
    }

    // Smooth camera movement
    float diff = targetCameraY - cameraY;
    cameraY += diff * CAMERA_FOLLOW_SPEED;

    // Don't scroll below ground
    if (cameraY < 0) {
        cameraY = 0;
    }
}

// Get camera offset for rendering
float getCameraOffset() {
    return cameraY;
}

// Reset camera for new stage
void resetCamera() {
    cameraY = 0.0f;
    targetCameraY = 0.0f;
}
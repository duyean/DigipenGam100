#include "cprocessing.h"
#include "cameraClass.h"

//when using this create a blank camera then run the command through this. Or else we get permission errors! -day
void CreateCamera(Camera* cam, float x, float y) {
    cam->x = x;
    cam->y = y;
    cam->offsetX = 0;
    cam->offsetY = 0;
}

void UpdateCamera(Camera* cam, float playerX, float playerY, float playerDX, float playerDY, float smoothing) {
	float lagFactor = 30.0f;                //lag intensity factor
	cam->offsetX += playerDX * lagFactor;   //player DX & DY is movement from last frame
    cam->offsetY += playerDY * lagFactor;

    cam->offsetX *= 0.9f;
    cam->offsetY *= 0.9f;

    // Target position includes offset and centers player on screen
    float targetX = playerX + cam->offsetX - 640;
    float targetY = playerY + cam->offsetY - 360;

    cam->x += (targetX - cam->x) * smoothing;
    cam->y += (targetY - cam->y) * smoothing;
}

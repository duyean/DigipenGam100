#pragma once

typedef struct {
    float x, y;           // Camera position
    float offsetX, offsetY; // Lag offset based on player movement
} Camera;
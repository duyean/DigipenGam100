#pragma once

#include "cprocessing.h"
#include "layerEnum.h"

typedef struct {
    CP_Image image;
    ParallaxDepth depth;
    float x, y;
    float scale;
    float zoomSpeed;
    int isZooming;
} ParallaxLayer;


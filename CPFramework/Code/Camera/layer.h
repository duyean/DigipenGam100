#pragma once
#include "layerEnum.h"
#include "layerClass.h"
#include "cameraClass.h"


void ParallaxLayer_Init(ParallaxLayer* layer, const char* path, ParallaxDepth depth, float x, float y);
void ParallaxLayer_StartZoom(ParallaxLayer* layer, float targetScale, float speed);
void ParallaxLayer_Update(ParallaxLayer* layer);
void ParallaxLayer_Draw(ParallaxLayer* layer, Camera* cam);

/*---------------------------------------------------------------
  File: layer.c
  Project: GAM100, Team ChocoMochiPie
  Author: Daniel
  Purpose: background layers

  Copyright: 2025, Digipen Institute of Technology, Singapore
----------------------------------------------------------------*/
#include "layerClass.h"
#include "layerEnum.h"
#include "camera.h"
#include "cprocessing.h"
#include <stdio.h>

// Maps depth to scroll factor for parallax effect
static float GetScrollFactor(ParallaxDepth depth) {
    switch (depth) {
    case PARALLAX_BACKGROUND: return 0.9f;
    case PARALLAX_CENTER:     return 1.0f;
    case PARALLAX_FOREGROUND: return 1.2f;
    default: return 1.0f;
	} //please edit when capable, I have not tested the offsets -day
}

void ParallaxLayer_Init(ParallaxLayer* layer, const char* path, ParallaxDepth depth, float x, float y) {
    layer->image = CP_Image_Load(path);
    layer->depth = depth;
    layer->x = x;
    layer->y = y;
    layer->scale = 1.0f;
    layer->zoomSpeed = 0;
    layer->isZooming = 0;
}

void ParallaxLayer_StartZoom(ParallaxLayer* layer, float targetScale, float speed) {
    layer->zoomSpeed = speed;
    layer->isZooming = 1;
} //if you ever need to zoom in or out on a layer, use this function -day

void ParallaxLayer_Update(ParallaxLayer* layer) {
    if (layer->isZooming) {
        layer->scale += layer->zoomSpeed;
        if (layer->zoomSpeed > 0 && layer->scale >= 1.0f) layer->isZooming = 0;
        if (layer->zoomSpeed < 0 && layer->scale <= 1.0f) layer->isZooming = 0;
    } 
}

void ParallaxLayer_Draw(ParallaxLayer* layer, Camera* cam) {
    float factor = GetScrollFactor(layer->depth);
    float screenX = layer->x - cam->x * factor;
    float screenY = layer->y - cam->y * factor;
    float w = CP_Image_GetWidth(layer->image) * layer->scale;
    float h = CP_Image_GetHeight(layer->image) * layer->scale;
    CP_Image_Draw(layer->image, screenX, screenY, w, h, 255);
}
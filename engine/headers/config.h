#pragma once
//engine
#define title "sandbox"
#define screenWidth 1024
#define screenHeight 720
#define fps 144
#define mapRows 32
#define mapCols 32
#define colliderColor GREEN
int BLOOM_INTENSITY = 96;

//box2D
#define vIterations 8
int32_t velocityIterations = vIterations;
#define pIterations 3
int32_t positionIterations = pIterations;
#define b2Grav 800
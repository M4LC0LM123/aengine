#pragma once
// engine
#define title "sandbox"
#define screenWidth 1024
#define screenHeight 720
#define fps 144
#define mapRows 32
#define mapCols 32
#define colliderColor GREEN
int BLOOM_INTENSITY = 0;

// box2D
#define Physics2D
#define PhysicsTimeStep 144
#define vIterations 8
int32_t velocityIterations = vIterations;
#define pIterations 3
int32_t positionIterations = pIterations;
#define b2Grav 800

// react 3d
#define Physics3D
#define PhysicsTimeStep3D 60
#define vIterations3D 15
int32_t velocityIterations3D = vIterations3D;
#define pIterations3D 8
int32_t positionIterations3D = pIterations;
#define grav3D 9

// user defined
//#define ASSERT_TILEMAP
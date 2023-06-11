#ifndef ANIMATION_H
#define ANIMATION_H
#pragma once

struct Animation 
{
    Texture2D texture;
    int frame;
    int speed;
    int frames;
    int frameCounter;
    Vector2 frameSize;
};

#endif
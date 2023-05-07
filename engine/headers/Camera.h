#pragma once
#include "raylib.h"

void cameraFollow(Camera2D* camera, Vector2 pos)
{
    camera->target = (Vector2) {pos.x, pos.y};
}

void lerpCamera(Camera2D* camera, Vector2 pos, float delta)
{
    camera->target = lerp(camera->target, pos, delta);
}

void smoothCamera(Camera2D* camera, Vector2 pos, float delta)
{
    float minSpeed = 30;
    float minEffectLength = 10;
    float fractionSpeed = 0.8f;

    camera->offset = (Vector2){ sWidth/2.0f, sHeight/2.0f };
    Vector2 diff = sub(pos, camera->target);
    float Length = length(diff);

    if (Length > minEffectLength)
    {
        float speed = fmaxf(fractionSpeed * Length, minSpeed);
        camera->target = add(camera->target, scale(diff, speed*delta/Length));
    }
}

void cameraBoundsPush(Camera2D* camera, Vector2 pos, float delta)
{
    Vector2 bbox = { 0.2f, 0.2f };

    Vector2 bboxWorldMin = GetScreenToWorld2D((Vector2){ (1 - bbox.x)*0.5f*sWidth, (1 - bbox.y)*0.5f*sHeight }, *camera);
    Vector2 bboxWorldMax = GetScreenToWorld2D((Vector2){ (1 + bbox.x)*0.5f*sWidth, (1 + bbox.y)*0.5f*sHeight }, *camera);
    camera->offset = (Vector2){ (1 - bbox.x)*0.5f * sWidth, (1 - bbox.y)*0.5f*sHeight };

    if (pos.x < bboxWorldMin.x) camera->target.x = pos.x;
    if (pos.y < bboxWorldMin.y) camera->target.y = pos.y;
    if (pos.x > bboxWorldMax.x) camera->target.x = bboxWorldMin.x + (pos.x - bboxWorldMax.x);
    if (pos.y > bboxWorldMax.y) camera->target.y = bboxWorldMin.y + (pos.y - bboxWorldMax.y);
}

void limitCameraToMap(Camera2D* camera, TileMap* tileMap)
{
    if (camera->target.x - camera->offset.x <= 0) camera->target.x = camera->offset.x;
    if (camera->target.y - camera->offset.y <= 0) camera->target.y = camera->offset.y;
    if (camera->target.x + camera->offset.x >= mapCols * tileMap->tileScale.x) camera->target.x = mapCols * tileMap->tileScale.x - camera->offset.x*2;
    if (camera->target.y + camera->offset.y >= mapRows * tileMap->tileScale.y) camera->target.y = mapRows * tileMap->tileScale.y - camera->offset.y*2;
}

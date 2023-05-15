#pragma once

void cameraFollow(Camera2D* camera, Vector2 pos);
void lerpCamera(Camera2D* camera, Vector2 pos, float delta);
void smoothCamera(Camera2D* camera, Vector2 pos, float delta);
void cameraBoundsPush(Camera2D* camera, Vector2 pos, float delta);
void limitCameraToMap(Camera2D* camera, TileMap* tileMap);
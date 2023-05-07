#include "headers/OrthographicCamera.h"

#define sWidth GetScreenWidth()
#define sHeight GetScreenHeight()

struct OrthographicCamera
{
    Camera2D matrix;
    Vector2 position;
    Vector2 offset;
    float rotation;
    float zoom;
    float viewportWidth;
    float viewportHeight;

    void init(Vector2 pos)
    {
        this->position = pos;
        this->rotation = 0.0f;
        this->zoom = 1.0f;
        this->viewportWidth = (float) GetScreenWidth();
        this->viewportHeight = (float) GetScreenHeight();
        this->offset = (Vector2){this->viewportWidth/2.0f, this->viewportHeight/2.0f};
        this->matrix.target = this->position;
        this->matrix.offset = this->offset;
        this->matrix.rotation = this->rotation;
        this->matrix.zoom = this->zoom;
    }

    void update()
    {
        this->matrix.target = this->position;
        this->matrix.offset = this->offset;
        this->matrix.rotation = this->rotation;
        this->matrix.zoom = this->zoom;
    }

    void setSize(float w, float h)
    {
        this->viewportWidth = w;
        this->viewportHeight = h;
    }

    int getViewportWidth()
    {
        return this->viewportWidth;
    }

    int getViewportHeight()
    {
        return this->viewportHeight;
    }

    void lerp(Vector2 target, float alpha)
    {
        this->position.x += alpha * (target.x - this->position.x);
        this->position.y += alpha * (target.y - this->position.y);
    }

    void smooth(Vector2 pos, float delta)
    {
        float minSpeed = 30;
        float minEffectLength = 10;
        float fractionSpeed = 0.8f;

        this->offset = (Vector2){ sWidth/2.0f, sHeight/2.0f };
        Vector2 diff = sub(pos, this->position);
        float Length = length(diff);

        if (Length > minEffectLength)
        {
            float speed = fmaxf(fractionSpeed * Length, minSpeed);
            this->position = add(this->position, scale(diff, speed*delta/Length));
        }
    }

    void boundsPush(Vector2 pos, float delta)
    {
        Vector2 bbox = { 0.2f, 0.2f };

        Vector2 bboxWorldMin = GetScreenToWorld2D((Vector2){ (1 - bbox.x)*0.5f*sWidth, (1 - bbox.y)*0.5f*sHeight }, this->matrix);
        Vector2 bboxWorldMax = GetScreenToWorld2D((Vector2){ (1 + bbox.x)*0.5f*sWidth, (1 + bbox.y)*0.5f*sHeight }, this->matrix);
        this->offset = (Vector2){ (1 - bbox.x)*0.5f * sWidth, (1 - bbox.y)*0.5f*sHeight };

        if (pos.x <= bboxWorldMin.x) this->position.x = pos.x;
        if (pos.y <= bboxWorldMin.y) this->position.y = pos.y;
        if (pos.x >= bboxWorldMax.x) this->position.x = bboxWorldMin.x + (pos.x - bboxWorldMax.x);
        if (pos.y >= bboxWorldMax.y) this->position.y = bboxWorldMin.y + (pos.y - bboxWorldMax.y);
    }

    void limitToMap(TileMap* tileMap)
    {
        if (this->position.x - this->offset.x <= 0) this->position.x = this->offset.x;
        if (this->position.y - this->offset.y <= 0) this->position.y = this->offset.y;
        if (this->position.x + this->offset.x >= mapCols * tileMap->tileScale.x) this->position.x = mapCols * tileMap->tileScale.x - this->offset.x;
        if (this->position.y + this->offset.y >= mapRows * tileMap->tileScale.y) this->position.y = mapRows * tileMap->tileScale.y - this->offset.y;
    }

};

#include "headers/PerspectiveCamera.h"
#include "raylib.h"
#include "raymath.h"

struct PerspectiveCamera
{
    private:
        Vector2 prevMousePos;
        Vector2 currentMousePos;

    public:
        Camera3D matrix;
        Vector3 position;
        Vector3 target;
        Vector3 up;
        Vector3 front;
        Vector3 right;
        Vector2 rotation;
        float fov;

        void update()
        {
            this->matrix.position = this->position;
            this->matrix.target = this->target;
            this->matrix.up = this->up;
            this->matrix.fovy = this->fov;
        }

        void SetFirstPerson(float sensitivity, bool isMouseLocked)
        {
            if (isMouseLocked)
            {
                HideCursor();
                currentMousePos = GetMousePosition();
                Vector2 mouseDelta = {currentMousePos.x - this->prevMousePos.x, -1 * (currentMousePos.y - this->prevMousePos.y)};

                // Adjust camera angles based on mouse movement
                this->rotation.y += mouseDelta.x * sensitivity;
                this->rotation.x -= mouseDelta.y * sensitivity;

                // Clamp camera pitch to avoid flipping
                if (this->rotation.x > 89.0f)
                    this->rotation.x = 89.0f;
                if (this->rotation.x < -89.0f)
                    this->rotation.x = -89.0f;

                // Update previous mouse position
                this->prevMousePos = currentMousePos;

                // Lock mouse to window center
                SetMousePosition(GetScreenWidth() / 2, GetScreenHeight() / 2);
                this->prevMousePos = GetMousePosition();
            }
            else
            {
                ShowCursor();
            }

            // Calculate camera front vector
            Matrix cameraRotation = MatrixRotateXYZ((Vector3){DEG2RAD * this->rotation.x, DEG2RAD * this->rotation.y, 0});
            this->front = Vector3Transform((Vector3){0.0f, 0.0f, -1.0f}, cameraRotation);
            this->right = Vector3Transform((Vector3){1.0f, 0.0f, 0.0f}, cameraRotation);
            this->up = Vector3Transform((Vector3){0.0f, 1.0f, 0.0f}, cameraRotation);
        }

        void SetDefaultFPSControls(int keyForward, int keyBackward, int keyLeft, int keyRight, int speed, bool isMouseLocked)
        {
            if (IsKeyDown(keyForward) && isMouseLocked)
            {
                this->position.x = this->position.x + this->front.x * speed * GetFrameTime();
                this->position.z = this->position.z + this->front.z * speed * GetFrameTime();
            }
            if (IsKeyDown(keyBackward) && isMouseLocked)
            {
                this->position.x = this->position.x - this->front.x * speed * GetFrameTime();
                this->position.z = this->position.z - this->front.z * speed * GetFrameTime();
            }
            if (IsKeyDown(keyLeft) && isMouseLocked)
            {
                this->position.x = this->position.x - this->right.x * speed * GetFrameTime();
                this->position.z = this->position.z - this->right.z * speed * GetFrameTime();
            }
            if (IsKeyDown(keyRight) && isMouseLocked)
            {
                this->position.x = this->position.x + this->right.x * speed * GetFrameTime();
                this->position.z = this->position.z + this->right.z * speed * GetFrameTime();
            }

        }

        void DefaultFPSMatrix()
        {
            this->target = Vector3Add(this->position, this->front);
        }

};

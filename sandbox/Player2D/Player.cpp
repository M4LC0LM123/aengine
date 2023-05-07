#include "Player.h"
#include "raylib.h"
#include "../engine/headers/engine.h"

Player::Player() 
{ 
    this->scale = {40, 40};
    this->addComponent<Bloom>();
    this->addComponent<KinematicBody>();
    this->getComponent<KinematicBody>()->textureScale = {40, 40};
    this->getComponent<KinematicBody>()->color = BLANK;
    this->getComponent<KinematicBody>()->bounce = false;
    this->debugInfo = false;
    this->debugToggle = 1;
    this->tag = "Player";
    this->setZ(1);
}

void Player::init()
{
    this->anim.texture = LoadTexture("../assets/animation.png");
    this->anim.speed = 10;
    this->anim.frames = 5;
    this->anim.frameSize = {16, 16};
    this->getComponent<KinematicBody>()->texture = LoadTexture("../assets/engine.png");
    this->getComponent<KinematicBody>()->setFrame({16, 16}, 0);
    this->getComponent<Bloom>()->setColorFromImage(this);
}

void Player::update()
{
    Entity::update();
    if (!console.isActive())
    {
        if (IsGamepadAvailable(0))
        {
            this->velocity.x = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) * 500;

            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && this->getComponent<KinematicBody>()->isGrounded())
            {
                this->velocity.y = -500;
            }

            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
            {
                debugToggle++;
            }
        }

        if (IsKeyDown(KEY_A)) 
        {
            this->velocity.x = -500;
            this->getComponent<KinematicBody>()->flipH = true;
        } 
        else if (IsKeyDown(KEY_D)) 
        {
            this->velocity.x = 500;
            this->getComponent<KinematicBody>()->flipH = false;
        }
        else
        {
            if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) == 0)
            {
                this->velocity.x = 0;
            }
        }
        
        if (IsKeyPressed(KEY_SPACE) && this->getComponent<KinematicBody>()->isGrounded())
        {
            this->velocity.y = -500;
        }

        if (IsKeyPressed(KEY_E))
        {
            this->debugToggle++;
        }
    }
    
    if (this->debugToggle % 2 == 0)
    {
        this->debugInfo = true;
    }
    else 
    {
        this->debugInfo = false;
    }

    this->velocity.y += 800 * GetFrameTime();
    if (this->velocity.y >= 500) this->velocity.y = 500;
    this->getComponent<KinematicBody>()->velocity = this->velocity;
}

void Player::render()
{
    Entity::render();
    if (this->getComponent<KinematicBody>()->velocity.x != 0) this->getComponent<KinematicBody>()->animate(&this->anim);
    else this->getComponent<KinematicBody>()->isAnimActive = false;
}

void Player::dispose()
{
    Entity::dispose();
}

bool Player::operator==(const Player& other) const
{
    return this->id == other.id;
}

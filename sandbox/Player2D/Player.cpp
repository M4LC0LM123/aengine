#include "Player.h"
#include "raylib.h"
#include "../engine/headers/engine.h"

Player::Player() 
{ 
    this->scale = {40, 40};
    this->addComponent<Bloom>();
    this->kb = this->addComponent<KinematicBody>();
    this->kb->textureScale = {40, 40};
    this->kb->color = BLANK;
    this->kb->bounce = false;
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
    this->kb->texture = LoadTexture("../assets/engine.png");
    this->kb->setFrame({16, 16}, 0);
    this->getComponent<Bloom>()->setColorFromImage(this);
    this->jumpSound = LoadSound("../assets/jump.wav");
    SetSoundVolume(this->jumpSound, 0.5f);
}

void Player::update()
{
    Entity::update();

    if (!console.isActive())
    {
        if (IsGamepadAvailable(0))
        {
            this->velocity.x = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) * 500;

            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN) && this->kb->isGrounded())
            {
                this->velocity.y = -500;
                PlaySound(this->jumpSound);
            }

            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT))
            {
                debugToggle++;
            }
        }

        if (IsKeyDown(KEY_A)) 
        {
            this->velocity.x = -500;
            // this->getComponent<KinematicBody>()->flipH = true;
            this->kb->flipH = true;
        } 
        else if (IsKeyDown(KEY_D)) 
        {
            this->velocity.x = 500;
            // this->getComponent<KinematicBody>()->flipH = false;
            this->kb->flipH = false;
        }
        else
        {
            if (GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X) == 0)
            {
                this->velocity.x = 0;
            }
        }
        
        if (IsKeyPressed(KEY_SPACE) && this->kb->isGrounded())
        {
            this->velocity.y = -500;
            PlaySound(this->jumpSound);
        }

        if (IsKeyPressed(KEY_E))
        {
            this->debugToggle++;
        }
    }
    
    std::vector<Entity*> ents = this->getBoundingEntities();
    for (Entity* e : ents)
    {
        if (e->tag == "SCRIPT")
        {
            if (CheckCollisionRecs(this->getBoundingBox(), e->getBoundingBox()))
            {
                e->getComponent<Sprite>()->color = RED;
            }
            else
            {
                e->getComponent<Sprite>()->color = GREEN;
            }
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
    this->kb->velocity = this->velocity;
}

void Player::render()
{
    Entity::render();
    if (this->kb->velocity.x != 0) this->kb->animate(&this->anim);
    else this->kb->isAnimActive = false;
}

void Player::dispose()
{
    Entity::dispose();
}

bool Player::operator==(const Player& other) const
{
    return this->id == other.id;
}

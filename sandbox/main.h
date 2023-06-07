#pragma once
#include "../engine/headers/engine.h"
#include "../include/box2d/box2d.h"
#include "Player2D/Player.cpp"

OrthographicCamera camera;
Vector2 mousePos;
Vector2 worldMousePos;

Texture2D tileTex;
TileMap tileMap;

ParticleData pd = {100, 250, PINK, 255.0f, 10, TOPDOWN, POINT};
ParticleSystem ps(pd);
int addParticles;

Player player;
Entity prefab;

Console console;

Font font;

//fiziks
b2BodyDef groundBodyDef;
b2Body* groundBody;
b2PolygonShape groundBox;

b2BodyDef bodyDef;
b2Body* body;
b2PolygonShape dynamicBox;
b2FixtureDef fixtureDef;

Entity b2Entity;
Entity kinematic;

Entity script;

ObjectPool<StaticBody> staticPool;

void tileCheck(TileMap* tileMap)
{
    if (getTile(tileMap) == -1)
    {
        player.getComponent<KinematicBody>()->pos = {tileMap->y * tileMap->tileScale.x, tileMap->x * tileMap->tileScale.y};
        script.pos = {tileMap->y * tileMap->tileScale.x, tileMap->x * tileMap->tileScale.y};
    }
    else if (getTile(tileMap) == -2)
    {
        pd.x = tileMap->y * tileMap->tileScale.x;
        pd.y = tileMap->x * tileMap->tileScale.y;
        ps.setParticleData(pd);
    }
    else if (getTile(tileMap) == -3)
    {
        Entity* entity = new Entity;
        entity->pos = {tileMap->y * tileMap->tileScale.x, tileMap->x * tileMap->tileScale.y};
        entity->scale = tileMap->tileScale;
        entity->tag = "MUSIC";
        entity->addComponent<AmbientAudio>();
        entity->getComponent<AmbientAudio>()->set(LoadSound("../assets/underground.mp3"));
        entity->getComponent<AmbientAudio>()->play();
    }
    else if (getTile(tileMap) > 0)
    {
        Entity* entity = new Entity;
        entity->pos = {tileMap->y * tileMap->tileScale.x, tileMap->x * tileMap->tileScale.y};
        entity->scale = tileMap->tileScale;
        entity->addComponent<Bloom>();
        StaticBody* bodyComponent = staticPool.get();
        bodyComponent->texture = tileMap->texture;
        bodyComponent->color = GRAY;
        bodyComponent->setFrame({tileMap->frameScale.x, tileMap->frameScale.y}, tileMap->map[tileMap->x][tileMap->y] - 1);
        entity->addComponent(bodyComponent);
        entity->getComponent<Bloom>()->setColorFromImage(entity);
    }
}

void start() 
{  
    SetExitKey(KEY_NULL);
    SetWindowIcon(LoadImage("../assets/icon.png"));
    player.init();
    tileTex = LoadTexture("../assets/tile.png");

    script.scale = {40, 40};
    script.tag = "SCRIPT";
    script.addComponent<ScriptComponent>("../assets/scripts/test.lua");
    script.addComponent<Sprite>();
    script.getComponent<Sprite>()->color = GREEN;

    tileMap.texture = tileTex;
    tileMap.frameScale = {16, 16};
    tileMap.tileScale = {50, 50};
    tileMap.color = GRAY;
    initMap("../assets/maps/grid05.jbch", &tileMap);

    LoadPrefab(&prefab, "../assets/prefabs/test.jbch");

    addParticles = 1;

    camera.init(player.pos);

    font = LoadFontEx("../assets/fonts/CascadiaMono.ttf", 18, 0, 250);

    //fiziks
    groundBodyDef.position.Set(0.0f, 1500.0f);
    groundBody = EntityManager::world.CreateBody(&groundBodyDef);
    groundBox.SetAsBox(100.0f, 25.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    bodyDef.type = (b2BodyType) Dynamic;
    bodyDef.position.Set(0.0f, 1250.0f);
    body = EntityManager::world.CreateBody(&bodyDef);
    dynamicBox.SetAsBox(20.0f, 20.0f);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 3.25f;
    body->CreateFixture(&fixtureDef);

    b2Entity.scale = {40.0f, 40.0f};
    b2Entity.addComponent<Bloom>();
    b2Entity.addComponent<PhysicsBody>();
    b2Entity.getComponent<PhysicsBody>()->type = (b2BodyType) Static;
    b2Entity.getComponent<PhysicsBody>()->pos = {50.0f, 1600.0f};
    b2Entity.getComponent<PhysicsBody>()->color = MAROON;
    b2Entity.getComponent<PhysicsBody>()->texture = LoadTexture("../assets/fiziks.png");
    b2Entity.getComponent<PhysicsBody>()->setTexturePos(50, 1650);
    b2Entity.getComponent<PhysicsBody>()->setFrame({32, 32}, 0);
    b2Entity.getComponent<PhysicsBody>()->init();
    b2Entity.getComponent<Bloom>()->setColorFromImage(&b2Entity);

    kinematic.scale = {25.0f, 25.0f};
    kinematic.addComponent<Bloom>();
    kinematic.addComponent<PhysicsBody>();
    kinematic.getComponent<PhysicsBody>()->type = (b2BodyType) Kinematic;
    kinematic.getComponent<PhysicsBody>()->pos = {0, 1450.0f};
    kinematic.getComponent<PhysicsBody>()->color = MAROON;
    kinematic.getComponent<PhysicsBody>()->init();
    kinematic.getComponent<Bloom>()->setColorFromShape(&kinematic);

    Debug::printCurrentDir();
}

void update()
{
    player.console = console;
    console.update();
    mousePos = GetMousePosition();
    worldMousePos = GetScreenToWorld2D(mousePos, camera.matrix);
    camera.update();
    camera.setSize((float)GetScreenWidth(), (float)GetScreenHeight());
    EntityManager::update();
    EntityManager::setCamera(&camera.matrix);
    if (addParticles % 2 == 0) ps.addParticle();

    if (!console.isActive())
    {
        if (IsKeyPressed(KEY_P)) addParticles++;

        if (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            Entity* rigidBody = new Entity;
            rigidBody->pos = {worldMousePos.x, worldMousePos.y};
            rigidBody->scale = {50, 50};
            rigidBody->addComponent<Bloom>();
            rigidBody->addComponent<RigidBody>();
            rigidBody->getComponent<RigidBody>()->color = ORANGE;
            rigidBody->getComponent<RigidBody>()->mass = GetRandomValue(2, 4);
            rigidBody->getComponent<RigidBody>()->gravity = 800;
            rigidBody->getComponent<Bloom>()->setColorFromShape(rigidBody);
        }

        if (!IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        {
            setTileAt(&tileMap, 2, (int)worldMousePos.x/tileMap.tileScale.x, (int)worldMousePos.y/tileMap.tileScale.y);
            Entity* entity = new Entity;
            entity->pos = {worldMousePos.x, worldMousePos.y};
            entity->scale = tileMap.tileScale;
            entity->addComponent<Bloom>();
            entity->addComponent<StaticBody>();
            entity->getComponent<StaticBody>()->texture = tileTex;
            entity->getComponent<StaticBody>()->color = GRAY;
            entity->getComponent<StaticBody>()->setFrame({tileMap.frameScale.x, tileMap.frameScale.y}, GetRandomValue(0, 1));
            entity->getComponent<Bloom>()->setColorFromImage(entity);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            for (Entity* entity : EntityManager::entities)
            {
                if (entity->hasComponent<Object>())
                {
                    if (CheckCollisionPointRec(worldMousePos, entity->getComponent<Object>()->rec))
                    {
                        EntityManager::kill(entity);
                    }
                }
            }
        }

        if (IsKeyPressed(KEY_R))
        {
            for (Entity* entity : EntityManager::entities)
            {
                if (entity->hasComponent<StaticBody>())
                {
                    EntityManager::kill(entity);
                }
            }
        }
    }

    for (Entity* entity : EntityManager::entities)
    {
        if (entity->tag == "MUSIC" && entity->hasComponent<AmbientAudio>())
        {
            entity->getComponent<AmbientAudio>()->target = player.pos;
        }
    }
    

    if (player.pos.y >= 1600)
    {
        player.getComponent<KinematicBody>()->pos = getTilePos(&tileMap, -1);
    }
	
    camera.lerp(center(player.pos, player.scale), 0.02f);
    //camera.smooth(center(player.pos, player.scale), 0.02f);
    //camera.boundsPush(center(player.pos, player.scale));
    //camera.limitToMap(&tileMap);
    ps.removeParticles();

    //fiziks

    if (IsKeyDown(KEY_LEFT)) body->ApplyLinearImpulse(b2Vec2(-10000.0f, 0.0f), body->GetWorldCenter(), true);
    if (IsKeyDown(KEY_RIGHT)) body->ApplyLinearImpulse(b2Vec2(10000.0f, 0.0f), body->GetWorldCenter(), true);
    if (IsKeyPressed(KEY_UP)) body->ApplyLinearImpulse(b2Vec2(0.0f, -5000000.0f), body->GetWorldCenter(), true);
    
    Vector2 kVel = B2Vec2ToVector2(kinematic.getComponent<PhysicsBody>()->body->GetLinearVelocity());
    if (IsKeyDown(KEY_J)) kVel.x = -100;
    if (IsKeyDown(KEY_L)) kVel.x = 100;
    if (IsKeyDown(KEY_K)) kVel.y = 100;
    if (IsKeyDown(KEY_I)) kVel.y = -100;
    if (!IsKeyDown(KEY_J) && !IsKeyDown(KEY_L) && !IsKeyDown(KEY_K) && !IsKeyDown(KEY_K) && !IsKeyDown(KEY_I)) kVel = {0, 0};
    kinematic.getComponent<PhysicsBody>()->body->SetLinearVelocity(Vector2ToB2Vec2(kVel));
}

void render()
{
    ClearBackground(BLACK);
    BeginMode2D(camera.matrix);

    EntityManager::render();
    if (player.debugInfo)
        EntityManager::renderColliders(true);

    DrawRectanglePro({body->GetPosition().x, body->GetPosition().y, 40, 40}, {20, 20}, body->GetAngle()*RAD2DEG, GREEN);
    DrawRectanglePro({groundBody->GetPosition().x, groundBody->GetPosition().y, 200, 50}, {100, 25}, groundBody->GetAngle()*RAD2DEG, GREEN);

    EndMode2D();

    DrawTextEx(font, TextFormat("Pos: %.2f, %.2f", player.pos.x, player.pos.y), {10, 10}, font.baseSize, 2, WHITE);
    DrawTextEx(font, TextFormat("Scale: %.2f, %.2f", player.scale.x, player.scale.y), {10, 30}, font.baseSize, 2, WHITE);
    DrawTextEx(font, TextFormat("Velocity: %.2f, %.2f", player.getComponent<KinematicBody>()->velocity.x, player.getComponent<KinematicBody>()->velocity.y), {10, 50}, font.baseSize, 2, WHITE);
    DrawTextEx(font, TextFormat("isGrounded: %i", player.getComponent<KinematicBody>()->isGrounded()), {10, 70}, font.baseSize, 2, WHITE);
    DrawTextEx(font, TextFormat("Entities: %i", EntityManager::entities.size()), {10, 90}, font.baseSize, 2, WHITE);
    DrawTextEx(font, TextFormat("Mouse pos and tile under: %.2f, %.2f, %i", worldMousePos.x, worldMousePos.y, getTileAt(&tileMap, worldMousePos.x/tileMap.tileScale.x, worldMousePos.y/tileMap.tileScale.y)), {10, 110}, font.baseSize, 2, WHITE);
    DrawTextEx(font, TextFormat("Camera pos: %.2f, %.2f", EntityManager::camera.target.x, EntityManager::camera.target.y), {10, 130}, font.baseSize, 2, WHITE);
    DrawTextEx(font, TextFormat("Box2DBodies: %.i", EntityManager::world.GetBodyCount()), {10, 150}, font.baseSize, 2, WHITE);
    for (Entity* entity : EntityManager::entities)
    {
        if (entity->hasComponent<Object>())
        {
            if (CheckCollisionPointRec(worldMousePos, entity->getComponent<Object>()->rec))
            {
                DrawTextEx(font, TextFormat("Entity tag: %s", entity->tag.c_str()), {10, 170}, font.baseSize, 2, WHITE);
            }
        }
    }

    DrawFPS(GetScreenWidth() - 100.0f, 10);
    console.render();
}

void dispose()
{
    EntityManager::dispose();
}
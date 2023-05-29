#pragma once
#include "Component.h"
#include "iostream"

class ScriptComponent : public Component
{
    public:
        sol::load_result script;

        ScriptComponent(const std::string& scriptPath);
        virtual ~ScriptComponent();
        virtual void update(Entity* entity) override;
        virtual void render() override;
        virtual void dispose() override;

    private:
        std::string scriptPath;
};

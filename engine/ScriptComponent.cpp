#include "headers/ScriptComponent.h"
#include "headers/Entity.h"
#include "iostream"
#include "raylib.h"

sol::state lua;

ScriptComponent::ScriptComponent(const std::string& scriptPath)
    : scriptPath(scriptPath)
{
    // Initialize your scripting environment and load the script from the given path.

    lua.open_libraries(sol::lib::base, sol::lib::math);

    sol::usertype<Vector2> v2 = lua.new_usertype<Vector2>("Vector2");
    v2["x"] = &Vector2::x;
    v2["y"] = &Vector2::y;

    sol::usertype<Color> clr = lua.new_usertype<Color>("Color");
    clr["r"] = &Color::r;
    clr["g"] = &Color::g;
    clr["b"] = &Color::b;
    clr["a"] = &Color::a;
    
    sol::usertype<Vector3> v3 = lua.new_usertype<Vector3>("Vector3");
    v3["x"] = &Vector3::x;
    v3["y"] = &Vector3::y;
    v3["z"] = &Vector3::z;

    // sol::usertype<Vector4> v4 = lua.new_usertype<Vector4>("Vector4");
    // v4["x"] = &Vector4::x;
    // v4["y"] = &Vector4::y;
    // v4["z"] = &Vector4::z;
    // v4["w"] = &Vector4::w;

    // sol::usertype<Color> clr = lua.new_usertype<Color>("Color");
    // clr["r"] = &Color::r;
    // clr["g"] = &Color::g;
    // clr["b"] = &Color::b;
    // clr["a"] = &Color::a;

    // sol::usertype<Image> img = lua.new_usertype<Image>("Image");
    // img["width"] = &Image::width;
    // img["height"] = &Image::height;
    // img["data"] = &Image::data;
    // img["format"] = &Image::format;
    // img["mipmaps"] = &Image::mipmaps;

    // sol::usertype<Texture> tex = lua.new_usertype<Texture>("Texture");
    // tex["width"] = &Texture::width;
    // tex["height"] = &Texture::height;
    // tex["id"] = &Texture::id;
    // tex["format"] = &Texture::format;
    // tex["mipmaps"] = &Texture::mipmaps;

    // sol::usertype<Camera2D> camera2D = lua.new_usertype<Camera2D>("Camera2D");
    // camera2D["offset"] = &Camera2D::offset;
    // camera2D["rotation"] = &Camera2D::rotation;
    // camera2D["target"] = &Camera2D::target;
    // camera2D["zoom"] = &Camera2D::zoom;

    // sol::usertype<Sound> sound = lua.new_usertype<Sound>("Sound");
    // sound["stream"] = &Sound::stream;
    // sound["frameCount"] = &Sound::frameCount;


    lua.set_function("GetFrameTime", GetFrameTime);

    // Load and execute the script file
    this->script = lua.load_file(scriptPath);
    if (!this->script.valid())
    {
        sol::error err = this->script;
        throw std::runtime_error("Failed to load script: " + std::string(err.what()));
    }

    // // et up any necessary bindings between C++ and the script environment
    // // bind the entity object:
    // sol::usertype<Entity> entity_type = lua.new_usertype<Entity>("Entity",
    //     "addComponent", &Entity::addComponent<Component>,
    //     "getComponent", &Entity::getComponent<Component>,
    //     "hasComponent", &Entity::hasComponent<Component>,
    //     // Add any other bindings you need
    // );

    sol::usertype<Entity> entity_type = lua.new_usertype<Entity>("Entity");
    entity_type["tag"] = &Entity::tag;
    entity_type["pos"] = &Entity::pos;
    entity_type["scale"] = &Entity::scale;
    entity_type["rotation"] = &Entity::rotation;

    // You can expose additional functions, data, or bindings as necessary

    // Run the script's main function if it exists
    sol::protected_function mainFunc = this->script;
    if (mainFunc.valid())
    {
        sol::protected_function_result result = mainFunc();
        if (!result.valid())
        {
            sol::error err = result;
            throw std::runtime_error("Failed to execute script: " + std::string(err.what()));
        }
    }

    this->script();
}

void ScriptComponent::update(Entity* entity)
{
    // Implement the update logic in your scripting component
    // For example, using Sol2 and Lua:
    
    // Call the update function in the script environment
    sol::protected_function updateFunc = lua["update"];
    if (updateFunc.valid())
    {
        sol::protected_function_result result = updateFunc(entity);
        if (!result.valid())
        {
            sol::error err = result;
            throw std::runtime_error("Failed to execute script update function: " + std::string(err.what()));
        }
    }
}

void ScriptComponent::render()
{
    // Implement the render logic in your scripting component
    // For example, using Sol2 and Lua:
    // Call the render function in the script environment
    sol::protected_function renderFunc = lua["render"];
    if (renderFunc.valid())
    {
        sol::protected_function_result result = renderFunc();
        if (!result.valid())
        {
            sol::error err = result;
            throw std::runtime_error("Failed to execute script render function: " + std::string(err.what()));
        }
    }
}

void ScriptComponent::dispose()
{
    // Implement the dispose logic in your scripting component
    // For example, using Sol2 and Lua:
    // Call the dispose function in the script environment
    sol::protected_function disposeFunc = lua["dispose"];
    if (disposeFunc.valid())
    {
        sol::protected_function_result result = disposeFunc();
        if (!result.valid())
        {
            sol::error err = result;
            throw std::runtime_error("Failed to execute script dispose function: " + std::string(err.what()));
        }
    }
}
#pragma once
#include "algorithm"
#include "iostream"    
#include "stdio.h"
#include "dirent.h"
#include "vector"
#include "stdlib.h"

class Entity;
float length(Vector2 vector);

float clamp(float value, float min, float max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}

Vector3 addV3(Vector3 v1, Vector3 v2)
{
    return (Vector3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vector3 subV3(Vector3 v1, Vector3 v2)
{
    return (Vector3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vector3 normalizeV3(Vector3 v) {
    float length = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    if (length != 0.0f) {
        v.x /= length;
        v.y /= length;
        v.z /= length;
    }
    return v;
}

Vector3 addMV3(Vector3 vector, float scalar)
{
    Vector3 result;
    result.x = vector.x * scalar;
    result.y = vector.y * scalar;
    result.z = vector.z * scalar;
    return result;
}

Vector3 scaleV3(Vector3 v, float scale) {
    v.x *= scale;
    v.y *= scale;
    v.z *= scale;
    return v;
}

Vector3 CrossProductV3(Vector3 v1, Vector3 v2) {
    Vector3 result;
    result.x = v1.y * v2.z - v1.z * v2.y;
    result.y = v1.z * v2.x - v1.x * v2.z;
    result.z = v1.x * v2.y - v1.y * v2.x;
    return result;
}

void RotateY(Vector3* v, float angle)
{
    float sinAngle = sinf(angle);
    float cosAngle = cosf(angle);

    float x = v->x * cosAngle + v->z * sinAngle;
    float z = v->z * cosAngle - v->x * sinAngle;

    v->x = x;
    v->z = z;
}

void RotateZ(Vector3 *v, float angle)
{
    float sinAngle = sinf(angle);
    float cosAngle = cosf(angle);
    float x = v->x * cosAngle - v->y * sinAngle;
    float y = v->x * sinAngle + v->y * cosAngle;
    v->x = x;
    v->y = y;
}

Vector2 add(Vector2 v1, Vector2 v2)
{
    return (Vector2){v1.x + v2.x, v1.y + v2.y};
}

Vector2 sub(Vector2 v1, Vector2 v2)
{
    return (Vector2){v1.x - v2.x, v1.y - v2.y};
}

Vector2 addM(Vector2 v1, Vector2 v2, float multiplier)
{
    if (multiplier == 0)
    {
        return (Vector2){v1.x + v2.x * 1, v1.y + v2.y * 1};
    }
    else
    {
        return (Vector2){v1.x + v2.x * multiplier, v1.y + v2.y * multiplier};
    }
}

Vector2 multiply(Vector2 v1, float b)
{
    return (Vector2){v1.x * b, v1.y * b};
}

Vector2 multiplyV2(Vector2 v1, Vector2 v2)
{
    return (Vector2){v1.x * v2.x, v1.y * v2.y};
}

Vector2 lerp(Vector2 start, Vector2 end, float alpha)
{
    Vector2 result;
    result.x = -(start.x + (end.x - start.x) * alpha);
    result.y = -(start.y + (end.y - start.y) * alpha);
    return result;
}

Vector2 scale(Vector2 vector, float scale)
{
    Vector2 scaled = { vector.x * scale, vector.y * scale };
    return scaled;
}

Vector2 center(Vector2 pos, Vector2 scale)
{
    return (Vector2) {pos.x + scale.x/2, pos.y + scale.y/2};
}

float getDistance(Vector2 v1, Vector2 v2)
{
    float xDist = v2.x - v1.x;
    float yDist = v2.y - v1.y;
    return length((Vector2){xDist, yDist});
}

float length(Vector2 vector)
{
    return (float) sqrt(vector.x * vector.x + vector.y * vector.y);
}

bool isInVector(std::vector<Entity*> v, Entity* entity)
{
    if(std::find(v.begin(), v.end(), entity) != v.end()) 
    {
        return true;
    } else 
    {
        return false;
    }
}

bool ContainsInteger(const char *str)
{
    while (*str)
    {
        if (isdigit(*str))
        {
            return true;
        }
        str++;
    }
    return false;
}

b2Vec2 Vector2ToB2Vec2(Vector2 v)
{
    return b2Vec2(v.x, v.y);
}

Vector2 B2Vec2ToVector2(b2Vec2 v)
{
    return (Vector2){v.x, v.y};
}

template <typename T>
void moveElementToBack(std::vector<T>& v)
{
   std::swap(v[v.end()-1], v.back());
}

void bubbleSort(std::vector<int>& arr)
{
   int n = arr.size();
   for (int i = 0; i < n - 1; i++)
   {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
   }
}

template <typename T>
int getArrSize(T arr[])
{
    return sizeof(arr) / sizeof(int);
}

int randBit()
{
    int bit = GetRandomValue(0, 1);
    if (bit == 0)
        return -1;
    else 
        return 1;
}

Vector2 randBitVector2()
{
    int bit = GetRandomValue(0, 1);
    int bit2 = GetRandomValue(0, 1);
    if (bit == 0)
        bit = -1;
    else 
        bit = 1;
    if (bit2 == 0)
        bit2 = -1;
    else 
        bit2 = 1;
    return Vector2{(float)bit, (float)bit2};
}

#ifdef _WIN32
    std::string getCurrentDir()
    {
        char* cwd = _getcwd( 0, 0 ); // **** microsoft specific ****
        std::string working_directory(cwd);
        std::free(cwd);
        return working_directory;
    }
#elif __linux__
    #include <filesystem>
    #include <unistd.h>

    std::string getCurrentDir()
    {
        return std::filesystem::current_path();
    }
#elif __APPLE__
    #include <filesystem>
    #include <unistd.h>

    std::string getCurrentDir()
    {
        return std::__fs::filesystem::current_path();
    }
#endif
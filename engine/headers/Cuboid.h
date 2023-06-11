#ifndef CUBE_H
#define CUBE_H
#pragma once

struct Cuboid
{
    float x;
    float y;
    float z;
    float width;
    float height;
    float length;
};

bool CheckCollisionCuboids(Cuboid cube1, Cuboid cube2)
{
    float cube1MinX = cube1.x - cube1.width / 2;
    float cube1MaxX = cube1.x + cube1.width / 2;
    float cube1MinY = cube1.y - cube1.height / 2;
    float cube1MaxY = cube1.y + cube1.height / 2;
    float cube1MinZ = cube1.z - cube1.length / 2;
    float cube1MaxZ = cube1.z + cube1.length / 2;

    float cube2MinX = cube2.x - cube2.width / 2;
    float cube2MaxX = cube2.x + cube2.width / 2;
    float cube2MinY = cube2.y - cube2.height / 2;
    float cube2MaxY = cube2.y + cube2.height / 2;
    float cube2MinZ = cube2.z - cube2.length / 2;
    float cube2MaxZ = cube2.z + cube2.length / 2;

    if (cube1MinX <= cube2MaxX && cube1MaxX >= cube2MinX &&
        cube1MinY <= cube2MaxY && cube1MaxY >= cube2MinY &&
        cube1MinZ <= cube2MaxZ && cube1MaxZ >= cube2MinZ) {
        return true; 
    }

    return false;  
}

#endif
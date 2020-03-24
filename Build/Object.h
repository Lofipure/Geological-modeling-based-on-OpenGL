#ifndef OBJECT_H
#define OBJECT_H

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vector>
#include <cstdio>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object
{
/*
    相当于一个地层类
*/
public:
    // vn == vertices number
    // in == indices number
    int vn, in;

    float *vertices;                //存放顶点数据的数组
    unsigned int *indices;          //存放定点顺序的数组(EBO)

    unsigned int VAO, VBO, EBO;
    Object();

    void drawObject();
};

#endif // !OBJECT_H

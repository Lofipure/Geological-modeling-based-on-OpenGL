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

    顶点数组对象：Vertex Array Object，VAO
    顶点缓冲对象：Vertex Buffer Object，VBO
    索引缓冲对象：Element Buffer Object，EBO 或Index Buffer Object，IBO
*/
public:
    // vn == vertices number
    // in == indices number
    int vn, in;

    float *vertices;                //存放顶点数据的数组
    unsigned int *indices;          //存放定点顺序的数组(EBO)

    unsigned int VAO, VBO, EBO;
    std::vector<float> vTemp;
    std::vector<unsigned int> iTemp;

    void getInIndices(int n,int index);
    void getInVertices();

    void finalHandle();

    void drawObject();
    Object();
};

#endif // !OBJECT_H

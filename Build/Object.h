#ifndef OBJECT_H
#define OBJECT_H

#define GLEW_STATIC
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <vector>
#include <cstdio>
#include <iostream>

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

class Object {
public:
    //std::vector<float> verticesT;
    //std::vector<unsigned int> indicesT;
    int vn, in;

    float* vertices;
    unsigned int* indices;

    unsigned int VAO, VBO, EBO;
    Object();

    void drawObject();

};

#endif // !OBJECT_H

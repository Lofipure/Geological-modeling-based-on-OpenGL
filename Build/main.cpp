#include <iostream>
#include <cstdio>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "Object.h"

#include "TIN.h"

glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 1600.0f / 2.0;
float lastY = 900.0f / 2.0;
float fov = 45.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

/*
	@Function name: mouse_callback
	@Function param: 窗口对象，当前鼠标所在位置的二维坐标
	@Function return value: 根据鼠标的移动计算俯仰角和偏航角
*/
void mouse_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}
	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

/*
	@Function name: scroll_callback
	@Function param: 窗口对象，yoffset值代表竖直滚动的大小
	@Function return value: 根据滚轮的滚动所放大或缩小
*/
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}

/*
	@Function Name: pressInput
	@Function param: 当前窗口对象
	@Function return value: 对按键做出响应
*/
void pressInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	float cameraSpeed = 2.5 * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		cameraPos += cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		cameraPos -= cameraSpeed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	}
}

/*
	@Function Name: main
	@Function param: void
	@Function return value: 程序入口
*/
int main(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow *window = glfwCreateWindow(1600, 900, "Demo", nullptr, nullptr);
	if (window == NULL)
	{
		std::cout << "window init error" << std::endl;
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(window);

	glfwSetCursorPosCallback(window, mouse_callback);		//为鼠标注册回调事件
	glfwSetScrollCallback(window, scroll_callback);			//为滚轮注册回调事件

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "glew init error" << std::endl;
		glfwTerminate();

		return -1;
	}
	glViewport(0, 0, 1600, 900);

	Object Tir;

	// 建立地层TIN模型
	TIN tinModel;
	int m, n;
	std::cout << "the number of the point: ";
	std::cin >> n;
	std::cout << "the number of the tower: ";
	std::cin >> m;

	for (int index = 0; index < m; ++index) {
		tinModel.createPoint(n,index);
		tinModel.createTin();
		tinModel.writeFile();

		Tir.getInVertices();
		Tir.getInIndices(n,index);

		remove("input.txt");
		remove("Tin.txt");

		tinModel.emptyData();	
	}

	Tir.finalHandle();
	std::cout << "TIN Model Rendering Over" << std::endl;

	// 准备着色器
	Shader shaderProgram("shader.vs", "shader.fs");

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//开启奇妙的只画线模式
	glEnable(GL_DEPTH);							//当出现多个图层时开启深度监视

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		pressInput(window);

		glClearColor(0.3f, 0.6f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();

		/*
			2D到3D的空间变换需要三个核心矩阵：Model( 模型 )、View( 观察 )、Projection( 投影 )
		*/
		glm::mat4 projection = glm::perspective(glm::radians(fov), (float)1600 / (float)900, 0.1f, 100.0f);
		shaderProgram.setMat4("projection", projection);

		glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		shaderProgram.setMat4("view", view);

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.3f, 0.5f));
		shaderProgram.setMat4("model", model);

		// 绘制图形
		Tir.drawObject();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
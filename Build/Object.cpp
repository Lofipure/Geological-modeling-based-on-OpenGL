#include "Object.h"

/*
	@Function name: Object类的构造函数
	@Function param: void
	@Function return value: ...... ?
*/
Object::Object() {
	this->vertices = NULL;
	this->indices = NULL;

	std::vector<float> vTemp;
	std::vector<unsigned int> iTemp;

	FILE* fVer = fopen("input.txt", "r");
	FILE* fInd = fopen("Tin.txt", "r");

	if (fVer == NULL || fInd == NULL) {
		std::cout << "file open error" << std::endl;
		system("pause");
	}

	// 读取顶点数据到vector
	float a, b, c;
	while (fscanf(fVer, "%f\t%f\t%f\n", &a, &b, &c) > 0) {
		vTemp.push_back(a);
		vTemp.push_back(b);
		vTemp.push_back(c);
	}

	// 读取EBO到vector
	int x, y, z;
	while (fscanf(fInd, "%d\t%d\t%d\n", &x, &y , &z) > 0) {
		iTemp.push_back((unsigned int)x);
		iTemp.push_back((unsigned int)y);
		iTemp.push_back((unsigned int)z);
	}

	vn = vTemp.size(), in = iTemp.size();

	this->vertices = new float[vn];
	this->indices = new unsigned int[in];

	// 把从文件中读取出来的vertices和indices分别存放到vertice和indices数组中
	int i = 0, j = 0;
	for (std::vector<float>::iterator it = vTemp.begin(); it != vTemp.end(); ++it) {
		*(vertices + i++) = *it;
	}

	for (std::vector<unsigned int>::iterator it = iTemp.begin(); it != iTemp.end(); ++it) {
		*(indices + j++) = *it;
	}

	fclose(fVer);
	fclose(fInd);

	//OpenGL 绑定四连，就这么豪横
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER,in*sizeof(float),indices,GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vn*sizeof(unsigned int), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void Object::drawObject() {
	//glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, in, GL_UNSIGNED_INT, 0);
}

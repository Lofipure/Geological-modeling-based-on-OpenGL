#include "Object.h"

/*
	@Function name: Object类的构造函数
	@Function param: void
	@Function return value: ...... ?
*/
Object::Object() {
}

void Object::drawObject() {
	//glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDrawElements(GL_TRIANGLES, in, GL_UNSIGNED_INT, 0);
}

void Object::getInIndices(int n,int index) {
	FILE* fInd = fopen("Tin.txt", "r");

	if (fInd == NULL) {
		std::cout << "File Open Error" << std::endl;
		system("pause");
	}

	int x, y, z;
	while (fscanf(fInd, "%d\t%d\t%d\n", &x, &y, &z) > 0) {
		iTemp.push_back((unsigned int)x+index*n);
		iTemp.push_back((unsigned int)y+index*n);
		iTemp.push_back((unsigned int)z+index*n);
	}
	fclose(fInd);
}

void Object::getInVertices() {
	FILE* fVer = fopen("input.txt", "r");

	if (fVer == NULL) {
		std::cout << "File Open Error" << std::endl;
		system("pause");
	}

	float a, b, c;
	while (fscanf(fVer, "%f\t%f\t%f\n", &a, &b, &c) > 0) {
		vTemp.push_back(a);
		vTemp.push_back(b);
		vTemp.push_back(c);
	}
	fclose(fVer);
	return;
}

void Object::finalHandle() {
	this->vertices = NULL;
	this->indices = NULL;

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

	//OpenGL 绑定四连，就这么豪横
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, in * sizeof(float), indices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vn * sizeof(unsigned int), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);		// 链接顶点属性
	glEnableVertexAttribArray(0);

}

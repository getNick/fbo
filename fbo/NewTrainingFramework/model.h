#pragma once
#include "Vertex.h"
#include <vector>

class model
{
public:
	model(void);
	~model(void);
	void loadModel(const char * fileName);
	void loadTexture(const char * fileName, GLuint *textureHandle);
	Vector3 getModelPivot(long vertices, Vertex* verticesData);
	Vertex *vertices;
	unsigned int *indices;
	GLuint m_hIndexBuffer;
	GLuint m_hVertexBuffer;
	int nrVertices;
	int nrIndices;
	Vector3 pivot;
	Matrix modelMatrix;
};


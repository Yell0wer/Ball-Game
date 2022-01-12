#include "VertexArray.h"

VertexArray::VertexArray(const float* verts, uint numVerts, const uint* indices, uint numIndices) : 
	mNumVerts(numVerts),
	mNumIndices(numIndices)
{
	// create vertex array
	glGenVertexArrays(1, &mVAID);
	glBindVertexArray(mVAID);
	// create vertex buffer
	glGenBuffers(1, &mVBID);
	glBindBuffer(GL_ARRAY_BUFFER, mVBID);
	glBufferData(GL_ARRAY_BUFFER, numVerts * 5 * sizeof(float), verts, GL_STATIC_DRAW);
	// create index buffer
	glGenBuffers(1, &mIBID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(uint), indices, GL_STATIC_DRAW);
	// vertex attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, reinterpret_cast<void*>(sizeof(float) * 3));
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVBID);
	glDeleteBuffers(1, &mIBID);
	glDeleteVertexArrays(1, &mVAID);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVAID);
}
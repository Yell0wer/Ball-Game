#pragma once
#include "stdafx.h"

class VertexArray
{
public:
	VertexArray(const float* verts, uint numVerts, const uint* indices, uint numIndices);
	~VertexArray();
	// activate vertex array to draw
	void SetActive();
	// getter functions
	uint GetNumVerts() const { return mNumVerts; }
	uint GetNumIndices() const { return mNumIndices; }
private:
	// number of verts and indices
	uint mNumVerts;
	uint mNumIndices;
	// opengl id of vertex and index buffers and vertex array
	GLuint mVBID;
	GLuint mIBID;
	GLuint mVAID;
};


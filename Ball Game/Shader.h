#pragma once
#include "stdafx.h"

class Shader
{
public:
	Shader();
	~Shader();
	// load/unload shaders
	bool Load(const std::string& vertName, const std::string& fragName);
	void Unload();
	// set as active shader program
	void SetActive();

	void SetMatrixUniform(const char* name, const Matrix4& matrix);
private:
	// compile specified shader
	bool CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader);
	// check whether shader compiled
	bool IsCompiled(GLuint shader);
	// tests linking
	bool IsValid();
	// ids
	GLuint mVID;
	GLuint mFID;
	GLuint mSID;
};


#include "stdafx.h"

Shader::Shader() {}

Shader::~Shader() {}

bool Shader::Load(const std::string& vertName, const std::string& fragName)
{
	// compile shaders
	if (!CompileShader(vertName, GL_VERTEX_SHADER, mVID) || !CompileShader(fragName, GL_FRAGMENT_SHADER, mFID)) return 0;
	mSID = glCreateProgram();
	glAttachShader(mSID, mVID);
	glAttachShader(mSID, mFID);
	glLinkProgram(mSID);
	if (!IsValid()) return 0;
	return 1;
}

void Shader::Unload()
{
	glDeleteProgram(mSID);
	glDeleteShader(mVID);
	glDeleteShader(mFID);
}

void Shader::SetActive()
{
	glUseProgram(mSID);
}

bool Shader::CompileShader(const std::string& fileName, GLenum shaderType, GLuint& outShader)
{
	// open file
	std::ifstream shaderFile(fileName);
	if (shaderFile.is_open())
	{
		// read text into string
		std::stringstream sstream;
		sstream << shaderFile.rdbuf();
		std::string contents = sstream.str();
		const char* contentsChar = contents.c_str();
		// create shader of specified type
		outShader = glCreateShader(shaderType);
		// set source chars and compile
		glShaderSource(outShader, 1, &(contentsChar), nullptr);
		glCompileShader(outShader);
		if (!IsCompiled(outShader))
		{
			SDL_Log("Failed to compile shader %s\n", fileName.c_str());
			return 0;
		}
	}
	else
	{
		SDL_Log("Shader file not found: %s\n", fileName.c_str());
		return 0;
	}
	return 1;
}

bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	// query compile status
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:%s\n", buffer);
		return 0;
	}
	return 1;
}

bool Shader::IsValid()
{
	GLint status;
	// query program status
	glGetProgramiv(mSID, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, sizeof(buffer));
		glGetShaderInfoLog(mSID, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:%s\n", buffer);
		return 0;
	}
	return 1;
}

void Shader::SetMatrixUniform(const char* name, const Matrix4& matrix)
{
	// Find uniform
	GLuint loc = glGetUniformLocation(mSID, name);
	// Copy matrix to uniform
	glUniformMatrix4fv(loc, 1, GL_TRUE, matrix.GetAsFloatPtr());
}
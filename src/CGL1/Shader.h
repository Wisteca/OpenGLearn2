#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace std;
using namespace glm;

const string MODEL_MAT4_NAME = "uniModel";
const string VIEW_MAT4_NAME = "uniView";
const string PROJECTION_MAT4_NAME = "uniProjection";

/**
 * @brief Utility shader class
 * Compile, link, retrieve errors of a shader program and provide
 * useful function to use it.
 */
class Shader
{
    private :

    GLuint m_shaderID = 0; /**< shader program ID */

    public :

    /**
     * @brief Compile, link and retrieve errors of a shader program
     */
    Shader(const string vShaderPath, const string fShaderPath);

    /**
     * @brief Tell OpenGL to use this program now
     */
    void use();

    /**
     * @brief Modify a uniform variable of the shader program
     */
    void setUniform(const string name, float value);
    void setUniform(const string name, bool value);
    void setUniform(const string name, int value);
    void setUniform(const string name, float x, float y, float z);
    void setUniform(const string name, mat4 matrix);

    private :

    GLuint compileShader(GLuint shaderType, const string source);
    GLint uniformLocation(const string name);
};

#pragma once

#include "Utils.h"
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
    void setUniform(string name, float value);
    void setUniform(string name, bool value);
    void setUniform(string name, int value);
    void setUniform(string name, vec2 v);
    void setUniform(string name, vec3 v);
    void setUniform(string name, vec4 v);
    void setUniform(string name, mat4 matrix);

    private :

    GLuint compileShader(GLuint shaderType, const string source);
    GLint uniformLocation(const string name);
};

/**
 * Implementation
 * @date 20.03.2021
 */

#include "Shader.h"

Shader::Shader(const string vShaderPath, const string fShaderPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try 
    {
        // open files
        vShaderFile.open(vShaderPath);
        fShaderFile.open(fShaderPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();		
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode   = vShaderStream.str();
        fragmentCode = fShaderStream.str();		
    }
    catch(std::ifstream::failure const&)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        return;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // 2. compile and link shaders
    GLuint vID = compileShader(GL_VERTEX_SHADER, vShaderCode);
    GLuint fID = compileShader(GL_FRAGMENT_SHADER, fShaderCode);
    if(vID == 0 || fID == 0)
        return;

    // Shader program
    // Create the shader program, attach vertex and fragment shaders to it and link. 
    // Then retrieve errors to be sure everything happened fine
    GLuint program = glCreateProgram();
    if(program == 0)
    {
        cout << "Unable to create shader program" << endl;
        return;
    }

    glAttachShader(program, vID);
    glAttachShader(program, fID);
    glLinkProgram(program); // Linking, here errors can happen

    // Retrieve error and print it if necessary
    int success;
    char message[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(program, 512, nullptr, message);
        cout << "Error while linking shaders :\n" << message << endl;
        return;
    }

    // Delete the shaders objects
    glDeleteShader(vID);
    glDeleteShader(fID);

    // Finally, if everything happens fine
    m_shaderID = program;
}

GLuint Shader::compileShader(GLuint shaderType, const string source)
{
    GLuint shader_id = glCreateShader(shaderType); // Create a shader of given type
    if(shader_id == 0)
    {
        cout << "Unable to create shader object." << endl;
        return 0;
    }

    // Set the source code of the shader
    const char* src = source.c_str();
    glShaderSource(shader_id, 1, &src, nullptr);
    // Next, compile the shader
    glCompileShader(shader_id);

    // Test if the compilation failed, and print the error message if it failed
    int success;
    char message[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader_id, 512, nullptr, message);
        cout << "Error while compiling shader :\nERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << message << endl;
        return 0;
    }

    return shader_id;
}

void Shader::use()
{
    if(m_shaderID)
        glUseProgram(m_shaderID);
}

void Shader::setUniform(const string name, float value)
{
    glUniform1f(uniformLocation(name), value); 
}

void Shader::setUniform(const string name, bool value)
{
    glUniform1i(uniformLocation(name), (int) value); 
}

void Shader::setUniform(const string name, int value)
{
    glUniform1i(uniformLocation(name), value); 
}

void Shader::setUniform(const string name, float x, float y, float z)
{
    glUniform3f(uniformLocation(name), x, y, z);
}

void Shader::setUniform(const string name, mat4 matrix)
{
    glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, value_ptr(matrix));
}

GLint Shader::uniformLocation(const string name)
{
    if(m_shaderID)
    {
        GLint loc = glGetUniformLocation(m_shaderID, name.c_str());
        if(loc == -1)
        {
            static string lastName = "";
            if(lastName != string(name))
            {
                lastName = name;
                cout << "Can't find location of " << name << " in shader program" << endl;
            }
        }
        return loc;
    }
    return 0;
}

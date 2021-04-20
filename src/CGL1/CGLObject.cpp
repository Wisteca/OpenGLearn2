/** 
 * @file CGLObject.cpp
 * @brief This source file implements the CGLObject class interface.
 *
 * The CGLObject is an abstract class that extends WObject. It's the top hierarchy graphic
 * object. It manages vertices and textures.
 * 
 * @author Bastian Cerf
 * @date 20.04.2021
 */

#include "CGLObject.h"

namespace cgl
{
    CGLObject::CGLObject(vector<float> vertices, char nbreVertexAttrib, vec3 pos) : WObject(pos)
    {
        m_vertices = vertices;
        configVertices(m_vertices, nbreVertexAttrib);
    }
    
    void CGLObject::setRotation(vec3 rot)
    {
        m_rot = rot;
    }

    vec3 CGLObject::getRotation() const
    {
        return m_rot;
    }

    void CGLObject::setScale(vec3 scale)
    {
        m_scale = scale;
    }

    vec3 CGLObject::getScale() const
    {
        return m_scale;
    }

    void CGLObject::setTexture(Texture* tex)
    {
        m_tex = tex;
    }

    Texture* CGLObject::getTexture() const
    {
        return m_tex;
    }

    void CGLObject::render(Shader& program)
    {
        // Shader program must be in use.

        // Send eventually texture to the shader
        if(m_tex)
            m_tex->bind();

        program.setUniform(MODEL_MAT4_NAME, model(mat4(1.0f))); // Send model matrix
        glBindVertexArray(m_vaoID); // Bind the vao
        glDrawArrays(GL_TRIANGLES, 0, m_vertices.size() / m_nbreVertexAttrib); // Draw
    }

    void CGLObject::configVertices(vector<float>& vertices, char nbreVertexAttrib)
    {
        // First create an array of vertices that can be passed to a vbo.
        float vArray[vertices.size()];
        for(size_t i = 0 ; i < vertices.size() ; ++i)
            vArray[i] = vertices[i];

        // Create a vbo that will be filled in with vertices
        GLuint vboID;
        glGenBuffers(1, &vboID);

        // Create the VAO
        glGenVertexArrays(1, &m_vaoID);
        glBindVertexArray(m_vaoID); // Bind the vao, from this point, all actions on the vbo will be stored.

        glBindBuffer(GL_ARRAY_BUFFER, vboID); // Bind the vbo
        glBufferData(GL_ARRAY_BUFFER, sizeof(vArray), &vArray, GL_STATIC_DRAW); // Fill the buffer

        // Tell OpenGL how to interpret vertices.
        // First three args are always coord data (x, y, z), next two args are texture coord (x, y).
        GLsizei stride = nbreVertexAttrib * sizeof(float); // Space between vertices

        // pos x, y, z is at index 0 and composed by 3 float
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*) 0);
        glEnableVertexAttribArray(0);

        // texture x, y at index 1 composed by 2 float
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*) (3 * sizeof(float)));
        glEnableVertexAttribArray(1); 

        // Call configVertexAttrib of sub class to give the possibility of configuring something else.
        configVertexAttrib();

        glBindVertexArray(0); // Unbind, vao is configured.
    }

    void CGLObject::configVertexAttrib()
    {}

    mat4 CGLObject::model(mat4 work) const
    {
        work = WObject::model(work); // Call super 
        // Apply rotation and scaling
        work = scale(work, m_scale);
        work = rotate(work, m_rot.x, vec3(1, 0, 0)); // On x axis (pitch)
        work = rotate(work, m_rot.y, vec3(0, 1, 0)); // On y axis (yaw)
        work = rotate(work, m_rot.z, vec3(0, 0, 1)); // On z axis (roll)
        
        return work;
    }
}

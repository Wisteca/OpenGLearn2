/** 
 * @file CGLObject.h
 * @brief This header file describe the CGLObject class interface.
 *
 * The CGLObject is an abstract class that extends WObject. It's the top hierarchy graphic
 * object. It manages vertices and textures.
 * 
 * @author Bastian Cerf
 * @date 19.04.2021
 */

#pragma once

#include "WObject.h"
#include "Texture.h"
#include <vector>
using namespace std;

namespace cgl
{
    class CGLObject : public WObject
    {
        private :

        GLuint m_vaoID; /**< This is the vao used to render object */
        vector<float> m_vertices; /**< Array of vertices */
        char m_nbreVertexAttrib = 5; /**< Number of vertex attributes, by default 3 coord and 2 tex coord */

        protected :

        vec3 m_rot = vec3(0, 0, 0); /**< Rotation, x is pitch, y is yaw and z is roll */
        vec3 m_scale = vec3(1, 1, 1); /**< Scale on x, y and z */

        Texture* m_tex = nullptr; /**< For now, a CGLObject can have only one texture */

        public :

        CGLObject(vector<float> vertices, char nbreVertexAttrib = 5, vec3 pos = vec3(0, 0, 0));

        virtual void setRotation(vec3 rot);

        vec3 getRotation() const;

        virtual void setScale(vec3 scale);

        vec3 getScale() const;

        virtual void setTexture(Texture* tex);

        Texture* getTexture() const;

        virtual void render(Shader& program);

        private :

        void configVertices(vector<float>& vertices, char nbreVertexAttrib);

        protected :

        virtual void configVertexAttrib();

        mat4 model(mat4 work) const override;
    };
}

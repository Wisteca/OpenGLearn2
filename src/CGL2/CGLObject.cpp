/** 
 * @file CGLObject.cpp
 * @brief This source file implements the CGLObject class interface.
 *
 * This is the superclass of all game objects that have a position in 3D space.
 * 
 * @author Bastian Cerf
 * @date 21.04.2021
 */

#include "CGLObject.h"
#include <glm/gtc/matrix_transform.hpp>

namespace cgl
{
    CGLObject::CGLObject(vec3 pos)
    {
        m_pos = pos;
    }

    vec3 CGLObject::getPosition() const
    {
        return m_pos;
    }

    void CGLObject::setPosition(vec3 pos)
    {
        m_pos = pos;
    }

    mat4 CGLObject::model(mat4 work) const
    {
        return translate(work, m_pos);
    }
}

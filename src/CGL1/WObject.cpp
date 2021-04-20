/** 
 * @file WObject.cpp
 * @brief This source file implements the WObject class interface.
 *
 * A WObject (for World Object) is an abstract class all objects that can be added
 * in a world must extends.
 * 
 * @author Bastian Cerf
 * @date 19.04.2021
 */

#include "WObject.h"
#include <glm/gtc/matrix_transform.hpp>

namespace cgl
{
    WObject::WObject(vec3 pos)
    {
        m_pos = pos;
    }

    vec3 WObject::getPosition() const
    {
        return m_pos;
    }

    void WObject::setPosition(vec3 pos)
    {
        m_pos = pos;
    }

    mat4 WObject::model(mat4 work) const
    {
        return translate(work, m_pos);
    }
}

/** 
 * @file WObject.h
 * @brief This header file describe the WObject class interface.
 *
 * A WObject (for World Object) is an abstract class all objects that can be added
 * in a world must extends.
 * 
 * @author Bastian Cerf
 * @date 19.04.2021
 */

#pragma once

#include "Utils.h"
using namespace glm; // For use with glm.

/**
 * @brief Namespace of the little engine (Cerf Graphic Library).
 */
namespace cgl
{
    /**
     * A WObject (for World Object) is an abstract class all objects that can be added
     * in a world must extends.
     * 
     * A WObject has a position in 3D space.
     */
    class WObject
    {
        protected :

        vec3 m_pos = vec3(0, 0, 0); /**< Position in the world. */

        /**
         * @brief Create an object at position (0,0,0).
         * The constructor is protected because the class can't be instantiated (abstract).
         */
        WObject() = default;

        /**
         * @brief Create an object with a specified position.
         * The constructor is protected because the class can't be instantiated (abstract).
         */
        WObject(vec3 pos);

        public :

        /**
         * @brief Default destructor.
         */
        virtual ~WObject() = default;

        /**
         * @return The position.
         */
        vec3 getPosition() const;

        /**
         * @brief Change the position.
         */
        virtual void setPosition(vec3 pos);

        protected :

        /**
         * @return The matrix passed as argument with the translation applied.
         */
        virtual mat4 model(mat4 work) const;
    };
}

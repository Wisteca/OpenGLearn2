/** 
 * @file CGLObject.h
 * @brief Basic abstract game object
 *
 * This is the superclass of all game objects that have a position in 3D space.
 * 
 * @author Bastian Cerf
 * @date 21.04.2021
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
     * This is the superclass of all game objects that have a position in 3D space.
     */
    class CGLObject
    {
        protected :

        vec3 m_pos = vec3(0, 0, 0); /**< Position in the world. */

        /**
         * @brief Create an object at position (0,0,0).
         * The constructor is protected because the class can't be instantiated (abstract).
         */
        CGLObject() = default;

        /**
         * @brief Create an object with a specified position.
         * The constructor is protected because the class can't be instantiated (abstract).
         */
        CGLObject(vec3 pos);

        public :

        /**
         * @brief Default destructor.
         */
        virtual ~CGLObject() = default;

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

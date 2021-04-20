/** 
 * @file Texture.h
 * @brief Class for loading and creating textures.
 *
 * This class gives useful methods for loading and creating textures that can be applied on
 * CGLObject for example. 
 * 
 * @author Bastian Cerf
 * @date 20.04.2021
 */

#pragma once

#include "Utils.h"

namespace cgl
{
    class Texture
    {
        private :

        GLuint m_texID; /**< OpenGL texture ID */

        public :

        /**
         * @brief Load an image at a specified location on disk.
         * @param Flip image at loading.
         */
        Texture(string path, bool flip = true);

        /**
         * @brief Bind texture for use in a shader program. 
         * @param index Index of texture unit in shader program.
         */
        void bind(int index = 0) const;
    };
}

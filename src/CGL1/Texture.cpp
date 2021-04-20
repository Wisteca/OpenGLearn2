/** 
 * @file Texture.cpp
 * @brief Class for loading and creating textures.
 *
 * This class gives useful methods for loading and creating textures that can be applied on
 * CGLObject for example. 
 * 
 * @author Bastian Cerf
 * @date 20.04.2021
 */

#include "Texture.h"

// Include STB image loader library.
#ifndef STB_IMAGE_IMPLEMENTATION
    #define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h>

namespace cgl
{
    Texture::Texture(string path, bool flip)
    {
        // Load image using stb library
        stbi_set_flip_vertically_on_load(flip);
        int w, h, chan;
        unsigned char* data = stbi_load(path.c_str(), &w, &h, &chan, 0);

        if(!data)
        {
            cerr << "Failed to load " << path << "." << endl;
            m_texID = 0;
            return;
        }

        // Create opengl texture object and store id in m_texID.
        glGenTextures(1, &m_texID);

        glActiveTexture(GL_TEXTURE0); // This is the texture 0 for next operations.
        glBindTexture(GL_TEXTURE_2D, m_texID); // Tell OpenGL we're using this texture for all next operations

        // Display options, we'll be using linear displaying
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Now, time to put loaded datas inside the texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D); // Generate the mipmap for zoom.

        // Free texture data
        stbi_image_free(data);
    }

    void Texture::bind(int index) const
    {
        if(!m_texID)
            return;

        glActiveTexture(GL_TEXTURE0 + index); // Unit index
        glBindTexture(GL_TEXTURE_2D, m_texID);
    }
}

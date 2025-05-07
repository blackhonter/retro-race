#include "texture.h"

Texture* Texture::instance()
{
    static Texture instance;

    return &instance;
}

void Texture::load_textures(vector<string> files)
{
    for (int i = 0; i < (int)files.size(); i++)
    {
        const char* file_name = files[i].c_str();
        upng_t* upng = upng_new_from_file(file_name);

        if (upng != NULL)
        {
            printf("File loaded: %s\n", file_name);

            upng_decode(upng);

            if (upng_get_error(upng) == UPNG_EOK)
            {
		        texture_t m_texture;

                m_texture.upng_texture = upng;
                m_texture.width = upng_get_width(upng);
                m_texture.height = upng_get_height(upng);
                m_texture.texture_buffer = (uint32_t*)upng_get_buffer(upng);

                this->textures.push_back(m_texture);

		        printf("Texture Created: %s\n", file_name);
            }
            else if(upng_get_error(upng) == UPNG_ENOMEM)
            {
                printf("Error Texture Created: Out of memory %s\n", file_name);
                std::cout<<upng_get_error_line(upng)<<std::endl;
            }
            else if(upng_get_error(upng) == UPNG_ENOTFOUND)
            {
                printf("Error Texture Created: Resource not found %s\n", file_name);
                std::cout<<upng_get_error_line(upng)<<std::endl;
            }
            else if(upng_get_error(upng) == UPNG_ENOTPNG)
            {
                printf("Error Texture Created: Invalid file header (not a PNG image) %s\n", file_name);
                std::cout<<upng_get_error_line(upng)<<std::endl;
            }
            else if(upng_get_error(upng) == UPNG_EMALFORMED)
            {
                printf("Error Texture Created: PNG image data does not follow spec and is malformed %s\n", file_name);
                std::cout<<upng_get_error_line(upng)<<std::endl;
            }
            else if(upng_get_error(upng) == UPNG_EUNSUPPORTED )
            {
                printf("Error Texture Created: PNG image data is well-formed but not supported by uPNG %s\n", file_name);
                std::cout<<upng_get_error_line(upng)<<std::endl;
            }
            else
            {
                 printf("Generic Error Created: %s\n", file_name);
            }
        }
        else
        {
            printf("UPNG Error: %i\n", upng_get_error(upng));
        }
    }
}

texture_t Texture::print_texture(int index)
{

        return this->textures[index];

}

void Texture::free_textures()
{
    for (int i = 0; i < (int)this->textures.size(); i++)
    {
        upng_free(this->textures[i].upng_texture);
    }

     this->textures.clear();
}

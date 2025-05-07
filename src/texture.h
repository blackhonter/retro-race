#ifndef TEXTURE_H
	#define TEXTURE_H

	#include <stdint.h>
	#include <iostream>
	#include <vector>
	#include <string>

	#include "definitions.h"


        #include "upng.h"


	using namespace std;

	typedef struct
	{
	    upng_t* upng_texture;
	    int width;
	    int height;
	    uint32_t* texture_buffer;
	} texture_t;

	class Texture
	{
		private:
			vector<texture_t> textures;

			//Singleton
			Texture(){}
			~Texture(){}

			Texture(const Texture& rhs);
			Texture& operator=(const Texture& rhs);

		public:
			static Texture* instance();

			void load_textures(vector<string> files);
			void free_textures();

			texture_t print_texture(int index);

	};
#endif

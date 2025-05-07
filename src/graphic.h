#ifndef GRAPHIC_H
	#define GRAPHIC_H

	#include <stdint.h>
	#include <stdbool.h>
	#include <iostream>

	#include <SDL2/SDL.h>

	#include "definitions.h"

	class Graphic
	{
		private:
			SDL_Window *window = NULL;
			SDL_Renderer *renderer = NULL;
			SDL_Texture *color_buffer_texture = NULL;
			
			uint32_t* color_buffer = NULL;

			//Singleton
			Graphic(){}
			~Graphic(){}

			Graphic(const Graphic& rhs);
			Graphic& operator=(const Graphic& rhs);

		public:
			static Graphic* instance();			

			bool initialize(void);
			bool initialize_window(void);
			bool initialize_renderer(void);
			bool initialize_textures(void);

			void drawn_pixel_in_color_buffer(int x, int y, uint32_t color);
			void drawn_rect_in_color_buffer(int x, int y, int w, int h, uint32_t color);
			void drawn_line_in_color_buffer(int x1, int y1, int x2, int y2, uint32_t color);

			void change_color_intensity(uint32_t* color, float factor );

			void render_color_buffer(void);
			void clear_color_buffer(uint32_t color);

			void update_window_title(const char *title);

			void destroy_window(void);

		
	};

#endif
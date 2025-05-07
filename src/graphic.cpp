#include "graphic.h"

Graphic* Graphic::instance()
{
	static Graphic instance;

	return &instance;
}

bool Graphic::initialize(void)
{
	if(SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Error initializing SDL \n");

		return false;
	}

	return true;
}

bool Graphic::initialize_window(void)
{
	this->window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
	if(!this->window)
	{
		fprintf(stderr, "Error creating SDL Window \n");

		return false;
	}

	return true;
}

bool Graphic::initialize_renderer(void)
{
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_SOFTWARE);
	if(!this->renderer)
	{
		fprintf(stderr, "Error creating SDL Renderer \n");

		return false;
	}

	SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_BLEND);

	return true;
}

bool Graphic::initialize_textures(void)
{
	this->color_buffer = (uint32_t*) malloc( sizeof(uint32_t) * (uint32_t) WINDOW_WIDTH * (uint32_t) WINDOW_HEIGHT);
	this->color_buffer_texture = SDL_CreateTexture(this->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STREAMING, WINDOW_WIDTH, WINDOW_HEIGHT);
	if(!this->color_buffer_texture)
	{
		fprintf(stderr, "Error creating SDL Texture \n");

		return false;
	}

	SDL_SetTextureBlendMode(this->color_buffer_texture, SDL_BLENDMODE_BLEND);

	return true;
}

void Graphic::drawn_pixel_in_color_buffer(int x, int y, uint32_t color)
{
	this->color_buffer[(WINDOW_WIDTH * y) + x] = color;
}

void Graphic::drawn_rect_in_color_buffer(int x, int y, int w, int h, uint32_t color)
{
	for(int i=x; i<=(x+w); i++)
	{
		for(int j=y; j<=(y+h); j++)
		{
			this->color_buffer[(WINDOW_WIDTH * j) + i] = color;
		}
	}
}

void Graphic::drawn_line_in_color_buffer(int x1, int y1, int x2, int y2, uint32_t color)
{
	int deltaX = (x2 - x1);
    int deltaY = (y2 - y1);

    int longestSideLength = (abs(deltaX) >= abs(deltaY)) ? abs(deltaX) : abs(deltaY);

    float xIncrement = deltaX / (float)longestSideLength;
    float yIncrement = deltaY / (float)longestSideLength;

    float currentX = x1;
    float currentY = y1;

    for (int i = 0; i < longestSideLength; i++) 
    {
        this->color_buffer[(WINDOW_WIDTH * (int)round(currentY)) + (int)round(currentX)] = color;
        
        currentX += xIncrement;
        currentY += yIncrement;
    }
}

void Graphic::change_color_intensity(uint32_t* color, float factor )
{
	factor = factor > 1 ? 1: factor;

	uint32_t a = (*color & 0xFF000000);
	uint32_t r = (*color & 0x00FF0000) * factor;
	uint32_t g = (*color & 0x0000FF00) * factor; 
	uint32_t b = (*color & 0x000000FF) * factor; 

	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

void Graphic::render_color_buffer(void)
{
	SDL_UpdateTexture(this->color_buffer_texture, NULL, this->color_buffer, (int) (uint32_t) WINDOW_WIDTH * sizeof(uint32_t));
	SDL_RenderCopy(this->renderer, this->color_buffer_texture, NULL, NULL);

	SDL_RenderPresent(this->renderer);
}

void Graphic::clear_color_buffer(uint32_t color)
{
	for (int x=0; x<WINDOW_WIDTH; x++)
	{
		for(int y=0; y<WINDOW_HEIGHT; y++)
		{
			this->color_buffer[(WINDOW_WIDTH * y) + x] = color;
		}
	}

	SDL_RenderClear(this->renderer);
}

void Graphic::update_window_title(const char *title)
{
	SDL_SetWindowTitle(this->window, title);
}

void Graphic::destroy_window(void)
{
	free(this->color_buffer);

	SDL_DestroyTexture(this->color_buffer_texture);
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}

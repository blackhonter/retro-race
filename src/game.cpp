#include "game.h"

Game::Game(void)
{
	this->is_running = Graphic::instance() -> initialize();
	this->is_running = Graphic::instance() -> initialize_window();
	this->is_running = Graphic::instance() -> initialize_renderer();
	this->is_running = Graphic::instance() -> initialize_textures();

	this->is_running = Sound::instance() -> initialize();

	this->is_running = GPIO::instance() -> initialize();
}

void Game::setup(void)
{
	//track
	vecTrack.push_back(make_pair(0.0f, 10.0f)); 
	vecTrack.push_back(make_pair(0.0f, 200.0f));
	vecTrack.push_back(make_pair(0.6f, 200.0f));
	vecTrack.push_back(make_pair(-0.4f, 400.0f));
	vecTrack.push_back(make_pair(0.0f, 100.0f));
	vecTrack.push_back(make_pair(1.0f, 200.0f));
	vecTrack.push_back(make_pair(0.0f, 50.0f));
	vecTrack.push_back(make_pair(-1.0f, 200.0f));
	vecTrack.push_back(make_pair(1.0f, 200.0f));
	vecTrack.push_back(make_pair(0.0f, 200.0f));
	vecTrack.push_back(make_pair(0.2f, 500.0f));
	vecTrack.push_back(make_pair(0.0f, 200.0f));

	// Calculate total track distance, so we can set lap times
	//for (auto t : vecTrack)
		//fTrackDistance += t.second;

	//listLapTimes = {0, 0, 0, 0, 0};
	//fCurrentLapTime = 0.0f;
}

void Game::process_input(void)
{
	//SDL CHECK
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
			case SDL_QUIT:
				//printf("sdl event quit \n");

				this->is_running = false;
				break;

			case SDL_KEYDOWN:
				//printf("sdl event keydown \n");
	    		
	    		switch(event.key.keysym.sym) 
	    		{
	    			case SDLK_ESCAPE: 
						this->is_running = false;
						break;

					case SDLK_LEFT:
						this->isTurning = true;
						this->nCarDirection = -1;
						break;

					case SDLK_RIGHT:
						this->isTurning = true;
						this->nCarDirection = +1;
						break;

					case SDLK_UP:
						this->isAcelerating = true;
						break;

					case SDLK_DOWN:
						this->isBreaking = true;
						break;
				}
				break;

			case SDL_KEYUP:
				//printf("sdl event keyup \n");

				switch(event.key.keysym.sym) 
	    			{
	    			case SDLK_LEFT:
						this->isTurning = false;
						this->nCarDirection = 0;
						break;

					case SDLK_RIGHT:
						this->isTurning = false;
						this->nCarDirection = 0;
						break;

					case SDLK_UP:
						this->isAcelerating = false;
						break;

					case SDLK_DOWN:
						this->isBreaking = false;
						break;
				}
			    break;

			case SDL_MOUSEMOTION:
				//printf("sdl event mouse motion \n");
				break;

			case SDL_MOUSEBUTTONDOWN:
				//printf("sdl event mouse button down \n");

				switch (event.button.button)
			    {
			        case SDL_BUTTON_LEFT:
			            break;

			        case SDL_BUTTON_RIGHT:
			            break;

			        default:
			            break;
			    }
                break;
                
            case SDL_MOUSEBUTTONUP:
            	//printf("sdl event mouse button up \n");

            	switch (event.button.button)
			    {
			        case SDL_BUTTON_LEFT:
			            break;

			        case SDL_BUTTON_RIGHT:
			            break;

			        default:
			            break;
			    }
           		break;
		}
	}

	//GPIO Check
	switch(GPIO::instance() -> process_input())
	{
		case KEYUP:
			printf("key press up \n");
			break;

		case KEYDOWN:
			printf("key press down \n");
			break;

		case KEYLEFT:
			printf("key press left \n");
			break;

		case KEYRIGHT:
			printf("key press rigth \n");
			break;

		default:
			break;
	}
}

void Game::fix_update(void)
{
	/*
	* Todo: calc FixDeltaTime for Physics
	*/
}

void Game::update(void)
{
	//FPS Control (Fix FPS)
	int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - this->last_frame_time);
	if(time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME)
	{
		SDL_Delay(time_to_wait);
	}

	this->frame_time = (SDL_GetTicks() - this->last_frame_time) / 1000.0f;
	float frame_rate = (1.0f / this->frame_time);

	string new_title = (string) GAME_NAME + " - " + to_string(frame_rate);
	const char* title = new_title.c_str();
	Graphic::instance() -> update_window_title(title);

	//Deltatime
	this->delta_time = (SDL_GetTicks() - this->last_frame_time) / 1000.0f;
	this->last_frame_time = SDL_GetTicks();

	EventSystem::instance() -> process_events();

	/*
	* Game Logig Here
	*/
		// Car Curvature is accumulated left/right input, but inversely proportional to speed
		// i.e. it is harder to turn at high speed
		if (this->isAcelerating)
		{
			this->fSpeed += 2.0f * this->delta_time;
		}

		if (this->isBreaking)
		{
			this->fSpeed -= 1.0f * this->delta_time;
		}

		if (this->isTurning && this->nCarDirection == -1)
		{
			this->fPlayerCurvature -= 0.7f * this->delta_time * (1.0f - this->fSpeed / 2.0f);
		}

		if (this->isTurning && this->nCarDirection == +1)
		{
			this->fPlayerCurvature += 0.7f * this->delta_time * (1.0f - this->fSpeed / 2.0f);
		}

		// If car curvature is too different to track curvature, slow down
		// as car has gone off track
		if (fabs(this->fPlayerCurvature - this->fTrackCurvature) >= 0.8f)
		{
			this->fSpeed -= 5.0f * this->delta_time;
		}

		// Clamp Speed
		if (fSpeed < 0.0f)
			fSpeed = 0.0f;

		if (fSpeed > 1.0f)
			fSpeed = 1.0f;

		// Move car along track according to car speed
		fDistance += (70.0f * fSpeed) * this->delta_time;

		// Lap Timing and counting
		/*
		fCurrentLapTime += this->delta_time;
		if (fDistance >= fTrackDistance)
		{
			fDistance -= fTrackDistance;
			listLapTimes.push_front(fCurrentLapTime);
			listLapTimes.pop_back();
			fCurrentLapTime = 0.0f;
		}
		*/

		// Find position on track (could optimise)
		while (nTrackSection < vecTrack.size() && fOffset <= fDistance)
		{
			fOffset += vecTrack[nTrackSection].second;
			nTrackSection++;
		}

		// Interpolate towards target track curvature
		float fTargetCurvature = vecTrack[nTrackSection - 1].first;
		float fTrackCurveDiff = (fTargetCurvature - fCurvature) * this->delta_time * fSpeed;

		// Accumulate player curvature
		fCurvature += fTrackCurveDiff;

		// Accumulate track curvature
		fTrackCurvature += (fCurvature) * this->delta_time * fSpeed;

		//Car position
		if ( (fPlayerCurvature - fTrackCurvature) >= -0.85f && (fPlayerCurvature - fTrackCurvature) <= 0.85f)
		{
			fCarPos = (fPlayerCurvature - fTrackCurvature);
		}

}

void Game::render(void)
{
	Graphic::instance() -> clear_color_buffer(0xFF000000);

	/*
	* Game Render Here
	*/
		// Draw Sky - light blue and dark blue
		for (int y = 0; y < WINDOW_HEIGHT / 2; y++)
		{
			for (int x = 0; x < WINDOW_WIDTH; x++)
			{
				Graphic::instance()->drawn_pixel_in_color_buffer(x, y, 0xFFFF0000);
			}
		}

		// Draw Scenery - our hills are a rectified sine wave, where the phase is adjusted by the
		// accumulated track curvature
		for (int x = 0; x < WINDOW_WIDTH; x++)
		{
			int nHillHeight = (int)(fabs(sinf(x * 0.01f + fTrackCurvature) * 40.0f));
			for (int y = (WINDOW_HEIGHT / 2) - nHillHeight; y < WINDOW_HEIGHT / 2; y++)
			{
				Graphic::instance()->drawn_pixel_in_color_buffer(x, y, 0xFFDEFF00);
			}
		}

		// Draw Track - Each row is split into grass, clip-board and track
		for (int y = 0; y < WINDOW_HEIGHT / 2; y++)
		{
			for (int x = 0; x < WINDOW_WIDTH; x++)
			{
				// Perspective is used to modify the width of the track row segments
				float fPerspective = (float)y / (WINDOW_HEIGHT / 2.0f);

				//float fRoadWidth = 0.6f;
				float fRoadWidth = 0.1f + fPerspective * 0.8f; // Min 10% Max 90%
				float fClipWidth = fRoadWidth * 0.15f;
				fRoadWidth *= 0.5f; // Halve it as track is symmetrical around center of track, but offset...

				// ...depending on where the middle point is, which is defined by the current
				// track curvature.
				float fMiddlePoint = 0.5f + fCurvature * powf((1.0f - fPerspective), 5);

				// Work out segment boundaries
				int nLeftGrass = (fMiddlePoint - fRoadWidth - fClipWidth) * WINDOW_WIDTH;
				int nLeftClip = (fMiddlePoint - fRoadWidth) * WINDOW_WIDTH;
				int nRightClip = (fMiddlePoint + fRoadWidth) * WINDOW_WIDTH;
				int nRightGrass = (fMiddlePoint + fRoadWidth + fClipWidth) * WINDOW_WIDTH;

				int nRow = WINDOW_HEIGHT / 2 + y;

				// Using periodic oscillatory functions to give lines, where the phase is controlled
				// by the distance around the track. These take some fine tuning to give the right "feel"
				uint32_t nGrassColour = sinf(20.0f * powf(1.0f - fPerspective, 3) + fDistance * 0.1f) > 0.0f ? 0xFF4C9900 : 0xFF006633;
				uint32_t nClipColour = sinf(80.0f * powf(1.0f - fPerspective, 2) + fDistance) > 0.0f ? 0xFF0000FF : 0xFFFFFFFF;

				// Start finish straight changes the road colour to inform the player lap is reset
				uint32_t nRoadColour = 0xFF333333;
				if( (nTrackSection - 1) == 0 || nTrackSection >= vecTrack.size())
					nRoadColour = 0xFFEEEEEE;

				// Draw the row segments
				if (x >= 0 && x < nLeftGrass)
					Graphic::instance()->drawn_pixel_in_color_buffer(x, nRow, nGrassColour);
				if (x >= nLeftGrass && x < nLeftClip)
					Graphic::instance()->drawn_pixel_in_color_buffer(x, nRow, nClipColour);
				if (x >= nLeftClip && x < nRightClip)
					Graphic::instance()->drawn_pixel_in_color_buffer(x, nRow, nRoadColour);
				if (x >= nRightClip && x < nRightGrass)
					Graphic::instance()->drawn_pixel_in_color_buffer(x, nRow, nClipColour);
				if (x >= nRightGrass && x < WINDOW_WIDTH)
					Graphic::instance()->drawn_pixel_in_color_buffer(x, nRow, nGrassColour);
			}
		}

		//Draw Car
		int nCarPos = WINDOW_WIDTH / 2 + ((int)(WINDOW_WIDTH * fCarPos) / 2.0)-40 ; // Offset for sprite

		Graphic::instance()->drawn_rect_in_color_buffer(nCarPos, WINDOW_HEIGHT - 30, 80, 20, 0xFF00FFFF);

	Graphic::instance()->render_color_buffer();
}

void Game::release_resources(void)
{
	EventSystem::instance() -> shut_down();
	Texture::instance() -> free_textures();
	Sound::instance() -> free_sounds();
	Graphic::instance() -> destroy_window();
}
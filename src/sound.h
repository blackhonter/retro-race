#ifndef SOUND_H
	#define SOUND_H

	#include <stdint.h>
	#include <stdbool.h>
	#include <iostream>
	#include <vector>
	#include <string>
        #include <climits>

	#include <SDL2/SDL.h>
	#include <SDL2/SDL_mixer.h>

	#include "definitions.h"
	#include "functions.h"

	using namespace std;

	enum sound_type {efx = 1, music = 2};

	class Sound
	{
		private:
			vector<Mix_Chunk*> sound_efxs;
			vector<Mix_Music*> musics;

			//Singleton
			Sound(){}
			~Sound(){}

			Sound(const Sound& rhs);
			Sound& operator=(const Sound& rhs);

		public:
			static Sound* instance();
			
			bool initialize(void);

			void load_sounds(vector<string> files, enum sound_type st = efx);
			void free_sounds();

			void play_music(int index, int times = -1, int volume=MIX_MAX_VOLUME);

			void play_efx(int index, int times, int angle, float distance);
			void update_efx(int index, int angle, float distance);

		
	};
#endif
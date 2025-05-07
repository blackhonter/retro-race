#ifndef GAME_H
	#define GAME_H

	#include <iostream>
	#include <stdio.h>
	#include <stdint.h>
	#include <stdbool.h>
	#include <bits/stdc++.h>
	#include <string>
	#include <vector>

	#include <SDL2/SDL.h>

	#include "definitions.h"
	#include "graphic.h"
	#include "texture.h"
	#include "sound.h"
	#include "gpio.h"
	#include "eventSystem.h"

	using namespace std;

	class Game
	{
		public:
			Game(void);

			void setup(void);
			void process_input(void);
			void fix_update(void);
			void update(void);
			void render(void);
			void release_resources(void);

			bool is_running = false;
			
		protected:
			float fDistance = 0.0f;		  // Distance car has travelled around track
			float fCurvature = 0.0f;	  // Current track curvature, lerped between track sections
			float fTrackCurvature = 0.0f; // Accumulation of track curvature
			float fTrackDistance = 0.0f;  // Total distance of track

			float fCarPos = 0.0f;		   // Current car position
			float fPlayerCurvature = 0.0f; // Accumulation of player curvature
			float fSpeed = 0.0f;		   // Current player speed

			vector<pair<float, float>> vecTrack; // Track sections, sharpness of bend, length of section (curvature, distance)

			//list<float> listLapTimes; // List of previous lap times
			//float fCurrentLapTime;	  // Current lap time

			int nCarDirection = 0;

			bool isAcelerating = false;
			bool isBreaking = false;
			bool isTurning = false;

			float fOffset = 0;
			int nTrackSection = 0;

		private:
			float last_frame_time = 0.0f;
			float delta_time = 0.0f;
			float frame_time = 0.0f;
	};
	
#endif
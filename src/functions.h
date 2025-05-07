#ifndef FUNCTIONS_H
	#define FUNCTIONS_H

	//INCLUDES
		#include <math.h>
		#include <stdlib.h>
		#include <time.h>

		#include "definitions.h"

	//METHODOS
    #ifdef __cplusplus
        extern "C" {
    #endif
		float deg_to_rad(float angle_in_degrees);
		float rad_to_deg(float angle_in_radians);
		float normalize_angle(float angle);
		float distance_between_points(float x1, float y1, float x2, float y2);
		float map_values(float value, int a, int b, int c, int d);
		int get_random_num(int min, int max);
    #ifdef __cplusplus
        }
    #endif

#endif

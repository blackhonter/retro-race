#include "functions.h"

float deg_to_rad(float angle_in_degrees)
{
	return ((angle_in_degrees) * PI / 180.0);
}

float rad_to_deg(float angle_in_radians)
{
	return ((angle_in_radians) * 180.0 / PI);
}

float normalize_angle(float angle)
{
	angle = remainder(angle, deg_to_rad(360));

    if (angle < 0) 
    {
        angle = deg_to_rad(360) + angle;
    }

    return angle;
}

float distance_between_points(float x1, float y1, float x2, float y2)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float map_values(float value, int a, int b, int c, int d)
{
    return ((value-a)/(b-a) * (d-c) + c);
}

int get_random_num(int min, int max)
{
    static bool first = true;
    if (first)
    {
        srand(time(NULL));
        first = false;
    }
    return min + rand() % ((max + 1) - min);
}

#define PI 3.14159265358979323846
#include <math.h>
#include "distance.h"

float rad (float x){
    return x * PI / 180;
}


float calc_dist_bet_2_points(float p1Lat, float p2Lat,float p1Lang,float p2Lang){
	 float  R = 6378137;
   float dLat = rad(p2Lat - p1Lat);
   float dLong = rad(p2Lang - p1Lang);
   float a = sin(dLat / 2) * sin(dLat / 2)+
    cos(rad(p1Lat)) * cos(rad(p2Lat))*
    sin(dLong / 2) * sin(dLong / 2);

    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float  d = R * c;
return d;
	 
}

void conv (char finalvalue[7],float dis)
{
				sprintf(finalvalue,"%f",dis);
}
	

	
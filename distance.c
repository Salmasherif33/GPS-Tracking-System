#include "DT.h"
#define PI 3.14159265358979323846
#include <math.h>
#include "distance.h"
#include <stdio.h>


double rad (double x){
    return x * PI / 180;
}


double calc_dist_bet_2_points(double p1Lat, double p2Lat,double p1Lang,double p2Lang){
	 double  R = 6378137;
   double dLat = rad(p2Lat - p1Lat);
   double dLong = rad(p2Lang - p1Lang);
   double a = sin(dLat / 2) * sin(dLat / 2)+
    cos(rad(p1Lat)) * cos(rad(p2Lat))*
    sin(dLong / 2) * sin(dLong / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double  d = R * c;
return d;
	 
}

 void conv (char finalvalue[7],double dis)
{
				sprintf(finalvalue,"%f",dis);
}

	

	
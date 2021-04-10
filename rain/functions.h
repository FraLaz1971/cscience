/*  Meteorologists studied the precipitation levels in the Bay Area
and has come up with a model r(m,t)
where r is the amount of rain, m is the month, and t is a scalar parameter
epending on the location. Problem:
Given the formula for r and the value of t, compute the annual rainfall.
      defining function r
      r(m,t) = t/10 * (m^2 + 14*m + 46) --> if this is positive
      r(m,t) = 0                        --> otherwise
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float monthly_rain(float m, float t);

float in2cm(float ti);

float cm2in(float tc);

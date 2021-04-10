/*  Meteorologists studied the precipitation levels in the Bay Area and has come up with a model r(m,t) 
c  where r is the amount of rain, m is the month, and t is a scalar parameter 
c depending on the location. Problem:
c Given the formula for r and the value of t, compute the annual rainfall. 
c
c      defining function r
c      r(m,t) = t/10 * (m^2 + 14*m + 46) --> if this is positive
c      r(m,t) = 0                        --> otherwise     
c */
#include "functions.h"

float monthly_rain(float m, float t){
            float r;
            r = 0.1*t * (pow(-1*m, 2) - 15*m  + 146);
            if (r < 0) 
                r = 0.0;
            return r;
        }

float in2cm(float ti){
            return 2.54*ti;
}
      
float cm2in(float tc){
          return tc*0.39370079;
}


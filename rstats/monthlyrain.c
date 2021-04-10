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

int main(int argc, char **argv){
        float r, t, ret, rete, ti;
        int m;
        if(argc <3){
            fprintf(stderr,"usage:%s <local-parameter (0-5]> <month [1-12]>\n", argv[0] );
            return 1;
        } else {
            t = atof(argv[1]);            
            m = atoi(argv[2]);            
            ret = 0.0;
            ret = monthly_rain(m, t);
            rete = in2cm(ret);
/*            printf("Monthly rainfall is %f inches\n", ret); */
            printf("rainfall for month %i is %f cm\n", m, rete);
            return 0;
        }
}

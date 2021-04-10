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
        if(argc <2){
            fprintf(stderr,"usage:%s <local-parameter (0-5]>\n", argv[0] );
            return 1;
        } else {
                float r, t, sum, sume, rinc2cm, ti;
                int m;
            t = atof(argv[1]);            
            sum = 0.0;
            for(m=1; m<=12; m++){
                sum = sum + monthly_rain(m, t);
            }
            sume = in2cm(sum);
            printf("Annual rainfall is %f inches\n", sum);
            printf("Annual rainfall is %f cm\n", sume);
            return 0;
        }
}

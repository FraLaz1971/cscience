#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* global variables */

struct Array2x2 {
    double a, b; 
    double c, d; 
} a2x2;  

struct Array3x3 {
    double d_1, e_1, f_1; 
    double d_2, e_2, f_2; 
    double d_3, e_3, f_3; 
} a3x3;  

typedef struct Array2x2 Array2x2;
typedef struct Array3x3 Array3x3;

struct Circle {
    /* points on the circle */
    double x1, y1; 
    double x2, y2; 
    double x3, y3; 
    double w[3]; /* known terms array, size=3 */
    /* arrays to support the computation */
    Array3x3 a33, a33s1, a33s2, a33s3; 
    /* determinants and solution array */
    double da3, d3s[3];
    double a, b, c;
    double radius;
    double x_c,y_c; /* centre coordinates */
} circle;  
typedef struct Circle Circle;


struct Matrix {
    /* points on the circle */
    double x1, y1;
    double x2, y2;
    double x3, y3;
    double w[3]; /* known terms array, size=3 */
    /* arrays to support the computation */
    Array2x2 a22;
    Array3x3 a33, a33s1, a33s2, a33s3;
    /* determinants and solution array */
    double x_c,y_c; /* coordinates of the centre*/
} matrix;
typedef struct Matrix Matrix;


struct Run {
    int  argc;
    char** argv;
} run;

typedef struct Run Run;

int read_circle_input(char ** margv, Circle *circ);
int read_matrix_input(char ** margv, Matrix *matr);
int show_system(char ** margv, Circle *matr);
int show_circle_matrix(char ** margv, Circle *circ);
int show_matrix_matrix(char ** margv, Matrix *matr);
int set_run_par(int margc, char ** margv);
int set_circle_arrays(Circle *circ);
int set_matrix_arrays(Matrix *matr);
void estarline(void);
int show_solution();
int dump_circle(int npts);
int dump_matrix(int npts);

/* functions related to 2x2 arrays */

/* set the values in data to the Array fields*/
int set_Array2x2_data(Array2x2 *a2x2, double *data);
/* gives the determinant of the given matrix */
double detA2x2(Array2x2 *a2x2);
int show_Array2x2(Array2x2 *a2x2);
int show_Array2x2_system(Array2x2 *a2x2, double *v);
int dump_Array2x2(Array2x2 *a2x2);
/* given the linear system of 2 equations and 2 unknown variables 
 * a2x2 --> coefficient array;
 * v --> known terms array
 saves the solution as sol[0], sol[1] */
int get_2x2_solution(Array2x2 *a2x2, double *v, double *sol);
/* functions related to 3x3 arrays */
/* set the values in data to the Array fields */
int set_Array3x3_data(Array3x3 *a3x3, double *data);
double detA3x3(Array3x3 *a3x3);
int show_Array3x3(Array3x3 *a3x3);
int show_Array3x3_system(Array3x3 *a3x3, double *w);
int dump_Array3x3(Array3x3 *a3x3);

/* given the linear system of 3 equations and 3 unknown variables 
 * a3x3 --> coefficients array;
 * v    --> known terms array
 saves the solution in sol[0], sol[1], sol[2] */
int get_3x3_solution(Array3x3 *a3x3, double *v, double *sol);

/* global structure */
Run run;
/* global temp variables */
double dres;
/* first example: P1(0,2) P2(2,4) P3(1,0) */
int main(int argc, char **argv){
    /* variable definition */
    int mret; Matrix mymatr; 
    /* data for the 2x2 equations system */
    Array2x2 a22; double e1_2x2[4];
    /* determinants for matrix, sol1, sol2*/
    double da2, d2s[2];
    double v[2]; /* known terms array size=2 */
    /* data for the 3x3 equations system */
    Array3x3 a33, a33s1, a33s2, a33s3; double e1_3x3[9];
    double w[3]; /* known terms array size=3 */
    /* determinants for matrix, sol1, sol2, sol3*/
    double da3, d3s[3];

    /* computing steps */
    /* set the input parameters of current run */
    set_run_par(argc, argv);
    mret = read_input(argv, &mymatr);
    mret = show_system(argv, &mymatr);
    mret = show_matrix_matrix(argv, &mymatr);
    /* 2x2 array example */
    /* assign values to 2x2 matrix */
    e1_2x2[0]= 2;e1_2x2[1]=-1;
    e1_2x2[2]= 1;e1_2x2[3]= 3;  
    /* assign values to known terms size=2 array */
    v[0]=4;v[1]=9;
    mret = set_Array2x2_data(&a22, (double *)&e1_2x2);
    /* show the array content on stderr */
    fprintf(stderr,"%s: showing content of 2x2 array a22 \n",run.argv[0]);
    /* show the array determinant on stderr */
    mret = show_Array2x2(&a22);
    mret = show_Array2x2_system(&a22, (double *)&v);
    da2 = detA2x2(&a22);
    fprintf(stderr,"%s: det(a22) is %g\n",run.argv[0], da2);
    if (da2 == 0 ){ 
        fprintf(stderr,"%s: the equation system (a2) (v) cannot be solved \n",run.argv[0]);
    } else{
        /* create matrix of the first unknown variable */
        /* compute and shows determinant of first unknown variable x */
        estarline();
        fprintf(stderr,"%s: det(a22s1) is %g\n",run.argv[0], d2s[0]);
        /* create matrix of the second unknown variable */
        /* compute and shows determinant of second unknown variable y */
        fprintf(stderr,"%s: det(a22s2) is %g\n",run.argv[0], d2s[1]);
        estarline();
    }
    return 0;
}

int read_input(char ** margv, Circle *circ){
    int ret;
    estarline();
    fprintf(stderr, "%s: please, enter first point  P1: x1 y1 separated by space:\n", margv[0]);
    ret = scanf("%lf %lf", &circ->x1, &circ->y1);
    fprintf(stderr,"%s: you entered P1(%g,%g)\n", margv[0], circ->x1, circ->y1);
    fprintf(stderr, "%s: please, enter second point P2: x2 y2 separated by space:\n", margv[0]);
    ret = scanf("%lf %lf", &circ->x2, &circ->y2);
    fprintf(stderr,"%s: you entered P2(%g,%g)\n", margv[0], circ->x2, circ->y2);
    fprintf(stderr, "%s: please, enter third point  P3: x3 y3 separated by space:\n", margv[0]);
    ret = scanf("%lf %lf", &circ->x3, &circ->y3);
    fprintf(stderr,"%s: you entered P3(%g,%g)\n", margv[0], circ->x3, circ->y3);
    /*assign computed values */
    circ->w[0]=-1*(circ->x1*circ->x1+circ->y1*circ->y1);
    circ->w[1]=-1*(circ->x2*circ->x2+circ->y2*circ->y2);
    circ->w[2]=-1*(circ->x3*circ->x3+circ->y3*circ->y3);
    estarline();
    /* compute the equation system */
    // e1 = x1*x1+y1*y1
    return 0;    
}

int show_system(char ** margv, Circle *circ){    
    estarline();
    fprintf(stderr,"%s: %g+%g+a*%g+b*%g+c = 0\n", margv[0], circ->x1*circ->x1, circ->y1*circ->y1, circ->x1, circ->y1);
    fprintf(stderr,"%s: %g+%g+a*%g+b*%g+c = 0\n", margv[0], circ->x2*circ->x2, circ->y2*circ->y2, circ->x2, circ->y2);
    fprintf(stderr,"%s: %g+%g+a*%g+b*%g+c = 0\n", margv[0], circ->x3*circ->x3, circ->y3*circ->y3, circ->x3, circ->y3);
    estarline();
    return 0;
}

void estarline(void){
    fprintf(stderr,"**********************************\n");
}

int show_circle_equations(char ** margv, Circle *circ){    
    estarline();
    fprintf(stderr,"%s: %g+%g+a*%g+b*%g+c = 0\n", margv[0], circ->x1*circ->x1, circ->y1*circ->y1, circ->x1, circ->y1);
    fprintf(stderr,"%s: %g+%g+a*%g+b*%g+c = 0\n", margv[0], circ->x2*circ->x2, circ->y2*circ->y2, circ->x2, circ->y2);
    fprintf(stderr,"%s: %g+%g+a*%g+b*%g+c = 0\n", margv[0], circ->x3*circ->x3, circ->y3*circ->y3, circ->x3, circ->y3);
    estarline();
    return 0;
}

int show_circle_matrix(char ** margv, Circle *circ){    
    estarline();
    fprintf(stderr,"%s: (%2g %2g  1 ) (a) = (%2g)\n", margv[0], circ->x1, circ->y1, -1*(circ->x1*circ->x1+circ->y1*circ->y1));
    fprintf(stderr,"%s: (%2g %2g  1 ) (b) = (%2g)\n", margv[0], circ->x2, circ->y2, -1*(circ->x2*circ->x2+circ->y2*circ->y2));
    fprintf(stderr,"%s: (%2g %2g  1 ) (c) = (%2g)\n", margv[0], circ->x3, circ->y3, -1*(circ->x3*circ->x3 + circ->y3*circ->y3));
    estarline();
    return 0;
}
int show_matrix_equations(char ** margv, Matrix *circ){    
    estarline();
    fprintf(stderr,"%s: %g+%g+a*%g+b*%g+c = 0\n", margv[0], circ->x1*circ->x1, circ->y1*circ->y1, circ->x1, circ->y1);
    fprintf(stderr,"%s: %g+%g+a*%g+b*%g+c = 0\n", margv[0], circ->x2*circ->x2, circ->y2*circ->y2, circ->x2, circ->y2);
    fprintf(stderr,"%s: %g+%g+a*%g+b*%g+c = 0\n", margv[0], circ->x3*circ->x3, circ->y3*circ->y3, circ->x3, circ->y3);
    estarline();
    return 0;
}

int show_matrix_matrix(char ** margv, Matrix *circ){    
    estarline();
    fprintf(stderr,"%s: (%2g %2g  1 ) (a) = (%2g)\n", margv[0], circ->x1, circ->y1, -1*(circ->x1*circ->x1+circ->y1*circ->y1));
    fprintf(stderr,"%s: (%2g %2g  1 ) (b) = (%2g)\n", margv[0], circ->x2, circ->y2, -1*(circ->x2*circ->x2+circ->y2*circ->y2));
    fprintf(stderr,"%s: (%2g %2g  1 ) (c) = (%2g)\n", margv[0], circ->x3, circ->y3, -1*(circ->x3*circ->x3 + circ->y3*circ->y3));
    estarline();
    return 0;
}


int set_run_par(int margc, char ** margv){
    run.argc = margc;
    run.argv = margv;
    int count;
    for(count=0; count<=run.argc; count++){
            fprintf(stderr,"%s: run.argv[%i] = %s\n",run.argv[0], count, run.argv[count]);
    }
    return 0;
}


int dump_circle(int npts)
{
    int count;
    for(count=0; count<=npts; count++){
            fprintf(stderr,"%s %i %s\n",run.argv[0], count, run.argv[count]);
    }
        return 0;
}

int dump_matrix(int npts)
{
    int count;
    for(count=0; count<=npts; count++){
            fprintf(stderr,"%s %i %s\n",run.argv[0], count, run.argv[count]);
    }
        return 0;
}

int set_Array2x2_data(Array2x2 *a2x2, double *data){
    a2x2->a = data[0];a2x2->b = data[1];
    a2x2->c = data[2];a2x2->d = data[3];
    return 0;
}

double detA2x2(Array2x2 *a2x2){
        return a2x2->a * a2x2->d - a2x2->b*a2x2->c;
}


int show_Array2x2(Array2x2 *a2x2){
    estarline();
    fprintf(stderr,"%s: (%2g %2g )\n",run.argv[0], a2x2->a, a2x2->b);
    fprintf(stderr,"%s: (%2g %2g )\n",run.argv[0], a2x2->c, a2x2->d);
    estarline();
    return 0;
}

int show_Array2x2_system(Array2x2 *a2x2, double *v){
    estarline();
    fprintf(stderr,"%s: %2g*x + %2g*y = %2g\n", run.argv[0], a2x2->a,a2x2->b, v[0]);    
    fprintf(stderr,"%s: %2g*x + %2g*y = %2g\n", run.argv[0], a2x2->c,a2x2->d, v[1]);    
    estarline();
    return 0;
}


int dump_Array2x2(Array2x2 *a2x2){
    return 0;
}

int set_Array3x3_data(Array3x3 *a3x3, double *data){
    a3x3->d_1 = data[0];a3x3->e_1 = data[1];a3x3->f_1 = data[2];
    a3x3->d_2 = data[3];a3x3->e_2 = data[4];a3x3->f_2 = data[5];
    a3x3->d_3 = data[6];a3x3->e_3 = data[7];a3x3->f_3 = data[8];
    return 0;
}


double detA3x3(Array3x3 *a3x3){
        dres = a3x3->d_1 * a3x3->e_2 * a3x3->f_3 + \
               a3x3->e_1 * a3x3->f_2 * a3x3->d_3 + \
               a3x3->f_1 * a3x3->d_2 * a3x3->e_3 - \
               a3x3->f_1 * a3x3->e_2 * a3x3->d_3 - \
               a3x3->e_1 * a3x3->d_2 * a3x3->f_3 - \
               a3x3->d_1 * a3x3->f_2 * a3x3->e_3;
               return dres;
}

int show_Array3x3(Array3x3 *a3x3){
    estarline();
    fprintf(stderr,"%s (%2g %2g %2g )\n",run.argv[0], a3x3->d_1, a3x3->e_1, a3x3->f_1);
    fprintf(stderr,"%s (%2g %2g %2g )\n",run.argv[0], a3x3->d_2, a3x3->e_2, a3x3->f_2);
    fprintf(stderr,"%s (%2g %2g %2g )\n",run.argv[0], a3x3->d_3, a3x3->e_3, a3x3->f_3);
    estarline();
    return 0;
}


int show_Array3x3_system(Array3x3 *a3x3, double *w){
    return 0;
}

int set_circle_arrays(Circle *circ){
   /* assign values to 3x3 matrix */
    double e1_3x3[9]; double w[3]; int mret;
    e1_3x3[0]=circ->x1;e1_3x3[1]=circ->y1;e1_3x3[2]=1;
    e1_3x3[3]=circ->x2;e1_3x3[4]=circ->y2;e1_3x3[5]=1;
    e1_3x3[6]=circ->x3;e1_3x3[7]=circ->y3;e1_3x3[8]=1;
    /* assign values to known terms size=3 array */
    
    w[0]=circ->w[0]; w[1]=circ->w[1]; w[2]=circ->w[2];

    mret = set_Array3x3_data(&circ->a33, (double *)&e1_3x3);
    /* show the array content on stderr */
    fprintf(stderr,"%s:set_circle_arrays() showing content of 3x3 array a33 \n",run.argv[0]);
    mret = show_Array3x3(&circ->a33);
    circ->da3 = detA3x3(&circ->a33);
    fprintf(stderr,"%s:set_circle_arrays() det(a33) is %g\n",run.argv[0], circ->da3);
    if (circ->da3 == 0 ){ 
        fprintf(stderr,"%s:set_circle_arrays() the equation system (a3) (w) cannot be solved \n",run.argv[0]);
    } else{
            //Array3x3 a33, a33s1, a33s2, a33s3; double e1_3x3[9];
        /* create matrix of the first unknown variable */
        circ->a33s1.d_1=circ->w[0];circ->a33s1.e_1=circ->a33.e_1;circ->a33s1.f_1=circ->a33.f_1;  
        circ->a33s1.d_2=circ->w[1];circ->a33s1.e_2=circ->a33.e_2;circ->a33s1.f_2=circ->a33.f_2;  
        circ->a33s1.d_3=circ->w[2];circ->a33s1.e_3=circ->a33.e_3;circ->a33s1.f_3=circ->a33.f_3;  
        /* create matrix of the second unknown variable */
        circ->a33s2.d_1=circ->a33.d_1;circ->a33s2.e_1=circ->w[0];circ->a33s2.f_1=circ->a33.f_1;  
        circ->a33s2.d_2=circ->a33.d_2;circ->a33s2.e_2=circ->w[1];circ->a33s2.f_2=circ->a33.f_2;  
        circ->a33s2.d_3=circ->a33.d_3;circ->a33s2.e_3=circ->w[2];circ->a33s2.f_3=circ->a33.f_3;  
        /* create matrix of the third unknown variable */
        circ->a33s3.d_1=circ->a33.d_1;circ->a33s3.e_1=circ->a33.e_1;circ->a33s3.f_1=circ->w[0];  
        circ->a33s3.d_2=circ->a33.d_2;circ->a33s3.e_2=circ->a33.e_2;circ->a33s3.f_2=circ->w[1];  
        circ->a33s3.d_3=circ->a33.d_3;circ->a33s3.e_3=circ->a33.e_3;circ->a33s3.f_3=circ->w[2];  
        /* compute and shows determinant of first unknown variable a */
        circ->d3s[0] = detA3x3((Array3x3*)&circ->a33s1);
        estarline();
        fprintf(stderr,"%s:set_circle_arrays() det(circ->a33s1) is %g\n",run.argv[0], circ->d3s[0]);
        /* compute and shows determinant of second unknown variable b */
        circ->d3s[1] = detA3x3((Array3x3*)&circ->a33s2);
        estarline();
        fprintf(stderr,"%s:set_circle_arrays() det(circ->a33s2) is %g\n",run.argv[0], circ->d3s[1]);
        /* compute and shows determinant of first unknown variable c */
        circ->d3s[2] = detA3x3((Array3x3*)&circ->a33s3);
        estarline();
        fprintf(stderr,"%s:set_circle_arrays() det(circ->a33s3) is %g\n",run.argv[0], circ->d3s[2]);
        estarline();
        circ->a=circ->d3s[0]/circ->da3;
        circ->b=circ->d3s[1]/circ->da3;
        circ->c=circ->d3s[2]/circ->da3;
        fprintf(stderr,"%s:set_circle_arrays() the value of a is %g\n",run.argv[0], circ->a);
        fprintf(stderr,"%s:set_circle_arrays() the value of b is %g\n",run.argv[0], circ->b);
        fprintf(stderr,"%s:set_circle_arrays() the value of c is %g\n",run.argv[0], circ->c);
        circ->x_c=circ->a/-2;circ->y_c=circ->b/-2; /* centre coordinates */
        fprintf(stderr,"%s:set_circle_arrays() the centre is (%g,%g)\n",run.argv[0], circ->x_c, circ->y_c);
        circ->radius = sqrt(circ->x_c*circ->x_c  + circ->y_c*circ->y_c - circ->c); /*radius*/
        fprintf(stderr,"%s:set_circle_arrays() the radius r is %g\n",run.argv[0], circ->radius);
        estarline();
    }
     return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
    int n; // term count
    int **array; // [n] x [4] function_id / coefficient / pow / subcoefficent:W sin(Wt)
    // function_id => polynomial (1) , sinx (2), cosx(3)
}F;

typedef struct{
	double a1;
    double a2;
    double expectedResult; // certain real result of differantial equations
    double myResult; // calculated result   
    F function;
}ODE;

void getEquations(ODE *equations);
void getFunction(ODE *equations);
void printFunction(ODE equations);
double calculateFx(ODE equations, double xi);
double rungeKuttaMethod(ODE equations, double xi, double yi,double *stepsize);


int main(){
    ODE equations; 
    double x0,y0,h;
    double **data= (double **) malloc(sizeof(double*));
    int i,flag=1,len=0;
    getEquations(&equations);
    printFunction(equations);
    
    printf("Enter the x0 value : ");
    scanf("%lf",&x0);
    printf("Enter the y(%lf) value : ",x0);
    scanf("%lf",&y0);
    printf("Enter the expected result : ");
    scanf("%lf",&equations.expectedResult);
    while(flag==1){
        data = realloc(data,len+1);

        equations.myResult = rungeKuttaMethod(equations,x0,y0,&h);
        printf("\n----------------------\n");
        printf("Runge Kutta-4 result: %lf\n",equations.myResult);
        printf("Expexted result     : %lf\n",equations.expectedResult);
        printf("Error value         : %lf\n",fabs(equations.myResult - equations.expectedResult));
        
        // add test values into data array
        data[len] = (double*) malloc(3*sizeof(double));
        // step size / RK-4 result / error value
        data[len][0] = h;
        data[len][1] = equations.myResult;
        data[len][2] = fabs(equations.myResult - equations.expectedResult);
        len++;

        printf("\nDo you want to calculate RK-4 with different stepsize (Yes:1 / No:0): ");
        scanf("%d",&flag);
    }
    printf("\nAll test values:\n");
    printf("Step Size (h) | RK-4 Result | Error Value\n------------------------------------------\n");
    for(i=0;i<len;i++){
        printf("%.8lf    | %.8lf  | %.10lf\n",data[i][0],data[i][1],data[i][2]);
    }

    // deallocate data array
    for(i=0;i<len-1;i++){
        free(data[i]);
    }free(data);
    
    // deallocate equations.function.array
    for(i=0;i<equations.function.n;i++){
        free(equations.function.array[i]);
    }free(equations.function.array);

    return 1;
}

void getEquations(ODE *equations){
    // bu fonksiyon ile kullaniciden denklemi alin
    printf("Enter the number of elements of the function f(x):");
    scanf("%d",&(equations->function.n));
    
    getFunction(equations);
    printf("\n------------\n");
    printf("Enter the coefficient of [A] A* y' : ");
    scanf("%lf",&equations->a1);
    printf("Enter the coefficient of [B] B* y : ");
    scanf("%lf",&equations->a2);
}

void getFunction(ODE *equations){
    printf("\nThe following types can be found in the function:\n");
    printf("\t- ID:1 polynomial\n\t- ID:2 sin(Ax)\n\t- ID:3 cos(Ax)\n");
    int i;
    int n = equations->function.n;
    // memory allocation for the array
    equations->function.array = (int**) malloc(n*sizeof(int*));
    for(i=0; i< n ;i++){
        equations->function.array[i] = (int*) malloc(4*sizeof(int));
    }
    
    // n tane terim icin katsayi alacagiz
    for(i=0; i< n; i++){
        printf("\nEnter the function_id for element #%d\n",i+1);
        printf("\t- ID:1 polynomial\n\t- ID:2 sin(Ax)\n\t- ID:3 cos(Ax)\n");
        scanf("%d",&equations->function.array[i][0]);

        switch (equations->function.array[i][0])
        {
        case 1: 
            /* a*(x^n) */
            printf("Enter the coefficient [a] of a*(x^n) : ");
            scanf("%d",&equations->function.array[i][1]);
            printf("Enter exponent [n] of a*(x^n) : ");
            scanf("%d",&equations->function.array[i][2]);
            break;
        case 2:
            /* a*sin(Bx) */
            printf("Enter the coefficient [a] of a*[ sin(Bx) ]^n : ");
            scanf("%d",&equations->function.array[i][1]);
            printf("Enter sub coefficient [B] of a*[ sin(Bx) ]^n : ");
            scanf("%d",&equations->function.array[i][3]);
            printf("Enter the exponent [n] of a*[ sin(Bx) ]^n : ");
            scanf("%d",&equations->function.array[i][2]);
            break;
        case 3:
            /* a*cos(Bx) */
            printf("Enter the coefficient [a] of a*[ cos(Bx) ]^n : ");
            scanf("%d",&equations->function.array[i][1]);
            printf("Enter sub coefficient [B] of a*[ cos(Bx) ]^n : ");
            scanf("%d",&equations->function.array[i][3]);
            printf("Enter the exponent [n] of a*[ cos(Bx) ]^n : ");
            scanf("%d",&equations->function.array[i][2]);
            break;
        default:
            printf("Enter a valid function ID !\n");
            i--;
			break;
        }
    }
}

void printFunction(ODE equations){
    int i;
    printf("\n-------------\n%lf*y' + %lf*y + ",equations.a1,equations.a2);
    printf("[ ");
    for (i = 0; i < equations.function.n; i++)
    {
        switch (equations.function.array[i][0])
        {
        case 1:
            printf("%d*x^%d + ",equations.function.array[i][1],equations.function.array[i][2]);
            break;
        case 2:
            printf("%d*[ sin(%dx) ]^%d + ",equations.function.array[i][1],equations.function.array[i][3],equations.function.array[i][2]);
            break;
        case 3:
            printf("%d*[ cos(%dx) ]^%d + ",equations.function.array[i][1],equations.function.array[i][3],equations.function.array[i][2]);
            break;        
        }
    }
    printf("] = 0\n\n");
}

double calculateFx(ODE equations, double xi){
	double result =0,x ,sin_x,cos_x;
	int i,pow;
 	
    for (i = 0; i < equations.function.n; i++)
    {
    	x = xi;
        switch (equations.function.array[i][0])
        {
        
        case 1:
            // polynomial a*(x^n)
            if(equations.function.array[i][2] >=1){
                for(pow=1; pow < equations.function.array[i][2] ;pow++){
                    // x has the value of the 1st power, so if the exponent is greater than 1, we will multiply x by itself
                    x *=x;
                }
                result += equations.function.array[i][1] * x;
            }
            else{
                result += equations.function.array[i][1];
            }
            break;
        case 2:
            // sinx a*sin(Bx)
            sin_x = sin(equations.function.array[i][3] * x);
            
            for(pow=1; pow < equations.function.array[i][2] ;pow++){
                // if exponent greater than 1, we will multiply x by itself otherwise do nothing because we have already calculate sin() once
                sin_x *= sin_x;
            }
            result += equations.function.array[i][1] * sin_x; 
            break;
        case 3:
            // cosx a*cos(Bx)
            cos_x = cos(equations.function.array[i][3] * x);
            for(pow=1; pow < equations.function.array[i][2] ;pow++){
                // if exponent greater than 1, we will multiply x by itself otherwise do nothing because we have already calculate cos() once
                cos_x *= cos_x;
            }
            result += equations.function.array[i][1] * cos_x; 
            break;      
        }
    }
	return result;
}

double rungeKuttaMethod(ODE equations, double x, double y,double *stepsize){
    // A.y' + B.y + f(x) = 0 
    // y'= (- B.yi - f(x) ) /A
    double h,ynew=y , targetValue,k1,k2,k3,k4;
    double A = equations.a1 , B = equations.a2;
    int i=0,iter;
    printf("Enter the step size (h): ");
    scanf("%lf",&h);
    *stepsize = h;
    printf("Enter the target value (x) : ");
    scanf("%lf",&targetValue);
    printf("\n-------------\n");
    
    if(targetValue < x){
        h *= -1;
    }
    iter = (int)((targetValue - x)/h);
    for(i=0 ; i < iter; i++){
        y = ynew;
        k1 = ( -( B*y + calculateFx(equations, x) ) ) / A;
        k2 = ( -(B*(y+ (0.5*k1*h)) + calculateFx(equations, (x+ 0.5*h))) ) / A;
        k3 = ( -(B*(y+ (0.5*k2*h)) + calculateFx(equations, (x+ 0.5*h))) ) / A;
        k4 = ( -(B*(y+ (k3*h)) + calculateFx(equations, (x+h))) ) / A;
    
        printf("k1 = %lf\tk2 = %lf\tk3 = %lf\tk4 = %lf\n",k1,k2,k3,k4);
        // y(xi + h) = y(xi) + 1/6(k1 + 2*k2 +2*k3+k4)*h
        ynew = y + ( (1.0/6.0)*h*(k1 + 2*k2 +2*k3+k4));

        x +=h;
        printf("iter #%d\ty(%lf) = %lf\n\n",i+1,x,ynew);
    }
    
    return ynew;
}

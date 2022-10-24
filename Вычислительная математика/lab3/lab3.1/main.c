#include "cmath.h"

int f(n, x, y, dydx)
int    n;
double x, y[], dydx[];
{
    dydx[0] = -40.0 * y[0] + 260.0 * y[1] + 1 / (10.0 * x * x + 1);
    dydx[1] = 30.0 * y[0] - 270.0 * y[1] + exp(-2 * x);
    return (0);
}

double adams1(double x, double y0, double y1)
{
    return -40.0 * y0 + 260.0 * y1 + 1 / (10 * x * x + 1);
}

double adams2(double x, double y0, double y1)
{
    return 30.0 * y0 - 270 * y1 + exp(-2 * x);
}

rkf()
{
    int f(), nfe, fail, step;
    int n = 2;
    int flag = 1;
    int maxfe = 5000;
    
    double h, x1, x2;
    double relerr = 1.0e-4;
    double abserr = 1.0e-4;
    double y[2], yp[2];

    rkfinit(n, &fail);

    if (fail == 0)
    {
        y[0] = 0.0;
        y[1] = 1.0;

        printf("\n                 RKF45\n");
        printf("------------|------------|------------\n");
        printf("      x     |    y[0]    |    y[1]\n");
        printf("------------|------------|------------\n");

        for (step = 1; step <= 0.4 / 0.02; step++)
        {
            x2 = 0.02 * step;
            x1 = x2 - 0.02;
            
            rkf45(f, n, y, yp, &x1, x2, &relerr, abserr, &h, &nfe, maxfe, &flag);
            printf("%10.6f  |%10.6f  |%10.6f \n", x1, y[0], y[1]);
            
            if (flag != 2)
            {
                printf("%s\n", cmathmsg(RKF45_C, flag));
                break;
            }
        }

        rkfend();
    }

    return (0);
}

adams(double shag)
{
    int f(), nfe, fail, step;
    int n = 2;
    int flag = 1;
    int maxfe = 5000;
    
    double  h, x1, x2;
    double relerr = 1.0e-4;
    double abserr = 1.0e-4;
    double  y[2], yp[2];

    rkfinit(n, &fail);

    if (fail == 0)
    {
        y[0] = 0.0;
        y[1] = 1.0;

        if (shag > 1.0e-3)
        {
            printf("\n             ADAMS(%.3f)\n", shag);
        }
        else
        {
            printf("\n             ADAMS(%.5f)\n", shag);
        }

        printf("------------|------------|------------\n");
        printf("      x     |    y[0]    |    y[1]\n");
        printf("------------|------------|------------\n");

        x2 = shag;
        x1 = x2 - shag;
        
        rkf45(f, n, y, yp, &x1, x2, &relerr, abserr,
            &h, &nfe, maxfe, &flag);

        rkf45(f, n, y, yp, &x1, x2, &relerr, abserr,
            &h, &nfe, maxfe, &flag);

        //метод Адамса
        x2 = shag * 4;
        for (step = 4; step <= (0.4 / shag + 1); ++step)
        {
            x2 = shag * step;
            x1 = x2 - shag;

            y[0] = y[0] + shag * (23 * adams1(x2, y[0], y[1]) - 16 * adams1(x2 - shag, y[0], y[1]) + 5 * adams1(x2 - 2 * shag, y[0], y[1])) / 12;
            y[1] = y[1] + shag*(23 * adams2(x2, y[0], y[1]) - 16 * adams2(x2 - shag, y[0], y[1]) + 5 * adams2(x2 - 2 * shag, y[0], y[1])) / 12;

            if (shag > 1.0e-3)
            {
                if (step % 10 - 1 == 0)
                {
                    printf("%10.6f  |%10.6f  |%10.6f \n", x1, y[0], y[1]);
                }
            }
            else
            {
                if (step % 1000 - 1 == 0)
                {
                    printf("%10.6f  |%10.6f  |%10.6f \n", x1, y[0], y[1]);
                }
            }
                
        }
 
        rkfend();
    }

    return (0);
}

main()
{
    rkf();
    adams(0.002);
    adams(0.00002);
    return (0);
}

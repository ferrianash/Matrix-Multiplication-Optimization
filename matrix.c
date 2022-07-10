#include <stdlib.h>
#define V1
#ifdef V1
void matrix(double *a, double *b, double *c, long n)
{
   long i, j, k;

   for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            for(k = 0; k < n; k++)
                c[i*n+j] += a[i*n+k]*b[k*n+j];
}
#endif

#ifdef V2
void matrix(double *a, double *b, double *c, long n)
{
    long i, j, k;
    for (i = 0; i < n; i++){
        for(k = 0; k < n; k++){
            for (j = 0; j < n; j++){
                c[i*n+j] += a[i*n+k] * b[k*n+j];
            }
        }
    }
}
#endif

#ifdef V3
void matrix(double *a, double *b, double *c, long n)
{
    long i, j, k;
    double t1;
    for (i = 0; i < n; i++){
        for(k = 0; k < n; k++){
            t1 = a[i*n+k];
            for (j = 0; j < n; j++){
                c[i*n+j] += t1 * b[k*n+j];
            }
        }
    }
}
#endif

#ifdef V4
void matrix(double *a, double *b, double *c, long n)
{
    long i, j, k;
    long in, kn;
    double t1;
    for (i = 0; i < n; i++){
        in = i *n;
        for(k = 0; k < n; k++){
            t1 = a[in+k];
            kn = k *n;
            for (j = 0; j < n; j++){
                c[in+j] += t1 * b[kn+j];
            }
        }
    }
}
#endif

#ifdef V5
void matrix(double *a, double *b, double *c, long n)
{
    long i, j, k;
    double t1, t2, t3, t4, t0;
    for (i = 0; i < n; i += 4){
        for(k = 0; k < n; k++){
            t1 = a[i*n+k];
            t2 = a[(i+1)*n+k];
            t3 = a[(i+2)*n+k];
            t4 = a[(i+3)*n+k];
            for (j = 0; j < n; j++){
                c[i*n+j] += t1 * b[k*n+j];
                c[(i+1)*n+j] += t2 * b[k*n+j];
                c[(i+2)*n+j] += t3 * b[k*n+j];
                c[(i+3)*n+j] += t4 * b[k*n+j];
            }
        }
    }
}
#endif

#ifdef V6
void matrix(double *a, double *b, double *c, long n)
{
    long i, j, k;
    double t1, t2, t3, t4, t0;
    long in1, in2, in3, in4;
    for (i = 0; i < n; i += 4){
        for(k = 0; k < n; k++){
            in1 = i*n;
            in2 = in1 + n;
            in3 = in2 + n;
            in4 = in3 + n;
            t1 = a[in1+k];
            t2 = a[in2+k];
            t3 = a[in3+k];
            t4 = a[in4+k];
            for (j = 0; j < n; j++){
                c[in1+j] += t1 * b[k*n+j];
                c[in2+j] += t2 * b[k*n+j];
                c[in3+j] += t3 * b[k*n+j];
                c[in4+j] += t4 * b[k*n+j];
            }
        }
    }
}
#endif

#ifdef V7
void matrix(double *a, double *b, double *c, long n)
{
    // double *b2 = malloc(sizeof(double) * n * n);
    // for (int i = 0; i < n; i++){
    //     for (int j = 0; j < n; j++){
    //         b2[i*n+j] = b[j*n+i];
    //     }
    // }
    long i, j, k;
    double t1, t2, t3, t4, t0;
    long in1, in2, in3, in4;
    for (i = 0; i < n; i += 2){
        for(k = 0; k < n; k++){
            in1 = i*n;
            in2 = in1 + n;
            t1 = a[in1+k];
            t2 = a[in2+k];
            for (j = 0; j < n; j++){
                t0 = b[k*n+j];
                c[in1+j] += t1 * t0;
                c[in2+j] += t2 * t0;
            }
        }
    }
}
#endif

#ifdef V9
void matrix(double *a, double *b, double *c, long n)
{
    if n <= 0 goto END;
    i = 0;
    do{
        k = 0;
        do{
            j = 0;
            t1 = a[i*n+k];
            t2 = a[(i+1)*n+k];
            t3 = a[(i+2)*n+k];
            t4 = a[(i+3)*n+k];
            do{
                t0 = b[k*n+j];
                c[i*n+j] += t1 * t0;
                c[(i+1)*n+j] += t2 *t0;
                c[(i+2)*n+j] += t3 *t0;
                c[(i+3)*n+j] += t4 *t0;
                j++;
            } while (j < n);
            k += 4;
        } while (k < n);
        i++;
    } while (i < n);

    i = 0;
L1:
    k = 0;
L2:
    s6 = k * n;
    s1 = i * n;
    s2 = s1 + n;
    s3 = s2 + n;
    s4 = s3 + n;

    s5 = s1 + k;
    t1 = a[s5];
    s5 = s5 + n;
    t2 = a[s5];
    s5 = s5 + n;
    t3 = a[s5];
    s5 = s5 + n;
    t4 = a[s5];
    
    j = 0;
L3:
    t0 = b[s6];
    c[s1] = c[s1] + t1 * t0;
    c[s2] = c[s2] + t2 * t0;
    c[s3] = c[s3] + t3 * t0;
    c[s4] = c[s4] + t4 * t0;

    // s1 = s1 + 2;
    // s2 = s2 + 2;
    // s3 = s3 + 2;
    // s4 = s4 + 2;
    // s6 = s6 + 2;
    j = j + 2;
    if j < n goto L3;
    k = k + 4;
    if k < n goto L2;
    i = i + 1;
    if i < n goto L1;

END:
    return;
}
#endif

#ifdef V8
void matrix(double *a, double *b, double *c, long n)
{
    long i, j, k, r;
    double t1, t2, t3, t4, t0;
    // long in1, in2, in3, in4;
    long s1, s2;
    for (i = 0; i < n; i += 8){
        for(k = 0; k < n; k++){
            for (j = 0; j < n; j++){
                t1 = b[k*n+j];
                s1 = i*n+j;
                for (r = 0; r < 8; r++){
                    c[s1] += a[s1+k-j] * t1;
                    s1 += n;
                }
            }
        }
    }
}
#endif

#ifdef V10
void matrix(double *a, double *b, double *c, long n)
{
    long i, j, k;
    double t1, t2, t3, t4, t0;
    long in1, in2, in3, in4;
    long inj1, inj2, inj3, inj4;
    for (i = 0; i < n; i += 4){
        for(k = 0; k < n; k++){
            in1 = i*n;
            in2 = in1 + n;
            in3 = in2 + n;
            in4 = in3 + n;
            t1 = a[in1+k];
            t2 = a[in2+k];
            t3 = a[in3+k];
            t4 = a[in4+k];
            for (j = 0; j < n; j++){
                t0 = b[k*n+j];
                inj1 = in1 + j;
                inj2 = in2 + j;
                inj3 = in3 + j;
                inj4 = in4 + j;
                c[inj1] += t1 * t0;
                c[inj2] += t2 * t0;
                c[inj3] += t3 * t0;
                c[inj4] += t4 * t0;
            }
        }
    }
}
#endif

#ifdef V11
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    for (int i = 0; i < n; i+=4){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            double t2 = 0;
            double t3 = 0;
            double t4 = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            for (int k = 0; k < n; k++){
                double t0 = b2[j*n+k];
                long ink1 = in1 + k;
                long ink2 = in2 + k;
                long ink3 = in3 + k;
                long ink4 = in4 + k;
                t1 += a[ink1] * t0;
                t2 += a[ink2] * t0;
                t3 += a[ink3] * t0;
                t4 += a[ink4] * t0;
            }
            c[in1 + j] = t1;
            c[in2 + j] = t2;
            c[in3 + j] = t3;
            c[in4 + j] = t4;
        }
    }
}
#endif

#ifdef V12
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    int i;
    for (i = 0; i < n; i+=8){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            double t2 = 0;
            double t3 = 0;
            double t4 = 0;
            double t5 = 0;
            double t6 = 0;
            double t7 = 0;
            double t8 = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            long in5 = in4 + n;
            long in6 = in5 + n;
            long in7 = in6 + n;
            long in8 = in7 + n;
            for (int k = 0; k < n; k++){
                double t0 = b2[j*n+k];
                t1 += a[in1++] * t0;
                t2 += a[in2++] * t0;
                t3 += a[in3++] * t0;
                t4 += a[in4++] * t0;
                t5 += a[in5++] * t0;
                t6 += a[in6++] * t0;
                t7 += a[in7++] * t0;
                t8 += a[in8++] * t0;
            }
            c[in1 - n + j] = t1;
            c[in2 - n + j] = t2;
            c[in3 - n + j] = t3;
            c[in4 - n + j] = t4;
            c[in5 - n + j] = t5;
            c[in6 - n + j] = t6;
            c[in7 - n + j] = t7;
            c[in8 - n + j] = t8;
        }
    }
    for (;i < n; i++){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            long in1 = i*n;
            long jn = j*n;
            for (int k = 0; k < n; k++){
                double t0 = b2[jn+k];
                t1 += a[in1 + k] * t0;
            }
            c[in1 + j] = t1;
            // c[in1] = t1;
            // for (int k = 0; k < n; k++){
            //     c[i*n+j] += a[i*n+k] * b[j*n+k];
            // }
        }
    }
}
#endif

#ifdef V13
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    int i;
    for (i = 0; i + 5 < n; i+=6){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            double t2 = 0;
            double t3 = 0;
            double t4 = 0;
            double t5 = 0;
            double t6 = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            long in5 = in4 + n;
            long in6 = in5 + n;
            long jn = j * n;
            for (int k = 0; k < n; k++){
                double t0 = b2[jn+k];
                long ink1 = in1 + k;
                long ink2 = in2 + k;
                long ink3 = in3 + k;
                long ink4 = in4 + k;
                long ink5 = in5 + k;
                long ink6 = in6 + k;
                t1 += a[ink1] * t0;
                t2 += a[ink2] * t0;
                t3 += a[ink3] * t0;
                t4 += a[ink4] * t0;
                t5 += a[ink5] * t0;
                t6 += a[ink6] * t0;
            }
            c[in1 + j] = t1;
            c[in2 + j] = t2;
            c[in3 + j] = t3;
            c[in4 + j] = t4;
            c[in5 + j] = t5;
            c[in6 + j] = t6;
        }
    }
    for (;i < n; i++){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            long in1 = i*n;
            long jn = j*n;
            for (int k = 0; k < n; k++){
                double t0 = b2[jn+k];
                t1 += a[in1 + k] * t0;
            }
            c[in1 + j] = t1;
            // c[in1] = t1;
            // for (int k = 0; k < n; k++){
            //     c[i*n+j] += a[i*n+k] * b[j*n+k];
            // }
        }
    }
}
#endif

#ifdef V14
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    int i;
    for (i = 0; i + 5 < n; i+=6){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            double t2 = 0;
            double t3 = 0;
            double t4 = 0;
            double t5 = 0;
            double t6 = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            long in5 = in4 + n;
            long in6 = in5 + n;
            long jn = j * n;
            for (int k = 0; k < n; k++){
                double t0 = b2[jn+k];
                t1 += a[in1++] * t0;
                t2 += a[in2++] * t0;
                t3 += a[in3++] * t0;
                t4 += a[in4++] * t0;
                t5 += a[in5++] * t0;
                t6 += a[in6++] * t0;
            }
            c[in1 - n + j] = t1;
            c[in2 - n + j] = t2;
            c[in3 - n + j] = t3;
            c[in4 - n + j] = t4;
            c[in5 - n + j] = t5;
            c[in6 - n + j] = t6;
        }
    }
    for (;i < n; i++){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            long in1 = i*n;
            for (int k = 0; k < n; k++){
                double t0 = b2[j*n+k];
                t1 += a[in1 + k] * t0;
            }
            c[in1 + j] = t1;
            // c[in1] = t1;
            // for (int k = 0; k < n; k++){
            //     c[i*n+j] += a[i*n+k] * b[j*n+k];
            // }
        }
    }
}
#endif

#ifdef V15
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    for (int i = 0; i < n; i+=4){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            double t2 = 0;
            double t3 = 0;
            double t4 = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            for (int k = 0; k < n; k++){
                double t0 = b2[j*n+k];
                t1 += a[in1++] * t0;
                t2 += a[in2++] * t0;
                t3 += a[in3++] * t0;
                t4 += a[in4++] * t0;
            }
            c[in1 - n + j] = t1;
            c[in2 - n + j] = t2;
            c[in3 - n + j] = t3;
            c[in4 - n + j] = t4;
        }
    }
}
#endif

#ifdef V16
void matrix(double *a, double *b, double *c, long n)
{
    long i, j, k;
    double t1, t2, t3, t4, t0;
    long in1, in2, in3, in4;
    long inj1, inj2, inj3, inj4;
    for (i = 0; i < n; i += 4){
        for(k = 0; k < n; k++){
            in1 = i*n;
            in2 = in1 + n;
            in3 = in2 + n;
            in4 = in3 + n;
            t1 = a[in1+k];
            t2 = a[in2+k];
            t3 = a[in3+k];
            t4 = a[in4+k];
            for (j = 0; j < n; j++){
                t0 = b[k*n+j];
                c[in1++] += t1 * t0;
                c[in2++] += t2 * t0;
                c[in3++] += t3 * t0;
                c[in4++] += t4 * t0;
            }
        }
    }
}
#endif

#ifdef V17
void matrix(double *a, double *b, double *c, long n)
{
    long i, j, k;
    for (i = 0; i + 5 < n; i += 6){
        for(k = 0; k < n; k++){
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            long in5 = in4 + n;
            long in6 = in5 + n;
            double t1 = a[in1+k];
            double t2 = a[in2+k];
            double t3 = a[in3+k];
            double t4 = a[in4+k];
            double t5 = a[in5+k];
            double t6 = a[in6+k];
            for (j = 0; j < n; j++){
                double t0 = b[k*n+j];
                c[in1++] += t1 * t0;
                c[in2++] += t2 * t0;
                c[in3++] += t3 * t0;
                c[in4++] += t4 * t0;
                c[in5++] += t5 * t0;
                c[in6++] += t6 * t0;
            }
        }
    }
    for (; i < n; i++){
        for(k = 0; k < n; k++){
            long in1 = i*n;
            double t1 = a[in1+k];
            for (j = 0; j < n; j++){
                double t0 = b[k*n+j];
                c[in1++] += t1 * t0;
            }
        }
    }
}
#endif

#ifdef V18
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    int i;
    for (i = 0; i + 4 < n; i+=5){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            double t2 = 0;
            double t3 = 0;
            double t4 = 0;
            double t5 = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            long in5 = in4 + n;
            long jn = j * n;
            for (int k = 0; k < n; k++){
                double t0 = b2[jn+k];
                t1 += a[in1++] * t0;
                t2 += a[in2++] * t0;
                t3 += a[in3++] * t0;
                t4 += a[in4++] * t0;
                t5 += a[in5++] * t0;
            }
            c[in1 - n + j] = t1;
            c[in2 - n + j] = t2;
            c[in3 - n + j] = t3;
            c[in4 - n + j] = t4;
            c[in5 - n + j] = t5;
        }
    }
    for (;i < n; i++){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            long in1 = i*n;
            for (int k = 0; k < n; k++){
                double t0 = b2[j*n+k];
                t1 += a[in1 + k] * t0;
            }
            c[in1 + j] = t1;
        }
    }
}
#endif

#ifdef V19
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    int i;
    for (i = 0; i + 6 < n; i+=7){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            double t2 = 0;
            double t3 = 0;
            double t4 = 0;
            double t5 = 0;
            double t6 = 0;
            double t7 = 0;
            double t8 = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            long in5 = in4 + n;
            long in6 = in5 + n;
            long in7 = in6 + n;
            for (int k = 0; k < n; k++){
                double t0 = b2[j*n+k];
                t1 += a[in1++] * t0;
                t2 += a[in2++] * t0;
                t3 += a[in3++] * t0;
                t4 += a[in4++] * t0;
                t5 += a[in5++] * t0;
                t6 += a[in6++] * t0;
                t7 += a[in7++] * t0;
            }
            c[in1 - n + j] = t1;
            c[in2 - n + j] = t2;
            c[in3 - n + j] = t3;
            c[in4 - n + j] = t4;
            c[in5 - n + j] = t5;
            c[in6 - n + j] = t6;
            c[in7 - n + j] = t7;
        }
    }
    for (;i < n; i++){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            long in1 = i*n;
            for (int k = 0; k < n; k++){
                double t0 = b2[j*n+k];
                t1 += a[in1 + k] * t0;
            }
            c[in1 + j] = t1;
        }
    }
}
#endif

#ifdef V20
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    for (int i = 0; i < n; i+=4){
        for (int j = 0; j < n; j+=2){
            double t11 = 0;
            double t21 = 0;
            double t31 = 0;
            double t41 = 0;
            double t12 = 0;
            double t22 = 0;
            double t32 = 0;
            double t42 = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            long jn1 = j*n;
            long jn2 = jn1 + n;
            for (int k = 0; k < n; k++){
                double ta1 = a[in1++];
                double ta2 = a[in2++];
                double ta3 = a[in3++];
                double ta4 = a[in4++];
                double tb1 = b2[jn1++];
                double tb2 = b2[jn2++];
                t11 += ta1 * tb1;
                t21 += ta2 * tb1;
                t31 += ta3 * tb1;
                t41 += ta4 * tb1;
                t12 += ta1 * tb2;
                t22 += ta2 * tb2;
                t32 += ta3 * tb2;
                t42 += ta4 * tb2;
            }
            long off = j - n;
            c[in1 + off] = t11;
            c[in2 + off] = t21;
            c[in3 + off] = t31;
            c[in4 + off] = t41;
            off++;
            c[in1 + off] = t12;
            c[in2 + off] = t22;
            c[in3 + off] = t32;
            c[in4 + off] = t42;
        }
    }
}
#endif

#ifdef V21
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    for (int i = 0; i < n; i+=4){
        for (int j = 0; j < n; j+=2){
            double t11 = 0;
            double t21 = 0;
            double t31 = 0;
            double t41 = 0;
            double t12 = 0;
            double t22 = 0;
            double t32 = 0;
            double t42 = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            long jn1 = j*n;
            long jn2 = jn1 + n;
            for (int k = 0; k < n; k+=2){
                double ta1x = a[in1++];
                double ta1y = a[in1++];
                double ta2x = a[in2++];
                double ta2y = a[in2++];
                double ta3x = a[in3++];
                double ta3y = a[in3++];
                double ta4x = a[in4++];
                double ta4y = a[in4++];
                double tb1x = b2[jn1++];
                double tb1y = b2[jn1++];
                double tb2x = b2[jn2++];
                double tb2y = b2[jn2++];
                t11 += ta1x * tb1x + ta1y * tb1y;
                t21 += ta2x * tb1x + ta2y * tb1y;
                t31 += ta3x * tb1x + ta3y * tb1y;
                t41 += ta4x * tb1x + ta4y * tb1y;
                t12 += ta1x * tb2x + ta1y * tb2y;
                t22 += ta2x * tb2x + ta2y * tb2y;
                t32 += ta3x * tb2x + ta3y * tb2y;
                t42 += ta4x * tb2x + ta4y * tb2y;
            }
            long off = j - n;
            c[in1 + off] = t11;
            c[in2 + off] = t21;
            c[in3 + off] = t31;
            c[in4 + off] = t41;
            off++;
            c[in1 + off] = t12;
            c[in2 + off] = t22;
            c[in3 + off] = t32;
            c[in4 + off] = t42;
        }
    }
}
#endif

#ifdef V22
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    for (int i = 0; i < n; i+=2){
        for (int j = 0; j < n; j+=2){
            double t11 = 0;
            double t21 = 0;
            double t12 = 0;
            double t22 = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long jn1 = j*n;
            long jn2 = jn1 + n;
            for (int k = 0; k < n; k+=2){
                double ta1x = a[in1++];
                double ta1y = a[in1++];
                double ta2x = a[in2++];
                double ta2y = a[in2++];
                double tb1x = b2[jn1++];
                double tb1y = b2[jn1++];
                double tb2x = b2[jn2++];
                double tb2y = b2[jn2++];
                t11 += ta1x * tb1x + ta1y * tb1y;
                t21 += ta2x * tb1x + ta2y * tb1y;
                t12 += ta1x * tb2x + ta1y * tb2y;
                t22 += ta2x * tb2x + ta2y * tb2y;
            }
            long off = j - n;
            c[in1 + off] = t11;
            c[in2 + off] = t21;
            off++;
            c[in1 + off] = t12;
            c[in2 + off] = t22;
        }
    }
}
#endif

#ifdef V23
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    int i;
    for (i = 0; i + 5 < n; i+=6){
        for (int j = 0; j < n; j+=1){
            double t11x = 0;
            double t11y = 0;
            double t21x = 0;
            double t21y = 0;
            double t31x = 0;
            double t31y = 0;
            double t41x = 0;
            double t41y = 0;
            double t51x = 0;
            double t51y = 0;
            double t61x = 0;
            double t61y = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            long in5 = in4 + n;
            long in6 = in5 + n;
            long jn1 = j*n;
            for (int k = 0; k < n; k+=2){
                double ta1x = a[in1++];
                double ta1y = a[in1++];
                double ta2x = a[in2++];
                double ta2y = a[in2++];
                double ta3x = a[in3++];
                double ta3y = a[in3++];
                double ta4x = a[in4++];
                double ta4y = a[in4++];
                double ta5x = a[in5++];
                double ta5y = a[in5++];
                double ta6x = a[in6++];
                double ta6y = a[in6++];
                double tb1x = b2[jn1++];
                double tb1y = b2[jn1++];
                t11x += ta1x * tb1x;
                t11y += ta1y * tb1y;
                t21x += ta2x * tb1x;
                t21y += ta2y * tb1y;
                t31x += ta3x * tb1x;
                t31y += ta3y * tb1y;
                t41x += ta4x * tb1x;
                t41y += ta4y * tb1y;
                t51x += ta5x * tb1x;
                t51y += ta5y * tb1y;
                t61x += ta6x * tb1x;
                t61y += ta6y * tb1y;
            }
            long off = j - n;
            c[in1 + off] = t11x + t11y;
            c[in2 + off] = t21x + t21y;
            c[in3 + off] = t31x + t31y;
            c[in4 + off] = t41x + t41y;
            c[in5 + off] = t51x + t51y;
            c[in6 + off] = t61x + t61y;
        }
    }
    for (;i < n; i++){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            long in1 = i*n;
            for (int k = 0; k < n; k++){
                double t0 = b2[j*n+k];
                t1 += a[in1 + k] * t0;
            }
            c[in1 + j] = t1;
        }
    }
}
#endif

#ifdef V24
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            b2[i*n+j] = b[j*n+i];
        }
    }
    for (int i = 0; i < n; i+=4){
        for (int j = 0; j < n; j+=2){
            double t11x = 0;
            double t11y = 0;
            double t21x = 0;
            double t21y = 0;
            double t31x = 0;
            double t31y = 0;
            double t41x = 0;
            double t41y = 0;
            double t12x = 0;
            double t12y = 0;
            double t22x = 0;
            double t22y = 0;
            double t32x = 0;
            double t32y = 0;
            double t42x = 0;
            double t42y = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            long jn1 = j*n;
            long jn2 = jn1 + n;
            for (int k = 0; k < n; k+=2){
                double ta1x = a[in1++];
                double ta1y = a[in1++];
                double ta2x = a[in2++];
                double ta2y = a[in2++];
                double ta3x = a[in3++];
                double ta3y = a[in3++];
                double ta4x = a[in4++];
                double ta4y = a[in4++];
                double tb1x = b2[jn1++];
                double tb1y = b2[jn1++];
                double tb2x = b2[jn2++];
                double tb2y = b2[jn2++];
                t11x += ta1x * tb1x;
                t11y += ta1y * tb1y;
                t21x += ta2x * tb1x;
                t21y += ta2y * tb1y;
                t31x += ta3x * tb1x;
                t31y += ta3y * tb1y;
                t41x += ta4x * tb1x;
                t41y += ta4y * tb1y;
                t12x += ta1x * tb2x;
                t12y += ta1y * tb2y;
                t22x += ta2x * tb2x;
                t22y += ta2y * tb2y;
                t32x += ta3x * tb2x;
                t32y += ta3y * tb2y;
                t42x += ta4x * tb2x;
                t42y += ta4y * tb2y;
            }
            long off = j - n;
            c[in1 + off] = t11x + t11y;
            c[in2 + off] = t21x + t21y;
            c[in3 + off] = t31x + t31y;
            c[in4 + off] = t41x + t41y;
            off++;
            c[in1 + off] = t12x + t12y;
            c[in2 + off] = t22x + t22y;
            c[in3 + off] = t32x + t32y;
            c[in4 + off] = t42x + t42y;
        }
    }
}
#endif

#ifdef V25
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);

    // long inj = 0;
    // for (int i = 0; i < n; i++){
    //     long jni = i;
    //     for (int j = 0; j < n; j++){
    //         b2[inj++] = b[jni];
    //         jni += n;
    //     }
    // }

    long inj = 0;
    for (int i = 0; i < n; i++){
        long jni = i;
        for (int j = 0; j < n; j++){
            b2[inj++] = b[jni];
            jni += n;
        }
    }

    int i;
    for (i = 0; i + 3 < n; i+=4){
        for (int j = 0; j < n; j+=1){
            double t11x = 0;
            double t11y = 0;
            double t21x = 0;
            double t21y = 0;
            double t31x = 0;
            double t31y = 0;
            double t41x = 0;
            double t41y = 0;
            long in1 = i*n;
            long in2 = in1 + n;
            long in3 = in2 + n;
            long in4 = in3 + n;
            long jn1 = j*n;
            for (int k = 0; k < n; k+=2){
                double ta1x = a[in1++];
                double ta1y = a[in1++];
                double ta2x = a[in2++];
                double ta2y = a[in2++];
                double ta3x = a[in3++];
                double ta3y = a[in3++];
                double ta4x = a[in4++];
                double ta4y = a[in4++];
                double tb1x = b2[jn1++];
                double tb1y = b2[jn1++];
                t11x += ta1x * tb1x;
                t11y += ta1y * tb1y;
                t21x += ta2x * tb1x;
                t21y += ta2y * tb1y;
                t31x += ta3x * tb1x;
                t31y += ta3y * tb1y;
                t41x += ta4x * tb1x;
                t41y += ta4y * tb1y;
            }
            long off = j - n;
            c[in1 + off] = t11x + t11y;
            c[in2 + off] = t21x + t21y;
            c[in3 + off] = t31x + t31y;
            c[in4 + off] = t41x + t41y;
        }
    }
    for (;i < n; i++){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            long in1 = i*n;
            long jn1 = j*n;
            for (int k = 0; k < n; k++){
                double t0 = b2[jn1+k];
                t1 += a[in1 + k] * t0;
            }
            c[in1 + j] = t1;
        }
    }
}
#endif

#ifdef V25
void matrix(double *a, double *b, double *c, long n)
{
    double *b2 = malloc(sizeof(double) * n * n);

    long inj = 0;
    for (int i = 0; i < n; i++){
        long jni = i;
        for (int j = 0; j < n; j++){
            b2[inj++] = b[jni];
            jni += n;
        }
    }

    int i;
    for (i = 0; i + 3 < n; i+=4){
        for (int j = 0; j < n; j+=1){
            double t11x = 0;
            double t11y = 0;
            double t21x = 0;
            double t21y = 0;
            double t31x = 0;
            double t31y = 0;
            double t41x = 0;
            double t41y = 0;
            long *in1 = &a[i*n];
            long *in2 = in1 + n;
            long *in3 = in2 + n;
            long *in4 = in3 + n;
            long *jn1 = &b2[j*n];
            for (int k = 0; k + 1 < n; k+=2){
                double ta1x = in1[k];
                double ta1y = in1[k];
                double ta2x = in2[k];
                double ta2y = in2[k];
                double ta3x = in3[k];
                double ta3y = in3[k];
                double ta4x = in4[k];
                double ta4y = in4[k];
                double tb1x = jn1[k];
                double tb1y = jn1[k];
                t11x += ta1x * tb1x;
                t11y += ta1y * tb1y;
                t21x += ta2x * tb1x;
                t21y += ta2y * tb1y;
                t31x += ta3x * tb1x;
                t31y += ta3y * tb1y;
                t41x += ta4x * tb1x;
                t41y += ta4y * tb1y;
            }
            long *in1 = &c[i*n + j];
            long *in2 = in1 + n;
            long *in3 = in2 + n;
            long *in4 = in3 + n;
            *in1 = t11x + t11y;
            *in2 = t21x + t21y;
            *in3 = t31x + t31y;
            *in4 = t41x + t41y;
        }
    }
    for (;i < n; i++){
        for (int j = 0; j < n; j++){
            double t1 = 0;
            long in1 = i*n;
            long jn1 = j*n;
            for (int k = 0; k < n; k++){
                double t0 = b2[jn1+k];
                t1 += a[in1 + k] * t0;
            }
            c[in1 + j] = t1;
        }
    }
}
#endif
// C pseudocode of matrix.S
void matrix(double *a, double *b, double *c, long n){
    long i, j, k;
    if (n <= 0) return;

    // 矩阵转置，从b到b2
    double *b2 = (double*)malloc(8*n*n);
    double *b2in0 = b2;         // b2[i][0]
    double *b2in1 = &b2in0[n];  // b2[i+1][0]
    double *b2in2 = &b2in1[n];  // b2[i+2][0]
    double *b2in3 = &b2in2[n];  // b2[i+3][0]
    for (i = 0; i < n; i += 4){
        double *bjni = &b[j*n]; // b[j][0] 
        for (j = 0; j < n; j++){
            b2in0[j] = bjni[0]; // b2[i][j] = b[j][i];
            b2in1[j] = bjni[1]; // b2[i+1][j] = b[j][i+1];
            b2in2[j] = bjni[2]; // b2[i+2][j] = b[j][i+2];
            b2in3[j] = bjni[3]; // b2[i+3][j] = b[j][i+3];
            bjni = &bjni[n];
        }
        b2in0 = &b2in0[4*n];
        b2in1 = &b2in1[4*n];
        b2in2 = &b2in2[4*n];
        b2in3 = &b2in3[4*n];
    }

    if (n/2) goto REST;
    // 矩阵乘法的核心部分
    for (i = 0; i + 4 <= n; i += 4){
        for (j = 0; j < n; j++){
            xmm0 = xmm1 = xmm2 = xmm3 = 0;
            double *ain0 = &a[i*n];
            double *ain1 = &ain0[n];  
            double *ain2 = &ain1[n];
            double *ain3 = &ain2[n];
            double *b2jn = &b2[j*n];
            for (k = 0; k < n; k += 2){
                xmm4 = (ain0[k]:ain0[k+1]); // a[i][k]:a[i][k+1]
                xmm5 = (ain1[k]:ain1[k+1]); // a[i+1][k]:a[i+1][k+1]
                xmm6 = (ain2[k]:ain2[k+1]); // a[i+2][k]:a[i+2][k+1]
                xmm7 = (ain3[k]:ain3[k+1]); // a[i+3][k]:a[i+3][k+1]
                xmm8 = (b2jn[k]:b2jn[k+1]); // b[k][j]:b[k+1][j]

                xmm4 *= xmm8;
                xmm5 *= xmm8;
                xmm6 *= xmm8;
                xmm7 *= xmm8;

                xmm0 += xmm4;
                xmm1 += xmm5;
                xmm2 += xmm6;
                xmm3 += xmm7;
            }
            double *cin0j = &c[i*n+j]; // c[i][j]
            double *cin1j = &cin0j[n]; // c[i+1][j]
            double *cin2j = &cin1j[n]; // c[i+2][j]
            double *cin3j = &cin2j[n]; // c[i+3][j]
            cin0j[0] = xmm0.high + xmm0.low;
            cin1j[0] = xmm1.high + xmm1.low;
            cin2j[0] = xmm2.high + xmm2.low;
            cin3j[0] = xmm3.high + xmm3.low;
        }
    }

REST: 
    // 矩阵乘法的剩余部分，应对奇数矩阵规模的情况，
    // 或者模4余2的矩阵规模的最后两行的情况
    for (; i < n; i++){
        for (j = 0; j < n; j++){
            xmm2.low = 0;
            double *ain = &a[i*n];   // a[i][0]
            double *b2jn = &b2[j*n]; // b[0][j]
            for (k = 0; k < n; k++){
                xmm0.low = b2jn[k]; // b[k][j]
                xmm1.low = ain[k];  // a[i][k]
                xmm2.low += xmm0.low * xmm1.low;
            }
            c[i*n+j] = xmm2.low;
        }

    }

    free(b2);
}
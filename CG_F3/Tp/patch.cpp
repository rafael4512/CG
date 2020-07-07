#include "headers/patch.h"

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

    //Matriz M
static const double m[4][4] = {
    { -1, +3, -3, +1 },
    { +3, -6, +3, +0 },
    { -3, +3, +0, +0 },
    { +1, +0, +0, +0 }
};

void cross(double* a, double* b, double* res) {
    res[0] = a[1] * b[2] - a[2] * b[1];
    res[1] = a[2] * b[0] - a[0] * b[2];
    res[2] = a[0] * b[1] - a[1] * b[0];
}
//multiplica uma matriz por um vetor
double* crossMatrix(double a[4]) {
    double *res = (double*) malloc(sizeof(double) * 5);

    for (int i = 0; i < 4; ++i)
    {
        res[i] = 0;
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            res[i] += a[j] * m[j][i];
        }
    }

    return res;
}


void normalize(double* a) {
    float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
    if (l != 0) {
        a[0] = a[0] / l;
        a[1] = a[1] / l;
        a[2] = a[2] / l;
    }
    else {
        a[0] = 0;
        a[1] = 0;
        a[2] = 0;
    }
}

vector<double> calculateWithinCurve(double t, double mat[4][3]) {
    double x, y, z;

    double b[4];

    //vetor t
    b[0] = powf(t,3);
    b[1] = powf(t,2);
    b[2] = t;
    b[3] = 1;

    double* res;

    res = crossMatrix(b);

    //faz a multiplicação de dos vetor pela matriz recebida.
    x = res[0] * mat[0][0] + res[1] * mat[1][0] + res[2] * mat[2][0] + res[3] * mat[3][0];
    y = res[0] * mat[0][1] + res[1] * mat[1][1] + res[2] * mat[2][1] + res[3] * mat[3][1];
    z = res[0] * mat[0][2] + res[1] * mat[1][2] + res[2] * mat[2][2] + res[3] * mat[3][2];

    vector<double> p;

    p.push_back(x);
    p.push_back(y);
    p.push_back(z);
    
    return p;
}

vector<double> calculateWithinPatch(double u, double v, double mat[4][4][3]) {
    double finalCurveMatrix[4][3];
    double currentCurveMatrix[4][3];

    // Calculate curve of patch u

    for (int i = 0; i < 4; i++) {
        //lemos uma linha do teapot.patch
        for (int j = 0; j < 4; j++)
        {
            currentCurveMatrix[j][0] = mat[i][j][0];
            currentCurveMatrix[j][1] = mat[i][j][1];
            currentCurveMatrix[j][2] = mat[i][j][2];
        }
        
        vector<double> tmp = calculateWithinCurve(u, currentCurveMatrix);
        //calculamos os novos 4 pontos. 
        finalCurveMatrix[i][0] = tmp.at(0);
        finalCurveMatrix[i][1] = tmp.at(1);
        finalCurveMatrix[i][2] = tmp.at(2);
    }

    // Calculate curve of patch u
    return calculateWithinCurve(v, finalCurveMatrix);
}



vector<double> calculatePointsBezier(int tess, int noPatches, vector<double> patch_list) {
    int N = patch_list.size() / noPatches / 3;

    double passo = 1.0 / tess;
    double u1, u2, v1, v2;
    
    vector<double> pt1;
    vector<double> pt2;
    vector<double> pt3;
    vector<double> pt4;


    vector<double> res;
    for (int patch = 0; patch < noPatches; patch++) {
        double ptCtrl[4][4][3];

        // Ler pts de controlo de um 
        for (int p = 0; p < N; p++) {
            int pX, pY;
            pX = p / 4;
            pY = p % 4;

            ptCtrl[pX][pY][0] = patch_list.at(patch * N * 3 + p * 3);
            ptCtrl[pX][pY][1] = patch_list.at(patch * N * 3 + p * 3 + 1);
            ptCtrl[pX][pY][2] = patch_list.at(patch * N * 3 + p * 3 + 2);
        }
        
        for (int i = 0; i < tess; i++) {
            u1 = i * passo;
            u2 = (i + 1) * passo;
            
            for (int j = 0; j < tess; j++) {
                v1 = j * passo;
                v2 = (j + 1) * passo;

                pt1 = calculateWithinPatch(u1, v1, ptCtrl);
                pt2 = calculateWithinPatch(u1, v2, ptCtrl);
                pt3 = calculateWithinPatch(u2, v1, ptCtrl);
                pt4 = calculateWithinPatch(u2, v2, ptCtrl);


                res.push_back(pt3.at(0));
                res.push_back(pt3.at(1));
                res.push_back(pt3.at(2));
                
                res.push_back(pt4.at(0));
                res.push_back(pt4.at(1));
                res.push_back(pt4.at(2));

                res.push_back(pt2.at(0));
                res.push_back(pt2.at(1));
                res.push_back(pt2.at(2));


                res.push_back(pt1.at(0));
                res.push_back(pt1.at(1));
                res.push_back(pt1.at(2));

                res.push_back(pt3.at(0));
                res.push_back(pt3.at(1));
                res.push_back(pt3.at(2));
               
                res.push_back(pt2.at(0));
                res.push_back(pt2.at(1));
                res.push_back(pt2.at(2));
            }
        }
    }
    
    return res;
}

float getBezierTangentPointForU(double u, double v, double p[4][4]) {
    float res = 0;
    float UM[4];
    float UMP[4];
    float UMPM[4];

    for (int i = 0; i < 4; i++)
    {
        UM[i] = (3 * powf(u, 2.0) * m[0][i]) + (2 * u * m[1][i]) + (1 * m[2][i]);
    }

    for (int i = 0; i < 4; i++) {
        UMP[i] = (UM[0] * p[0][i]) + (UM[1] * p[1][i]) + (UM[2] * p[2][i]) + (UM[3] * p[3][i]);
    }

    for (int i = 0; i < 4; i++) {
        UMPM[i] = (UMP[0] * m[0][i]) + (UMP[1] * m[1][i]) + (UMP[2] * m[2][i]) + (UMP[3] * m[3][i]);
    }

    res = UMPM[0] * powf(v, 3.0);
    res += UMPM[1] * powf(v, 2.0);
    res += UMPM[2] * v;
    res += UMPM[3];

    return res;
}

float getBezierTangentPointForV(double u, double v, double p[4][4]) {
    float res = 0;
    float UM[4];
    float UMP[4];
    float UMPM[4];

    for (int i = 0; i < 4; i++)
    {
        UM[i] = (3 * powf(u, 2.0) * m[0][i]) + (2 * u * m[1][i]) + (1 * m[2][i]);
    }

    for (int i = 0; i < 4; i++) {
        UMP[i] = (UM[0] * p[0][i]) + (UM[1] * p[1][i]) + (UM[2] * p[2][i]) + (UM[3] * p[3][i]);
    }

    for (int i = 0; i < 4; i++) {
        UMPM[i] = (UMP[0] * m[0][i]) + (UMP[1] * m[1][i]) + (UMP[2] * m[2][i]) + (UMP[3] * m[3][i]);
    }

    res = UMPM[0] * (3 * powf(v, 2.0));
    res += UMPM[1] * (2 * v);
    res += UMPM[2];

    return res;
}

vector<double> calculateNormalBezier(int tess, int noPatches, vector<double> patch_list) {
    int N = patch_list.size() / noPatches / 3;

    double du[4][3], dv[4][3];
    double normal[4][3];

    double u1, u2, v1, v2;
    double passo = 1.0 / tess;

    vector<double> derivadas;
    for (int patch = 0; patch < noPatches; patch++) {
        double ptCtrl[3][4][4];

        // Ler pts de controlo
        for (int p = 0; p < N; p++) {
            int pX, pY;
            pX = p / 4;
            pY = p % 4;
            
            ptCtrl[0][pX][pY] = patch_list.at(patch * N * 3 + p * 3);
            ptCtrl[1][pX][pY] = patch_list.at(patch * N * 3 + p * 3 + 1);
            ptCtrl[2][pX][pY] = patch_list.at(patch * N * 3 + p * 3 + 2);
        }

        for (int i = 0; i < tess; i++) {
            for (int j = 0; j < tess; j++) {
                u1 = i * passo;
                u2 = (i + 1) * passo;
                v1 = j * passo;
                v2 = (j + 1) * passo;

                // px == ptCtrl[0] py == [1]
                du[0][0] = getBezierTangentPointForU(u1, v1, ptCtrl[0]);
                du[0][1] = getBezierTangentPointForU(u1, v1, ptCtrl[1]);
                du[0][2] = getBezierTangentPointForU(u1, v1, ptCtrl[2]);

                dv[0][0] = getBezierTangentPointForV(u1, v1, ptCtrl[0]);
                dv[0][1] = getBezierTangentPointForV(u1, v1, ptCtrl[1]);
                dv[0][2] = getBezierTangentPointForV(u1, v1, ptCtrl[2]);

                du[1][0] = getBezierTangentPointForU(u1, v2, ptCtrl[0]);
                du[1][1] = getBezierTangentPointForU(u1, v2, ptCtrl[1]);
                du[1][2] = getBezierTangentPointForU(u1, v2, ptCtrl[2]);

                dv[1][0] = getBezierTangentPointForV(u1, v2, ptCtrl[0]);
                dv[1][1] = getBezierTangentPointForV(u1, v2, ptCtrl[1]);
                dv[1][2] = getBezierTangentPointForV(u1, v2, ptCtrl[2]);

                du[2][0] = getBezierTangentPointForU(u2, v1, ptCtrl[0]);
                du[2][1] = getBezierTangentPointForU(u2, v1, ptCtrl[1]);
                du[2][2] = getBezierTangentPointForU(u2, v1, ptCtrl[2]);

                dv[2][0] = getBezierTangentPointForV(u2, v1, ptCtrl[0]);
                dv[2][1] = getBezierTangentPointForV(u2, v1, ptCtrl[1]);
                dv[2][2] = getBezierTangentPointForV(u2, v1, ptCtrl[2]);

                du[3][0] = getBezierTangentPointForU(u2, v2, ptCtrl[0]);
                du[3][1] = getBezierTangentPointForU(u2, v2, ptCtrl[1]);
                du[3][2] = getBezierTangentPointForU(u2, v2, ptCtrl[2]);

                dv[3][0] = getBezierTangentPointForV(u2, v2, ptCtrl[0]);
                dv[3][1] = getBezierTangentPointForV(u2, v2, ptCtrl[1]);
                dv[3][2] = getBezierTangentPointForV(u2, v2, ptCtrl[2]);

                normalize(du[0]);
                normalize(dv[0]);
                normalize(du[1]);
                normalize(dv[1]);
                normalize(du[2]);
                normalize(dv[2]);
                normalize(du[3]);
                normalize(dv[3]);

                cross(du[0], dv[0], normal[0]);
                cross(du[1], dv[1], normal[1]);
                cross(du[2], dv[2], normal[2]);
                cross(du[3], dv[3], normal[3]);

                derivadas.push_back(normal[0][0]);
                derivadas.push_back(normal[0][1]);
                derivadas.push_back(normal[0][2]);

                derivadas.push_back(normal[2][0]);
                derivadas.push_back(normal[2][1]);
                derivadas.push_back(normal[2][2]);
                
                derivadas.push_back(normal[3][0]);
                derivadas.push_back(normal[3][1]);
                derivadas.push_back(normal[3][2]);
            
                derivadas.push_back(normal[0][0]);
                derivadas.push_back(normal[0][1]);
                derivadas.push_back(normal[0][2]);

                derivadas.push_back(normal[3][0]);
                derivadas.push_back(normal[3][1]);
                derivadas.push_back(normal[3][2]);

                derivadas.push_back(normal[1][0]);
                derivadas.push_back(normal[1][1]);
                derivadas.push_back(normal[1][2]);
            }
        }
    }

    return derivadas;
}

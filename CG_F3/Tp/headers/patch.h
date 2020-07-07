#ifndef __PATCH_H__
#define __PATCH_H__

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std; 

vector<double> calculatePointsBezier(int tess, int noPatches, vector<double> patch_list);
vector<double> calculateNormalBezier(int tess, int noPatches, vector<double> patch_list);

#endif
#ifndef DATARESOURCES_H
#define DATARESOURCES_H

#include "WPILib.h"
#include <vector>
using namespace std;

typedef struct {
    string id;
    double* value;
} NumData;

typedef struct {
    string id;
    string* value;
} StringData;

typedef struct {
    string id;
    bool* value;
} BoolData;

typedef struct {
    string id;
    PIDSource* source;
} SensorData;

typedef struct {
    vector<NumData> nums;
    vector<StringData> strings;
    vector<BoolData> bools;
    vector<SensorData> sensors;
} ResourcePackage;

#endif // DATARESOURCES_H

#include <cmath>
#include <cstdint>
#include <cstring>

using namespace std;

float outNumF = 0;
int outNum = 0;

struct pythF
{
    float O;
    float A;
    float AO;
    float out;
};

struct pyth
{
    int O;
    int A;
    int AO;
    int out;
};

pythF pyF;
pyth py;

void math_Init() {
    pyF.O = 0;
    pyF.A = 0;
    pyF.AO = 0;
    pyF.out = 0;

    py.O = 0;
    py.A = 0;
    py.AO = 0;
    py.out = 0;
}

void reset() {
    pyF.O = 0;
    pyF.A = 0;
    pyF.AO = 0;
    pyF.out = 0;

    py.O = 0;
    py.A = 0;
    py.AO = 0;
    py.out = 0;
}

float get_sqrF(float num) {
    outNumF = sqrt(num);

    return outNumF;
}

int get_sqr(float num) {
    outNum = sqrt(num);
    
    return outNum;
}

float pythagorasF(float o, float a) {
    reset();

    pyF.A = a*a;
    pyF.O = o*o;

    pyF.AO = pyF.A + pyF.O;

    pyF.out = sqrt(pyF.AO);

    return pyF.out;
}

int pythagoras(int o, int a) {
    reset();

    py.A = a*a;
    py.O = o*o;

    py.AO = py.A + py.O;

    py.out = sqrt(py.AO);

    return py.out;
}

float fast_sqrt(float x) { // This is not my code, why because i stoll it from Id software HEHE Quake III there code go brrrrrrrrrrrr
    if (x <= 0.0f) return 0.0f;

    float xhalf = 0.5f * x;
    std::int32_t i;
    std::memcpy(&i, &x, sizeof(float));
    i = 0x5f3759df - (i >> 1);
    std::memcpy(&x, &i, sizeof(float));

    x = x * (1.5f - xhalf * x * x);
    x = x * (1.5f - xhalf * x * x);

    return 1.0f / x;
}
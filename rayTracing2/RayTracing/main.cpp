#include <iostream>
#include <sstream>
#include "tracer.h"
using namespace std;

int main()
{
    Tracer* trac;
    trac = new Tracer();
    trac->makeScene();
    return 0;
}

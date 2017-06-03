#ifndef TRACER_H
#define TRACER_H
#include <fstream>
#include <sstream>
#include "vec.h"
#include "object.h"
#include "light.h"
#include "screen.h"
#include "image.h"
using namespace std;

class Tracer
{
    public:
        Tracer(stringstream* arq);
        Tracer(){_scene = false;}
        void makeScene();
        void newScene(stringstream* arq);
        Image* render();
    protected:
        Vec render(int i, int j);
        int intersect(Vec o, Vec d, Vec& p, unit min);
        Vec objCol(Vec o, Vec p, int obj, int r);
        Vec diffSpec(Vec o, Vec p, int obj, Vec& spec);
        Vec refCol(Vec o, Vec p, Vec n, int r);
        Vec fraCol(Vec o, Vec p, int obj, int r, unit& fra, unit& ref);
        Vec reflected(Vec i, Vec n);
        Vec refracted(Vec i, Vec n, unit n1, unit n2, unit& fra, unit& ref);
        Vec bisector(Vec v, Vec l);
        unit min(unit a, unit b);
    private:
        void deleteScene();
        void saveScene(string s);
        void buildScene();
        void modScene();
		void editLight();
		void editObj();
        Screen _scr;					//screen
        int _nlight;					//number of light sources
        Light** _li;					//light source array
        Vec _totalinten;				//total light intensity
        int _nobj;						//number of objects
        Object** _obj;					//object array
        Vec _obs;						//observer coordinates
        unit _amb;						//ambient light factor
        int _ref;						//maximum number of reflections
        unit _n0;						//air refraction index
        int _ssample;					//supersampling factor
        bool _scene;                     //Whether the scene is defined
};

#endif // TRACER_H

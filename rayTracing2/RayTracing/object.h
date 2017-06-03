#ifndef OBJECT_H
#define OBJECT_H
#include <sstream>
#include "vec.h"
#include <exception>
#include <iostream>
using namespace std;

class Object
{
    public:
    protected:
        Object() {}
        virtual ~Object() throw() {}
        virtual Vec normal(Vec o, Vec p) = 0;
		//Returns vector normal to point p, with ray source o
        virtual Vec intersect(Vec o, Vec d) = 0;
		//Returns point on object surface where the ray od intersects object
		//Must return o if it does not intersect
        virtual Vec colour(Vec p) = 0;
		//Returns colour of object on point p
        virtual unit ref(Vec p) = 0;
		//Returns reflectance on point p
        virtual unit spec(Vec p) = 0;
		//Returns specular coefficient on point p
        virtual unit shiny(Vec p) = 0;
		//Returns shininess of point p
        virtual unit n2(Vec p) = 0;
		//Returns refraction index on point p
        virtual unit fra(Vec p) = 0;
		//Returns refractance proportion on point p
        virtual bool entering(Vec o, Vec p) = 0;
		//Verifies whether ray op is entering
        virtual void printDetails() = 0;
		//prints object details
        virtual string write() = 0;
        //returns string description of object
        virtual bool build() = 0;
        //builds object based on user input
        static int* hexToInt(stringstream* arquivo);
        static int* hexToInt(string s);
        unit abs(unit a) {return (a >= 0) ? a : -a;}
    private:
        static int hexToInt(char c);
    friend class Tracer;
    friend class Builder;
};

class Plane : public Object
{
    public:
    protected:
        Plane(stringstream* arq)
        {
            /*
			Standard plane input is
            px py pz nx ny nz
            where (px, py, pz) defines a point belonging to the plane
            and (nx, ny, nz) defines a vector normal to the plane
            */
            unit u[3];
            int i;
            for(i = 0; i < 3; i++)
                (*arq) >> u[i];
            _p0 = u;
            for(i = 0; i < 3; i++)
                (*arq) >> u[i];
            _normal = u;
            _normal.normalise();
            _pn = (_p0*_normal);
        }
        Plane() {}
        virtual Vec normal(Vec o, Vec p);
        virtual Vec intersect(Vec o, Vec d);
        virtual bool entering(Vec o, Vec p) {return true;}
        virtual unit n2(Vec p) {return 0;}
        virtual unit fra(Vec p) {return 0;}
		virtual bool build();
        Vec _p0;
        Vec _normal;
        unit _pn;
    private:
    friend class Builder;
};

class SimPlane : public Plane
{
    public:
    protected:
        SimPlane(stringstream* arq) : Plane(arq)
        {
            /*
            A simple plane's input is
            px py pz nx ny nz colour d r c s
			the first six numbers are exactly the same as the regular plane's
			colour must be a hexadecimal input (e.g.: FF00FF)
			d and r are the relative proportions of diffusion and reflection (no refraction on a plane)
			c is the specular coefficient
			s is the shininess
            */
            unit d, r;
            _colour = Vec(hexToInt(arq));
            (*arq) >> d;
            (*arq) >> r;
            _ref = r/(d + r);
            (*arq) >> _spec;
            if(_spec < 0 || _spec > 1)
                throw "Invalid specular coefficient. Must be between 0 and 1.\n";
            (*arq) >> _shiny;
			if (_shiny < 0)
				throw "Invalid shininess. Must be nonnegative.";
        }
        SimPlane() : Plane() {}
        virtual Vec colour(Vec v) {return _colour;}
        virtual unit ref(Vec v) {return _ref;}
        virtual unit spec(Vec p) {return _spec;}
        virtual unit shiny(Vec p) {return _shiny;}
        virtual void printDetails()
        {
            cout << "Simple plane." << endl << "  Point on plane: " << _p0 << endl << "  Normal vector: " << _normal << endl <<
            "  Colour: " << _colour.toHex() << endl << "  Reflection index: " << _ref << endl << "  Specular highlight index: " << _spec << endl <<
            "  Shininess: " << _shiny << endl;
        }
        virtual string write()
        {
            return ("0 " + to_string((double)_p0[0]) + " " + to_string((double)_p0[1]) + " " + to_string((double)_p0[2]) + " " +
            to_string((double)_normal[0]) + " " + to_string((double)_normal[1]) + " " + to_string((double)_normal[2]) + " " +
            _colour.toHex() + " " + to_string((double)(1 - _ref)) + " " + to_string((double)(_ref)) + " " + to_string((double)_spec) + " " +
            to_string((double)_shiny) + "\n");
        }
        virtual bool build();
    private:
        Vec _colour;
        unit _ref;
        unit _spec;
        unit _shiny;
    friend class Builder;
};

class Sphere : public Object
{
    public:
    protected:
        Sphere(stringstream* arq)
        {
            /*
			Standard sphere input
            x y z r
			(x, y, z) is the center and r is the radius
            */
            unit c[3];
            for(int i = 0; i < 3; i++)
                (*arq) >> c[i];
            _center = c;
            (*arq) >> _rad;
        }
        Sphere() {}
        virtual Vec normal(Vec o, Vec p);
        virtual Vec intersect(Vec o, Vec d);
        virtual bool entering(Vec o, Vec p);
		virtual bool build();
        Vec _center;
        unit _rad;
    private:
    friend class Builder;
};

class SimSphere : public Sphere
{
    public:
    protected:
        SimSphere(stringstream* arq) : Sphere(arq)
        {
            /*
			Simple sphere input is given by
            x y z r colour d r f c s n
            The first four are like a regular spheres
			Colour identifies sphere colour in hexadecimal (e.g.: FF00FF)
			d, r, and f are the relative proportions of diffusion, reflection, and refraction
			c is the specular coefficient
			s is the shininess
			n is the refractance index
            */
            unit d, r, f;
            _colour = Vec(hexToInt(arq));
            (*arq) >> d;
			if (d < 0)
				throw "Invalid diffuse reflection proportion. Must be nonnegative.\n";
            (*arq) >> r;
			if (r < 0)
				throw "Invalid mirror reflection proportion. Must be nonnegative.\n";
            (*arq) >> f;
			if (f < 0)
				throw "Invalid refracion proportion. Must be nonnegative.\n";
			if (d + r + f == 0)
				throw "Invalid proportion values. At least one of diffuse reflection, mirror reflection, or refraction proportion must be positive.\n";
            _ref = ((d + r) > 0) ? r / (d + r) : 0;
            _f = ((d + f) > 0) ? f/(d + f) : 0;
            (*arq) >> _spec;
            if(_spec < 0 || _spec > 1)
            {
                throw "Invalid specular coefficient. Must be between 0 and 1.\n";
            }
            (*arq) >> _shiny;
			if (_shiny < 0)
			{
				throw "Invalid shininess. Must be nonnegative.\n";
			}
            (*arq) >> _n;
			if (_n < 0)
				throw "Invalid refraction index. Must be positive.\n";
        }
        SimSphere() : Sphere() {}
        virtual Vec colour(Vec v) {return _colour;}
        virtual unit ref(Vec v) {return _ref;}
        virtual unit spec(Vec p) {return _spec;}
        virtual unit shiny(Vec p) {return _shiny;}
        virtual unit n2(Vec p) {return _n;}
        virtual unit fra(Vec p) {return _f;}
        virtual void printDetails()
        {
            cout << "Simple sphere." << endl << "  Center: " << _center << endl << "  Radius: " << _rad << endl <<
            "  Colour : " << _colour.toHex() << endl << "  Reflection index: " << _ref << endl << "  Specular highlight index: " << _spec << endl <<
            "  Shininess: " << _shiny << endl << "  Refraction index: " << _f << endl << "  Refractance: " << _n << endl;
        }
        virtual string write()
        {
            return ("1 " + to_string((double)_center[0]) + " " + to_string((double)_center[1]) + " " + to_string((double)_center[2]) + " " +
            to_string((double)_rad) + " " + _colour.toHex() + " " + to_string((double)(1 - _ref - _f)) + " " + to_string((double)_ref) + " " +
            to_string((double)_f) + " " + to_string((double)_spec) + " " + to_string((double)_shiny) + " " + to_string((double)_n) + "\n");
        }
        virtual bool build();
    private:
        Vec _colour;
        unit _ref;
        unit _spec;
        unit _shiny;
        unit _f;
        unit _n;
    friend class Builder;
};

/*
class Ellipsoid : public Object
{
    public:
    protected:
        Ellipsoid(stringstream* arq)
        {
            /*
            Um elipsoide orientado arbitrariamente e' definido por
            xc yc zc x0 y0 z0 x1 y1 z1 x2 y2 z2
            onde (xc, yc, zc) define o centro e
            [x0 y0 z0]
            [x1 y1 z1]
            [x2 y2 z2]
            e' uma matriz positive-definite que define a orientacao e eixos
			*//*
            unit c[3];
            (*arq) >> c[0];
            (*arq) >> c[1];
            (*arq) >> c[2];
            _center = c;
            (*arq) >> c[0];
            (*arq) >> c[1];
            (*arq) >> c[2];
            _A[0] = c;
            (*arq) >> c[0];
            (*arq) >> c[1];
            (*arq) >> c[2];
            _A[1] = c;
            (*arq) >> c[0];
            (*arq) >> c[1];
            (*arq) >> c[2];
            _A[2] = c;
        }
        virtual Vec normal(Vec o, Vec p);
        virtual Vec intersect(Vec o, Vec d);
        virtual bool entering(Vec o, Vec p);
    private:
        Vec _center;
        Vec _A[3];
    friend class Builder;
};*/

class Builder
{
    /*
	This is a static class whose purpose is object building
    */
    public:
    protected:
        static Object* build(stringstream* arquivo)
        {
            //This function builds objects based on file input
            int tipo;
            (*arquivo) >> tipo;
            switch (tipo)
            {
                case 0:
                    return (new SimPlane(arquivo));
                    break;
                case 1:
                    return (new SimSphere(arquivo));
                    break;
                default:
                    throw "Invalid object type.\n";
            }
        }

        static Object* make()
        {
            //This function creates objects based on user input
            int tipo;
            string s;
            Object* obj;
            while(true)
            {
                cout << "Possible objects:" << endl << "0 - Simple plane." << endl << "1 - Simple sphere." << endl << "Choose object type: ";
                cin >> s;
                if(s == "x")
                    return 0;
                tipo = atoi(s.c_str());
                switch(tipo)
                {
				case 0:
                        obj = new SimPlane();
                        if(!(obj->build()))
                        {
                            delete obj;
                            return 0;
                        }
                        return obj;
                        break;
                    case 1:
                        obj = new SimSphere();
                        if(!(obj->build()))
                        {
                            delete obj;
                            return 0;
                        }
                        return obj;
                        break;
                    default:
                        cout << "Invalid option. ";
                }
            }
        }
    private:
    friend class Tracer;
};

#endif // OBJECT_H

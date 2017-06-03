#ifndef LIGHT_H
#define LIGHT_H
#include <sstream>
#include <iostream>
#include "vec.h"
using namespace std;

class Light
{
    public:
    protected:
        Light() {}
        Light(stringstream* arq)
        {
            /*
			A light source input is given by
            x y z xi yi zi xs ys zs
            where (x, y, z) are the light source's coordinates
            (xi, yi, zi) is the diffuse intensity of light on each colour
            (xs, ys, zs) is the specular intensity of light on each colour
            */
            unit u[3];
            (*arq) >> u[0];
            (*arq) >> u[1];
            (*arq) >> u[2];
            _pos = u;
            (*arq) >> u[0];
            (*arq) >> u[1];
            (*arq) >> u[2];
            _int = u; 
			if (_int.null())
				throw "Invalid light source intensity (must be non-null).\n";
            (*arq) >> u[0];
            (*arq) >> u[1];
            (*arq) >> u[2];
            _spec = u;
        }
        Vec getPos() {return _pos;}
        Vec getInt() {return _int;}
        Vec getSpec() {return _spec;}
        friend ostream &operator<<(ostream &output, const Light &l )
        {
            output << "  Position: " << l._pos << endl << "  Intensity: " << l._int << endl << "  Specular highlights: " << l._spec << endl;
            return output;
        }
        string write()
        {
            return (to_string((double)_pos[0]) + " " + to_string((double)_pos[1]) + " " + to_string((double)_pos[2]) + " " +
                    to_string((double)_int[0]) + " " + to_string((double)_int[1]) + " " + to_string((double)_int[2]) + " " +
                    to_string((double)_spec[0]) + " " + to_string((double)_spec[1]) + " " + to_string((double)_spec[2]) + "\n");
        }
        bool build()
        {
            string s;
            unit u[3];
            cout << "Please input x coordinate of source position: ";
            cin >> s;
            if(s == "x")
                return false;
            u[0] = atof(s.c_str());
            cout << "Please input y coordinate of source position: ";
            cin >> s;
            if(s == "x")
                return false;
            u[1] = atof(s.c_str());
            cout << "Please input z coordinate of source position: ";
            cin >> s;
            if(s == "x")
                return false;
            u[2] = atof(s.c_str());
            _pos = u;

            while(true)
            {
                cout << "Please input red coordinate of source intensity: ";
                cin >> s;
                if(s == "x")
                    return false;
                u[0] = atof(s.c_str());
				cout << "Please input green coordinate of source intensity: ";
				cin >> s;
				if (s == "x")
					return false;
				u[1] = atof(s.c_str());
				cout << "Please input blue coordinate of source intensity: ";
				cin >> s;
				if (s == "x")
					return false;
				u[2] = atof(s.c_str());
				_int = u;
				if (!_int.null())
					break;
                cout << "Invalid input (must be a non-null vector)." << endl;
            }

            cout << "Please input red coordinate of source specular highlight intensity: ";
            cin >> s;
            if(s == "x")
                return false;
            u[0] = atof(s.c_str());

            cout << "Please input green coordinate of source specular highlight intensity: ";
            cin >> s;
            if(s == "x")
                return false;
            u[1] = atof(s.c_str());

            cout << "Please input blue coordinate of source specular highlight intensity: ";
            cin >> s;
            if(s == "x")
                return false;
            u[2] = atof(s.c_str());

            _spec = u;

            return true;
        }
    private:
        Vec _pos;
        Vec _int;
        Vec _spec;
    friend class Tracer;
};

#endif // LIGHT_H

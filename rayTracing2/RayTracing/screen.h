#ifndef SCREEN_H
#define SCREEN_H
#include <sstream>
#include <iostream>
#include <exception>
#include "vec.h"
using namespace std;

/*
This is the screen object
*/

class Screen
{
    public:
    protected:
        Screen() {}
        Screen(stringstream* arq)
        {
            /*
			Screen data is given by
            xp yp zp xw yw zw xh yh zh w h
            (xp, yp, zp) indicates starting vertex
            (xw, yw, zw) indicates a horizontal vector to the right
            (xh, yh, zh) indicates a vertical vector pointing down
            w indicates horizontal resolution
            h indicates vertical resolution
            */
            unit u[3];
            (*arq) >> u[0];
            (*arq) >> u[1];
            (*arq) >> u[2];
            _p = u;                 //gets starting point

            (*arq) >> u[0];
            (*arq) >> u[1];
            (*arq) >> u[2];
            _v[0] = u;              //gets horizontal vector

            (*arq) >> u[0];
            (*arq) >> u[1];
            (*arq) >> u[2];
            _v[1] = u;              //gets vertical vector

            (*arq) >> _res[0];		//Gets resolution values
            if(_res[0] < 0)
            {
                throw "Invalid value for resolution.\n";
            }
            (*arq) >> _res[1];
            if(_res[1] < 0)
            {
                throw "Invalid value for resolution.\n";
            }
        }
        bool build()
        {
            /*
            Screen data is given by
            xp yp zp xw yw zw xh yh zh w h
            (xp, yp, zp) indicates starting vertex
            (xw, yw, zw) indicates a horizontal vector to the right
            (xh, yh, zh) indicates a vertical vector pointing down
            w indicates horizontal resolution
            h indicates vertical resolution
            */
            unit u[3];
            string s;
            cout << "You will now input information to build the screen." << endl;
            cout << "Please input x coordinate of top left vertex: ";
            cin >> s;
            if(s == "x")
                return false;
            u[0] = atof(s.c_str());
            cout << "Please input y coordinate of top left vertex: ";
            cin >> s;
            if(s == "x")
                return false;
            u[1] = atof(s.c_str());
            cout << "Please input z coordinate of top left vertex: ";
            cin >> s;
            if(s == "x")
                return false;
            u[2] = atof(s.c_str());
            _p = u;                 //receives starting vertex

            while(true)
            {
                cout << "Please input x coordinate of horizontal vector: ";
                cin >> s;
                if(s == "x")
                    return false;
                u[0] = atof(s.c_str());
                cout << "Please input y coordinate of horizontal vector: ";
                cin >> s;
                if(s == "x")
                    return false;
                u[1] = atof(s.c_str());
                cout << "Please input z coordinate of horizontal vector: ";
                cin >> s;
                if(s == "x")
                    return false;
                u[2] = atof(s.c_str());
                _v[0] = u;              //receives horizontal vector
                if(!_v[0].null())		//If the horizontal vector is not null
                    break;
                cout << "Invalid input (the vector must be non-null). ";
            }

            while(true)
            {
                cout << "Please input x coordinate of vertical vector: ";
                cin >> s;
                if(s == "x")
                    return false;
                u[0] = atof(s.c_str());
                cout << "Please input y coordinate of vertical vector: ";
                cin >> s;
                if(s == "x")
                    return false;
                u[1] = atof(s.c_str());
                cout << "Please input y coordinate of vertical vector: ";
                cin >> s;
                if(s == "x")
                    return false;
                u[2] = atof(s.c_str());
                _v[1] = u;              //receives vertical vector
                if(!_v[1].null())		//if vertical vector is not null
                    break;
                cout << "Invalid input (the vector must be non-null). ";
            }

            while(true)
            {
                cout << "Please input horizontal resolution: ";
                cin >> s;
                if(s == "x")
                    return false;
                _res[0] = atoi(s.c_str());
                if(_res[0] > 0)
                    break;
                cout << "Invalid value for resolution (must be a positive integer). ";
            }

            while(true)
            {
                cout << "Please input vertical resolution: ";
                cin >> s;
                if(s == "x")
                    return false;
                _res[1] = atoi(s.c_str());
                if(_res[1] > 0)
                    break;
                cout << "Invalid value for resolution (must be a positive integer). ";
            }

            return true;
        }
        Vec point(int i, int j)
        {
            /*
			This function finds the point of the screen in the scene
			that corresponds to pixel (i, j)
            */
			return (_p + (_v[0] * j) / _res[0] + (_v[1] * i) / _res[1]);
        }
        int width() {return _res[0];}
        int height() {return _res[1];}
        Vec point() {return _p;}
        Vec v0() {return _v[0];}
        Vec v1() {return _v[1];}
        friend ostream &operator<<(ostream &output, const Screen &s )
        {
            Vec v = s._p;
            output << v << endl;
            v = v + s._v[0];
            output << v << endl;
            v = v + s._v[1];
            output << v << endl;
            v = v - s._v[0];
            output << v << endl << "Horizontal vector: " << s._v[0] << endl << "Vertical vector: " << s._v[1];
            return output;
        }
        string write()
        {
            //Writes screen data into string
            return (to_string((double)_p[0]) + " " + to_string((double)_p[1]) + " " + to_string((double)_p[2]) + " " + to_string((double)(_v[0])[0]) + " " + to_string((double)(_v[0])[1]) + " " + to_string((double)(_v[0])[2]) + " " +
            to_string((double)(_v[1])[0]) + " " + to_string((double)(_v[1])[1]) + " " + to_string((double)(_v[1])[2]) + " " + to_string(_res[0]) + " " + to_string(_res[1]) + "\n");
        }
    private:
        Vec _p;
        Vec _v[2];
        int _res[2];
    friend class Tracer;
};

#endif // SCREEN_H

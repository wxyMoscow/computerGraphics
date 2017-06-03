#ifndef VEC_H
#define VEC_H
#include <math.h>
#include <iostream>
#include <string>
#define unit long double
#ifndef epsilon
#define epsilon 0.000000001
#endif // epsilon
//This is the basic unit of our vector
using namespace std;

class Vec
{
    public:
        Vec();
        Vec(unit x, unit y, unit z);
        Vec(unit x[3]);
        Vec(int x[3]);
        string toHex();
		static string toHex(Vec v) { return v.toHex(); }
        unit operator[](int i) const {return _dir[i];}
        unit mod() {return sqrt(pow(_dir[0],2) + pow(_dir[1],2) + pow(_dir[2],2));}
        Vec& operator=(Vec v);
        Vec& operator=(unit f[3]);
		Vec& operator=(int f[3]);
        friend ostream &operator<<(ostream &output, const Vec &v )
        {
            output << "(" << v._dir[0] << ", " << v._dir[1] << ", " << v._dir[2] << ")";
            return output;
        }
        Vec operator+(const Vec& v2);
        Vec operator-(const Vec& v2);
        Vec operator^(const Vec& v2);
        unit operator*(const Vec& v2);
        Vec operator*(const unit f);
        Vec operator+(const unit f[3]);
        bool operator==(const Vec& v2);
        bool operator!=(const Vec& v2);
        bool null();
        Vec operator/(const unit f);
        void normalise();
        static Vec multi(Vec v1, Vec v2)
        {
			//Multiplies each component of two vectors
            return Vec(v1[0]*v2[0], v1[1]*v2[1], v1[2]*v2[2]);
        }

        static Vec div(Vec v1, Vec v2)
        {
			//Divides each component of two vectors
            return Vec(v1[0]/v2[0], v1[1]/v2[1], v1[2]/v2[2]);
        }
        Vec normal();
    protected:
    private:
        char toHex(int n);
        unit _dir[3];
};

#endif // Vec_H

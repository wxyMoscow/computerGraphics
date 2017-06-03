
#include "vec.h"

string Vec::toHex()
{
    //Converts the vector to a hexadecimal value
    string s = "";
    int h, i, m;
    for(i = 0; i < 3; i++){
        h = (int)_dir[i] % 256;
        m = h % 16;
        s += toHex(h/16);
        s += toHex(m);
    }
    return s;
}

char Vec::toHex(int n)
{
	//Converts an integer to a hexadecimal value between 0 and F inclusive
    if(n >= 0 && n < 10)
        return (n + '0');
    switch(n)
    {
        case 10:
            return 'A';
            break;
        case 11:
            return 'B';
            break;
        case 12:
            return 'C';
            break;
        case 13:
            return 'D';
            break;
        case 14:
            return 'E';
            break;
        case 15:
            return 'F';
            break;
        default:
            return '0';
    }
}

Vec& Vec::operator=(Vec v)
{
	//Assignment operator
    _dir[0] = v[0];
    _dir[1] = v[1];
    _dir[2] = v[2];
    return *this;
}

Vec& Vec::operator=(unit f[3])
{
	//Assignment operator with an array f
	_dir[0] = f[0];
	_dir[1] = f[1];
	_dir[2] = f[2];
    return *this;
}

Vec& Vec::operator=(int f[3])
{
	//Assignment operator with an array f
	_dir[0] = f[0];
	_dir[1] = f[1];
	_dir[2] = f[2];
	return *this;
}

Vec Vec::operator+(const Vec& v2)
{
	//Sum operation between vectors
    unit x, y, z;
    x = _dir[0] + v2[0];
    y = _dir[1] + v2[1];
    z = _dir[2] + v2[2];
    return Vec(x, y, z);
}

Vec Vec::operator-(const Vec& v2)
{
	//Subtraction operator between vectors
    unit x, y, z;
    x = _dir[0] - v2[0];
    y = _dir[1] - v2[1];
    z = _dir[2] - v2[2];
    return Vec(x, y, z);
}

Vec Vec::operator^(const Vec& v2)
{
	//Cross product between vectors
    unit x, y, z;
    x = _dir[1]*v2[2] - _dir[2]*v2[1];
    y = _dir[2]*v2[0] - _dir[0]*v2[2];
    z = _dir[0]*v2[1] - _dir[1]*v2[0];
    return Vec(x, y, z);
}

unit Vec::operator*(const Vec& v2)
{
	//Dot product between vectors
    return _dir[0]*v2[0] + _dir[1]*v2[1] + _dir[2]*v2[2];
}

Vec Vec::operator*(const unit f)
{
	//Multiplication between a vector and a number f
    return Vec(f*_dir[0], f*_dir[1], f*_dir[2]);
}

Vec Vec::operator/(const unit f)
{
	//Division between a vector and a number f
    return Vec(_dir[0]/f, _dir[1]/f, _dir[2]/f);
}

Vec::Vec(unit x, unit y, unit z)
{
    _dir[0] = x;
    _dir[1] = y;
    _dir[2] = z;
}

Vec::Vec(unit x[3])
{
    _dir[0] = x[0];
    _dir[1] = x[1];
    _dir[2] = x[2];
}

Vec::Vec(int x[3])
{
    _dir[0] = x[0];
    _dir[1] = x[1];
    _dir[2] = x[2];
}

Vec::Vec()
{
    _dir[0] = 0;
    _dir[1] = 0;
    _dir[2] = 0;
}

Vec Vec::operator+(const unit f[3])
{
	//Adds a vector and a unit array
    return Vec(_dir[0] + f[0], _dir[1] + f[1], _dir[2] + f[2]);
}

bool Vec::operator==(const Vec& v2)
{
	//Compares two vectors
    if(_dir[0] == v2[0] && _dir[1] == v2[1] && _dir[2] == v2[2])
        return true;
    return false;
}

bool Vec::operator!=(const Vec& v2)
{
    if(_dir[0] != v2[0] || _dir[1] != v2[1] || _dir[2] != v2[2])
        return true;
    return false;
}

bool Vec::null()
{
	//Returns whether a vector is the null vector
	unit x = _dir[0], y = _dir[1], z = _dir[2];
	x = (x >= 0) ? x : -x;
	y = (y >= 0) ? y : -y;
	z = (z >= 0) ? z : -z;
    if(x < epsilon && y < epsilon && z < epsilon)
        return true;
    return false;
}

void Vec::normalise()
{
	//Normalises a vector
	if ((*this).null())
		return;
    unit n = mod();
    for(int i = 0; i < 3; i++)
        _dir[i] = _dir[i]/n;
}

Vec Vec::normal()
{
	//Returns a normalised vector
    Vec v = (*this);
    v.normalise();
    return v;
}

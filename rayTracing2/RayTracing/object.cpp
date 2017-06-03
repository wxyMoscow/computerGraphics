#include "object.h"

int* Object::hexToInt(stringstream* arquivo)
{
    string s;
    (*arquivo) >> s;
    return hexToInt(s);
}

int* Object::hexToInt(string s)
{
    int* cor = new int[3];
    for(int i = 0; i < 3; i++)
    {
        cor[i] = Object::hexToInt(s[2*i + 1]);
        if(cor[i] < 0)
        {
            throw "Invalid hexadecimal number.\n";
        }
		cor[i] = Object::hexToInt(s[2 * i]) * 16 + cor[i];
        if(cor[i] < 0)
        {
            throw "Invalid hexadecimal number.\n";
        }
    }
    return cor;
}

int Object::hexToInt(char c)
{
    if(c >= '0' && c <= '9')
        return (c - '0');
    if(c >= 'A' && c <= 'F')
        return ((c - 'A') + 10);
    if(c >= 'a' && c <= 'f')
        return ((c - 'a') + 10);
    return -1;
}

Vec Plane::normal(Vec o, Vec p)
{
    Vec v1;
    v1 = p - o;                     //incident vector
    if(v1*_normal > 0)
        return _normal*(-1);
    return _normal;
}

Vec Plane::intersect(Vec o, Vec d)
{
    unit t;
    Vec v = d;
    v.normalise();
    if(v*_normal == 0)                       //in case the direction is parallel to the plane
        return o;
    t = (_pn - (_normal*o))/(_normal*v);	//calculates distance traversed by ray
    if(t <= 0)                              //negative distance
        return o;
	return (v*t + o);
}

bool Plane::build()
{
	unit u[3];
	string s;
	cout << "Please input x coordinate of a point on the plane: ";
	cin >> s;
	if (s == "x")
		return false;
	u[0] = atof(s.c_str());
	cout << "Please input y coordinate of that point: ";
	cin >> s;
	if (s == "x")
		return false;
	u[1] = atof(s.c_str());
	cout << "Please input z coordinate of that point: ";
	cin >> s;
	if (s == "x")
		return false;
	u[2] = atof(s.c_str());
	_p0 = u;

	while (true)
	{
		cout << "Please input x coordinate of a vector normal to the plane: ";
		cin >> s;
		if (s == "x")
			return false;
		u[0] = atof(s.c_str());
		cout << "Please input y coordinate of that vector: ";
		cin >> s;
		if (s == "x")
			return false;
		u[1] = atof(s.c_str());
		cout << "Please input z coordinate of that vector: ";
		cin >> s;
		if (s == "x")
			return false;
		u[2] = atof(s.c_str());
		_normal = u;
		_normal.normalise();
		if (!_normal.null())
			break;
		cout << "Invalid vector (must be non-null). ";
	}
	_pn = _p0*_normal;
	return true;
}

bool SimPlane::build()
{
	string s;
	unit d, r;
	if (!Plane::build())
		return false;
	cout << "Please input plane colour in hexadecimal: ";
	cin >> s;
	if (s == "x")
		return false;
	_colour = Object::hexToInt(s);
	while (true)
	{
		while (true)
		{
			cout << "Please input proportion of diffuse reflection: ";
			cin >> s;
			if (s == "x")
				return false;
			d = atof(s.c_str());
			if (d >= 0)
				break;
			cout << "Invalid value (must be nonnegative). ";
		}
		while (true)
		{
			cout << "Please input proportion of mirror reflection: ";
			cin >> s;
			if (s == "x")
				return false;
			r = atof(s.c_str());
			if (r >= 0)
				break;
			cout << "Invalid value (must be nonnegative). ";
		}
		d = d + r;
		if (d > 0)
			break;
		cout << "Invalid values (at least one of them must be nonzero). ";
	}
	_ref = r / d;
	while (true)
	{
		cout << "Please input specular coefficient: ";
		cin >> s;
		if (s == "x")
			return false;
		_spec = atof(s.c_str());
		if (_spec >= 0 && _spec <= 1)
			break;
		cout << "Invalid value (must be a number between 0 and 1 inclusive). ";
	}
	while (true)
	{
		cout << "Please input shininess: ";
		cin >> s;
		if (s == "x")
			return false;
		_shiny = atoi(s.c_str());
		if (_shiny >= 0)
			break;
		cout << "Invalid value (must be a nonnegative integer). ";
	}
    return true;
}

Vec Sphere::normal(Vec o, Vec p)
{
    Vec v1 = p - _center;          //finds external normal
    Vec v2 = p - o;                //and incident ray
    v1.normalise();
    if(v1*v2 > 0)
        return (v1*(-1));
    return v1;
}

Vec Sphere::intersect(Vec o, Vec d)
{
    Vec v = o - _center;        //to make calculations easier
    Vec a = d.normal();
    unit vd, delta, t;
    vd = v*a;
    delta = pow(vd, 2) - (v*v - pow(_rad,2));
    if(delta < 0)               //ray does not intersect sphere
        return o;
    delta = sqrt(delta);
    t = -vd - delta;
    v = a*t + o;
    if(t > 0)                   //least solution of quadratic equation
        return v;
    t = t + (2*delta);          //greatest solution of quadratic equation
    v = a*t + o;
    if(t > 0)
        return v;
    return o;
}

bool Sphere::entering(Vec o, Vec p)
{
    if((p - o)*(p - _center) < 0)
        return true;
    return false;
}

bool Sphere::build()
{
	string s;
	unit u[3];
	cout << "Please input x coordinate of center: ";
	cin >> s;
	if (s == "x")
		return false;
	u[0] = atof(s.c_str());
	cout << "Please input y coordinate of center: ";
	cin >> s;
	if (s == "x")
		return false;
	u[1] = atof(s.c_str());
	cout << "Please input z coordinate of center: ";
	cin >> s;
	if (s == "x")
		return false;
	u[2] = atof(s.c_str());
	_center = u;

	while (true)
	{
		cout << "Please input radius: ";
		cin >> s;
		if (s == "x")
			return false;
		_rad = atof(s.c_str());
		if (_rad > epsilon)
			break;
		cout << "Invalid value (must be positive). ";
	}
	return true;
}

bool SimSphere::build()
{
	string s;
	unit d, r, f;
	if (!Sphere::build())
		return false;
	cout << "Please input sphere colour in hexadecimal: ";
	cin >> s;
	if (s == "x")
		return false;
	_colour = Object::hexToInt(s);
	while (true)
	{
		while (true)
		{
			cout << "Please input relative proportion of diffuse reflection: ";
			cin >> s;
			if (s == "x")
				return false;
			d = atof(s.c_str());
			if (d >= 0)
				break;
			cout << "Invalid value (must be nonnegative). ";
		}
		while (true)
		{
			cout << "Please input relative proportion of mirror reflection: ";
			cin >> s;
			if (s == "x")
				return false;
			r = atof(s.c_str());
			if (r >= 0)
				break;
			cout << "Invalid value (must be nonnegative). ";
		}
		while (true)
		{
			cout << "Please input relative proportion of refraction: ";
			cin >> s;
			if (s == "x")
				return false;
			f = atof(s.c_str());
			if (f >= 0)
				break;
			cout << "Invalid value (must be nonnegative). ";
		}
		d = d + r + f;
		if (d > 0)
			break;
		cout << "Invalid values (at least one of them must be positive). ";
	}
	_ref = r / (d - f);
	_f = f / (d - r);

	while (true)
	{
		cout << "Please input specular coefficient: ";
		cin >> s;
		if (s == "x")
			return false;
		_spec = atof(s.c_str());
		if (_spec >= 0 && _spec <= 1)
			break;
		cout << "Invalid value (must be a number between 0 and 1 inclusive). ";
	}

	while (true)
	{
		cout << "Please input shininess: ";
		cin >> s;
		if (s == "x")
			return false;
		_shiny = atof(s.c_str());
		if (_shiny >= 0)
			break;
		cout << "Invalid value (must be nonnegative). ";
	}

	while (true)
	{
		cout << "Please input refraction index: ";
		cin >> s;
		if (s == "x")
			return false;
		_n = atof(s.c_str());
		if (_n >= 0)
			break;
		cout << "Invalid value (must be positive). ";
	}
    return true;
}

/*
Vec Ellipsoid::normal(Vec o, Vec p)
{
    //TODO
    return Vec(0,0,0);
}

Vec Ellipsoid::intersect(Vec o, Vec d)
{
    /*
    Assumindo que vetores sao colunas
	*//*
    Vec dd = d.normal();                        //garantir normalizacao
    Vec v = o - _center;                        //para facilitar a vida
    Vec Ad = Vec(_A[0]*dd, _A[1]*dd, _A[2]*dd);
    Vec Av = Vec(_A[0]*v, _A[1]*v, _A[2]*v);
    unit a = dd*Ad;
    unit b = dd*Av + v*Ad;
    unit c = v*Av - 1;
    unit delta = pow(b, 2) - 4*a*c;
    unit t;
    if(delta < 0)                               //nao intersecta o elipsoide
        return o;
    delta = sqrt(delta)/(2*a);
    t = (-b/(2*a)) - delta;
    v = o + dd*t;
    if(t > 0)                   //menor solucao da equacao quadratica
        return v;
    t = t + (2*delta);          //maior solucao da equacao quadratica
    v = o + dd*t;
    if(t > 0)
        return v;
    return o;
}

bool Ellipsoid::entering(Vec o, Vec p)
{
    //TODO
    return true;
}
*/
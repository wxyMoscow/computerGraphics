#include "tracer.h"

void Tracer::buildScene()
{
    //This builds the scene based on input from user
    string s;
    unit u[3];
    int i;
    Light** lis;
    Object** objs;
    _scene = false;
    cout << "To cancel, input x at any time." << endl;
    while(true)
    {
        cout << "Please input ambient light factor: ";
        cin >> s;
        if(s == "x")
            return;
        _amb = atof(s.c_str());
        if(_amb >= 0 && _amb <= 1)
            break;
        cout << "Invalid input (must be a number between 0 and 1). ";
    }

    while(true)
    {
        cout << "Please input maximum number of reflections: ";
        cin >> s;
        if(s == "x")
            return;
        _ref = atoi(s.c_str());
        if(_ref > 0)
            break;
        cout << "Invalid input (must be a positive integer). ";
    }

    while(true)
    {
        cout << "Please input refraction index of medium: ";
        cin >> s;
        if(s == "x")
            return;
        _n0 = atof(s.c_str());
        if(_n0 > 0)
            break;
        cout << "Invalid input (must be positive). ";
    }

    cout << "Please input x coordinate of the observer: ";
    cin >> s;
    if(s == "x")
        return;
    u[0] = atof(s.c_str());

    cout << "Please input y coordinate of the observer: ";
    cin >> s;
    if(s == "x")
        return;
    u[1] = atof(s.c_str());

    cout << "Please input z coordinate of the observer: ";
    cin >> s;
    if(s == "x")
        return;
    u[2] = atof(s.c_str());
    _obs = u;
    if(!_scr.build())
        return;

    while(true)
    {
        cout << "Please input supersampling factor (1 means no supersampling): ";
        cin >> s;
        if(s == "x")
            return;
        _ssample = atoi(s.c_str());
        if(_ssample > 0)
            break;
        cout << "Invalid input (must be a positive integer). ";
    }

    while(true)
    {
        cout << "Please input number of light sources: ";
        cin >> s;
        if(s == "x")
            return;
        _nlight = atoi(s.c_str());
        if(_nlight >= 0)
            break;
        cout << "Invalid input (must be a nonnegative integer). ";
    }
    lis = new Light*[_nlight];
    for(i = 0; i < _nlight; i++)
    {
        lis[i] = new Light();
        cout << "--" << i+1;
        if(((i+1) % 10 == 1) && ((i+1) != 11))
            cout << "st ";
        else if(((i+1) % 10 == 2) && ((i+1) != 12))
            cout << "nd ";
        else if(((i+1) % 10 == 3) && ((i+1) != 13))
            cout << "rd ";
        else
            cout << "th ";
        cout << "light source--" << endl;
        if(!(lis[i]->build()))
            return;
        _totalinten = _totalinten + lis[i]->getInt();
    }
    cout << "----" << endl;
    _li = lis;

    while(true)
    {
        cout << "Please input number of objects: ";
        cin >> s;
        if(s == "x")
            return;
        _nobj = atoi(s.c_str());
        if(_nobj > 0)
            break;
        cout << "Invalid input (must be a positive integer). ";
    }
    objs = new Object*[_nobj];
    for(i = 0; i < _nobj; i++)
    {
        cout << "--" << i+1;
        if(((i+1) % 10 == 1) && ((i+1) != 11))
            cout << "st";
        else if(((i+1) % 10 == 2) && ((i+1) != 12))
            cout << "nd";
        else if(((i+1) % 10 == 3) && ((i+1) != 13))
            cout << "rd";
        else
            cout << "th ";
        cout << " object--" << endl;
        objs[i] = Builder::make();
        if(objs[i] == 0)
            return;
    }
    cout << "----" << endl;
    _obj = objs;
    cout << "Scene was created successfully!" << endl;
    _scene = true;
}
void Tracer::modScene()
{
	int opt = 0;
	unit temp = 0, u[3];
	int temp2 = 0;
	string s;
	Screen scr;
	while (true)
	{
		cout << endl << "--Possible options--" << endl << "1 - Change ambient light." << endl << "2 - Change maximum number of reflections." << endl << "3 - Change refraction index of medium." << endl <<
			"4 - Change observer coordinates." << endl << "5 - Change screen details." << endl << "6 - Change supersampling factor." << endl << "7 - Edit light sources." << endl << "8 - Edit objects." << endl <<
			"0 - Return to previous menu." << endl << "What would you like to do? ";
		cin >> opt;
		switch (opt)
		{
			case 0:
				return;
				break;
			case 1:
				while (true)
				{
					cout << "Input new value for ambient light or x to cancel: ";
					cin >> s;
					if (s == "x")
						break;
					temp = atof(s.c_str());
					if (temp >= 0 && temp <= 1)
					{
						_amb = temp;
						cout << "Modification recorded!" << endl;
						break;
					}
					cout << "Invalid value (must be between 0 and 1 inclusive). ";
				}
				break;
			case 2:
				while (true)
				{
					cout << "Input new value for maximum number of reflections or x to cancel: ";
					cin >> s;
					if (s == "x")
						break;
					temp2 = atoi(s.c_str());
					if (temp2 > 0)
					{
						_ref = temp2;
						cout << "Modification recorded!" << endl;
						break;
					}
					cout << "Invalid value (must be a positive integer). ";
				}
				break;
			case 3:
				while (true)
				{
					cout << "Input new value for refraction index or x to cancel: ";
					cin >> s;
					if (s == "x")
						break;
					temp = atof(s.c_str());
					if (temp > 0)
					{
						_n0 = temp;
						cout << "Modification recorded!" << endl;
						break;
					}
					cout << "Invalid value (must be a positive number). ";
				}
				break;
			case 4:
				cout << "Input new value for observer coordinates." << endl << "Input x coordinate or x to cancel: ";
				cin >> s;
				if (s == "x")
					break;
				u[0] = atof(s.c_str());
				cout << "Input y coordinate or x to cancel: ";
				cin >> s;
				if (s == "x")
					break;
				u[1] = atof(s.c_str());
				cout << "Input z coordinate or x to cancel: ";
				cin >> s;
				if (s == "x")
					break;
				u[2] = atof(s.c_str());
				_obs = u;
				cout << "Modification recorded!" << endl;
				break;
			case 5:
				cout << "Input x at any time to cancel operation." << endl;
				if (!scr.build())
					break;
				cout << "Modifications recorded!" << endl;
				break;
			case 6:
				while (true)
				{
					cout << "Input new supersampling factor or x to cancel: ";
					cin >> s;
					if (s == "x")
						break;
					temp2 = atoi(s.c_str());
					if (temp2 > 0)
					{
						_ssample = temp2;
						cout << "Modification recorded!" << endl;
						break;
					}
					cout << "Invalid value (must be a positive integer). ";
				}
				break;
			case 7:
				editLight();
				break;
			case 8:
				editObj();
				break;
			default:
				cout << "Invalid option.";
		}
	}
}
void Tracer::editLight()
{
	int opt;
	string s;
	Light** lis = 0;
	Light* newli = 0;
	int i;
	while (true)
	{
		cout << endl << "--Possible options--" << endl << "1 - Add new light source." << endl << "2 - Delete light source." << endl <<
			"3 - See all light sources." << endl << "0 - Return to previous menu." << endl << "What would you like to do? ";
		cin >> opt;
		switch (opt)
		{
		case 0:
			return;
			break;
		case 1:
			newli = new Light();
			if (newli->build())
			{
				_nlight++;
				lis = new Light*[_nlight];
				for (i = 0; i < _nlight - 1; i++)
					lis[i] = _li[i];
				lis[_nlight - 1] = newli;
				delete _li;
				_li = lis;
				lis = 0;
			}
			break;
		case 2:
			if (_nlight > 0)
			{
				cout << "> Light sources:" << endl;
				for (i = 0; i < _nlight; i++)
				{
					cout << ">> Source " << i + 1 << ":" << endl;
					cout << (*_li[i]);
				}
				while (true)
				{
					cout << "Which light source would you like to delete? Choose 0 to cancel: ";
					cin >> opt;
					if (opt == 0)
						break;
					else if (opt < 0 || opt > _nlight)
						cout << "Invalid value. ";
					else
					{
						while (true)
						{
							cout << "Are you sure (y/n)? ";
							cin >> s;
							if (s == "y")
							{
								opt--;
								newli = _li[opt];
								_nlight--;
								lis = new Light*[_nlight];
								for (i = 0; i < opt; i++)
									lis[i] = _li[i];
								for (i = opt; i < _nlight; i++)
									lis[i] = _li[i + 1];
								delete newli;
								delete _li;
								_li = lis;
								lis = 0;
								break;
							}
							else if (s == "n")
								break;
							else
								cout << "Invalid input. ";
						}
						break;
					}
				}
			}
			else
				cout << "There are no light sources." << endl;
			break;
		case 3:
			if (_nlight > 0)
			{
				cout << endl << "> Light sources:" << endl;
				for (i = 0; i < _nlight; i++)
				{
					cout << ">> Source " << i + 1 << ":" << endl;
					cout << (*_li[i]);
				}
			}
			else
				cout << "There are no light sources." << endl;
			break;
		default:
			cout << "Invalid option." << endl;
			break;
		}
	}
}
void Tracer::editObj()
{
	int opt;
	string s;
	Object** objs = 0;
	Object* newobj = 0;
	int i;
	while (true)
	{
		cout << endl << "--Possible options--" << endl << "1 - Add new object." << endl << "2 - Delete object." << endl <<
			"3 - See all objects." << endl << "0 - Return to previous menu." << endl << "What would you like to do? ";
		cin >> opt;
		switch (opt)
		{
		case 0:
			return;
			break;
		case 1:
			cout << "Input x at any time to cancel." << endl;
			newobj = Builder::make();
			if (newobj != 0)
			{
				_nobj++;
				objs = new Object*[_nobj];
				for (i = 0; i < _nobj - 1; i++)
					objs[i] = _obj[i];
				objs[_nobj - 1] = newobj;
				delete _obj;
				_obj = objs;
				objs = 0;
			}
			break;
		case 2:
			if (_nobj > 1)
			{
				cout << "> Objects:" << endl;
				for (i = 0; i < _nobj; i++)
				{
					cout << ">> Object " << i + 1 << ":" << endl;
					_obj[i]->printDetails();
				}
				while (true)
				{
					cout << "Which object would you like to delete? Choose 0 to cancel: ";
					cin >> opt;
					if (opt == 0)
						break;
					else if (opt < 0 || opt > _nobj)
						cout << "Invalid value. ";
					else
					{
						while (true)
						{
							cout << "Are you sure (y/n)? ";
							cin >> s;
							if (s == "y")
							{
								opt--;
								newobj = _obj[opt];
								_nobj--;
								objs = new Object*[_nobj];
								for (i = 0; i < opt; i++)
									objs[i] = _obj[i];
								for (i = opt; i < _nobj; i++)
									objs[i] = _obj[i + 1];
								delete newobj;
								delete _obj;
								_obj = objs;
								objs = 0;
								break;
							}
							else if (s == "n")
								break;
							else
								cout << "Invalid input. ";
						}
						break;
					}
				}
			}
			else
				cout << "You can't delete the last object." << endl;
			break;
		case 3:
			cout << "> Objects:" << endl;
			for (i = 0; i < _nobj; i++)
			{
				cout << ">> Object " << i + 1 << ":" << endl;
				_obj[i]->printDetails();
			}
			break;
		default:
			cout << "Invalid option." << endl;
			break;
		}
	}
}
void Tracer::makeScene()
{
    int opt = 0;
    int i = 0;
    fstream arqin;
    string entrada;
    stringstream defin;
    Image* im = 0;
    cout << endl << ">>> Welcome to the Ray Tracer <<<" << endl;
    while(true)
    {
        cout << endl << "--Possible options--" << endl << "1 - Create new scene." << endl << "2 - Load scene from file." << endl;
        if(_scene)
            cout << "3 - Save scene to file." << endl << "4 - Modify scene." << endl << "5 - See specifications of scene." << endl << "6 - Render scene." << endl;
        cout << "0 - Exit." << endl << "What would you like to do? ";
        cin >> opt;
        switch(opt)
        {
            case 0:
                return;
                break;
            case 1:
                buildScene();
                break;
            case 2:
                cout << "Please type the name of the input file (input file must be of type .prtr): " << endl;
                entrada = "";
                cin >> entrada;
                if(entrada.substr(entrada.length()-5,5) != ".prtr")
                {
                    cout << "Invalid file type." << endl;
                    break;
                }
                arqin.open(entrada.c_str(),fstream::in);
                if(!arqin.good()){
                    cout << "There was an error loading the file!" << endl;
                    break;
                }
                entrada = "";
                do{
                    getline(arqin,entrada);
                    defin << entrada << " ";
                }while(!arqin.eof());
                arqin.close();
                try
                {
                    newScene(&defin);
                    cout << "Scene loaded!" << endl;
                }
                catch(char const* c)
                {
                    cout << c;
                    cout << "Could not create scene." << endl;
                }
                break;
            case 3:
				if (!_scene)
				{
					cout << "Invalid option." << endl;
					break;
				}
                cout << "Choose file name (it will be saved as a .prtr): ";
                entrada = "";
                cin >> entrada;
                try
                {
                    saveScene(entrada + ".prtr");
                    cout << "File saved with success!" << endl;
                }
                catch(char const* c)
                {
                    cout << c;
                    cout << "Could not save file." << endl;
                }
                catch(...)
                {
                    cout << "An unknown error occurred. Could not save file." << endl;
                }
                break;
            case 4:
				if (!_scene)
				{
					cout << "Invalid option." << endl;
					break;
				}
                modScene();
                break;
            case 5:
				if (!_scene)
				{
					cout << "Invalid option." << endl;
					break;
				}
                cout << endl << "-- Current scene --" << endl << "> Ambient light: " << _amb << endl << "> Number of allowed reflections: " << _ref << endl <<
                "> Refraction index of the environment: " << _n0 << endl << "> Supersampling factor: " << _ssample << endl << "> Coordinates of the observer: " << _obs << endl << "> Screen corners and resolution:" << endl << "-----" <<
                endl << _scr << endl << _scr.width() << " x " << _scr.height() << endl << "-----" << endl;
                if(_nlight > 0)
                {
                    cout << "> Light sources:" << endl;
                    for(i = 0; i < _nlight; i++)
                    {
                        cout << ">> Source " << i+1 << ":" << endl;
                        cout << (*_li[i]);
                    }
                }
                cout << "-----" << endl << "> Objects:" << endl;
                for(i = 0; i < _nobj; i++)
                {
                    cout << ">> Object " << i+1 << ": ";
                    _obj[i]->printDetails();
                }
                break;
            case 6:
				if (!_scene)
				{
					cout << "Invalid option." << endl;
					break;
				}
                cout << "Type the name of output file (it will be saved as a .bmp): ";
                entrada = "";
                cin >> entrada;
                entrada = entrada + ".bmp";
                cout << "Rendering ";
                try
                {
                    im = render();
					cout << "Rendering was completed with success!" << endl;
                }
                catch(char const* c)
                {
                    cout << c;
                    cout << "Image was not rendered." << endl;
                }
				catch (...)
				{
					cout << "An unknown error occurred. Image was not rendered." << endl;
				}
                try{
                    im->WriteToFile((char *)entrada.c_str());
                }
                catch(char const* c)
                {
                    cout << c;
                    cout << "Image was not saved." << endl;
                }
                catch(...)
                {
                    cout << "An unknown error occurred. Image was not saved." << endl;
                }
                break;
            default:
				cout << "Invalid option." << endl;
        }
    }
}

void Tracer::newScene(stringstream* arq)
{
    /*
	Input is given by
    amb                             (ambient light factor, between 0 and 1)
    ref                             (maximum number of allowed reflections, must be a positive integer)
    n0                              (air's refraction index)
    xo yo zo                        (observer coordinates (xo, yo, zo))
    [screen details]
    ssample                         (supersampling factor)
    nlight                          (number of light sources)
    [light source details]
    nobj                            (number of objects)
    [object details]
    */
    int i;
    unit o[3];							//auxiliary variable
    Light** lis;						//auxiliary variable
    Object** objs;						//auxiliary variable
    if(_scene)
        deleteScene();
    _totalinten = Vec(0,0,0);

    (*arq) >> _amb;
    if(_amb < 0 || _amb > 1)
    {
        throw "Invalid ambient light value. Must be between 0 and 1.\n";
    }

    (*arq) >> _ref;
    if(_ref < 0)
    {
        throw "Invalid number of reflections. Must be a nonnegative integer.\n";
    }

    (*arq) >> _n0;

    (*arq) >> o[0];
    (*arq) >> o[1];
    (*arq) >> o[2];
    _obs = o;

    try{
        _scr = Screen(arq);             //inicializa a tela
    }
    catch(char const* c)
    {
        throw c;
    }
	catch (...)
	{
		throw "Unknown error occurred when building the screen.\n";
	}

    (*arq) >> _ssample;
	if (_ssample < 1)
		throw "Invalid supersampling factor.\n";

    (*arq) >> _nlight;
    if(_nlight < 0)
        throw "Invalid number of light sources. Must be nonnegative.\n";
    lis = new Light*[_nlight];
    for(i = 0; i < _nlight; i++)
    {
		try{
			lis[i] = new Light(arq);
		}
		catch (char const* c){
			throw "Light source " + to_string(i + 1) + ": " + c;
		}
		catch (...){
			throw "Unkown error occurred with light source " + to_string(i + 1) + ".";
		}
        _totalinten = _totalinten + lis[i]->getInt();
    }
    _li = lis;

    (*arq) >> _nobj;                //armazena o numero de objetos
    if(_nobj < 1)                   //pelo menos um objeto necessario
    {
        throw "Invalid number of objects. Must be positive.\n";
    }
    objs = new Object*[_nobj];
    for(i = 0; i < _nobj; i++){
        try{
            objs[i] = Builder::build(arq);
        }
        catch(char const* c)
        {
			throw c;
        }
		catch (...)
		{
			throw "Uknown error occurred with an object.";
		}
    }
    _obj = objs;
    _scene = true;
}

void Tracer::saveScene(string s)
{
	/*
	Saves scene to file s.
	*/
    string file;
    fstream arqout(s.c_str(), fstream::out);
    file = to_string((double)_amb) + "\n" + to_string(_ref) + "\n" + to_string((double)_n0) + "\n" + to_string((double)_obs[0]) + " " +
    to_string((double)_obs[1]) + " " + to_string((double)_obs[2]) + "\n" + _scr.write() + to_string(_ssample) + "\n" + to_string(_nlight) + "\n";
    for(int i = 0; i < _nlight; i++)
        file += _li[i]->write();
    file += to_string(_nobj) + "\n";
    for(int i = 0; i < _nobj; i++)
        file += _obj[i]->write();
    arqout << file;
}

void Tracer::deleteScene()
{
    if(!_scene)
        return;
    int i = 0;
    _scr = Screen();
    for(i = 0; i < _nlight; i++)
        delete _li[i];
    _nlight = 0;
    _totalinten = Vec(0,0,0);
    for(i = 0; i < _nobj; i++)
        delete _obj[i];
    _nobj = 0;
    _obs = Vec(0,0,0);
    _amb = 0;
    _ref = 0;
    _n0 = 0;
    _ssample = 0;
    _scene = false;
}

Tracer::Tracer(stringstream* arq)
{
    try
    {
        newScene(arq);
    }
    catch(char const *c)
    {
        throw c;
    }
}

Image* Tracer::render()
{
    if(!_scene)
    {
        throw "Scene not defined.";
    }
    int w = _scr.width(), h = _scr.height(), i, j, hundredth, count = 0, percent = 0;
    Image* im = new Image(w, h);
	cout << "0% complete.";
	hundredth = w*h / 100;
    for(i = 0; i < h; i++)
    {
        for(j = 0; j < w; j++)
        {
			count++;
			if (count == hundredth)
			{
				percent++;
				cout << "\r" << "Rendering " << percent << "% complete.";
				count = 0;
			}
            im->setColour(i, j, render(i, j));
        }
    }
	cout << "\r";
    return im;
}

Vec Tracer::render(int i, int j)
{
    /*
    Renders pixel (i, j)
    */
    Vec pxlcol(0,0,0);                      //initialises pizel colour
    Vec p(0,0,0);
    int obj;
    Vec dir = _scr.point(i,j), di, dj, v(0, 0, 0);
	int m, n;
	unit h, w;
	if (_ssample > 1)
	{
		//Performs supersampling
		di = _scr.point(i + 1, j) - dir;
		dj = _scr.point(i, j + 1) - dir;
		h = di.mod() / (_ssample + 1);
		w = dj.mod() / (_ssample + 1);
		for (m = 0; m < _ssample; m++)
		{
			for (n = 0; n < _ssample; n++)
			{
				v = dir + di*h*m + dj*w*n;      //divides pixel in _ssample^2 points
				v = v - _obs;
				obj = intersect(_obs, v, p, v.mod());
				if (obj != -1)
				{
					pxlcol = pxlcol + objCol(_obs, p, obj, _ref);
				}
			}
		}
	}
	else														//Since there is no supersampling, no need to execute the expensive procedures above
	{
		v = dir - _obs;
		obj = intersect(_obs, v, p, v.mod());
		if (obj != -1)
		{
			pxlcol = pxlcol + objCol(_obs, p, obj, _ref);
		}
	}
    return (pxlcol/pow(_ssample,2));
}

int Tracer::intersect(Vec o, Vec d, Vec& p, unit min)
{
    /*
	Finds the object that the ray starting at o with direction d
	intersects and the point p where that occurs. The ray must
	traverse a minimum distance min.
    */
    int obj, k;
    Vec temp = o;
    Vec ptry = o;
    obj = -1;
    for(k = 0; k < _nobj; k++)
    {
        temp = _obj[k]->intersect(o, d);
        if((temp != o) && (((temp - o).mod() < (ptry - o).mod() - epsilon) || (ptry == o)) && ((temp - o).mod() > min + epsilon))
        {
            /*
			If temp != o then the ray intersected an object
			if ptry == o then this is the first time that happens
            If ||temp - o|| < ||ptry - o|| then the new object is closer than previous one
            ||temp - o|| > min by definition
			epsilon is meant to avoid reflection/shadowing artefacts
            */
            ptry = temp;
            obj = k;
        }
    }
    p = ptry;
    return obj;
}

Vec Tracer::objCol(Vec o, Vec p, int obj, int r)
{
    /*
	Finds the colour of object obj at point p when seen from
	a ray coming from o, knowing that the maximum allowed
	number of reflections is r.
    */
	Vec colour(0, 0, 0);
    Vec diff(0,0,0), reflect(0,0,0), pcol(0,0,0), spec(0,0,0), refract(0,0,0);
    unit ref = _obj[obj]->ref(p);
    unit fra = _obj[obj]->fra(p);
    if((1 - ref - fra) > 0 && _amb < 1)							//in case there is diffuse reflection at that point
        diff = diffSpec(o, p, obj, spec);						//finds diffuse and specular intensities
    if(fra > 0)													//in case the object is transparent
        refract = fraCol(o, p, obj, r, fra, ref);				//finds refracted colour and index of reflection according to Fresnel Equations
    if(ref > 0 && r > 0)										//in case the object has mirror properties
        reflect = refCol(o, p, _obj[obj]->normal(o, p), r - 1);	//finds mirror reflection
    pcol = _obj[obj]->colour(p);								//initialises pixel colour
    pcol = pcol*_amb + Vec::multi(pcol, diff)*(1 - _amb);		//adds in diffuse intensity
    pcol = pcol*(1 - ref - fra) + reflect*ref + refract*fra;    //adds in refracted and reflected colours
    colour = Vec(255, 255, 255) - pcol;							//temporary vector for specular highlights
    colour = pcol + Vec::multi(colour, spec)*_obj[obj]->spec(p);//adds in specular highlights
    return colour;
}

Vec Tracer::diffSpec(Vec o, Vec p, int obj, Vec& spec)
{
    /*
	Finds diffuse intensity of object obj at point p as seen
	from o.
	Also finds specular highlight intensity.
    */
    Vec inten(0,0,0);							//diffuse intensity
    Vec s(0,0,0);								//specular highlight intensity
    Vec v = o - p;								//negative of incident vector
    unit alpha = _obj[obj]->shiny(p);			//shininess
    unit cos = 0;								//cosine between object normal and light ray
    Vec c(0,0,0);								//light ray
    Vec normal = _obj[obj]->normal(o, p);		//object normal
    Vec inter = o;								//intersection point
    bool block = false;							//determines whether a certain light source is blocked
	int l = 0, k = 0;
    v.normalise();
    for(l = 0; l < _nlight; l++)
    {
        c = _li[l]->getPos() - p;				//finds ray from p to light source
        block = false;
        if(c*normal > 0)						//in case the object itself is not blocking the source
        {
            for(k = 0; k < _nobj; k++)			//for each object
            {
                if(k != obj)					//except itself
                {
                    inter = _obj[k]->intersect(p, c);           //verifies whether it's blocking the light
                    inter = inter - p;
                    if(!(inter.null()) && (inter.mod() < c.mod()))
                    {
                        block = true;                           //that light ray is blocked
						break;
                    }
                }
            }
            if(!block)                                          //if no object blocks that light source
            {
                cos = (c*normal)/c.mod();                       //finds cosine (||normal|| == 1)
                inten = inten + _li[l]->getInt()*cos;           //finds contributed intensity
                c.normalise();
                cos = normal*bisector(v,c);
                s = s + _li[l]->getSpec()*pow(cos,alpha);		//finds specular intensity
            }
        }
    }

    inten = Vec::div(inten, _totalinten);                    //finds intensity relative to every light source
    spec = Vec(min(1, s[0]),min(1, s[1]),min(1, s[2]));      //guarantees the specular highlights saturate at 1
    return inten;
}

Vec Tracer::refCol(Vec o, Vec p, Vec n, int r)
{
    /*
	Finds reflected colour at point p as seen by o, knowing that
	n is the object's normal at that point and r is the maximum
	extra number of allowed reflections.
    */
    Vec rcol(0,0,0);
    Vec i = (p - o).normal();                                  //finds incident ray
    Vec refl(0,0,0);                                //reflected ray
    int obj = 0;                                    //index of reflected object
    Vec point(0,0,0);                               //point of that object
    refl = reflected(i, n);                         //finds reflected ray
    obj = intersect(p, refl, point, 0);
    if(obj != -1)                                   //in case it found an object
        rcol = objCol(p, point, obj, r);

    return rcol;
}

Vec Tracer::fraCol(Vec o, Vec p, int obj, int r, unit& fra, unit& ref)
{
    /*
	Calculates refracted colour as seen from o at point p on object obj that has
	refraction index n1 knowing that there are r reflections left
    */
    Vec refract(0,0,0);
    Vec i = (p - o).normal();                               //incident vector
    Vec n = _obj[obj]->normal(o, p);                        //normal vector
    Vec v(0,0,0);
    int inter = -1;
    unit T, R;
    if(_obj[obj]->entering(o, p))
        refract = refracted(i, n, _n0, _obj[obj]->n2(p), T, R);   //entering ray, n1 = n0 and n2 = object n
    else
        refract = refracted(i, n, _obj[obj]->n2(p), _n0, T, R);   //leaving ray, n1 = object n and n2 = n0
    ref = fra*R;                                            //new reflectance
    fra = fra*T;                                            //new refractance
    if(refract.null())                                      //critical angle
        return Vec(0,0,0);
    i = p - _obj[obj]->normal(o,p)*epsilon;
    inter = intersect(i, refract, v, 0);                    //finds next object refracted ray hits
    if(inter == -1)
        return Vec(0,0,0);
    return objCol(p, v, inter, r);
}

Vec Tracer::reflected(Vec i, Vec n)
{
    /*
	This function takes an incident normalised vector i and a normal vector
	n and returns the reflected vector
    */
    return (i - (n*(n*i))*2);
}

Vec Tracer::bisector(Vec v, Vec l)
{
    /*
	This function finds the bisector vector of two normalised
	vectors v and l pointing in the same direction
    */
    return (v + l).normal();
}

Vec Tracer::refracted(Vec i, Vec n, unit n1, unit n2, unit& fra, unit& ref)
{
    /*
	Finds refracted vector when incident vector is i, normal vector is n,
	n1 is incident medium refraction index, and n2 is transmitted medium
	refraction index
    */
    unit cosi = (i*n)*(-1);                                 //incident angle's cosine
    unit n1n2 = n1/n2;                                      //what it says on the tin
    unit sint = pow(n1n2,2)*(1-pow(cosi,2));                //transmitted angle's sine
    unit sint2 = 0;                                         //that thing, squared
    unit cost = 0;                                          //transmitted angle's cosine
    unit refpara, refperpe;                                 //reflectance components
    if(sint > 1)                                            //critical angle
    {
        fra = 0;                                            //according to the Fresnel equations
        ref = 1;                                            //according to the Fresnel equations
        return Vec(0,0,0);
    }
    sint2 = pow(sint,2);
    cost = sqrt(1 - sint2);
    Vec t = (i*n1n2) + n*(n1n2*cosi - cost);
    //Fresnel equations
    refperpe = pow((n1*cosi - n2*cost)/(n1*cosi + n2*cost),2);
    refpara = pow((n2*cosi - n1*cost)/(n2*cosi + n1*cost),2);
    ref = (refperpe + refpara)/2;
    fra = 1 - ref;
    return t;
}

unit Tracer::min(unit a, unit b)
{
    return ((a < b) ? a : b);
}

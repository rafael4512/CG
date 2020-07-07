#include "headers/figures.h"
#include "headers/patch.h"

#include <vector>

int newFigure(std::ofstream &file, int ntri)
{
	if (file.is_open()) 
	{
		file.clear();
		file << ntri << endl; //escreve o numero de triangulos na primeira linha
		return 0;
	}
	return -1;
}

string getLineNumber(string file_name, int n_line) {

	string line;

	ifstream file;
	file.open(file_name);

	if (file.is_open()) {
		for (int i = 0; i < n_line; i++)
			getline(file, line);
		file.close();
	}
	else cout << "Unable to open patch file: " << file_name << "." << endl;

	return line;
}

int drawTriangle(std::ofstream &file,double x1,double y1,double z1,double x2,double y2,double z2,double x3,double y3,double z3)
{
	if (file.is_open()) 
	{
		file << 
		x1 << " " << y1 << " " << z1 << " " <<
		x2 << " " << y2 << " " << z2 << " " <<
		x3 << " " << y3 << " " << z3 
		<< endl;
		return 0;
	}
	return -1;
}

int drawPlane(std::ofstream &file, double size)
{
	double coord=size/2;

	if (coord <= 0)
		coord = 1;

	newFigure(file, 4);

	drawTriangle(file,coord,0,coord,coord,0,-coord,-coord,0,coord);
	drawTriangle(file,coord,0,-coord,-coord,0,-coord,-coord,0,coord);
	drawTriangle(file,coord,0,-coord,coord,0,coord,-coord,0,coord);
	drawTriangle(file,-coord,0,coord,-coord,0,-coord,coord,0,-coord);

	return 0;
}

int drawBox(std::ofstream &file, double x, double y, double z, int dX, int dZ, int dY, int argc)
{
	// [divisões]
	int divX = 1;
	int divZ = 1;
	int divY = 1;

	if (argc >= 7)
	{
		divX = dX;
		if (divX <= 0)
		{
			// Para não haver 0 divisões /0 = imp
			divX = 1;
		}
	}

	if (argc >= 8)
	{
		divZ = dZ;
		if (divZ <= 0)
		{
			// Para não haver 0 divisões /0 = imp
			divZ = 1;
		}
	}

	if (argc >= 9)
	{
		divY = dY;
		if (divY <= 0)
		{
			// Para não haver 0 divisões /0 = imp
			divY = 1;
		}
	}
	if (x < 0)
	{
		x = -x;
	}
	if (y < 0)
	{
		y = -y;
	}
	if (z < 0)
	{
		z = -z;
	}

	int ntriangulos = 4 * (divX*divY + divX*divZ + divY*divZ);

	newFigure(file, ntriangulos);

	float x1, y1, z1, x2, y2, z2, x3, y3, z3;
	float x4, y4, z4, x5, y5, z5, x6, y6, z6;
		
	for (double k = 0; k < divZ; ++k)
	{
		for (double i = 0; i < divX; ++i)
		{
			x1 = i / divX * x -x/2;
			y1 = -y/2;
			z1 = k / divZ * z -z/2;
	
			x2 = (i + 1) / divX * x -x/2;
			y2 = -y/2;
			z2 = k / divZ * z -z/2;
					
			x3 = i / divX * x -x/2;
			y3 = -y/2;
			z3 = (k + 1) / divZ * z -z/2;
	
			x4 = x2;
			y4 = y2;
			z4 = z2;
	
			x5 = (i + 1) / divX * x -x/2;
			y5 = -y/2;
			z5 = (k + 1) / divZ * z -z/2;
					
			x6 = x3;
			y6 = y3;
			z6 = z3;

			//Base
			drawTriangle(file,x1,y1,z1,x2,y2,z2,x3,y3,z3);
			drawTriangle(file,x4,y4,z4,x5,y5,z5,x6,y6,z6);

			y1 = y2 = y3 = y4 = y5 = y6 = y/2;
				
			//Tampo
			drawTriangle(file,x1,y1,z1,x3,y3,z3,x2,y2,z2);
			drawTriangle(file,x4,y4,z4,x6,y6,z6,x5,y5,z5);
		}
	}

	for (double i = 0; i < divX; ++i)
	{
		for (double j = 0; j < divY; ++j)
		{
			//printf("\nXY\n");
		
			x1 = i / divX * x -x/2;
			y1 = j / divY * y -y/2;
			z1 = -z/2;

			x2 = i / divX * x -x/2;
			y2 = (j + 1) / divY * y -y/2;
			z2 =  -z/2;

			x3 = (i + 1) / divX * x -x/2;
			y3 = (j) / divY * y -y/2;
			z3 = -z/2;
					
			x4 = x2;
			y4 = y2;
			z4 = z2;
	
			x5 = (i + 1) / divX * x -x/2;
			y5 = (j + 1) / divY * y -y/2;
			z5 = -z/2;
					
			x6 = x3;
			y6 = y3;
			z6 = z3;

			//Base
			drawTriangle(file,x1,y1,z1,x2,y2,z2,x3,y3,z3);
			drawTriangle(file,x4,y4,z4,x5,y5,z5,x6,y6,z6);

			z1 = z2 = z3 = z4 = z5 = z6 = z/2;
				
			//Tampo
			drawTriangle(file,x1,y1,z1,x3,y3,z3,x2,y2,z2);
			drawTriangle(file,x4,y4,z4,x6,y6,z6,x5,y5,z5);
		}
	}
	for (double k = 0; k < divZ; ++k)
	{
		for (double j = 0; j < divY; ++j)
		{
			x1 = -x/2;
			y1 = j / divY * y -y/2;
			z1 = k / divZ * z -z/2;
	
			x2 = -x/2;
			y2 = j / divY * y -y/2;
			z2 = (k + 1) / divZ * z -z/2;
					
			x3 = -x/2;
			y3 = (j + 1) / divY * y -y/2;
			z3 = k / divZ * z -z/2;
	
			x4 = x2;
			y4 = y2;
			z4 = z2;
	
			x5 = -x/2;
			y5 = (j + 1) / divY * y -y/2;
			z5 = (k + 1) / divZ * z -z/2;
					
			x6 = x3;
			y6 = y3;
			z6 = z3;

			//Base
			drawTriangle(file,x1,y1,z1,x2,y2,z2,x3,y3,z3);
			drawTriangle(file,x4,y4,z4,x5,y5,z5,x6,y6,z6);

			x1 = x2 = x3 = x4 = x5 = x6 = x/2;

			//Tampo
			drawTriangle(file,x1,y1,z1,x3,y3,z3,x2,y2,z2);
			drawTriangle(file,x4,y4,z4,x6,y6,z6,x5,y5,z5);
		}		
	}
	return 0;
}

int drawSphere(std::ofstream &file, double raio, double slice, double stack)
{

	int ntriangulos = 2 * (stack * slice) - 2 * slice;

	newFigure(file, ntriangulos);

	if (raio <= 0)
	{
		raio = 1;
	}
	if (stack <= 2)
	{
		stack = 3;
	}
	if (slice <= 2)
	{
		slice = 3;
	}

	double x1, y1, z1, x2, y2, z2, x3, y3, z3 = 0;
	double x4, y4, z4, x5, y5, z5, x6, y6, z6 = 0;

	double phi = 0;
	double passoPHI = M_PI / stack;

	double passoTHETA = 2 * M_PI / slice;

	for (int i = 0; i < stack; ++i, phi += passoPHI)
	{
		double theta = 0;
		for (int j = 0; j < slice; ++j, theta += passoTHETA)
		{   
			//Cria triângulos em demasia no ponto mais alto e mais baixo
			x1 = raio * cos(theta) * sin(phi);
			y1 = raio * cos(phi);
			z1 = raio * sin(theta) * sin(phi);

			x2 = raio * cos(theta + passoTHETA) * sin(phi + passoPHI);
			y2 = raio * cos(phi + passoPHI);
			z2 = raio * sin(theta + passoTHETA) * sin(phi + passoPHI);

			x3 = raio * cos(theta) * sin(phi + passoPHI);
 			y3 = raio * cos(phi + passoPHI);
			z3 = raio * sin(theta) * sin(phi + passoPHI);
				
			if (i != stack - 1)
			{
				drawTriangle(file,x1,y1,z1,x2,y2,z2,x3,y3,z3);
			}

			if (i != 0)
			{
				x4 = x1;
				y4 = y1;
				z4 = z1;

				x5 = raio * cos(theta + passoTHETA) * sin(phi);
				y5 = raio * cos(phi);
				z5 = raio * sin(theta + passoTHETA) * sin(phi);
						
				x6 = x2;
				y6 = y2;
				z6 = z2;
				
				drawTriangle(file,x4,y4,z4,x5,y5,z5,x6,y6,z6);
			}
		}
	}
	return 0;
}

int drawCone(std::ofstream &file, double raio, double alt, int slice, int stack)
{
	int ntriangulos = slice + 2 * (stack * slice);

	newFigure(file, ntriangulos);

	if (raio <= 0)
	{
		raio = 1;
	}
	if (stack <= 2)
	{
		stack = 3;
	}
	if (slice <= 2)
	{
		slice = 3;
	}

	double x, y, z;
	double x1, x2, y1, y2, z1, z2;

	double passoAngulo = (double) 360/slice;
	double angulo = 0;
	double proxAng = passoAngulo;

	x = y = z = 0;
		
	//Base
	for (int i = 0; i < slice; ++i)
	{
		x1 = raio * cos(angulo * M_PI / 180);
		y1 = 0;
		z1 = raio * sin(angulo * M_PI / 180);

		x2 = raio * cos(proxAng * M_PI / 180);
		y2 = 0;
		z2 = raio * sin(proxAng * M_PI / 180);

		drawTriangle(file,x,y,z,x1,y1,z1,x2,y2,z2);

		angulo = proxAng;
		proxAng += passoAngulo;
	}

	double passo = (double) alt/stack;
	double h = 0;
	double proxH = h + passo;

	double x3, x4, y3, y4, z3, z4, x5, x6, y5, y6, z5, z6;
		
	for (int i = 0; i < stack; ++i)
	{
		double d1, d2;

		d1 = (double) raio * (alt - h) / alt;
		d2 = (double) raio * (alt - proxH) / alt;
		
		angulo = 90;
		proxAng = angulo + passoAngulo;
		for (int alfa = 0; alfa < slice; ++alfa)
		{
			x1 = d2 * cos((double)angulo * M_PI / 180);
			y1 = proxH;
			z1 = d2 * sin((double)angulo * M_PI / 180);
		
			x2 = d1 * cos((double)angulo * M_PI / 180);
			y2 = h;
			z2 = d1 * sin((double)angulo * M_PI / 180);
						
			x3 = d2 * cos((double)proxAng * M_PI / 180);
			y3 = proxH;
			z3 = d2 * sin((double)proxAng * M_PI / 180);
						
			x4 = x2;
			y4 = y2;
			z4 = z2;
						
			x5 = d1 * cos((double)proxAng * M_PI / 180);
			y5 = h;
			z5 = d1 * sin((double)proxAng * M_PI / 180);
						
			x6 = x3;
			y6 = y3;
			z6 = z3;
				
			//Base
			drawTriangle(file,x1,y1,z1,x2,y2,z2,x3,y3,z3);

			drawTriangle(file,x4,y4,z4,x5,y5,z5,x6,y6,z6);

			angulo = proxAng;
			proxAng += passoAngulo;
		}
		h = proxH;
		proxH += passo;
	}
	return 0;
}

int drawTorus(std::ofstream &file, double raio, double largura, double altura, int slice, int stack) {
	int ntriangulos = 2 * (stack * slice);

	newFigure(file, ntriangulos);

	if (raio < largura)
	{
		largura = raio;
	}
	if (raio <= 0)
	{
		raio = 1;
	}
	if (stack <= 2)
	{
		stack = 3;
	}
	if (slice <= 2)
	{
		slice = 3;
	}
	if (largura <= 0)
	{
		largura = raio;
	}
	if (altura <= 0)
	{
		altura = largura;
	}

	largura /= 2;
	altura /= 2;
	raio += largura;

	double x1, y1, z1, x2, y2, z2, x3, y3, z3 = 0;
	double x4, y4, z4, x5, y5, z5, x6, y6, z6 = 0;

	double phi = 0;
	double passoPHI = 2 * M_PI / stack;

	double passoTHETA = 2 * M_PI / slice;

	for (int i = 0; i < stack; ++i, phi += passoPHI)
	{
		double theta = 0;
		for (int j = 0; j < slice; ++j, theta += passoTHETA)
		{   
			//Cria triângulos em demasia no ponto mais alto e mais baixo
			x1 = raio * cos(phi + passoPHI) + largura * cos(phi + passoPHI) * cos(theta);
			y1 = altura * sin(theta);
			z1 = raio * sin(phi + passoPHI) + largura * sin(phi + passoPHI) * cos(theta);
			
			x2 = raio * cos(phi) + largura * cos(phi) * cos(theta);
			y2 = altura * sin(theta);
			z2 = raio * sin(phi) + largura * sin(phi) * cos(theta);

			x3 = raio * cos(phi) + largura * cos(phi) * cos(theta + passoTHETA);
 			y3 = altura * sin(theta + passoTHETA);
			z3 = raio * sin(phi) + largura * sin(phi) * cos(theta + passoTHETA);
				
			drawTriangle(file,x1,y1,z1,x2,y2,z2,x3,y3,z3);

			x4 = x1;
			y4 = y1;
			z4 = z1;
			
			x5 = x3;
			y5 = y3;
			z5 = z3;

			x6 = raio * cos(phi + passoPHI) + largura * cos(phi + passoPHI) * cos(theta + passoTHETA);
			y6 = altura * sin(theta + passoTHETA);
			z6 = raio * sin(phi + passoPHI) + largura * sin(phi + passoPHI) * cos(theta + passoTHETA);
										
			drawTriangle(file,x4,y4,z4,x5,y5,z5,x6,y6,z6);
		}
	}

	return 0;
}

int drawPatch(string input, std::ofstream& file, int tesselation) {
	if (tesselation <= 0) tesselation = 1;

	std::string line;
	std::ifstream infile(input);
	
	std::getline(infile, line);
	int noPatches = std::atoi(line.c_str());

	string token;
	string n_line;
	int index;
	double coords;

	vector<double> patch_list;
	
	for (int i = 0; i < noPatches; i++)
	{
		std::getline(infile, line);

		int position;
		for (int j = 0; j < 16; j++) {

			position = line.find(",");
			token = line.substr(0, position);
			index = atoi(token.c_str());
			line.erase(0, position + 1);

			n_line = getLineNumber(input, noPatches + 3 + index);
			//le o ponto.
			for (int j = 0; j < 3; j++) {
				position = n_line.find(",");
				token = n_line.substr(0, position);
				coords = atof(token.c_str());
				n_line.erase(0, position + 1);

				patch_list.push_back(coords);
			}
		}
	}

	vector<double> res = calculatePointsBezier(tesselation, noPatches, patch_list);
	vector<double> normais = calculateNormalBezier(tesselation, noPatches, patch_list);

	int noTriangles = res.size()/(3 * 3);

	newFigure(file, noTriangles);

	for (int i = 0; i < noTriangles * 9; i += 9)
	{
		drawTriangle(file, res.at(i), res.at(i + 1), res.at(i + 2), res.at(i + 3), res.at(i + 4), res.at(i + 5), res.at(i + 6), res.at(i + 7), res.at(i + 8));
	}

	return 0;
}
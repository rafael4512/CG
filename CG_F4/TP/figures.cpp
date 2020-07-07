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

int drawPoint(std::ofstream& file, double x, double y, double z, double nx, double ny, double nz, double tx, double ty)
{
	if (file.is_open())
	{
		file <<
			x << " " << y << " " << z << " " <<
			nx << " " << ny << " " << nz << " " <<
			tx << " " << ty
			<< endl;
		return 0;
	}
	return -1;
}

void drawTriangle(std::ofstream &file,double x1,double y1,double z1,double x2,double y2,double z2,double x3,double y3,double z3, double nx1, double ny1, double nz1, double nx2, double ny2, double nz2, double nx3, double ny3, double nz3, double tx1, double ty1, double tx2, double ty2, double tx3, double ty3)
{
	drawPoint(file, x1, y1, z1, nx1, ny1, nz1, tx1, ty1);
	drawPoint(file, x2, y2, z2, nx2, ny2, nz2, tx2, ty2);
	drawPoint(file, x3, y3, z3, nx3, ny3, nz3, tx3, ty3);
}

int drawPlane(std::ofstream &file, double size)
{
	double coord=size/2;

	if (coord <= 0)
		coord = 1;

	newFigure(file, 4);

	drawTriangle(file,coord,0,coord,coord,0,-coord,-coord,0,coord, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0);
	drawTriangle(file,coord,0,-coord,-coord,0,-coord,-coord,0,coord, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0);
	drawTriangle(file,coord,0,-coord,coord,0,coord,-coord,0,coord, 0, -1, 0, 0, -1, 0, 0, -1, 0, 1, 1, 1, 0, 0, 0);
	drawTriangle(file,-coord,0,coord,-coord,0,-coord,coord,0,-coord, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, 0, 0, 1, 1, 1);

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
		// Para não haver 0 divisões /0 = imp
		if (divX <= 0) divX = 1;
	}
	if (argc >= 8){
		divY = dY;
		// Para não haver 0 divisões /0 = imp
		if (divY <= 0) divY = 1;
	}
	if (argc == 9)
	{
		divZ = dZ;
		// Para não haver 0 divisões /0 = imp
		if (divZ <= 0) divZ = 1;
	}


	// Para não haver
	if (x < 0) x = -x;
	if (y < 0) y = -y;
	if (z < 0) z = -z;

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
			drawTriangle(file,x1,y1,z1,x2,y2,z2,x3,y3,z3, 0, -1, 0, 0, -1, 0, 0, -1, 0,
				(double) 1/3 * (1 +     i/divX), 
				(double) 1/2 * k/divZ,
				(double) 1/3 * (1 +   (i+1)/divX), 
				(double) 1/2 *     k/divZ,
				(double) 1/3 * (1 +     i/divX), 
				(double) 1/2 * (k+1)/divZ);

			drawTriangle(file,x4,y4,z4,x5,y5,z5,x6,y6,z6, 0, -1, 0, 0, -1, 0, 0, -1, 0,
				(double) 1/3 * (1 + (i+1)/divX), 
				(double) 1/2 * k/divZ,
				(double) 1/3 * (1 + (i + 1)/divX), 
				(double) 1/2 * (k+1)/divZ,
				(double) 1/3 * (1 +     i/divX), 
				(double) 1/2 * (k+1)/divZ);


			y1 = y2 = y3 = y4 = y5 = y6 = y/2;


			//Tampo
			drawTriangle(file,x1,y1,z1,x3,y3,z3,x2,y2,z2, 0, 1, 0, 0, 1, 0, 0, 1, 0, 
				(double) 1/3 * (1 +     i/divX), 
				1 - (double) 1 / 2 * k/divZ, 
				(double) 1/3 * (1 +     i/divX), 
				1 - (double) 1 / 2 * (k+1)/divZ, 
				(double) 1/3 * (1 +   (i+1)/divX), 
				1 - (double) 1 / 2 *     k/divZ);

			drawTriangle(file,x4,y4,z4,x6,y6,z6,x5,y5,z5, 0, 1, 0, 0, 1, 0, 0, 1, 0, 
				(double) 1/3 * (1 + (i+1)/divX), 
				 1 - (double) 1 / 2 * k/divZ, 
				(double) 1/3 * (1 +     i/divX), 
				 1 - (double) 1 / 2 * (k+1)/divZ, 
				(double) 1/3 * (1 + (i + 1)/divX), 
				 1 - (double) 1 / 2 * (k+1)/divZ);
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
			y3 = j / divY * y -y/2;
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

			//Face Z esquerda
			drawTriangle(file,x1,y1,z1,x2,y2,z2,x3,y3,z3, 0, 0, -1, 0, 0, -1, 0, 0, -1,
				(double) 1/3 * i / divX,
				(double) 1/2 - (double) 1/2 * j / divY,
				(double) 1/3 * i / divX,
				(double) 1/2 - (double) 1/2 * (j+1) / divY,
				(double) 1/3 * (i+1) / divX,
				(double) 1/2 - (double) 1/2 * j / divY);

			drawTriangle(file,x4,y4,z4,x5,y5,z5,x6,y6,z6, 0, 0, -1, 0, 0, -1, 0, 0, -1,
				(double) 1/3 * i / divX,
				(double) 1/2 - (double) 1/2 * (j+1) / divY,
				(double) 1/3 * (i+1) / divX,
				(double) 1/2 - (double) 1/2 * (j+1) / divY,
				(double) 1/3 * (i+1) / divX,
				(double) 1/2 - (double) 1/2 * j / divY);

			z1 = z2 = z3 = z4 = z5 = z6 = z/2;
				
			//Face Z direita
			drawTriangle(file,x1,y1,z1,x3,y3,z3,x2,y2,z2, 0, 0, 1, 0, 0, 1, 0, 0, 1,
				(double) 1/3 * i / divX,
				1 - (double) 1/2 * j / divY,
				(double) 1/3 * (i+1) / divX,
				1 - (double) 1/2 * j / divY,
				(double) 1/3 * i / divX,
				1 - (double) 1/2 * (j+1) / divY);
			
			drawTriangle(file,x4,y4,z4,x6,y6,z6,x5,y5,z5, 0, 0, 1, 0, 0, 1, 0, 0, 1,
				(double) 1/3 * i / divX,
				1 - (double) 1/2 * (j+1) / divY,
				(double) 1/3 * (i+1) / divX,
				1 - (double) 1/2 * j / divY,
				(double) 1/3 * (i+1) / divX,
				1 - (double) 1/2 * (j+1) / divY);
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

			//Trás
			drawTriangle(file, x1, y1, z1, x2, y2, z2, x3, y3, z3, -1, 0, 0, -1, 0, 0, -1, 0, 0,
				(double) 2/3 +(double) 1/3 * j / divY,
				(double) 1/2 +(double) 1/2 * k / divZ,
				(double) 2/3 +(double) 1/3 * j / divY,
				(double) 1/2 +(double) 1/2 * (k+1) / divZ,
				(double) 2/3 +(double) 1/3 * (j+1) / divY,
				(double) 1/2 +(double) 1/2 * k / divZ);

			drawTriangle(file, x4, y4, z4, x5, y5, z5, x6, y6, z6, -1, 0, 0, -1, 0, 0, -1, 0, 0,
				(double) 2/3 +(double) 1/3 * j / divY,
				(double) 1/2 +(double) 1/2 * (k+1) / divZ,
				(double) 2/3 +(double) 1/3 * (j + 1) / divY,
				(double) 1/2 +(double) 1/2 * (k + 1) / divZ,
				(double) 2/3 +(double) 1/3 * (j+1) / divY,
				(double) 1/2 +(double) 1/2 * k / divZ);

			x1 = x2 = x3 = x4 = x5 = x6 = x/2;

			//Frente
			drawTriangle(file,x1,y1,z1,x3,y3,z3,x2,y2,z2, 1, 0, 0, 1, 0, 0, 1, 0, 0,
				(double) 2/3 +(double) 1/3 *j / divY,
				(double) 1/2 * k / divZ,
				(double) 2/3 +(double) 1/3 *(j+1) / divY,
				(double) 1/2 * k / divZ,
				(double) 2/3 +(double) 1/3 *j / divY,
				(double) 1/2 * (k + 1) / divZ);
			
			drawTriangle(file,x4,y4,z4,x6,y6,z6,x5,y5,z5, 1, 0, 0, 1, 0, 0, 1, 0, 0,
				(double) 2/3 +(double) 1/3 * j / divY,
				(double) 1/2 * (k+1)/divZ,
				(double) 2/3 +(double) 1/3 *(j + 1) / divY,
				(double) 1/2 * k / divZ,
				(double) 2/3 +(double) 1/3 *(j+1) / divY,
				(double) 1/2 * (k+1) / divZ);
		}		
	}
	return 0;
}

int drawSphere(std::ofstream &file, double raio, double slice, double stack)
{

	int ntriangulos = 2 * (stack * slice) - 2 * slice;

	newFigure(file, ntriangulos);

	if (raio <= 0) raio = 1;
	if (stack <= 2) stack = 3;
	if (slice <= 2) slice = 3;

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
				drawTriangle(file, x1, y1, z1, x2, y2, z2, x3, y3, z3,
					(double) x1 / raio,
					(double) y1 / raio,
					(double) z1 / raio,
					(double) x2 / raio,
					(double) y2 / raio,
					(double) z2 / raio,
					(double) x3 / raio,
					(double) y3 / raio, 
					(double) z3 / raio, 
					1 - j / slice, 
					1 - i / stack, 
					1 - (j + 1) / slice, 
					1 - (i + 1) / stack, 
					1 - j / slice, 
					1 - (i + 1) / stack);
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
				
				drawTriangle(file,x4,y4,z4,x5,y5,z5,x6,y6,z6,
					(double) x4 / raio,
					(double) y4 / raio,
					(double) z4 / raio,
					(double) x5 / raio,
					(double) y5 / raio,
					(double) z5 / raio,
					(double) x6 / raio,
					(double) y6 / raio,
					(double) z6 / raio,
					1 - j / slice,
					1 - i / stack,
					1 - (j + 1) / slice,
					1 - i / stack,
					1 - (j + 1) / slice,
					1- (i + 1) / stack);
			}
		}
	}
	return 0;
}

int drawCone(std::ofstream &file, double raio, double alt, int slice, int stack)
{
	int ntriangulos = slice + 2 * (stack * slice);

	newFigure(file, ntriangulos);

	if (raio <= 0) raio  = 1;
	if (stack <= 2) stack = 3;
	if (slice <= 2) slice = 3;

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

		drawTriangle(file,x,y,z,x1,y1,z1,x2,y2,z2, 0, -1, 0, 0, -1, 0, 0, -1, 0,
			0.25,
			0.5,
			(double) 0.25 + (double) 0.25 * x1/raio,
			(double) 0.5 + (double) 0.5 * z1/raio,
			(double) 0.25 + (double) 0.25 * x2/raio,
			(double) 0.5 + (double) 0.5 * z2/raio);

		angulo = proxAng;
		proxAng += passoAngulo;
	}

	double passo = (double) alt/stack;
	double h = 0;
	double proxH = h + passo;

	double x3, x4, y3, y4, z3, z4, x5, x6, y5, y6, z5, z6;
		
	double comp = sqrt(pow(alt, 2) + pow(raio, 2));
	double nx = alt / comp;
	double ny = raio / comp;

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
					
			x2 = d2 * cos((double)proxAng * M_PI / 180);
			y2 = proxH;
			z2 = d2 * sin((double)proxAng * M_PI / 180);
		
			x3 = d1 * cos((double)angulo * M_PI / 180);
			y3 = h;
			z3 = d1 * sin((double)angulo * M_PI / 180);
					
			x4 = x2;
			y4 = y2;
			z4 = z2;

			x5 = d1 * cos((double)proxAng * M_PI / 180);
			y5 = h;
			z5 = d1 * sin((double)proxAng * M_PI / 180);
								
			x6 = x3;
			y6 = y3;
			z6 = z3;
				
			//Lados
			drawTriangle(file, x1, y1, z1, x2, y2, z2, x3, y3, z3, nx * cos((double)angulo * M_PI / 180), ny, nx * sin((double)angulo * M_PI / 180), nx * cos((double)proxAng * M_PI / 180), ny, nx * sin((double)proxAng * M_PI / 180), nx * cos((double)angulo * M_PI / 180), ny, nx * sin((double)angulo * M_PI / 180),
				(double) 0.75 + (double) 0.25 * x1 / raio, // nx == nz
				(double) 0.5 + (double) 0.5 * z1 / raio,
				(double) 0.75 + (double) 0.25 * x2 / raio,
				(double) 0.5 + (double) 0.5 *z2 / raio,
				(double) 0.75 + (double) 0.25 * x3 / raio,
				(double) 0.5 + (double) 0.5 *z3 / raio);

			drawTriangle(file, x4, y4, z4, x5, y5, z5, x6, y6, z6, nx * cos((double)proxAng * M_PI / 180), ny, nx * sin((double)proxAng * M_PI / 180), nx * cos((double)proxAng * M_PI / 180), ny, nx * sin((double)proxAng * M_PI / 180), nx * cos((double)angulo * M_PI / 180), ny, nx * sin((double)angulo * M_PI / 180), 
				(double) 0.75 + (double) 0.25 * x4 / raio,
				(double) 0.5 + (double) 0.5 *z4 / raio,
				(double) 0.75 + (double) 0.25 * x5 / raio,
				(double) 0.5 + (double) 0.5 *z5 / raio,
				(double) 0.75 + (double) 0.25 * x6 / raio,
				(double) 0.5 + (double) 0.5 *z6 / raio);

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

	if (raio < largura) largura = raio;
	if (raio <= 0) raio = 1;
	if (stack <= 2) stack = 3;
	if (slice <= 2) slice = 3;
	if (largura <= 0) largura = raio;
	if (altura <= 0) altura = largura;

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
			double cx1 = raio * cos(phi);
			double cz1 = raio * sin(phi);
			double cx2 = raio * cos(phi + passoPHI);
			double cz2 = raio * sin(phi + passoPHI);

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
				
			drawTriangle(file,x1,y1,z1,x2,y2,z2,x3,y3,z3, (x1 - cx2) / largura, y1/altura, (z1 - cz2)/largura, (x2 - cx1) / largura, y2/altura, (z2 - cz1) / largura, (x3 - cx1) / largura, y3/altura, (z3 - cz1) / largura,
				(double) j /slice,
				(double) (i + 1)/stack,
				(double) j / slice,
				(double) i / stack,
				(double) (j + 1) / slice,
				(double) i / stack);

			x4 = x1;
			y4 = y1;
			z4 = z1;
			
			x5 = x3;
			y5 = y3;
			z5 = z3;

			x6 = raio * cos(phi + passoPHI) + largura * cos(phi + passoPHI) * cos(theta + passoTHETA);
			y6 = altura * sin(theta + passoTHETA);
			z6 = raio * sin(phi + passoPHI) + largura * sin(phi + passoPHI) * cos(theta + passoTHETA);

			drawTriangle(file,x4,y4,z4,x5,y5,z5,x6,y6,z6, (x4-cx2)/largura, y4/altura, (z4-cz2) / largura, (x5-cx1) / largura, y5/altura, (z5-cz1) / largura, (x6-cx2) / largura, y6/altura, (z6-cz2) / largura,
				(double) j / slice,
				(double) (i + 1) / stack,
				(double) (j + 1) / slice,
				(double) i / stack,
				(double) (j + 1) / slice,
				(double) (i + 1) / stack);
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
	vector<double> text = calculateTextureBezier(tesselation, noPatches, patch_list);

	int noTriangles = res.size() / (3 * 3);

	newFigure(file, noTriangles);

	int patch = noTriangles / 16 / tesselation / tesselation;

	for (int i = 0; i < patch; i++)
		for (int j = 0; j < 4 * tesselation; j++)
			for (int k = 0; k < 4 * tesselation; k++)
			{
				int x = (i * 16 * tesselation * tesselation + j * 4 * tesselation + k) * 9;
				int t = (i * 16 * tesselation * tesselation + j * 4 * tesselation + k) * 6;

				drawTriangle(file, res.at(x), res.at(x + 1), res.at(x + 2), res.at(x + 3), res.at(x + 4), res.at(x + 5), res.at(x + 6), res.at(x + 7), res.at(x + 8), normais.at(x), normais.at(x + 1), normais.at(x + 2), normais.at(x + 3), normais.at(x + 4), normais.at(x + 5), normais.at(x + 6), normais.at(x + 7), normais.at(x + 8), text.at(t), text.at(t + 1), text.at(t + 2), text.at(t + 3), text.at(t + 4), text.at(t + 5));
			}

	return 0;
}
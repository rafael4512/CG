#include <stdlib.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <zconf.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#include "direct.h"
#include "zconf.h"
#endif


#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include </usr/local/Cellar/devil/1.8.0_1/include/IL/il.h>
#else
#include <IL/il.h>
#endif

//xml libraries
#include "tinyxml.h"

#include "headers/containerElement.h"
#include "headers/sceneElement.h"
#include "headers/lightElement.h"
#include "headers/groupElement.h"
#include "headers/modelElement.h"
#include "headers/modelsElement.h"
#include "headers/rotateElement.h"
#include "headers/translateElement.h"
#include "headers/scaleElement.h"
#include "headers/baseElement.h"
#include "headers/camera.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>


using namespace std;

string curdir;
SceneElement se;
bool orb = true;
bool isPaused = false;
double speed = 1;
double k;
int lightId = 0;
int nTriangles = 0;
int nLines = 0;


void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if(h == 0)
		h = 1;

	// compute window's aspect ratio
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f ,ratio, 1.0f ,100000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	static float t = 0;

	static float prevFrame = glutGet(GLUT_ELAPSED_TIME);
	k = (glutGet(GLUT_ELAPSED_TIME) - prevFrame);
	prevFrame = glutGet(GLUT_ELAPSED_TIME);


	if (isPaused == false) t += speed * k;
	if (t < 0) t = 0;

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera::placeCamera();
	Camera::drawAxis(20000);


	se.apply(t * 0.001, orb);

	// End of frame
	glutSwapBuffers();
}


void parseXML(TiXmlElement *elem, ContainerElement &parent)
{
	if(!strcmp(elem->Value(),"scene"))
	{
		for(TiXmlElement* aux = elem->FirstChildElement("group"); aux!=NULL; aux=aux->NextSiblingElement("group")){
		//for(TiXmlElement* aux = elem->FirstChildElement(); aux!=NULL; aux=aux->NextSiblingElement()){	
			parseXML(aux,se);
		}
	}
	else if (!strcmp(elem->Value(), "lights"))
	{
		for (TiXmlElement* aux = elem->FirstChildElement("light"); aux != NULL; aux = aux->NextSiblingElement("light")) {
			string type = aux->Attribute("type");
			
			float x = 0, y = 0, z = 0;
			if (aux->QueryFloatAttribute("posX", &x) == TIXML_WRONG_TYPE)	std::cerr << "X tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("posY", &y) == TIXML_WRONG_TYPE)	std::cerr << "Y tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("posZ", &z) == TIXML_WRONG_TYPE)	std::cerr << "Z tem tipo errado" << std::endl;
			
			float ambiR = 1, ambiB = 1, ambiG = 1, diffR = 1, diffG = 1, diffB = 1, specR = 1, specG = 1, specB = 1;
			if (aux->QueryFloatAttribute("specR", &specR) == TIXML_WRONG_TYPE)	std::cerr << "specR tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("specG", &specG) == TIXML_WRONG_TYPE)	std::cerr << "specG tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("specB", &specB) == TIXML_WRONG_TYPE)	std::cerr << "specB tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("ambiR", &ambiR) == TIXML_WRONG_TYPE)	std::cerr << "ambiR tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("ambiG", &ambiG) == TIXML_WRONG_TYPE)	std::cerr << "ambiG tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("ambiB", &ambiB) == TIXML_WRONG_TYPE)	std::cerr << "ambiB tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("diffR", &diffR) == TIXML_WRONG_TYPE)	std::cerr << "diffR tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("diffG", &diffG) == TIXML_WRONG_TYPE)	std::cerr << "diffG tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("diffB", &diffB) == TIXML_WRONG_TYPE)	std::cerr << "diffB tem tipo errado" << std::endl;

			float spotX = 0, spotY = 0, spotZ = -1, cutoff = -1, exp = 0;
			if (aux->QueryFloatAttribute("spotX", &spotX) == TIXML_WRONG_TYPE)	std::cerr << "spotX tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("spotY", &spotY) == TIXML_WRONG_TYPE)	std::cerr << "spotY tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("spotZ", &spotZ) == TIXML_WRONG_TYPE)	std::cerr << "spotZ tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("cutoff", &cutoff) == TIXML_WRONG_TYPE) std::cerr << "cutoff tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("exp", &exp) == TIXML_WRONG_TYPE)		std::cerr << "exp tem tipo errado" << std::endl;

			
			float attX = 1, attY = 0, attZ = 0;
			if (aux->QueryFloatAttribute("attX", &attX) == TIXML_WRONG_TYPE)	std::cerr << "attX tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("attY", &attY) == TIXML_WRONG_TYPE)	std::cerr << "attY tem tipo errado" << std::endl;
			if (aux->QueryFloatAttribute("attZ", &attZ) == TIXML_WRONG_TYPE)	std::cerr << "attZ tem tipo errado" << std::endl;
			

			if (lightId < 8)
			{
				shared_ptr<LightElement> light = make_shared<LightElement>(lightId++, type, x, y, z, ambiR, ambiB, ambiG,
					diffR, diffG, diffB, specR, specG, specB, spotX, spotY, spotZ, cutoff, exp, attX, attY, attZ);
				parent.addChild(light);
			}
		}
	}
	else if(!strcmp(elem->Value(),"group"))
	{
		shared_ptr<GroupElement> ge = make_shared<GroupElement>();
		parent.addChild(ge);
		for(TiXmlElement* aux = elem->FirstChildElement(); aux!=NULL; aux=aux->NextSiblingElement()){
			parseXML(aux, *ge);
		}
	}
	else if(!strcmp(elem->Value(),"models"))
	{
		shared_ptr<ModelsElement> models = make_shared<ModelsElement>();
		parent.addChild(models);
		for(TiXmlElement* aux = elem->FirstChildElement("model"); aux!=NULL; aux=aux->NextSiblingElement("model")){
			parseXML(aux,*models);
		}
	}
	else if(!strcmp(elem->Value(),"model"))
	{
		//Apanhar nome do ficheiro
		string fname=elem->Attribute("file");
		//Apanhar nome do ficheiro de textura
		const char *texfile = elem->Attribute("texture");

		float r = -1, g = -1, b = -1;

		if (elem->QueryFloatAttribute("R", &r) == TIXML_WRONG_TYPE)	std::cerr << "emisR tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("G", &g) == TIXML_WRONG_TYPE)	std::cerr << "emisG tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("B", &b) == TIXML_WRONG_TYPE)	std::cerr << "emisB tem tipo errado" << std::endl;

		float emisR = 0.1, emisG = 0.1, emisB = 0.1, ambiR = 0.1, ambiB = 0.1, ambiG = 0.1;
		float diffR = 0.1, diffG = 0.1, diffB = 0.1, specR = 0.1, specG = 0.1, specB = 0.1;

		if (elem->QueryFloatAttribute("emisR", &emisR) == TIXML_WRONG_TYPE)	std::cerr << "emisR tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("emisG", &emisG) == TIXML_WRONG_TYPE)	std::cerr << "emisG tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("emisB", &emisB) == TIXML_WRONG_TYPE)	std::cerr << "emisB tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("specR", &specR) == TIXML_WRONG_TYPE)	std::cerr << "specR tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("specG", &specG) == TIXML_WRONG_TYPE)	std::cerr << "specG tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("specB", &specB) == TIXML_WRONG_TYPE)	std::cerr << "specB tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("ambiR", &ambiR) == TIXML_WRONG_TYPE)	std::cerr << "ambiR tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("ambiG", &ambiG) == TIXML_WRONG_TYPE)	std::cerr << "ambiG tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("ambiB", &ambiB) == TIXML_WRONG_TYPE)	std::cerr << "ambiB tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("diffR", &diffR) == TIXML_WRONG_TYPE)	std::cerr << "diffR tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("diffG", &diffG) == TIXML_WRONG_TYPE)	std::cerr << "diffG tem tipo errado" << std::endl;
		if (elem->QueryFloatAttribute("diffB", &diffB) == TIXML_WRONG_TYPE)	std::cerr << "diffB tem tipo errado" << std::endl;
		
		float shiny = 32;

		if (elem->QueryFloatAttribute("shiny", &shiny) == TIXML_WRONG_TYPE)	std::cerr << "shiny tem tipo errado" << std::endl;


		shared_ptr<ModelElement> model = make_shared<ModelElement>(fname, texfile, r, g, b,
				emisR, emisG, emisB, ambiR, ambiB, ambiG, diffR, diffG, diffB, specR, specG, specB, shiny);

		//insert in group array
		parent.addChild(model);

	}
	else if(!strcmp(elem->Value(),"translate"))
	{
		float time = 0;
		float x = 0, y = 0, z = 0;
		if (elem->QueryFloatAttribute("time", &time) == TIXML_WRONG_TYPE)	std::cerr << "time tem tipo errado" << std::endl;

		if (time)
		{
			shared_ptr<TranslateElement> translate = make_shared<TranslateElement>(time,x,y,z);

			for (TiXmlElement* aux = elem->FirstChildElement("point"); aux != NULL; aux = aux->NextSiblingElement("point")) {

				if (aux->QueryFloatAttribute("X", &x) == TIXML_WRONG_TYPE) std::cerr << "X tem tipo errado" << std::endl;
				if (aux->QueryFloatAttribute("Y", &y) == TIXML_WRONG_TYPE) std::cerr << "Y tem tipo errado" << std::endl;
				if (aux->QueryFloatAttribute("Z", &z) == TIXML_WRONG_TYPE) std::cerr << "Z tem tipo errado" << std::endl;

				translate->addCoords(x, y, z);
			}
			//Generate curvePoints matrix
			translate->genCurveMatrix();

			//insert in group array
			parent.addChild(translate);
		}
		else
		{
			if (elem->QueryFloatAttribute("X", &x) == TIXML_WRONG_TYPE)	std::cerr << "X tem tipo errado" << std::endl;
			if (elem->QueryFloatAttribute("Y", &y) == TIXML_WRONG_TYPE)	std::cerr << "Y tem tipo errado" << std::endl;
			if (elem->QueryFloatAttribute("Z", &z) == TIXML_WRONG_TYPE)	std::cerr << "Z tem tipo errado" << std::endl;
			
			shared_ptr<TranslateElement> translate = make_shared<TranslateElement>(time,x,y,z);

			//insert in group array
			parent.addChild(translate);
		}
	}
	else if(!strcmp(elem->Value(),"rotate"))
	{
		float time = 0;
		if (elem->QueryFloatAttribute("time", &time) == TIXML_WRONG_TYPE)	std::cerr << "time tem tipo errado" << std::endl;

		float angle = 0, axisX = 0, axisY = 0, axisZ = 0;
		if(elem->QueryFloatAttribute("angle",&angle) == TIXML_WRONG_TYPE)	std::cerr << "angle tem tipo errado" << std::endl;
		if(elem->QueryFloatAttribute("axisX",&axisX) == TIXML_WRONG_TYPE)	std::cerr << "axisX tem tipo errado" << std::endl;
		if(elem->QueryFloatAttribute("axisY",&axisY) == TIXML_WRONG_TYPE)	std::cerr << "axisY tem tipo errado" << std::endl;
		if(elem->QueryFloatAttribute("axisZ",&axisZ) == TIXML_WRONG_TYPE)	std::cerr << "axisZ tem tipo errado" << std::endl;

		shared_ptr<RotateElement> rotate = make_shared<RotateElement>(time, angle, axisX, axisY, axisZ);

		//insert in group array
		parent.addChild(rotate);


	}
	else if(!strcmp(elem->Value(),"scale"))
	{
		float x = 0, y = 0, z = 0;
		if(elem->QueryFloatAttribute("X",&x) == TIXML_WRONG_TYPE)	std::cerr << "X tem tipo errado" << std::endl;
		if(elem->QueryFloatAttribute("Y",&y) == TIXML_WRONG_TYPE)	std::cerr << "Y tem tipo errado" << std::endl;
		if(elem->QueryFloatAttribute("Z",&z) == TIXML_WRONG_TYPE)	std::cerr << "Z tem tipo errado" << std::endl;
		
		shared_ptr<ScaleElement> scale = make_shared<ScaleElement>(x,y,z);

		//insert in group array
		parent.addChild(scale);
	}
}

void parseXML(char* filename){

	TiXmlDocument xml_doc(filename);

	if (!xml_doc.LoadFile()){
		cout<<"Erro ao abrir o ss.xml\t("<< xml_doc.ErrorDesc()<<")\n" ;
	}

	TiXmlElement *elem = xml_doc.FirstChildElement("scene");

	parseXML(elem,se);
}

string getcurDir( void ) {
	char buff[FILENAME_MAX];
	getcwd( buff, FILENAME_MAX );
	string current_working_dir(buff);
	return current_working_dir;
}


void printHelp(){
	cout << "#_____________________________ HELP _____________________________#" << endl;
	cout << "|                                                                |" << endl;
	cout << "| Usage: ./engine                                                |" << endl;
	cout << "|                 [-h]                                           |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   FILE:                                                        |" << endl;
	cout << "| Specify a path to an XML file in which the information about   |" << endl;
	cout << "| the models you wish to create are specified                    |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   MOVE:                                                        |" << endl;
	cout << "|   w: Move your position forward                                |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   s: Move your position back                                   |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   a: Move your position to the left                            |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   d: Move your position to the right                           |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   ↑: Rotate your view up                                       |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   ↓: Rotate your view down                                     |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   ←: Rotate your view to the left                              |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   →: Rotate your view to the right                             |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   q: Go up                                                     |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   z: Go down                                                   |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   p: Pause time                                                |" << endl;
	cout << "|    : Pause time                                                |" << endl;
	cout << "|   0: Pause time                                                |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   FORMAT:                                                      |" << endl;
	cout << "|   .: Change the figure format into points                      |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   -: Change the figure format into lines                       |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   ,: Fill up the figure                                        |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   e: Remove/draw Axis                                          |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   o: Remove/draw routes                                        |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   MOVEMENT:                                                    |" << endl;
	cout << "|   f: Change speed of camera                                    |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   v: Change type of camera                                     |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   r: Revert time                                               |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   *: Increase speed of system                                  |" << endl;
	cout << "|   2: Increase speed of system                                  |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   /: Decrease speed of system                                  |" << endl;
	cout << "|   1: Decrease speed of system                                  |" << endl;
	cout << "#________________________________________________________________#" << endl;
}

vector<string> split(const string& s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}

string appendDir(vector<string> s, char delim) {
	std::string str;

	string delims(1, delim);

	s.pop_back();
	for (auto i : s)
	{
		str.append(i);
		str.append(delims);

		if (i == "Engine") break;
	}
	
	return str;
}

void idleFunc() {
	Camera::idle(k);
}

int main(int argc, char **argv) {
	if (argc>1){
		if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"-help")) {
			printHelp();
			return 0;
		}
	}

	curdir = getcurDir();

	char delims;

	#ifdef __APPLE__
	delims = '//';
	#else
	delims = '\\';
    #endif

	vector<string> v = split(curdir, delims);
	curdir = appendDir(v, delims);

// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(200, 100);
	glutInitWindowSize(600, 500);
	glutCreateWindow("CG@DI-UM");

	Camera::resetKeys();
// Required callback registry 
	glutDisplayFunc(renderScene);
	glutIdleFunc(idleFunc);
	glutReshapeFunc(changeSize);

// Callback registration for keyboard processing
	glutIgnoreKeyRepeat;
	glutKeyboardFunc(Camera::keyDown);
	glutKeyboardUpFunc(Camera::keyUp);
	glutSpecialFunc(Camera::specialDown);
	glutSpecialUpFunc(Camera::specialUp);

#ifndef __APPLE__
	glewInit();
#endif

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);

	//Cria-se uma string com a diretoria do ficheiro xml
	string xml(curdir);
	xml.append("xmlfiles/ss.xml"); //ss.xml demoLightMatTexture.xml demoCatmullNoLight.xml ssRGB.xml ssNoMat
	char *xml_filename = (char *) xml.c_str();
	parseXML(xml_filename);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;

}

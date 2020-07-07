#include <stdlib.h>

//xml libraries
#include "tinyxml.h"

#include "headers/containerElement.h"
#include "headers/sceneElement.h"
#include "headers/groupElement.h"
#include "headers/modelElement.h"
#include "headers/modelsElement.h"
#include "headers/rotateElement.h"
#include "headers/translateElement.h"
#include "headers/scaleElement.h"
#include "headers/triangle.h"
#include "headers/baseElement.h"
#include "headers/camera.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>



#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <zconf.h>
#else
#include <GL/glut.h>
#include "direct.h"
#include "zconf.h"
#endif

using namespace std;

string curdir;
SceneElement se;


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
	gluPerspective(45.0f ,ratio, 1.0f ,1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Camera::placeCamera();
	Camera::drawAxis(100);

	se.Apply();

	// End of frame
	glutSwapBuffers();
}

// write function to process keyboard events
void keyboardIsPressed(unsigned char key, int x, int y){
	Camera::keyboardIsPressed(key, x, y);
}

void processSpecialKeys(int key, int xx, int yy) {
	Camera::processSpecialKeys(key, xx, yy);
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

		double r = 1, g = 1, b = 1;
		if(elem->QueryDoubleAttribute("R",&r) == TIXML_WRONG_TYPE)	std::cerr << "R tem tipo errado" << std::endl;

		if(elem->QueryDoubleAttribute("G",&g) == TIXML_WRONG_TYPE)	std::cerr << "G tem tipo errado" << std::endl;

		if(elem->QueryDoubleAttribute("B",&b) == TIXML_WRONG_TYPE)	std::cerr << "B tem tipo errado" << std::endl;

		//insert in triangulos
		shared_ptr<ModelElement> model = make_shared<ModelElement>(fname,r,g,b);
		
		//insert in group array
		parent.addChild(model);
	}
	else if(!strcmp(elem->Value(),"translate"))
	{
		double x = 0, y = 0, z = 0;
		if(elem->QueryDoubleAttribute("X",&x) == TIXML_WRONG_TYPE)	std::cerr << "X tem tipo errado" << std::endl;

		if(elem->QueryDoubleAttribute("Y",&y) == TIXML_WRONG_TYPE)	std::cerr << "Y tem tipo errado" << std::endl;

		if(elem->QueryDoubleAttribute("Z",&z) == TIXML_WRONG_TYPE)	std::cerr << "Z tem tipo errado" << std::endl;


		shared_ptr<TranslateElement> translate = make_shared<TranslateElement>(x,y,z);

		//insert in group array
		parent.addChild(translate);

	}
	else if(!strcmp(elem->Value(),"rotate"))
	{
		double angle = 0, axisX = 0, axisY = 0, axisZ = 0;
		if(elem->QueryDoubleAttribute("angle",&angle) == TIXML_WRONG_TYPE)	std::cerr << "angle tem tipo errado" << std::endl;

		if(elem->QueryDoubleAttribute("axisX",&axisX) == TIXML_WRONG_TYPE)	std::cerr << "axisX tem tipo errado" << std::endl;

		if(elem->QueryDoubleAttribute("axisY",&axisY) == TIXML_WRONG_TYPE)	std::cerr << "axisY tem tipo errado" << std::endl;

		if(elem->QueryDoubleAttribute("axisZ",&axisZ) == TIXML_WRONG_TYPE)	std::cerr << "axisZ tem tipo errado" << std::endl;


		shared_ptr<RotateElement> rotate = make_shared<RotateElement>(angle, axisX, axisY, axisZ);

		//insert in group array
		parent.addChild(rotate);


	}
	else if(!strcmp(elem->Value(),"scale"))
	{
		double x = 0, y = 0, z = 0;
		if(elem->QueryDoubleAttribute("X",&x) == TIXML_WRONG_TYPE)	std::cerr << "X tem tipo errado" << std::endl;

		if(elem->QueryDoubleAttribute("Y",&y) == TIXML_WRONG_TYPE)	std::cerr << "Y tem tipo errado" << std::endl;

		if(elem->QueryDoubleAttribute("Z",&z) == TIXML_WRONG_TYPE)	std::cerr << "Z tem tipo errado" << std::endl;
		
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
	cout << "|   Pag_UP: Zoom in                                              |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   Pag_Down: Zoom out                                           |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   q: Go up                                                     |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   z: Go down                                                   |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   FORMAT:                                                      |" << endl;
	cout << "|   .: Change the figure format into points                      |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   -: Change the figure format into lines                       |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   ,: Fill up the figure                                        |" << endl;
	cout << "|                                                                |" << endl;
	cout << "|   e: Remove/draw Axis                                          |" << endl;
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

int main(int argc, char **argv) {
	printHelp();
	if (argc>1){
		if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"-help")) {
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
	glutInitWindowPosition(0, 150);
	glutInitWindowSize(800, 1000);
	glutCreateWindow("CG@DI-UM");

// Required callback registry
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);


// put here the registration of the keyboard callbacks
	glutKeyboardFunc(keyboardIsPressed);
	glutSpecialFunc(processSpecialKeys);

	//Cria-se uma string com a diretoria do ficheiro xml
	string xml(curdir);
	xml.append("xmlfiles/ss.xml"); //filetest.xml
	char *xml_filename = (char *) xml.c_str();
	parseXML(xml_filename); 

//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
	glutMainLoop();

	return 1;

}

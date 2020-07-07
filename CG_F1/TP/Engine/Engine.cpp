#include <stdlib.h>

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#include <zconf.h>
#else
#include <GL/glut.h>
#include "direct.h"
#include "zconf.h"
#endif

#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>

//xml libraries
#include "tinyxml.h"

#include <iostream>
#include <vector>
using namespace std;

float xx = 0;
float yy = 0;
float zz = 10;
float cxx = 0;
float cyy = 0;
float czz = 0;
float angleX0Z = 0;
float angle0Y = 0;

string curdir;

struct Triangulo {
    float x1;
    float y1;
    float z1;

    float x2;
    float y2;
    float z2;

    float x3;
    float y3;
    float z3;

    Triangulo* prox;
};

struct ListaFiguras {
    Triangulo *figura;
    ListaFiguras *prox;
};

ListaFiguras *figurasGlobal = NULL;

ListaFiguras* initLFig() {
    ListaFiguras* tmp = (ListaFiguras*)malloc(sizeof(ListaFiguras));
    tmp->figura = NULL;
    tmp->prox = NULL;
    return tmp;
}

Triangulo* initTriangulo() {
    Triangulo* tmp = (Triangulo*)malloc(sizeof(Triangulo));
    tmp->x1 = tmp->y1 = tmp->z1 = tmp->x2 = tmp->y2 = tmp->z2 = tmp->x3 = tmp->y3 = tmp->z3 = NULL;
    tmp->prox = NULL;
    return tmp;
}

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

void desenharFigura(){
    glBegin(GL_TRIANGLES);
    ListaFiguras* tmp = figurasGlobal;
    int j = 0;
    for (; tmp != NULL ; j++, tmp = tmp->prox)
    {
        int i = 0;
        Triangulo *triangulo = tmp->figura;
        for (; triangulo != NULL; i++, triangulo = triangulo->prox) {

            glColor3f(1.0f, 0.0f, 0.0f);
            glVertex3f(triangulo->x1, triangulo->y1, triangulo->z1);
            glColor3f(0.0f, 1.0f, 0.0f);
            glVertex3f(triangulo->x2, triangulo->y2, triangulo->z2);
            glColor3f(0.0f, 0.0f, 1.0f);
            glVertex3f(triangulo->x3, triangulo->y3, triangulo->z3);
        }
    }

    glEnd();

}

float deg2rad(float deg){
    return deg * M_PI / 180;
}

void renderScene(void) {
    // clear buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set the camera
    glLoadIdentity();
    gluLookAt(
            (double) xx, yy, (double) zz,
            cxx, cyy, czz,
            0, 1, 0);


    // put drawing instructions here
    glBegin(GL_LINES);
    // X axis in red
    glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-100.0f, 0.0f, 0.0f); glVertex3f( 100.0f, 0.0f, 0.0f);
    // Y Axis in Green
    glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, -100.0f, 0.0f); glVertex3f(0.0f, 100.0f, 0.0f);
    // Z Axis in Blue
    glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, -100.0f); glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();

    desenharFigura();
    // End of frame
    glutSwapBuffers();
}

// write function to process keyboard events
void keyboardIsPressed(unsigned char key, int x, int y){
    float raio = sqrtf((xx - cxx) * (xx - cxx) + (zz - czz) * (zz - czz));

    switch (key){

        case 'a':
            // Andar para a esquerda
            xx -= 0.1 * cos(angleX0Z);
            cxx -= 0.1 * cos(angleX0Z);
            zz += 0.1 * sin(-angleX0Z);
            czz += 0.1 * sin(-angleX0Z);
            glutPostRedisplay();
            break;
        case 'd':
            // Andar para a direita
            xx += 0.1 * cos(angleX0Z);
            cxx += 0.1 * cos(angleX0Z);
            zz -= 0.1 * sin(-angleX0Z);
            czz -= 0.1 * sin(-angleX0Z);
            glutPostRedisplay();
            break;
        case 'w':
            // Andar em frente
            xx += 0.1 * sin(angleX0Z);
            cxx += 0.1 * sin(angleX0Z);
            zz -= 0.1 * cos(angleX0Z);
            czz -= 0.1 * cos(angleX0Z);
            glutPostRedisplay();
            break;
        case 's':
            // Andar em frente
            xx -= 0.1 * sin(angleX0Z);
            cxx -= 0.1 * sin(angleX0Z);
            zz += 0.1 * cos(angleX0Z);
            czz += 0.1 * cos(angleX0Z);
            glutPostRedisplay();
            break;
        case 'q':
            // Levantar
            yy += 0.1;
            cyy += 0.1;
            glutPostRedisplay();
            break;
        case 'z':
            // Baixar
            yy -= 0.1;
            cyy -= 0.1;
            glutPostRedisplay();
            break;
        case 'm':
            // Olhar para a direita
            angleX0Z += 0.05;
            cxx = xx + raio * sin(angleX0Z);
            czz = zz - raio * cos(angleX0Z);
            glutPostRedisplay();
            break;
        case 'n':
            // Olhar para a esquerda
            angleX0Z -= 0.05;
            cxx = xx + raio * sin(angleX0Z);
            czz = zz - raio * cos(angleX0Z);
            glutPostRedisplay();
            break;
        case '-':
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glutPostRedisplay();
            break;
        case '.':
            glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
            glutPostRedisplay();
            break;
        case ',':
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            glutPostRedisplay();
            break;

        case 'k':
            // Olhar para cima
            cyy += 1.5;
            glutPostRedisplay();
            break;
        case 'j':
            // Olhar para cima
            cyy -= 1.5;
            glutPostRedisplay();
            break;

        case 'e':
            xx -= (xx - cxx) / 2;
            yy -= (yy - cyy) / 2;
            zz -= (zz - czz) / 2;
            glutPostRedisplay();
            break;
        case 'c':
            // Afastar
            xx += (xx - cxx) / 2;
            yy += (yy - cyy) / 2;
            zz += (zz - czz) / 2;
            glutPostRedisplay();
            break;

        default:
            break;
    }
}

/**
 * Nesta função é feito o parse do nome de todos os ficheiros indicados pelo elemento model do xml.
 * @param filename diretoria do ficheiro XML
 * @return
 */
vector<string> parseXML(char* filename){

    TiXmlDocument xml_doc(filename);
    vector<string> res;
    if (!xml_doc.LoadFile()){
        cout<<"Erro ao abrir o file.xml\t("<< xml_doc.ErrorId()<<")\n" ;
        return res;
    }

    TiXmlElement *elem = xml_doc.FirstChildElement("scene");
    for(TiXmlElement* aux = elem->FirstChildElement("model"); aux!=NULL; aux=aux->NextSiblingElement("model") ){
        string fname=aux->Attribute("file");

        //Serve para tirar o carater das aspas\" \" da string  acima.
        fname.resize(fname.size());
        string path(curdir);
        path.append("Figures/");
        path.append(fname.c_str());


        //coloca no vetor.
        res.push_back(path);
    }
    return res;
}

int parseFig(char* filename,struct Triangulo **fig){
    //const char * filename="ola";

    //FILE * f = fopen("/Users/ril/Desktop/CG/CG_Generator/CG_Generator/plane.3d", "r");
    FILE * f = fopen(filename,"r");

    if (!f){//se for null
        cout << " Nao foi possivel abrir o ficheiro "<<filename <<"\n";
        return false;

    }
    //o int está omitido. poderia-se colocar unsigned  int .
    unsigned ntriangles = 0; //primeira linha
    fscanf(f, "%u\n", &ntriangles);


    Triangulo* tmp = initTriangulo();
    Triangulo* inicio = tmp;
    int i;
    for (i=0; i < ntriangles; i++) {
        int res = fscanf(f,
                         "%f %f %f %f %f %f %f %f %f\n",
                         &(tmp->x1), &(tmp->y1), &(tmp->z1),
                         &(tmp->x2), &(tmp->y2), &(tmp->z2),
                         &(tmp->x3), &(tmp->y3), &(tmp->z3));

        if (res != 9) break;

        tmp->prox = initTriangulo();
        tmp = tmp->prox;
    }

    fclose(f);

    if (i == ntriangles) {
        *fig = inicio;
    }
    else {
        free(tmp);
    }

    return i == ntriangles;
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
    cout << "| Usage: ./engine 			                                     |" << endl;
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
    cout << "|   j: Rotate your view up                     		             |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   k: Rotate your view down                         		     |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   n: Rotate your view to the left 		                     |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   m: Rotate your view to the right       		                 |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   e: Zoom in 			                                         |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   c: Zoom out			                                         |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   q: Go up				                                     |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   z: Go down				                                     |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   FORMAT:                                                      |" << endl;
    cout << "|   .: Change the figure format into points                      |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   -: Change the figure format into lines                       |" << endl;
    cout << "|                                                                |" << endl;
    cout << "|   ,: Fill up the figure                                        |" << endl;
    cout << "#________________________________________________________________#" << endl;
}

int main(int argc, char **argv) {
    if (argc>1){
        if(!strcmp(argv[1],"-h") || !strcmp(argv[1],"-help")) {
            printHelp();
            return 0;
        }
    }


    curdir = getcurDir();
#ifdef __APPLE__
    curdir.resize(curdir.size() - 17);
#else
    curdir.resize(curdir.size() - 5);
#endif


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

    //Cria-se uma string com a diretoria do ficheiro xml
    string xml(curdir);
    xml.append("file.xml");

    char *xml_filename = (char *) xml.c_str();

    vector<string> filenames = parseXML(xml_filename);

    int N = filenames.size();

    figurasGlobal = initLFig();
    ListaFiguras *figuraAtual = figurasGlobal;
    Triangulo *fig;
    for (int i = 0; i < N; i++) {
        parseFig((char *) filenames[i].c_str(), &fig);
        figuraAtual->figura = fig;
        figuraAtual->prox = initLFig();
        figuraAtual = figuraAtual->prox;
    }

//  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

// enter GLUT's main cycle
    glutMainLoop();

    return 1;

}
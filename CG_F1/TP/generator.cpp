#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <fstream>

//xml libraries
#include "Engine/tinyxml/tinyxml.h"
#include <string>

//our libraries
#include "headers/figures.h"

using namespace std;


void help(){
    cout << "#_____________________________ HELP ______________________________________#" << endl;
    cout << "|                                                                         |" << endl;
    cout << "|   Usage: ./generator {COMMAND} ... {OUTPUT FILE}                        |" << endl;
    cout << "|                      [-h]                                               |" << endl;
    cout << "|                                                                         |" << endl;
    cout << "|   COMMANDS:                                                             |" << endl;
    cout << "| - plane [SIZE]                                                          |" << endl;
    cout << "|      Creates a square in the XZ plane, centred in the origin.           |" << endl;
    cout << "|                                                                         |" << endl;
    cout << "| - box [SIZE X] [SIZE Y] [SIZE Z] [DIVISION X] [DIVISION Y] [DIVISION Z] |" << endl;
    cout << "|      Creates a box with the dimensions and divisions specified.         |" << endl;
    cout << "|                                                                         |" << endl;
    cout << "| - sphere [RADIUS] [SLICE] [STACK]                                       |" << endl;
    cout << "|      Creates a sphere with the radius, number of slices and             |" << endl;
    cout << "|      stacks given.                                                      |" << endl;
    cout << "|                                                                         |" << endl;
    cout << "| - cone [RADIUS] [HEIGHT] [SLICE] [STACK]                                |" << endl;
    cout << "|      Creates a cone with the radius, height, number of slices           |" << endl;
    cout << "|      and stacks given.                                                  |" << endl;
    cout << "|                                                                         |" << endl;
    cout << "|   OUTPUT FILE:                                                          |" << endl;
    cout << "| In the file section you can specify any file in which you wish          |" << endl;
    cout << "| to save the coordinates generated with the previous commands.           |" << endl;
    cout << "|                                                                         |" << endl;
    cout << "#_________________________________________________________________________#" << endl;
}

//Retorna 0 se inseriu ou -1 se figurefile já existia
int writeXMLFile(char *xmlfile, char *figurefile)
{
    TiXmlDocument doc(xmlfile);
    TiXmlElement *element;

    if (!doc.LoadFile() || !doc.FirstChild("scene"))
    {
        element = new TiXmlElement("scene");
        doc.LinkEndChild(element);
    }

    element = doc.FirstChildElement("scene");
    TiXmlElement *aux = element->FirstChildElement("model");

    //Vai a todos os irmão verificar se o nome do ficheiro já está inserido no xmlfile
    while(aux)
    {
        if(!strcmp(aux->Attribute("file"),figurefile)) return -1;
        aux = aux->NextSiblingElement();
    }
    //Cria elemento com nome model e colaca o respetivo atributo
    TiXmlElement *model = new TiXmlElement("model");
    model->SetAttribute("file", figurefile);

    element->LinkEndChild(model);

    doc.SaveFile(xmlfile);
    return 0;
}

int main(int argc, char const *argv[])
{

    if(argc < 4 || !strcmp(argv[1],"-h") || !strcmp(argv[1],"-help"))
    {
        help();
        return 0;
    }

    // Nome ficheiro
    char *grap = strdup(argv[1]);
    char *fileXML = strdup("Engine/file.xml");

    std::ofstream file;
    file.open(argv[argc-1], ios::trunc);

    if (strcmp("plane",grap) == 0 && argc == 4)
    {
        drawPlane(file,atof(argv[2]));

        char *nomeFig = strdup(argv[argc-1]);
        writeXMLFile(fileXML, nomeFig+15);
    }
    else if (strcmp("box",grap) == 0 && argc >= 6)
    {
        drawBox(file, atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), argc);

        char *nomeFig = strdup(argv[argc-1]);
        writeXMLFile(fileXML, nomeFig+15);
    }
    else if (strcmp("sphere",grap) == 0 && argc == 6)
    {
        drawSphere(file, atof(argv[2]), atoi(argv[3])-1, atoi(argv[4])-1);

        char *nomeFig = strdup(argv[argc-1]);
        writeXMLFile(fileXML, nomeFig+15);
    }
    else if (strcmp("cone",grap) == 0 && argc == 7)
    {
        drawCone(file, atof(argv[2]), atof(argv[3]), atoi(argv[4]), atoi(argv[5]));

        char *nomeFig = strdup(argv[6]);
        writeXMLFile(fileXML, nomeFig+15);
    }
    else
    {
        printf("Error command not found!\n");
    }

    file.close();

    return 0;
}

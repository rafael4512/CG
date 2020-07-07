#include "../headers/modelElement.h"



extern string curdir;
ModelElement::ModelElement(string filename, float red, float green, float blue)
{
	this->r = red;
	this->g = green;
	this->b = blue;

	filename.resize(filename.size());
	string path(curdir);
	path.append("Figures/");
	path.append(filename.c_str());

	prepareModel(path.c_str());
}

int ModelElement::prepareModel(const char* filename) {

	FILE * f = fopen(filename,"r");
	if (!f){//se for null
		cout << " Nao foi possivel abrir o ficheiro "<< filename <<"\n";
		return false;
	}

	int i;
	std::vector<float> vbo;
	float x1,x2,x3,y1,y2,y3,z1,z2,z3;

	int ntriangles = 0; //primeira linha
	fscanf(f, "%d\n", &ntriangles);

	for (i = 0; i < ntriangles; i++) {
		int res = fscanf(f, "%f %f %f %f %f %f %f %f %f\n",
						 &x1, &y1, &z1, &x2, &y2, &z2, &x3, &y3, &z3);

		vbo.push_back(x1); vbo.push_back(y1); vbo.push_back(z1);

		vbo.push_back(x2); vbo.push_back(y2); vbo.push_back(z2);

		vbo.push_back(x3); vbo.push_back(y3); vbo.push_back(z3);
	}

	this->vertexCount = vbo.size() / 3;

	// criar o VBO
	glGenBuffers(1, this->buffers);

	// copiar o vector para a memória gráfica
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
	glBufferData(
		GL_ARRAY_BUFFER, // tipo do buffer, só é relevante na altura do desenho
		sizeof(float) * vbo.size(), // tamanho do vector em bytes
		vbo.data(), // os dados do array associado ao vector
		GL_STATIC_DRAW); // indicativo da utilização (estático e para desenho)

	glVertexPointer(3,GL_FLOAT,0,0);
}


void ModelElement::apply(float t, bool orb)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->buffers[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

    glColor3f(r, g, b);
	glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);

} 
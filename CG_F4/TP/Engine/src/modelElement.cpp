#include "../headers/modelElement.h"

extern string curdir;
extern int nTriangles;

ModelElement::ModelElement(string filename, const char *texFile, float red, float green, float blue, float emisR, float emisG, float emisB,
		float ambiR, float ambiB, float ambiG, float diffR, float diffG, float diffB, float specR, float specG, float specB, float shiny)
{
	this->color[0] = red; this->color[1] = green; this->color[2] = blue; this->color[3] = 1.0; // alpha
	this->cEmis[0] = emisR; this->cEmis[1] = emisG; this->cEmis[2] = emisB; this->cEmis[3] = 1;
	this->cAmbi[0] = ambiR; this->cAmbi[1] = ambiG; this->cAmbi[2] = ambiB; this->cAmbi[3] = 1;
	this->cDiff[0] = diffR; this->cDiff[1] = diffG; this->cDiff[2] = diffB; this->cDiff[3] = 1;
	this->cSpec[0] = specR; this->cSpec[1] = specG; this->cSpec[2] = specB; this->cSpec[3] = 1;
	this->shiny = shiny;

	filename.resize(filename.size());
	string path(curdir);
	path.append("Figures/");
	path.append(filename.c_str());
	prepareModel(path.c_str());

	if (texFile != NULL)
	{
		this->hasTex = true;
		string tfile = texFile;
		tfile.resize(tfile.size());
		string pathTex(curdir);
		pathTex.append("textures/");
		pathTex.append(tfile.c_str());
		loadTexture(pathTex.c_str());
	}
	else
		this->hasTex = false;
}

int ModelElement::prepareModel(const char* filename) {

	FILE * f = fopen(filename,"r");
	if (!f){//se for null
		cout << " Nao foi possivel abrir o ficheiro "<< filename <<"\n";
		return false;
	}

	std::vector<float> v, n, t;
	float x, y, z, nx, ny, nz, tx, ty;

        int ntriangles = 0; //primeira linha
        fscanf(f, "%d\n", &ntriangles);

        for (int i = 0; i < ntriangles*3; i++) {
            int res = fscanf(f, "%f %f %f %f %f %f %f %f\n",
			&x, &y, &z, &nx, &ny, &nz, &tx, &ty);

		v.push_back(x); v.push_back(y); v.push_back(z);
		n.push_back(nx); n.push_back(ny); n.push_back(nz);
		t.push_back(tx); t.push_back(ty);
		
	}
	this->vertexCount = v.size() / 3;

	nTriangles = this->vertexCount / 3;

	glGenBuffers(1, &(this->vertices));
	glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 3, v.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &(this->normals));
	glBindBuffer(GL_ARRAY_BUFFER, this->normals);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexCount * 3, n.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &(this->texCoords));
	glBindBuffer(GL_ARRAY_BUFFER, this->texCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * vertexCount, t.data(), GL_STATIC_DRAW);	
	

	glVertexPointer(3,GL_FLOAT,0,0);//
}


void ModelElement::apply(float t, bool orb)
{
	
	//glPushMatrix();
	
	if (!glIsEnabled(GL_LIGHTING))
	{
		float alpha = 1;
		glColor4f(this->color[0], this->color[1], this->color[2], alpha);
	}
	else {

		if (this->color[0] != -1 && this->color[1] != -1 && this->color[2] != -1)
			glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, this->color);
		else
		{
			glMaterialfv(GL_FRONT, GL_AMBIENT, this->cAmbi);
			glMaterialfv(GL_FRONT, GL_DIFFUSE, this->cDiff);
		}

		glMaterialfv(GL_FRONT, GL_EMISSION, this->cEmis);
		glMaterialfv(GL_FRONT, GL_SPECULAR, this->cSpec);
		glMaterialf(GL_FRONT, GL_SHININESS, this->shiny);

	}

	


	glBindBuffer(GL_ARRAY_BUFFER, this->vertices);
	glVertexPointer(3, GL_FLOAT, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, this->normals);
	glNormalPointer(GL_FLOAT, 0, 0);

	if (hasTex)
	{
		glBindTexture(GL_TEXTURE_2D, this->texID);
		glBindBuffer(GL_ARRAY_BUFFER, this->texCoords);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);	
	}

	glDrawArrays(GL_TRIANGLES, 0, this->vertexCount);

	glBindTexture(GL_TEXTURE_2D, 0);

	//glPopMatrix();

} 

void ModelElement::loadTexture(std::string s) {

	unsigned int t, tw, th;
	unsigned char* texData;

	ilInit();
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring)s.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &(this->texID));

	glBindTexture(GL_TEXTURE_2D, this->texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);

}
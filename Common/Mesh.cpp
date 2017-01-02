#include <stdafx.h>
#include "Mesh.h"
#include <algorithm>
#include <cctype>

typedef struct {
	float x, y, z;
	float nx, ny, nz;
};

Mesh::Mesh()
{
}

Mesh::Mesh(std::string sFilename)
{
	this->load(sFilename);
}

void removeChar(char str[], char t)
{
	int i, iIntegers;
	i = 0;
	while (i<strlen(str))
	{
		if (str[i] == t)
		{
			for (iIntegers = i; iIntegers<strlen(str); iIntegers++)
				str[iIntegers] = str[iIntegers + 1];
		}
		else i++;
	}
}

bool Mesh::load(std::string sFilename)
{
	FILE* infile;

	std::string sFileLocation = ks_ModelPath + sFilename;
	
	char *file = new char[100];
	strcpy_s(file,100, sFileLocation.c_str());

	bool bHasNormals = false;
	bool bHasTexture = false;

	std::vector<float> fFloats;		//Temp float for parsed data
	std::vector<int> iIntegers;		//Temporary integers for parsed data
	fFloats.resize(3);
	iIntegers.resize(9);

	//Open file
	fopen_s(&infile, file, "r");
	
	if (infile == NULL) {
		return false;
	}
	//Parse file
	char line[100];
	while (fgets(line, 100, infile)) {	//Read line
		char sCharacter[3] = " ";	//Empty sCharacter
		
		sscanf_s(line, "%s", sCharacter, 3);

		if (!(strcmp(sCharacter, "v"))) {
			sscanf_s(line, "%*s %f %f %f", &fFloats[0], &fFloats[1], &fFloats[2]);
			vf_vertices.push_back(fFloats[0]);
			vf_vertices.push_back(fFloats[1]);
			vf_vertices.push_back(fFloats[2]);
			//printf_s(line, "%s%f%f%f \n");
		}
		else if (!(strcmp(sCharacter, "vn"))) {
			sscanf_s(line, "%*s%f%f%f", &fFloats[0], &fFloats[1], &fFloats[2]);
			vf_vertNormals.push_back(fFloats[0]);
			vf_vertNormals.push_back(fFloats[1]);
			vf_vertNormals.push_back(fFloats[2]);
			//printf_s(line, "%s%f%f%f\n");
		}
		else if (!(strcmp(sCharacter, "f"))) {
			int iFormat = 0;	//Line lenght to determine line format
			int iSlashCounter = 0;
			for (int i = 0; i < strlen(line); i++) {
				if (line[i] == '/') iSlashCounter++;
			}

			//"0 index" -1 applied to index data stored as OpenGL stores vertex data starting at 0;

			//If statements determine format to be read
			if (iSlashCounter <= 0) {
				//Read VertexIndices format: f i i i
				sscanf_s(line, "%*s%i%i%i", &iIntegers[0], &iIntegers[1], &iIntegers[2]);

				for (int i = 0; i < 3; i++) { vi_vertIndices.push_back(iIntegers[i]-1); } //Store data
			}
			else if (iSlashCounter <= 3) {
				//Read VertexIndices/TextureCoordIndices: f i/i i/i i/i
				sscanf_s(line, "%*s%i/%i %i/%i %i/%i", &iIntegers[0], &iIntegers[3], &iIntegers[1], &iIntegers[4], &iIntegers[2], &iIntegers[5]);

				for (int i = 0; i < 3; i++) { vi_vertIndices.push_back(iIntegers[i]-1); } //Store data
				for (int i = 3; i < 6; i++) { vi_textIndices.push_back(iIntegers[i]-1); }
			}
			else if (strstr(line, "//") != NULL) {
				//Read VertexIndices/VertexNormalIndices: f i//i i//i i//i
				sscanf_s(line, "%*s %i//%i %i//%i %i//%i", &iIntegers[0], &iIntegers[3], &iIntegers[1], &iIntegers[4], &iIntegers[2], &iIntegers[5]);
				for (int i = 0; i < 3; i++) { vi_vertIndices.push_back(iIntegers[i]-1); }	//Store data
				for (int i = 3; i < 6; i++) { vi_vertNormIndices.push_back(iIntegers[i]-1); }
			}
			else {
				//Read VertexIndices/TextureCoordIndices/VertexNormalIndices : f i/i/i i/i/i i/i/i 
				sscanf_s(
					line,
					"%*s %i/%i/%i %i/%i/%i %i/%i/%i",
					&iIntegers[0], &iIntegers[3], &iIntegers[6],
					&iIntegers[1], &iIntegers[4], &iIntegers[7],
					&iIntegers[2], &iIntegers[5], &iIntegers[8]
				);
				for (int i = 0; i < 3; i++) { vi_vertIndices.push_back(iIntegers[i]-1); }		//Store data
				for (int i = 3; i < 6; i++) { vi_textIndices.push_back(iIntegers[i]-1); }
				for (int i = 6; i < 9; i++) { vi_vertNormIndices.push_back(iIntegers[i]-1); }
			}

			//printf_s(line);
		}
		else if (!(strcmp(sCharacter, "vt"))) {
			//Process vertex texture
			sscanf_s(line, "%*s %f %f", &fFloats[0], &fFloats[1]);
			vf_textCoords.push_back(fFloats[0]);	//Store data
			vf_textCoords.push_back(fFloats[1]);
		}
		else {

		}
	}

	//Expand vertices in order to use UVs
	for (std::vector<GLuint>::iterator it = vi_vertIndices.begin(); it != vi_vertIndices.end(); ++it) {
		GLuint iIndex = *it * 3;	//Vertex index
		vf_expandedVertices.push_back(vf_vertices.at(iIndex));
		vf_expandedVertices.push_back(vf_vertices.at(iIndex+1));
		vf_expandedVertices.push_back(vf_vertices.at(iIndex+2));
	}

	for (std::vector<GLuint>::iterator it = vi_textIndices.begin(); it != vi_textIndices.end(); ++it) {
		GLuint iIndex = *it * 2;	//Vertex index
		vf_expandedTexCoords.push_back(vf_textCoords.at(iIndex));
		vf_expandedTexCoords.push_back(vf_textCoords.at(iIndex + 1));
	}

	delete[] file;
	fclose(infile);
	return true;
}

//const std::vector<GLfloat>&  Mesh::getVertices()
//{
//	return this->vf_vertices;
//}
//const std::vector<GLuint>&  Mesh::getVertIndices()
//{
//	return this->vi_vertIndices;
//}
const std::vector<GLfloat>& Mesh::getExpandedVertices()
{
	return this->vf_expandedVertices;
}
const std::vector<GLfloat>& Mesh::getExpandedTexCoords()
{
	return this->vf_expandedTexCoords;
}
const std::vector<GLfloat>& Mesh::getVertNormals()
{
	return vf_vertNormals;
}
const std::vector<GLuint>& Mesh::getVertNormIndices()
{
	return vi_vertNormIndices;
}
const std::vector<GLfloat>& Mesh::getTextCoords()
{
	return vf_textCoords;
}
const std::vector<GLuint>& Mesh::getTextIndices()
{
	return vi_textIndices;
}
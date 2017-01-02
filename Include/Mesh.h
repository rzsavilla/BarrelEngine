#pragma once

#include <stdafx.h>

class Mesh {
private:
	const std::string ks_ModelPath = "Source\\Resources\\models\\";	//!< Obj model resource folder
	std::vector<GLfloat> vf_vertices;			//Store models vertices
	std::vector<GLuint> vi_vertIndices;		//Store model vertex indices
	std::vector<float> vf_vertNormals;		//Stores vertex normals;
	std::vector<int> vi_vertNormIndices;	//Stores normal indices
	std::vector<float> vf_textCoords;		//Stores texture coordinates
	std::vector<int> vi_textIndices;		//Stores texture indices
public:
	Mesh();	//!< Default Constructor
	Mesh(std::string sFilename);	//!< Constructor set to parse obj file
	bool load(std::string sFilename);	//!< Parse obj file

	const std::vector<GLfloat>& getVertices();
	const std::vector<GLuint>& getVertIndices();
	const std::vector<float>* getVertNormals();
	const std::vector<int>* getVertNormIndices();
	const std::vector<float>* getTextCoords();
	const std::vector<int>* getTextIndices();
};
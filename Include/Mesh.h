#pragma once

#include <stdafx.h>

class Mesh {
private:
	const std::string ks_ModelPath = "Source\\Resources\\models\\";	//!< Obj model resource folder
	std::vector<GLfloat> vf_vertices;			//Store models vertices
	std::vector<GLuint> vi_vertIndices;		//Store model vertex indices
	
	std::vector<GLfloat> vf_vertNormals;		//Stores vertex normals;
	std::vector<GLuint> vi_vertNormIndices;	//Stores normal indices
	std::vector<GLfloat> vf_textCoords;		//Stores texture coordinates
	std::vector<GLuint> vi_textIndices;		//Stores texture indices

	std::vector<GLfloat> vf_expandedVertices;	//Expanded vertices
	std::vector<GLfloat> vf_expandedTexCoords;	//Expanded texture coordinates
public:
	Mesh();	//!< Default Constructor
	Mesh(std::string sFilename);	//!< Constructor set to parse obj file
	bool load(std::string sFilename);	//!< Parse obj file

	
	const std::vector<GLfloat>& getVertNormals();
	const std::vector<GLuint>& getVertNormIndices();
	const std::vector<GLfloat>& getTextCoords();
	const std::vector<GLuint>& getTextIndices();

	const std::vector<GLfloat>& getExpandedVertices();		//!< Returns expanded vertices
	const std::vector<GLfloat>& getExpandedTexCoords();		//!< Returns expanded texture coordinates
};
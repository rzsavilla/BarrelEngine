#pragma once
#include <stdafx.h>
#include "Mesh.h"
#include "Texture.h"
#include "QuatCamera.h"
#include "Material.h"


class ResourceManager {
private:
	std::vector<Mesh> m_vMeshes;			//!< Stores meshes
	std::vector<Texture*> m_vTextures;		//!< Stores textures
	std::vector<Material> m_vMaterials;		//!< Stores materials
public:
	ResourceManager();	//!< Default constructor

	/**	Store a mesh
		Stores mesh into a vector of meshes.
		\param newMesh Mesh object to be stored
		\return Returns the index of the mesh
	*/
	int addMesh(Mesh newMesh);

	/**	Store a mesh
		Stores texture into a vector of texture.
		\param newTexture Texture object to be stored
		\return Returns the index of the texture
	*/
	int addTexture(Texture* newTexture);

	/**	Store a material
		Stores material into a vector of material.
		\param newMaterial Material Object to be stored
		\return Returns the index of the material
	*/
	int addMaterial(Material newMaterial);

	/** Returns pointer to indexed mesh
		\param index Index to identy mesh element to return
		\return Returns pointer to mesh element
	*/
	Mesh* getMesh(int index);

	/** Returns pointer to indexed texture
	\param index Index to identy texture element to return
	\return Returns pointer to texture element
	*/
	Texture* getTexture(int index);

	/** Returns pointer to indexed material
	\param index Index to identy material element to return
	\return Returns pointer to material element
	*/
	Material* getMaterial(int index);
};
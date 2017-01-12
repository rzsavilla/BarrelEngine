#include <stdafx.h>
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{

}

int ResourceManager::addMesh(Mesh newMesh)
{
	m_vMeshes.push_back(newMesh);
	return (int)m_vMeshes.size() - 1;		//-1 for 0 index
}

int ResourceManager::addTexture(Texture* newTexture)
{
	m_vTextures.push_back(newTexture);
	return (int)m_vTextures.size() - 1;		//-1 for 0 index
}

int ResourceManager::addMaterial(Material newMaterial)
{
	m_vMaterials.push_back(newMaterial);
	return (int)m_vMaterials.size() - 1;		//-1 for 0 index
}

Mesh * ResourceManager::getMesh(int index)
{
	return &m_vMeshes.at(index);
}

Texture * ResourceManager::getTexture(int index)
{
	return m_vTextures.at(index);
}

Material * ResourceManager::getMaterial(int index)
{
	return &m_vMaterials.at(index);
}

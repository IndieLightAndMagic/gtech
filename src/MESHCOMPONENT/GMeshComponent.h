#ifndef __MESHCOMPONENT_H__
#define __MESHCOMPONENT_H__


#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GENG/g.h>
#include <glm/glm.hpp>




class GComponentNode : public G::GItemComponent
{
	std::string m_nodeName;
public:
	void addChild(GComponentNode * pNode);
protected:
	std::vector<GComponentNode*> m_child;

};

class GMaterialComponent : public GComponentNode
{
private:
	aiMaterial * m_pMaterial;
}
class GMeshComponent : public GComponentNode
{

private:
	aiMesh * m_pMesh;
};
class GSceneComponent : public GComponentNode
{

	GSceneComponent(const GSceneComponent & other);
	GMeshComponent * m_pMeshes;
private:
	aiScene * m_pScene;

};

class GLoaderComponent : public G::GItemComponent
{
	std::string m_resource;
	GLoaderComponent(Assimp::Importer & importer);
public:
	~GLoaderComponent();

private:
	Assimp::Importer m_importer;
	const aiScene*m_pScene;

public:
	static GLoaderComponent * openLoaderUsingResource(const std::string & resource);
	static void closeLoaderComponent();

	GComponentNode * createComponentNodeUsingResource(const std::string & resource);


};


#endif /*__MESHCOMPONENT_H__*/

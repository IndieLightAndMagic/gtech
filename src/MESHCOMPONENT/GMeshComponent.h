#ifndef __MESHCOMPONENT_H__
#define __MESHCOMPONENT_H__


#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GENG/g.h>
#include <glm/glm.hpp>


/* A Model Component is something you download */
class GAssimpLoaderComponent;
class GModelComponent : public G::GItemComponent
{
protected:
	const std::string m_nodeName;

public:
	static GModelComponent * createComponentNodeUsingResource(
		GLoaderComponent*pLoader, 
		std::string nodeName,
		bool bRecursive = false,
		unsigned int uiDepth = 0);	

};


class GAssimpLoaderComponent : public G::GItemComponent
{
	std::string m_resource;
	GAssimpLoaderComponent(Assimp::Importer & importer, const aiScene * pScene, std::string resource);
public:
	~GAssimpLoaderComponent();

private:
	Assimp::Importer 	m_importer;
	const aiScene*		m_pScene;
public:
	static GAssimpLoaderComponent * openLoaderUsingResource(const std::string & resource);
	static void closeLoaderComponent();

	GModelComponent * createComponentNodeUsingResource(const std::string & resource);
	void printLoaderGeneralInfo();
	void listLoaderNodes();

};


#endif /*__MESHCOMPONENT_H__*/

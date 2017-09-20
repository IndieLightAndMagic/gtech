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
class GLoaderComponent;
class GModelComponent : public G::GItemComponent
{
public:
	const std::string m_nodeName;

protected:
	static GModelComponent * createComponentNodeUsingResource(
		GLoaderComponent*pLoader, 
		std::string nodeName,
		bool bRecursive = false,
		unsigned int uiDepth = 0);	

};


class GLoaderComponent : public G::GItemComponent
{
	std::string m_resource;
	GLoaderComponent(Assimp::Importer & importer, const aiScene * pScene, std::string resource);
public:
	~GLoaderComponent();

private:
	Assimp::Importer 	m_importer;
	const aiScene*		m_pScene;
public:
	static GLoaderComponent * openLoaderUsingResource(const std::string & resource);
	static void closeLoaderComponent();

	GModelComponent * createComponentNodeUsingResource(const std::string & resource);
	void printLoaderGeneralInfo();
	void listLoaderNodes();

};


#endif /*__MESHCOMPONENT_H__*/

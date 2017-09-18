#ifndef __MESHCOMPONENT_H__
#define __MESHCOMPONENT_H__


#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GENG/g.h>

class GComponentNode : public G::GItemComponent
{
public:
	void addChild(GComponentNode * pNode);
protected:
	std::vector<GComponentNode*> m_child;

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

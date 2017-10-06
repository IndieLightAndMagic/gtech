#ifndef __MESHCOMPONENT_H__
#define __MESHCOMPONENT_H__


#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GENG/g.h>
#include <glm/glm.hpp>

using namespace Assimp;

/* A Model Component is something you download */
class GModelComponent : public G::GItemComponent
{

protected:
	const std::string m_nodeName;
	float * m_pModelData;

	int m_vertexArrayObject;
	int m_vertexBufferObject;
public:
	/**
	 * @brief      Creates a component node using resource.
	 *
	 * @param[in]  pScene    A pointer to the scene. An assimp aiScene.
	 * @param[in]  meshName  The mesh name. This is the name of the node you want to create the component off from.
	 *
	 * @return     On success this function returns a pointer to a model, a GModelComponent, on failure it will return a nullptr.
	 */
	static GModelComponent * createComponentNodeUsingResource(const aiScene *pScene, const std::string &meshName);
	virtual ~GModelComponent(){};

};


class GAssimpLoaderComponent : public G::GItemComponent
{

public:
	static Importer importer;
	static GModelComponent * loadComponentFromScene(const std::string &sceneResourceName, const std::string &meshName);
	static void printSceneGeneralInfo(const aiScene *pScene);
	static const aiNode * getMeshOnTheSceneByName(const aiNode *pNode,const std::string &meshName);


};


#endif /*__MESHCOMPONENT_H__*/

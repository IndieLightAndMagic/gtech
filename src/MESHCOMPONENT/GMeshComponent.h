#ifndef __MESHCOMPONENT_H__
#define __MESHCOMPONENT_H__

#include <cstddef>
#include <vector>
#include <string>
#include <memory>
#include <regex>
#include <map>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GENG/g.h>
#include <MESHCOMPONENT/GMaterialComponent.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace Assimp;

/* A Model Component is something you download */
class GModelComponent : public G::GItemComponent
{

protected:
	const std::string m_nodeName;
    std::vector<float> m_pModelData;


	unsigned int m_vertexArrayObject;
	unsigned int m_vertexBufferObject;
	
	glm::vec3 m_locationVector;
	glm::vec3 m_rotationAxisVector;
	float m_rotationMagnitude;

	glm::mat4 m_locationMatrix;
	glm::mat4 m_rotationMatrix;
	size_t m_rows;
public:
	unsigned int m_vertexArrayObject_public;
	unsigned int m_vertexBufferObject_public;
	/**
	 * @brief      Creates a component node using resource.
	 *
	 * @param[in]  pScene    A pointer to the scene. An assimp aiScene.
	 * @param[in]  meshName  The mesh name. This is the name of the node you want to create the component off from.
	 *
	 * @return     On success this function returns a pointer to a model, a GModelComponent, on failure it will return a nullptr.
	 */
    static std::unique_ptr<GModelComponent> createComponentNodeUsingResource(const aiScene *pScene, const std::string &meshName);
	virtual ~GModelComponent(){};

    GModelComponent() = default;
	GModelComponent(const aiScene * pScene, const aiNode * pNode, bool localOnly=false);
    GModelComponent(GModelComponent &&otherModelComponent) = default;
    GModelComponent(const GModelComponent &otherModelComponent) = default;
    GModelComponent& operator=(GModelComponent &&otherModelComponent) = default;
    GModelComponent& operator=(GModelComponent &otherModelComponent) = default;
    
    
	void setComponentLocation(glm::vec3 &locationVector);
	void setComponentRotation(glm::vec3 &rotationAxisVector, float rotationMagnitude_radians);
	void drawComponent(Program &shaderProgram);
};

class GCameraComponent;
class GAssimpLoaderComponent : public G::GItemComponent
{
    static const aiScene *loadScene(const std::string &sceneResourceName);
public:
	static Importer importer;
	
    static std::vector<GModelComponent> loadComponentFromScene(const std::string &sceneResourceName, const std::regex &regExpression);
    static std::vector<GMaterialComponent> loadMaterialsFromScene(const std::string &sceneResourceName);

	static std::unique_ptr<GModelComponent> loadComponentFromScene(const std::string &sceneResourceName, const std::string &meshName);
	static std::unique_ptr<GCameraComponent> loadCamFromScene(const std::string &sceneResourceFileName, const std::string &camName, unsigned int width, unsigned int height);

    
    
	static void printSceneGeneralInfo(const aiScene *pScene);
    static void printMaterialsInfo(std::vector<GMaterialComponent>&);
    static const aiNode* getMeshOnTheSceneByName(const aiNode *pNode,const std::string &meshName);
    static void getMeshesNodeNamesVectorOnTheSceneByRegExp(const aiNode *pNode, const std::regex &regularExpression, std::vector<std::string> &vec);
};

class GSceneComponent : public G::GItemComponent
{
    /* Here we have to start using the child node logic */
};

#endif /*__MESHCOMPONENT_H__*/

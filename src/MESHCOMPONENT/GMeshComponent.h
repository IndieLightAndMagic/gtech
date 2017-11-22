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

public:
	static Importer importer;
	
    static std::vector<GModelComponent> loadComponentFromScene(const std::string &sceneResourceName, const std::regex &regExpression);


	static std::unique_ptr<GModelComponent> loadComponentFromScene(const std::string &sceneResourceName, const std::string &meshName);
	static std::unique_ptr<GCameraComponent> loadCamFromScene(const std::string &sceneResourceFileName, const std::string &camName, unsigned int width, unsigned int height);

	static void printSceneGeneralInfo(const aiScene *pScene);
    static void printMaterialsInfo(const aiScene *pScene);
    static const aiNode* getMeshOnTheSceneByName(const aiNode *pNode,const std::string &meshName);
    static void getMeshesNodeNamesVectorOnTheSceneByRegExp(const aiNode *pNode, const std::regex &regularExpression, std::vector<std::string> &vec);
};

template <typename T>
class GMaterialProperty
{
    std::string m_propertyName;
    std::size_t m_sz;
    unsigned int m_count;
    std::unique_ptr<T> m_ptr;
    
    GMaterialProperty(const std::string &propertyName, T &value, size_t nelems=1, std::size_t sz=sizeof(T)):
        m_propertyName(propertyName),
        m_count(nelems),
        m_sz(sz)
    {
        m_ptr = std::make_unique<T>(new T[nelems * sz]);
    }
};


class GMaterialProperties : public G::GItemComponent
{
    std::map<std::string, float> m_fmap;
    std::map<std::string, double> m_dmap;
    std::map<std::string, std::string> m_smap;
    std::map<std::string, int> m_imap;
    std::map<std::string, std::unique_ptr<unsigned char>> m_ptrmap;
    std::map<std::string, size_t> m_ptrsz_map;
public:
    GMaterialProperties() = default;
    GMaterialProperties(GMaterialProperties &&otherMaterialProperty) = default;
    GMaterialProperties(const GMaterialProperties &otherMaterialProperty) = default;
    GMaterialProperties& operator=(GMaterialProperties &&otherMaterialProperty) = default;
    GMaterialProperties& operator=(GMaterialProperties &otherMaterialProperty) = default;
    
    float fget(const std::string &key);
    double dget(const std::string &key);
    std::string sget(const std::string &key);
    int iget(const std::string &key);
    
    
};


#endif /*__MESHCOMPONENT_H__*/

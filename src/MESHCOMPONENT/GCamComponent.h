#ifndef __CAMCOMPONENT_H__
#define __CAMCOMPONENT_H__

#include <vector>
#include <string>
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <GENG/g.h>
#include <SHDR/shdr.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class GCamComponent : public G::GItemComponent
{


	const std::string m_nodeName;

	glm::vec3 m_locationVector;
	glm::vec3 m_lookAtVector;
	glm::vec3 m_upVector;

	glm::mat4 m_viewModelCamMatrix;
	glm::mat4 m_projectionModelCamMatrix;

	float m_horizontalFieldOfViewRadians;
	float m_clipPlaneFar;
	float m_clipPlaneNear;
	float m_aspect;

	struct {
		unsigned int width, height;
	}m_screen;

public:
	static std::shared_ptr<GCamComponent> createCamNodeUsingResource(const aiScene *pScene, const std::string &camName);
	GCamComponent(const aiScene * pScene, const aiCamera *pCamera, float horizontalFieldOfView, unsigned int width, unsigned int height);
	void useCamera(Program &shaderProgram);
};


#endif /*__CAMCOMPONENT_H__*/



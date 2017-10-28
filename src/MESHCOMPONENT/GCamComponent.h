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

/*
 TODO:
     + Improve camera movements through Matrix.
     + Get A Generalization aka Better Abstraction.
 
     + Better relation with shader, camModel is something hardcoded.
 */
using namespace Assimp;
class GCameraComponent : public G::GItemComponent
{

	const std::string m_nodeName;
    bool m_dirty;
    public:
	glm::vec3 m_locationVector;
	private:
	glm::vec3 m_lookAtVector;
	glm::vec3 m_upVector;
	glm::vec3 m_rightVector;

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

    static std::unique_ptr<GCameraComponent> createCamNodeUsingResource(const aiScene *pScene, const std::string &camName, unsigned int width, unsigned int height);
	virtual ~GCameraComponent(){};

	GCameraComponent(const aiCamera *pCamera, const aiNode *pNode, unsigned int width, unsigned int height);
    GCameraComponent(GCameraComponent &other);
	void useCamera(Program &shaderProgram);
	void setCameraLocation(glm::vec3 locationVector);
    void setCameraOrientation(glm::vec3 lookAtVector, glm::vec3 upVector);


    // Camera Movements.
    // Position Translation.
    void moveCamera(glm::vec3 deltaPosition);
    
    // Move throughout camera's lookAtVector
    void moveCameraForwardBackwards(float dt, float scalarSpeed);
    void moveCameraForwardBackwards(float scalarDistance);

    // Move throughout camera's right vector 
    void moveCameraRightLeft(float dt, float scalarSpeed);
    void moveCameraRightLeft(float scalarDistance);

    // Move throughout camera's up vector
    void moveCameraUpDown(float dt, float scalarSpeed);
    void moveCameraUpDown(float scalarDistance);

    


};


#endif /*__CAMCOMPONENT_H__*/



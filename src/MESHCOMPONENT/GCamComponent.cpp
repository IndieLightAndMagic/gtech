#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#include <OpenGL/gl.h>
#endif /*__APPLE__*/

#include <MESHCOMPONENT/GCamComponent.h>
#include <MESHCOMPONENT/GMeshComponent.h>

void GCameraComponent::moveCamera(glm::vec3 deltaPosition)
{
    m_locationVector += deltaPosition;
    m_dirty = true;
}
void GCameraComponent::moveCameraForwardBackwards(float dt, float scalarSpeed)
{
    auto lookAtVector = glm::normalize(m_lookAtVector) * (dt * scalarSpeed);
    moveCamera(lookAtVector);
}
void GCameraComponent::moveCameraForwardBackwards(float scalarDistance)
{
    moveCameraForwardBackwards(1.0f, scalarDistance);
}

void GCameraComponent::moveCameraRightLeft(float dt, float scalarSpeed)
{
    auto rightVector = glm::normalize(m_rightVector) * (dt*scalarSpeed);
    moveCamera(rightVector);
}
void GCameraComponent::moveCameraRightLeft(float scalarDistance)
{
    moveCameraRightLeft(1.0f, scalarDistance);
}
void GCameraComponent::moveCameraUpDown(float dt, float scalarSpeed)
{
    auto upVector = glm::normalize(m_upVector) * (dt * scalarSpeed);
    moveCamera(upVector);
}
void GCameraComponent::moveCameraUpDown(float scalarDistance)
{
    moveCameraUpDown(1.0f, scalarDistance);
}
struct GCameraDecomposer{

    aiQuaterniont<float> quat;
    aiVector3t<float> scale;
    aiVector3t<float> location;
    aiVector3t<float> up;
    aiVector3t<float> lookAt;
    GCameraDecomposer(const aiCamera *pCamera, const aiNode *pNode)
    {
        aiMatrix4x4t<float> out = pNode->mTransformation;
        out.Decompose(scale, quat, location);
        up = quat.Rotate(pCamera->mUp);
        lookAt = quat.Rotate(pCamera->mLookAt);
    };
    
    glm::vec3 getUp() const
    {
        return glm::vec3{up.x, up.y, up.z};
    };
    glm::vec3 getLookAt() const
    {
        return glm::vec3{lookAt.x, lookAt.y, lookAt.z};
    };
    glm::vec3 getLocation() const
    {
        return glm::vec3{location.x, location.y, location.z};
    }

};
void GCameraComponent::useCamera(Program &shaderProgram)
{
    if (!m_dirty)
    {
    	return;
    }
    m_dirty = false;

    float fwidth  {(float)m_screen.width};
    float fheight {(float)m_screen.height};
    float fAspect {fwidth / fheight};

    m_projectionModelCamMatrix = glm::perspective(m_horizontalFieldOfViewRadians, fAspect, m_clipPlaneNear, m_clipPlaneFar);
    shaderProgram.setMat4("camModel.pr", m_projectionModelCamMatrix);

	m_viewModelCamMatrix = glm::lookAt(m_locationVector, m_locationVector + m_lookAtVector, m_upVector);
	shaderProgram.setMat4("camModel.vw", m_viewModelCamMatrix);
}
void GCameraComponent::setCameraLocation(glm::vec3 locationVector)
{
    m_locationVector = locationVector;
    m_dirty = true;
}

void GCameraComponent::setCameraOrientation(glm::vec3 lookAtVector, glm::vec3 upVector)
{
    m_lookAtVector = lookAtVector;
    m_upVector = upVector;
    m_rightVector = glm::cross(m_lookAtVector, m_upVector);
    m_dirty = true;
}
GCameraComponent::GCameraComponent(GCameraComponent &rOther)
{
    
}
GCameraComponent::GCameraComponent(const aiCamera *pCamera, const aiNode *cameraNode, unsigned int screenWidth, unsigned int screenHeight):
    m_nodeName(std::string(pCamera->mName.C_Str())),
    m_horizontalFieldOfViewRadians(pCamera->mHorizontalFOV*2),
    m_clipPlaneFar(pCamera->mClipPlaneFar),
    m_clipPlaneNear(pCamera->mClipPlaneNear),
    m_aspect(pCamera->mAspect),
    m_screen({screenWidth,screenHeight})
{
    /* Position is not stored in the camera itself, it is rather stored on the camera's node*/
    GCameraDecomposer decomposer(pCamera,cameraNode);
    setCameraOrientation(decomposer.getLookAt(), decomposer.getUp());
    setCameraLocation(decomposer.getLocation());
    
	float degrees = glm::degrees(m_horizontalFieldOfViewRadians);
	std::cout << "Camera Name is: " << m_nodeName <<"["<< m_screen.width << "x"<< m_screen.height<<"]["<<degrees<<"] Near: "<< m_clipPlaneNear<< " Far: "<< m_clipPlaneFar<<"\n";
	std::cout << "Position:<" << m_locationVector.x << " , " << m_locationVector.y << " , " << m_locationVector.z <<">\n";
	std::cout << "LookAt:<" << m_lookAtVector.x << " , " << m_lookAtVector.y << " , " << m_lookAtVector.z <<">\n";
	std::cout << "Up:<" << m_upVector.x << " , " << m_upVector.y << " , " << m_upVector.z <<">\n";
}

std::unique_ptr<GCameraComponent> GCameraComponent::createCamNodeUsingResource(const aiScene *pScene, const std::string &meshName, unsigned int width, unsigned int height)
{
    auto pCameraNode = GAssimpLoaderComponent::getMeshOnTheSceneByName(pScene->mRootNode, meshName);
    
    for (auto cameraIndex = 0; cameraIndex < pScene->mNumCameras; ++cameraIndex)
    {
        auto pCamera = pScene->mCameras[cameraIndex];
        auto cameraName = std::string{pCamera->mName.C_Str()};
        if (cameraName == meshName)
        {
            auto pComponent = std::unique_ptr<GCameraComponent>(new GCameraComponent(pCamera, pCameraNode, width, height));
            return pComponent;
        }
    }
    return nullptr;
}
std::unique_ptr<GCameraComponent> GAssimpLoaderComponent::loadCamFromScene(const std::string &sceneResourceFileName, const std::string &camName, unsigned int width, unsigned int height)
{
    Importer importer;
    const aiScene * pScene = importer.ReadFile(sceneResourceFileName, aiProcess_Triangulate);
    if (!pScene) return nullptr;
    return std::unique_ptr<GCameraComponent>(GCameraComponent::createCamNodeUsingResource(pScene, camName, width, height));

}

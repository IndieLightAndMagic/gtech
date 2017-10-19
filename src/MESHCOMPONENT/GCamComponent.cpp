#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#include <OpenGL/gl.h>
#endif /*__APPLE__*/

#include <MESHCOMPONENT/GCamComponent.h>
#include <MESHCOMPONENT/GMeshComponent.h>

void GCamComponent::useCamera(Program &shaderProgram)
{
    
    float fwidth  {(float)m_screen.width};
    float fheight {(float)m_screen.height};
    float fAspect {fwidth / fheight};

    m_projectionModelCamMatrix = glm::perspective(m_horizontalFieldOfViewRadians, fAspect, m_clipPlaneNear, m_clipPlaneFar);
    shaderProgram.setMat4("camModel.pr", m_projectionModelCamMatrix);

	m_viewModelCamMatrix = glm::lookAt(m_locationVector, m_locationVector + m_lookAtVector, m_upVector);
	shaderProgram.setMat4("camModel.vw", m_viewModelCamMatrix);
}
void GCamComponent::setCamLocation(glm::vec3 &locationVector)
{
    m_locationVector = locationVector;
}

/*void GCamComponent::setComponentRotation(glm::vec3 &rotationAxisVector, float rotationMagnitude_radians)
{
    if (rotationMagnitude_radians <= glm::epsilon<float>() && rotationMagnitude_radians>= -glm::epsilon<float>())
    {
        rotationAxisVector = glm::vec3(1.0f, 0.0f, 0.0f);
        rotationMagnitude_radians = glm::zero<float>();
    }
    m_rotationAxisVector = rotationAxisVector;
    m_rotationMagnitude = rotationMagnitude_radians;
    m_rotationMatrix = glm::mat4(1.0f);
    m_rotationMatrix = glm::rotate(m_rotationMatrix, float(rotationMagnitude_radians), rotationAxisVector);
}*/

GCamComponent::GCamComponent(const aiCamera *pCamera, const aiNode *cameraNode, float horizontalFieldOfView, unsigned int screenWidth, unsigned int screenHeight):
    m_nodeName(std::string(pCamera->mName.C_Str())),
    m_lookAtVector(glm::vec3(pCamera->mLookAt.x, pCamera->mLookAt.y, pCamera->mLookAt.z)),
    m_upVector(glm::vec3(pCamera->mUp.x, pCamera->mUp.y, pCamera->mUp.z)),
    m_horizontalFieldOfViewRadians(pCamera->mHorizontalFOV),
    m_clipPlaneFar(pCamera->mClipPlaneFar),
    m_clipPlaneNear(pCamera->mClipPlaneNear),
    m_aspect(pCamera->mAspect),
    m_screen({screenWidth,screenHeight})
{
    /* Position is not stored in the camera itself, it is rather stored on the camera's node*/
    auto cameraMatrix = cameraNode->mTransformation;
    
    aiVector3t<float>scaleVector;
    aiVector3t<float>rotationAxisVector;
    float rotationMagnitude_radians;
    aiVector3t<float>locationVector;
    cameraMatrix.Decompose(scaleVector, rotationAxisVector, rotationMagnitude_radians, locationVector);
    m_locationVector = glm::vec3{locationVector.x, locationVector.y, locationVector.z};
    
	float degrees = glm::degrees(m_horizontalFieldOfViewRadians);
	std::cout << "Camera Name is: " << m_nodeName <<"["<< m_screen.width << "x"<< m_screen.height<<"]["<<degrees<<"] Near: "<< m_clipPlaneNear<< " Far: "<< m_clipPlaneFar<<"\n";
	std::cout << "Position:<" << m_locationVector.x << " , " << m_locationVector.y << " , " << m_locationVector.z <<">\n";
	std::cout << "LookAt:<" << m_lookAtVector.x << " , " << m_lookAtVector.y << " , " << m_lookAtVector.z <<">\n";
	std::cout << "Up:<" << m_upVector.x << " , " << m_upVector.y << " , " << m_upVector.z <<">\n";
}

std::shared_ptr<GCamComponent> GCamComponent::createCamNodeUsingResource(const aiScene *pScene, const std::string &meshName, float horizontalFieldOfView, unsigned int width, unsigned int height)
{
    auto pCameraNode = GAssimpLoaderComponent::getMeshOnTheSceneByName(pScene->mRootNode, meshName);
    
    for (auto cameraIndex = 0; cameraIndex < pScene->mNumCameras; ++cameraIndex)
    {
        auto pCamera = pScene->mCameras[cameraIndex];
        auto cameraName = std::string{pCamera->mName.C_Str()};
        if (cameraName == meshName)
        {
            auto pComponent = std::make_shared<GCamComponent>(pCamera, pCameraNode, horizontalFieldOfView, width, height);
            return pComponent;
        }
    }
    return nullptr;
}
std::shared_ptr<GCamComponent> GAssimpLoaderComponent::loadCamFromScene(const std::string &sceneResourceFileName, const std::string &camName, float horizontalFieldOfView, unsigned int width, unsigned int height)
{
    Importer importer;
    const aiScene * pScene = importer.ReadFile(sceneResourceFileName, aiProcess_Triangulate);
    if (!pScene) return nullptr;
    return GCamComponent::createCamNodeUsingResource(pScene, camName, horizontalFieldOfView, width, height);

}

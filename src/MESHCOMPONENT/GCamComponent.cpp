#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#include <OpenGL/gl.h>
#endif /*__APPLE__*/

#include <MESHCOMPONENT/GCamComponent.h>


void GCamComponent::useCamera(Program &shaderProgram)
{
    m_projectionModelCamMatrix = glm::perspective(m_horizontalFieldOfViewRadians, (float)m_screen.width / (float)m_screen.height), m_clipPlaneNear, m_clipPlaneFar);
    shaderProgram.setMat4("camModel.pr", m_projectionModelCamMatrix);

	m_viewModelCamMatrix = glm::lookAt(m_locationVector, m_locationVector + m_lookAtVector, m_upVector);
	shaderProgram.setMat4("camModel.vw", m_viewModelCamMatrix);
}
void GCamComponent::setCamLocation(glm::vec3 &locationVector)
{
    m_locationCamVector = locationVector;
    m_locationMatrix = glm::mat4(1.0f);
    m_locationMatrix = glm::translate(m_locationMatrix, locationVector);
}

void GCamComponent::setComponentRotation(glm::vec3 &rotationAxisVector, float rotationMagnitude_radians)
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
}

GCamComponent::GCamComponent(const aiCamera *pCamera, unsigned int screenWidth, unsigned int screenHeight):
    m_nodeName(std::string(pNode->mName.C_Str())),
    m_locationVector(glm::vec3(pCamera->mPosition.x, pCamera->mPosition.y, pCamera->mPosition.z)),
    m_lookAtVector(glm::vec3(pCamera->mLookAt.x, pCamera->mLookAt.y, pCamera->mLookAt.z)),
    m_upVector(glm::vec3(pCamera->mUp.x, pCamera->mUp.y, pCamera->mUp.z)),
    m_horizontalFieldOfViewRadians(pCamera->mHorizontalFOV),
    m_clipPlaneNear(pCamera->mClipPlaneNear),
    m_clipPlaneFar(pCamera->mClipPlaneFar),
    m_aspect(pCamera->mAspect),
    m_screen.width(screenWidth),
    m_screen.height(screenHeight)
{
	float degrees = glm::degrees(m_horizontalFieldOfViewRadians);
	std::cout << "Camera Name is: " << m_nodeName <<"["<< m_screen.width << "x"<< m_screen.height<<"]["<<degrees<<"] Near: "<< m_clipPlaneNear<< " Far: "<< m_clipPlaneNear<<"\n";
	std::cout << "Position:<" << m_locationVector.x << " , " << m_locationVector.y << " , " << m_locationVector.z ">\n";
	std::cout << "LookAt:<" << m_lookAtVector.x << " , " << m_lookAtVector.y << " , " << m_lookAtVector.z "\n";
	std::cout << "Up:<" << m_upVector.x << " , " << m_upVector.y << " , " << m_upVector.z "\n";
}

std::shared_ptr<GCamComponent> GCamComponent::createCamNodeUsingResource(const aiScene *pScene, const std::string &meshName)
{
	auto nodeToCreateComponent = GAssimpLoaderComponent::getMeshOnTheSceneByName(pScene->mRootNode,meshName);
    std::shared_ptr<GCamComponent> pComponent = nullptr;
    if (nodeToCreateComponent)
    {
        pComponent = std::make_shared<GCamComponent>(pScene, nodeToCreateComponent);
    }
    return pComponent;
}

std::shared_ptr<GCamComponent> GAssimpLoaderComponent::loadComponentFromScene(const std::string &sceneResourceFileName, const std::string &meshName)
{
    Importer importer;
    const aiScene * pScene = importer.ReadFile(sceneResourceFileName, aiProcess_Triangulate);
    if (!pScene) return nullptr;
    return GCamComponent::createComponentNodeUsingResource(pScene, meshName);

}
void GAssimpLoaderComponent::printSceneGeneralInfo(const aiScene * m_pScene)
{
    class tabPrinter{
            void tabs(int tab){while (tab--) std::cout << " ";}
            void printMeshes(aiNode * pNode, const aiScene * pScene, unsigned int tab)
            {
                
                auto sz = pNode -> mNumMeshes;
                for (auto index = 0; index < sz; ++index)
                {   
                    
                    auto meshIndex = pNode -> mMeshes[index]; 
                    auto mesh = pScene -> mMeshes[meshIndex];
                    auto nFaces = mesh -> mNumFaces;

                    tabs(tab);std::cout << "MeshIndex: [" << meshIndex << "]\n";
                    {
                        tab++;
                        tabs(tab);std::cout << "Num Faces: " << nFaces << "\n";
                        tab--;
                        //Go through all meshes and create VBO.
                        
                    }
                    
                }
            }
        public:
            void operator()(aiNode*pNode, const aiScene * pScene, unsigned int tab)
            {
                bool bHasChildren = pNode -> mChildren != nullptr;
                bool bHasMeshes = pNode -> mNumMeshes > 0;
                unsigned int tablevel = tab;
                tabs(tab);
                if (bHasChildren)
                {
                    std::cout << "+";
                }
                else
                {
                    std::cout << ".";
                }
                std::cout <<std::string(pNode -> mName.C_Str()) + std::string("[#") << pNode -> mNumMeshes << std::string("]") << std::endl;
                if (bHasMeshes)
                {
                    tablevel++;
                    printMeshes(pNode, pScene, tablevel--);
                }
                if (bHasChildren)
                {
                    tablevel++;
                    /* Print Children */
                    for (auto index = 0; index < pNode -> mNumChildren; ++index )
                    {
                        this->operator()(pNode->mChildren[index], pScene, tablevel);
                    }
                }
            }
    };
    std::cout << "mNumAnimations: " << m_pScene->mNumAnimations << std::endl;
    std::cout << "mNumCameras: " << m_pScene->mNumCameras << std::endl;
    std::cout << "mNumLights: " << m_pScene->mNumLights << std::endl;
    std::cout << "mNumMaterials: " << m_pScene->mNumMaterials << std::endl;
    std::cout << "mNumMeshes: " << m_pScene->mNumMeshes << std::endl;
    std::cout << "mNumTextures: " << m_pScene->mNumTextures << std::endl;
    tabPrinter printer;
    printer(m_pScene->mRootNode, m_pScene, 0);
}




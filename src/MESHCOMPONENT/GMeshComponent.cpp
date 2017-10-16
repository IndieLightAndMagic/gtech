#include <iostream>

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else
#include <OpenGL/gl.h>
#endif /*__APPLE__*/

#include <SHDR/shdr.h>
#include <MESHCOMPONENT/GMeshComponent.h>


void GModelComponent::drawComponent(Program &shaderProgram)
{
    shaderProgram.setMat4("objModel.tx", m_locationMatrix);
    shaderProgram.setMat4("objModel.rt", m_rotationMatrix);
    glBindVertexArray(m_vertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, m_rows);

}
void GModelComponent::setComponentLocation(glm::vec3 &locationVector)
{
    m_locationVector = locationVector;
    m_locationMatrix = glm::mat4(1.0f);
    m_locationMatrix = glm::translate(m_locationMatrix, locationVector);

}
void GModelComponent::setComponentRotation(glm::vec3 &rotationAxisVector, float rotationMagnitude_radians)
{
    m_rotationAxisVector = rotationAxisVector;
    m_rotationMagnitude = rotationMagnitude_radians;
    m_rotationMatrix = glm::mat4(1.0f);
    m_rotationMatrix = glm::rotate(m_rotationMatrix, float(rotationMagnitude_radians), rotationAxisVector);
}

GModelComponent::GModelComponent(const aiScene * pScene, const aiNode * pNode):
    m_nodeName(std::string(pNode->mName.C_Str())),
    m_pModelData(new std::vector<float>),
    m_locationVector(glm::vec3(0.0f)),
    m_rotationAxisVector(glm::vec3(0.0f,0.0f,1.0f)),
    m_rotationMagnitude(0.0f),
    m_locationMatrix(glm::mat4(1.0f)),
    m_rotationMatrix(glm::mat4(1.0f))
{
    auto nMesh = pNode->mNumMeshes;
    m_rows = 0;
    //Get the meshes
    for (auto mesh_index = 0; mesh_index < nMesh; ++mesh_index)
    {   
        //Get pointer to mesh
        auto pMesh = pScene -> mMeshes[ pNode->mMeshes[mesh_index] ];
        auto nFace = pMesh->mNumFaces;
        for (auto face_index = 0; face_index < nFace; ++face_index)
        {
            auto face = pMesh->mFaces[face_index];
            for (auto index = 0; index < face.mNumIndices; ++index)
            {
                auto vertexIndex = face.mIndices[index];
                
                auto vertex = pMesh->mVertices[vertexIndex];
                auto normal = pMesh->mNormals[vertexIndex];
                
                m_pModelData->push_back(vertex.x);
                m_pModelData->push_back(vertex.y);
                m_pModelData->push_back(vertex.z);
                m_pModelData->push_back(normal.x);
                m_pModelData->push_back(normal.y);
                m_pModelData->push_back(normal.z);
                m_pModelData->push_back(0.0f);
                m_pModelData->push_back(0.0f);
                m_rows++;
            }
        }
    }
    if (nMesh>0)
    {
        glGenVertexArrays(1, &m_vertexArrayObject);
        glGenBuffers(1, &m_vertexBufferObject);
        
        auto fpdata = m_pModelData->data();
        auto fpdataSize = sizeof(fpdata);
        glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, fpdataSize, fpdata, GL_STATIC_DRAW);
        glBindVertexArray(m_vertexArrayObject);
        
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // normal attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coordinate attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }
}

std::shared_ptr<GModelComponent> GModelComponent::createComponentNodeUsingResource(const aiScene * pScene, const std::string &meshName)
{
	auto nodeToCreateComponent = GAssimpLoaderComponent::getMeshOnTheSceneByName(pScene->mRootNode,meshName);
    std::shared_ptr<GModelComponent> pComponent = nullptr;
    if (nodeToCreateComponent)
    {
        pComponent = std::make_shared<GModelComponent>(pScene, nodeToCreateComponent);
    }
    return pComponent;
}

std::shared_ptr<GModelComponent> GAssimpLoaderComponent::loadComponentFromScene(const std::string &sceneResourceFileName, const std::string &meshName)
{
    Importer importer;
    const aiScene * pScene = importer.ReadFile(sceneResourceFileName, aiProcess_Triangulate);
    if (!pScene) return nullptr;
    return GModelComponent::createComponentNodeUsingResource(pScene, meshName);

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
    std::cout << "mNumAnimations: " << m_pScene -> mNumAnimations << std::endl;
    std::cout << "mNumCameras: " << m_pScene -> mNumCameras << std::endl;
    std::cout << "mNumLights: " << m_pScene -> mNumLights << std::endl;
    std::cout << "mNumMaterials: " << m_pScene -> mNumMaterials << std::endl;
    std::cout << "mNumMeshes: " << m_pScene -> mNumMeshes << std::endl;
    std::cout << "mNumTextures: " << m_pScene -> mNumTextures << std::endl;
    tabPrinter printer;
    printer(m_pScene -> mRootNode, m_pScene, 0);
}

const aiNode *GAssimpLoaderComponent::getMeshOnTheSceneByName(const aiNode *pNode,const std::string &meshName)
{
	std::string nodeName{pNode -> mName.C_Str()};
	if (nodeName == meshName)
	{
		return pNode;
	}

	auto nChildren = pNode -> mNumChildren;
	for (auto childrenIndex = 0; childrenIndex < nChildren; ++childrenIndex)
	{
		auto nChildNode = getMeshOnTheSceneByName(pNode -> mChildren[childrenIndex], meshName);
		if (nChildNode != nullptr)
		{
			return nChildNode;
		}
	}
	return nullptr;
}



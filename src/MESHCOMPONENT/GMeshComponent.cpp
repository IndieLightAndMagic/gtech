#include <iostream>


#include <MESHCOMPONENT/GMeshComponent.h>






GModelComponent * GModelComponent::createComponentNodeUsingResource(const aiScene * pScene, const std::string &meshName)
{
	auto nodeToCreateComponent = GAssimpLoaderComponent::getMeshOnTheSceneByName(pScene->mRootNode,meshName);
	return nullptr;
}

GModelComponent * GAssimpLoaderComponent::loadComponentFromScene(const std::string &sceneResourceFileName, const std::string &meshName)
{
    const aiScene * pScene = GAssimpLoaderComponent::importer.ReadFile(sceneResourceFileName, aiProcess_Triangulate);
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

const aiNode * GAssimpLoaderComponent::getMeshOnTheSceneByName(const aiNode *pNode,const std::string &meshName)
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



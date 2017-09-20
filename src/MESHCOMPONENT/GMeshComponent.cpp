#include <iostream>


#include <MESHCOMPONENT/GMeshComponent.h>




using namespace Assimp;


GLoaderComponent::GLoaderComponent(Importer&importer, const aiScene * pScene, std::string resource):
        m_importer(importer)
    ,   m_pScene(pScene)
    ,   m_resource(resource)
    {
    }

GLoaderComponent*GLoaderComponent::openLoaderUsingResource(const std::string & resource)
{
    Importer importer;
    const aiScene * pScene = importer.ReadFile(resource, aiProcess_Triangulate);

    if (!pScene) return nullptr;
    return new GLoaderComponent(importer, pScene,resource); 

}
void GLoaderComponent::printLoaderGeneralInfo()
{
    std::cout << "Resource Name: " << m_resource << std::endl << std::endl;
    std::cout << "mNumAnimations: " << m_pScene -> mNumAnimations << std::endl;
    std::cout << "mNumCameras: " << m_pScene -> mNumCameras << std::endl;
    std::cout << "mNumLights: " << m_pScene -> mNumLights << std::endl;
    std::cout << "mNumMaterials: " << m_pScene -> mNumMaterials << std::endl;
    std::cout << "mNumMeshes: " << m_pScene -> mNumMeshes << std::endl;
    std::cout << "mNumTextures: " << m_pScene -> mNumTextures << std::endl;
}

void GLoaderComponent::listLoaderNodes()
{   
    class tabPrinter{
        public:
        void operator()(aiNode*pNode, unsigned tab)
        {
            bool bHasChildren = pNode -> mChildren != nullptr;
            unsigned int tablevel = tab;
            while (tab--)
            {
                std::cout << " ";
            }
            if (bHasChildren)
            {
                std::cout << "+";
            }
            else 
            {
                std::cout << ".";
            } 
            std::cout <<std::string(pNode -> mName.C_Str()) + std::string("[#") << pNode -> mNumMeshes << std::string("]") << std::endl;
            if (bHasChildren)
            {
                tablevel++;
                for (auto index = 0; index < pNode -> mNumChildren; ++index )
                {
                    this->operator()(pNode->mChildren[index],tablevel);
                }
            }
        }
    };
    printLoaderGeneralInfo();
    aiNode * pNode = m_pScene->mRootNode;
    unsigned int tablevel = 0;
    while (pNode)
    {   
        tabPrinter printer;
        printer(pNode,tablevel);
    }    
}

GModelComponent * GModelComponent::createComponentNodeUsingResource(
    GLoaderComponent * pLoader, 
    std::string nodeName,
    bool bRecursive,
    unsigned int uiDepth)
{
    /* Create a Model Component, using a name inside the Assimp data structure as reference */

    return nullptr;
}



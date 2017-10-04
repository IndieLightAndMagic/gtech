#include <iostream>


#include <MESHCOMPONENT/GMeshComponent.h>




using namespace Assimp;


GAssimpLoaderComponent::GAssimpLoaderComponent(Importer&importer, const aiScene * pScene, std::string resource):
    //    G::GItemComponent()
    m_importer(importer)
    ,   m_pScene(pScene)
    ,   m_resource(resource)
    {
        aiNode * pNode = pScene -> mRootNode;
        class tabPrinter{
            void tabs(int tab){while (tab--) std::cout << " ";}
            void printMeshes(aiNode * pNode, const aiScene * pScene, unsigned int tab)
            {
                tabs(tab);

                auto sz = pNode -> mNumMeshes;
                for (auto index = 0; index < sz; ++index)
                {
                    auto meshIndex = pNode -> mMeshes[index]; 
                    std::cout << "vidx: " << meshIndex << std::endl;
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
        printLoaderGeneralInfo();
        unsigned int tablevel = 0;
        if (pNode)
        {   
            tabPrinter printer;
            printer(pNode, pScene, tablevel);
        }
    }

GAssimpLoaderComponent*GAssimpLoaderComponent::openLoaderUsingResource(const std::string & resource)
{
    Importer importer;
    const aiScene * pScene = importer.ReadFile(resource, aiProcess_Triangulate);

    if (!pScene) return nullptr;
    return new GAssimpLoaderComponent(importer, pScene,resource); 

}
void GAssimpLoaderComponent::closeLoaderComponent()
{
    m_importer.FreeScene();
}
void GAssimpLoaderComponent::printLoaderGeneralInfo()
{
    std::cout << "Resource Name: " << m_resource << std::endl << std::endl;
    std::cout << "mNumAnimations: " << m_pScene -> mNumAnimations << std::endl;
    std::cout << "mNumCameras: " << m_pScene -> mNumCameras << std::endl;
    std::cout << "mNumLights: " << m_pScene -> mNumLights << std::endl;
    std::cout << "mNumMaterials: " << m_pScene -> mNumMaterials << std::endl;
    std::cout << "mNumMeshes: " << m_pScene -> mNumMeshes << std::endl;
    std::cout << "mNumTextures: " << m_pScene -> mNumTextures << std::endl;
}

void GAssimpLoaderComponent::listLoaderNodes()
{   
    
}

GModelComponent * GModelComponent::createComponentNodeUsingResource(
    GAssimpLoaderComponent * pLoader, 
    std::string nodeName,
    bool bRecursive,
    unsigned int uiDepth)
{
    /* Create a Model Component, using a name inside the Assimp data structure as reference */

    return nullptr;
}



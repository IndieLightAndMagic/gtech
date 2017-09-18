#include <iostream>


#include <MESHCOMPONENT/GMeshComponent.h>







void GComponentNode::addChild(GComponentNode * pNode)
{
    m_child.push_back(pNode);
}



GLoaderComponent::GLoaderComponent(Assimp::Importer&importer):
        m_importer(importer)
{

    m_pScene = m_importer.GetScene();

}
GLoaderComponent::~GLoaderComponent()
{
    
}

GLoaderComponent*GLoaderComponent::openLoaderUsingResource(const std::string & resource)
{
    Assimp::Importer importer;
    const aiScene * pScene = importer.ReadFile(resource, aiProcess_Triangulate);

    if (!pScene) return nullptr;
    return new GLoaderComponent(importer); 


}

GComponentNode * GLoaderComponent::createComponentNodeUsingResource(const std::string & resource)
{
    std::cout << "try to use " << resource << " to create component " << std::endl;
    return new GComponentNode();
}
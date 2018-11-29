#include "assetmanager.h"

#include <tuple>

#include <FS/path.h>
#include <FS/resolver.h>

std::shared_ptr<const GTech::Scene> GTech::SceneResourceManagerMap::LoadColladaVisitor(std::string filename, tinyxml2::XMLDocument& doc){

    auto result = doc.LoadFile(filename.c_str());

    if (result != tinyxml2::XML_SUCCESS){

        std::cout << "Returning an empty Scene.... Couldn't load collada file.... \n";
        return nullptr;
    
    } else {

        std::cout << "Ok scene file was successfully loaded.... \n"; 
        auto pvisitor = std::make_shared<GTech::ColladaVisitor>();
        doc.Accept(pvisitor.get());
        return pvisitor->GetScene();
    }


    return nullptr;
}

GTech::SceneResourceManagerMap::SceneResourceManagerMap(){

    sp_context  = std::make_shared<tinyxml2::XMLDocument>();
    fresolution = LoadColladaVisitor;

}

std::tuple<std::shared_ptr<GTech::Mesh>, int> GTech::MeshDataTuple(std::string resourcename, GTech::Scene& scene){

    //Check if the resource exists on the visitor.
    if (scene.nodes.find(resourcename) == scene.nodes.end()) return make_tuple(std::shared_ptr<GTech::Mesh>(), 0);

    //Get the node, if not a mesh node return nullptr.
    auto pnode           = scene.nodes[resourcename];
    auto pmesh           = std::dynamic_pointer_cast<GTech::Mesh>(scene.urlPtrMap[pnode->url]);
    
    if (pmesh == nullptr) {
        return std::make_tuple(pmesh, 0);
    }
    
    //Get number of triangle strips if 0 return nullptr;
    auto trianglearraysz = static_cast<int>(pmesh->triangleArray.size());
    
    return std::make_tuple(pmesh, 0); 

}
/***************************************************************************************
*  VAO                                                                                 *
***************************************************************************************/

/***************************************************************************************
*  MATERIAL                                                                            *
***************************************************************************************/



#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <memory>

#include <collader/collader.h>
#include <GTechUtils/weakmap.h>


namespace GTech{

    /**
     * @brief      Function which return a pointer to a mesh and the size of the vao array. 
     *
     * @param[in]  resourcename  The name of the mesh node.
     * @param      scene         A reference to the scene where mesh node is stored.
     *
     * @return     { description_of_the_return_value }
     */
    std::tuple<std::shared_ptr<GTech::Mesh>, int> MeshDataTuple(std::string resourcename, GTech::Scene& scene);
    

    class SceneNameMap : public GTech::WeakMap<const GTech::Scene, std::string, tinyxml2::XMLDocument>{

        static std::shared_ptr<const GTech::Scene> LoadColladaVisitor(std::string filename, tinyxml2::XMLDocument& doc);
        
       
    public:
        SceneNameMap();
    
    };
    
}



#endif /* ASSET_MANAGER_H */
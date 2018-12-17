#ifndef VAO_ARR_MAP
#define VAO_ARR_MAP
#include "assetmanager.h"

#include <memory>

#include <collader/collader.h>
#include <GTechUtils/weakmap.h>


namespace GTech{

    class MeshVaoArrayMap : public GTech::WeakMap<unsigned int, std::string, GTech::Scene>{

        static std::shared_ptr<unsigned int> LoadVaoArrayForMeshNode(std::string meshnodename, GTech::Scene& scene);
    public:
    	/**
    	 * @brief      Constructor using a by default nullptr when no context has been defined so far. 
    	 *
    	 * @param[in]  pscene  The pscene
    	 */
        MeshVaoArrayMap(std::shared_ptr<GTech::Scene> pscene = nullptr);

        /**
         * @brief      Sets the scene pointer for context. Notice this will be set only when the sp_context private pointer is null. 
         *
         * @param[in]  pscene  The pscene
         *
         * @return     true when successfully set the pointer. 
         */
        bool SetScenePtr(std::shared_ptr<GTech::Scene> pscene);
    };

}   

#endif /* VAO_ARR_MAP */
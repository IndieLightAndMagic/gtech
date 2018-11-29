#ifndef VAO_ARR_MAP
#define VAO_ARR_MAP
#include "assetmanager.h"

#include <memory>

#include <collader/collader.h>
#include <ECS/Component/componentmanager.h>
#include <GTechUtils/weakmap.h>


namespace GTech{

	class MeshVaoArrayMap : public GTech::WeakMap<unsigned int, std::string, GTech::Scene>{
		static std::shared_ptr<unsigned int> LoadVaoArrayForMeshNode(std::string meshnodename, GTech::Scene& scene);
	
	public:
		MeshVaoArrayMap(std::shared_ptr<GTech::Scene> pscene);
	};

}	

#endif /* VAO_ARR_MAP */
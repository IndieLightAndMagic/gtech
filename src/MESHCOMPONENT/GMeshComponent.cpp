#include <iostream>


#include <MESHCOMPONENT/GMeshComponent.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



const aiScene * GImporter::Load(std::string filepath)
{
    // read file via ASSIMP
    const aiScene* pScene = ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs );
    
    // check for errors
    if(!pScene || pScene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !pScene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << GetErrorString() << std::endl;
        return nullptr;
    }
    
    // retrieve the directory path of the filepath
    m_directory = filepath.substr(0, filepath.find_last_of('/'));

    return pScene;
}

const aiNode * GImporter::GetNode(std::string nodename)
{
    aiNode * pRootNode = 

}


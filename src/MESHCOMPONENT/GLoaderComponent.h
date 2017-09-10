


#ifndef _GLOADERCOMPONENT_H_
#define _GLOADERCOMPONENT_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glext.h>
#else 
#include <OpenGL/gl.h>
#endif /*__APPLE__*/

#include <STB/stb_image.h>
#include <GLM/glm.hpp>
#include <MESHCOMPONENT/GMeshComponent.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>
using namespace std;

class GLoaderComponent {

public:

    /*  ModelLoaderComponent Data */
    vector<GTextureComponent> m_textures_loaded;  // stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<GMeshComponent> m_meshes;
    string directory;
    bool m_bGammaCorrection;

	GModelComponent* operator()(string const&path, bool gamma = false);

private:
	void loadModel(string const &path);
	void processNode(aiNode*node, const aiScene *scene);
	GMeshComponent processMesh(aiMesh*mesh, const aiScene*scene);
	vector<GTextureComponent>loadMaterialTextures(aiMaterial*mat, aiTextureType type, string typeName);

};
unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);


#endif  /*_GLOADERCOMPONENT_H_*/
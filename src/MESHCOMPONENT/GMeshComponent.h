#ifndef __MESHCOMPONENT_H__
#define __MESHCOMPONENT_H__

#include <GENG/g.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>



using namespace Assimp;

class GNode : GItemComponent
{
	GNode(const GImporter & importer, std::string nodename);
public:
	static GNode * CreateGNode(const GImporter & importer, std::string nodename);
};

class GImporter: public Importer 
{
	std::string m_directory;
public:
	const aiScene * Load(std::string file);
	const aiNode * GetNode(std::string name);
};

#endif /*__MESHCOMPONENT_H__*/

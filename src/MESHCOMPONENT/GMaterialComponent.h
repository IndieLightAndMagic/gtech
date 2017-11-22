#ifndef __GMATERIALCOMPONENT_H__
#define __GMATERIALCOMPONENT_H__

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <regex>


// #include <assimp/Importer.hpp>
// #include <assimp/scene.h>
// #include <assimp/postprocess.h>

// #include <GENG/g.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>


// using namespace Assimp;
template <typename T>
class GProperty
{
protected:
	std::size_t m_sz;
	unsigned int m_count;
	std::unique_ptr<T> m_updata; 

	GProperty(T &r, unsigned int nelem)
	{
		m_updata = std::make_unique<T[]>(nelem);
	};
	virtual ~GProperty(){};
public:
	virtual T getProperty() {return *m_updata;};
	void setProperty(const T &data){ *m_updata = data;};
};



#endif /*__GMATERIALCOMPONENT_H__*/

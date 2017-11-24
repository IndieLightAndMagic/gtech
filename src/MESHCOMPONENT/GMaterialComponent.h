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
// 


using Ptr = unsigned char*;
using Byte = unsigned char;
class GPropertyValue
{
protected:
	std::size_t m_sz;
	Ptr m_ptr;
	std::unique_ptr<Byte> m_uptr;

	/**
	 * @brief      Create a value for the property.
	 *
	 * @param[in]  sz    The size
	 * @param[in]  ptr   The pointer
	 */
	GPropertyValue(std::size_t sz, Ptr ptr = nullptr):
	m_sz(sz)
	{
		m_uptr = std::make_unique<Byte>(sz);
		m_ptr = m_uptr.get();
		if (ptr)
		{
			//Copy if memory its being passed.
			std::memcpy(m_ptr, ptr, m_sz);
		}	
	};

	virtual ~GPropertyValue(){}
public:
	
	virtual void setPropertyValue(Ptr propertyValueAddress, std::size_t sz) = 0;
};



#endif /*__GMATERIALCOMPONENT_H__*/

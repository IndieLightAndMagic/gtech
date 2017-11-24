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


using Ptr = const unsigned char*;
using Byte = unsigned char;
class GPropertyValue
{
protected:
	std::size_t m_sz;
	volatile Ptr m_ptr;
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
			setPropertyValue(ptr,sz);
		}	
		std::cout << "Hello! @" << std::hex << this << "\n"; 

	};

	void *getPtr(){
		return m_uptr.get();
	}
public:
	std::size_t propertySize(){
		return m_sz;
	}
	virtual void setPropertyValue(Ptr propertyValueAddress, std::size_t sz)
	{
		//Copy if memory its being passed.
		std::memcpy((void*)m_ptr, propertyValueAddress, m_sz);
	}
	virtual ~GPropertyValue(){
		std::cout << "Goodbye! @" << std::hex << this << "\n"; 
	}
	

};



#endif /*__GMATERIALCOMPONENT_H__*/

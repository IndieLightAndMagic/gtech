#ifndef __GMATERIALCOMPONENT_H__
#define __GMATERIALCOMPONENT_H__

#include <iostream>
#include <vector>
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
class IGPropertyValue
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
	IGPropertyValue(std::size_t sz, Ptr ptr = nullptr):
	m_sz(sz)
	{
		m_uptr = std::make_unique<Byte>(sz);
		m_ptr = m_uptr.get();
		if (ptr)
		{
			setPropertyMemoryBuffer(ptr,sz);
		}	
		std::cout << "Hello! @" << std::hex << this << "\n"; 

	};
	void *getPtr(){
		return m_uptr.get();
	}
    void setPropertyMemoryBuffer(Ptr propertyValueAddress, std::size_t sz)
    {
        //Copy if memory its being passed.
        std::memcpy(getPtr(), propertyValueAddress, m_sz);
    }

public:
	std::size_t propertySize(){
		return m_sz;
	}
	template <typename T>
	T getPropertyValue()
	{
		T *pt = reinterpret_cast<T*>(getPtr());
		return *pt;
	} 
	virtual ~IGPropertyValue(){
		std::cout << "Goodbye! @" << std::hex << this << "\n"; 
	}
	

};
template <typename T>
class GPropertyValue : public IGPropertyValue
{
public:
	GPropertyValue(std::size_t sz = sizeof(T), T *tptr = nullptr):
	IGPropertyValue(sz,reinterpret_cast<Ptr>(tptr))
	{
		std::cout << "Derived::\n";
	}
	~GPropertyValue(){std::cout << "Derived::\n";};

	void setPropertyValue(const T *propertyValueAddress)
	{
		Ptr ptr = reinterpret_cast<Ptr>(propertyValueAddress);
		setPropertyMemoryBuffer(ptr,sizeof(T));
	}
	void setPropertyValue(const T &propertyValue)
	{
		setPropertyValue(&propertyValue);
	}
	T getPropertyValue()
	{
		T *tptr = reinterpret_cast<T*>(getPtr());
		return *tptr;
	}
};


#endif /*__GMATERIALCOMPONENT_H__*/

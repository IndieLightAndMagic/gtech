#ifndef __GMATERIALCOMPONENT_H__
#define __GMATERIALCOMPONENT_H__

#include <iostream>
#include <vector>
#include <memory>
#include <regex>
#include <utility>
#include <map>
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
public:
		enum class PropertyType{
		_8B,			//BYTE
		_8nB,			//BYTE ARRAY
		U8B,			//Unsigned BYTE
		U8nB,			//Unsigned BYTE ARRAY
		_I32I,			//INTEGER
		_I32nI,			//INTEGER ARRAY
		UI32I,			//UNSIGNED INTEGER
		UI32nI,			//UNSIGNED INTEGER ARRAY
		F32,			//FLOAT 
		F32Array,		//FLOAT ARRAY
		D32,			//DOUBLE
		D32Array,		//DOUBLE ARRAY
		FColor,			//COLOR (array of floats (x3) normalized to 0.0-1.0) RGB
		FColorArray		//COLOR ARRAY
	};

protected:
	std::size_t m_sz;
	volatile Ptr m_ptr;
	std::unique_ptr<Byte> m_uptr;

	IGPropertyValue(std::size_t sz, Ptr ptr = nullptr, PropertyType type = PropertyType::_8nB):
	m_sz(sz)
	{
		m_uptr = std::make_unique<Byte>(sz);
		m_ptr = m_uptr.get();
		if (ptr)
		{
			setPropertyMemoryBuffer(ptr,sz);
		}	
		std::cout << "Hello! @" << std::hex << this << std::dec << "\n"; 

	};
	void *getPtr(){
		return m_uptr.get();
	}
	std::unique_ptr<Byte>& getUPtr()
	{
		return m_uptr;
	}

    void setPropertyMemoryBuffer(Ptr propertyValueAddress, std::size_t sz)
    {
        //Copy if memory its being passed.
        std::memcpy(getUPtr().get(), propertyValueAddress, m_sz);
    }

public:
	std::size_t propertySize(){
		return m_sz;
	}
	template <typename T>
	T getPropertyValue()
	{
		T *pt = reinterpret_cast<T*>(getUPtr().get());
		return *pt;
	} 
	virtual ~IGPropertyValue(){
		std::cout << "Goodbye! @" << std::hex << this << std::dec << "\n"; 
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
	void setPropertyValue(T &&propertyValue)
	{
        setPropertyValue(propertyValue);
	}
	
};

class GMaterialComponent : public G::GItemComponent
{

	std::map<std::string, IGPropertyValue*> props;
public:
	const IGPropertyValue* getProperty(const std::string &propertyName)
	{
		auto search = props.find(propertyName);
		if (search == props.end())
		{
			return nullptr;
		}
		return props[propertyName];		
	}
    void setProperty(const std::string &propertyName,IGPropertyValue* pProp)
    {
        props[propertyName] = pProp;
    }
    bool find(const std::string &propertyName)
    {
    	auto search = props.find(propertyName);
    	return search != props.end() ? false : true; 	
    }
    bool empty()
    {
    	return props.empty();
    }
};

#endif /*__GMATERIALCOMPONENT_H__*/

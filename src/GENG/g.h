

#ifndef _G_H_
#define _G_H_

#include <fstream>
#include <iostream>
#include <map>

namespace G
{


class GIDBasedComponent
{
	static int m_iIdCounter;
protected:
	std::string m_sComponentName;
	int m_iId;

public:
	GIDBasedComponent(){
		m_iId = ++m_iIdCounter;
		std::cout << "[+]GIDBasedComponent @" << m_iId << std::endl; 

	}
	GIDBasedComponent(const GIDBasedComponent &rOther){
		m_iId = ++m_iIdCounter;
		std::cout << "[+]GIDBasedComponent @" << m_iId << " copied from @" << rOther.getComponentId() << std::endl;
	}
    GIDBasedComponent& operator=(GIDBasedComponent &rOther) = default;
	virtual ~GIDBasedComponent();


	int getComponentId() const
	{
		return m_iId;
	}

};


class GItemComponent: public GIDBasedComponent 
{
	

	GItemComponent * m_pParent = 0;
	std::map<int, GItemComponent*> m_mapComponents;
    
public:
    GItemComponent() = default;
    GItemComponent(const GItemComponent &other) = default;
    GItemComponent& operator=(GItemComponent &other) = default;

	void 	addComponent(GItemComponent * pChild);
	void	removeComponentById(int id);
	
	GItemComponent*	getParent();
	GItemComponent*	getComponentById(int id);


	virtual void init();
	virtual ~GItemComponent(){};



};

class GGameObjectComponent: public GItemComponent
{

public:
	virtual void update(float dt)=0;
	virtual void draw()=0;
};
}
#endif

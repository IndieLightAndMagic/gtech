

#ifndef _G_H_
#define _G_H_

#include <iostream>
#include <map>

namespace G0
{


class GIDBasedComponent
{
	static int m_iIdCounter;
protected:
	int m_iId;

public:
	GIDBasedComponent(){
		m_iId = ++m_iIdCounter;
		std::cout << "[+]GIDBasedComponent @" << m_iId << std::endl; 

	}
	GIDBasedComponent(GIDBasedComponent & other){
		m_iId = ++m_iIdCounter;
		std::cout << "[+]GIDBasedComponent @" << m_iId << " copied from @" << other.GetComponentId() << std::endl; 
	}
	virtual ~GIDBasedComponent()=0;


	int GetComponentId()
	{
		return m_iId;
	}
};

class GItemComponent: public GIDBasedComponent 
{
	

	GItemComponent * m_pParent;
	std::map<int, GItemComponent*> m_pmComponents;


public:

	int addComponents(GItemComponent * pChild);
	void removeComponentById(int id);
	GItemComponent * getParent();
	GItemComponent * getComponentById(int id);


	virtual void init();
	



};




}
#endif
#include "g.h"

using namespace G;

void GItemComponent::init()
{
	std::cout << "Init() @" << m_iId << std::endl;
}

GItemComponent * GItemComponent::getParent()
{
	return m_pParent;
}
GItemComponent * GItemComponent::getComponentById(int id)
{
	auto search = m_mapComponents.find(id);
	return search == m_mapComponents.end() ? nullptr : m_mapComponents[id];
}

void GItemComponent::removeComponentById(int id)
{
	auto search = m_mapComponents.find(id);
	if (search != m_mapComponents.end())
	{
		m_mapComponents.erase(id);
	}
}

void GItemComponent::addComponent(GItemComponent * pChild)
{
	auto compoId = pChild -> getComponentId();
	auto search = m_mapComponents.find(compoId);
	if (search==m_mapComponents.end())
	{
		m_mapComponents[compoId] = pChild;
	}
}
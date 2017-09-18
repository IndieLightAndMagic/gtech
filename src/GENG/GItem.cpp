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
	auto search = m_pmComponents.find(id);
	return search == m_pmComponents.end() ? nullptr : m_pmComponents[id];
}

void GItemComponent::removeComponentById(int id)
{
	auto search = m_pmComponents.find(id);
	if (search != m_pmComponents.end())
	{
		m_pmComponents.erase(id);
	}
}

void GItemComponent::addComponent(GItemComponent * pChild)
{
	auto compoId = pChild -> getComponentId();
	auto search = m_pmComponents.find(compoId);
	if (search==m_pmComponents.end())
	{
		m_pmComponents[compoId] = pChild;
	}
}
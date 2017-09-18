#include <GENG/g.h>

int G::GIDBasedComponent::m_iIdCounter = 0;
G::GIDBasedComponent::~GIDBasedComponent(){

	std::cout << "[-]GIDBasedComponent @" << m_iId << std::endl;

}

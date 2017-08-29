#include <GENG/g.h>

int G0::GIDBasedComponent::m_iIdCounter = 0;
G0::GIDBasedComponent::~GIDBasedComponent(){

	std::cout << "[-]GIDBasedComponent @" << m_iId << std::endl;

}

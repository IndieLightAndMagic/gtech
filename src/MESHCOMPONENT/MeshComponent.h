#ifndef __MESHCOMPONENT_H__
#define __MESHCOMPONENT_H__

#include <vector>

#include <GLM/glm.hpp>
#include <GENG/g.h>

using namespace G0;


class GMeshMaterial: publix GItemComponent
{
public:
	glm::vec3 m_ka_ambientColor;
	glm::vec3 m_kd_diffuseColor;
	glm::vec3 m_ks_specularColor;

	float m_ns_specularExponent;
	float m_ni_opticalDensity;
	float m_d_dissolve;

	int m_illumination;


	std::string m_ka_ambientTexture;
	std::string m_kd_diffuseTexture;
	std::string m_ks_specularTexture;
	std::string m_ns_specularHighLightTexture;
	std::string m_d_alphaTexture;
	std::string m_bumpMapTexture;

};

class GMeshComponent: public GItemComponent
{
public:
	std::vector<glm::vec3>	m_pvertices;
	std::vector<glm::vec3>	m_pnormals;
	std::vector<glm::vec3>	m_tcoords;
	std::vector<int>		m_indices;

	
	


};





#endif /*__MESHCOMPONENT_H__*/

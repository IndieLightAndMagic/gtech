#ifndef __MESHCOMPONENT_H__
#define __MESHCOMPONENT_H__

#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <GENG/g.h>

using namespace G0;

class GTextureComponent: public GItemComponent
{
public:

	struct
	{
		int width;
		int height;
		int nrComponents;
		unsigned char * textureData;
	}m_texture;

	std::string m_type;
	std::string m_path;
	unsigned int m_textureId;
	GTextureComponent(const std::string fullPath);
	GTextureComponent(const GTextureComponent & texture);



};

class GMaterialComponent: public GItemComponent
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

	GMaterialComponent(const GMaterialComponent & other);

};

class GVertexComponent: public GItemComponent
{

public:
	glm::vec3 m_position;
	glm::vec3 m_normal;
	glm::vec2 m_tcoords;

	GVertexComponent(){}
	GVertexComponent(const GVertexComponent&other);
};

class GMeshComponent: public GItemComponent
{
public:


	std::vector<GVertexComponent>	m_vertices;		
	std::vector<unsigned int>		m_indices;
	std::vector<GMaterialComponent>	m_materials;
	std::vector<GTextureComponent>	m_textures;
	
	GMeshComponent();
	GMeshComponent(const GMeshComponent & other);
	GMeshComponent(std::vector <GVertexComponent> vertices, std::vector <unsigned int> indices);

	void AddMaterialComponent 		(const GMaterialComponent	& material);
	void AddTextureComponent		(const GTextureComponent	& texture);
	void AddTextureComponentList	(const std::vector<GTextureComponent>	& textures);
	void AddMaterialComponentList	(const std::vector<GMaterialComponent>	& materials);
};

class GModelComponent: public GItemComponent 
{
public:
	std::vector<GMeshComponent> m_cMeshList;
	GModelComponent(){};

};


#endif /*__MESHCOMPONENT_H__*/

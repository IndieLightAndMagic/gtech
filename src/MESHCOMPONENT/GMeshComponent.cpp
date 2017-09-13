#include <STB/stb_image.h>
#include <MESHCOMPONENT/GMeshComponent.h>
#include <cassert>

GMeshComponent::GMeshComponent(const GMeshComponent & other)
{
    m_vertices = other.m_vertices;     
    m_indices = other.m_indices;
    m_materials = other.m_materials;
    m_textures = other.m_textures;
}
GMeshComponent::GMeshComponent(std::vector <GVertexComponent> vertices, std::vector <unsigned int> indices)
{
    m_vertices  = vertices;
    m_indices   = indices; 

}

void GMeshComponent::AddMaterialComponent(const GMaterialComponent & material)
{
    m_materials.push_back(material);
}
void GMeshComponent::AddTextureComponent(const GTextureComponent & texture)
{
    m_textures.push_back(texture);
}
void GMeshComponent::AddTextureComponentList(const std::vector<GTextureComponent> & textures)
{
    m_textures = textures;
}
void GMeshComponent::AddMaterialComponentList(const std::vector<GMaterialComponent> & materials)
{
    m_materials = materials;
}

GVertexComponent::GVertexComponent(const GVertexComponent & other)
{
    
    m_position  = other.m_position;
    m_normal    = other.m_normal;
    m_tcoords   = other.m_tcoords;

}
GTextureComponent::GTextureComponent(const GTextureComponent & other)
{
    m_type = other.m_type;
    m_path = other.m_path;
    m_textureId = other.m_textureId;
}
GMaterialComponent::GMaterialComponent(const GMaterialComponent & other)
{
    m_ka_ambientColor=other.m_ka_ambientColor;
    m_kd_diffuseColor=other.m_kd_diffuseColor;
    m_ks_specularColor=other.m_ks_specularColor;

    m_ns_specularExponent=other.m_ns_specularExponent;
    m_ni_opticalDensity=other.m_ni_opticalDensity;
    m_d_dissolve=other.m_d_dissolve;

    m_illumination=other.m_illumination;


    m_ka_ambientTexture=other.m_ka_ambientTexture;
    m_kd_diffuseTexture=other.m_kd_diffuseTexture;
    m_ks_specularTexture=other.m_ks_specularTexture;
    m_ns_specularHighLightTexture=other.m_ns_specularHighLightTexture;
    m_d_alphaTexture=other.m_d_alphaTexture;
    m_bumpMapTexture=other.m_bumpMapTexture;

}
GTextureComponent::GTextureComponent(const std::string & fullPath)
{

    m_texture.textureData = nullptr;
    m_texture.width = 0;
    m_texture.height = 0;
    m_texture.nrComponents = 0;

    m_textureId = 0;

    m_texture.textureData = stbi_load(fullPath.c_str(), &m_texture.width, &m_texture.height, &m_texture.nrComponents, 0);
    if (!m_texture.textureData)
    {
        assert(m_texture.textureData!=nullptr);
    }
    


}
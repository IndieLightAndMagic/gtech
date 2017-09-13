


// OBJ_Loader.h - A Single Header OBJ Model Loader
#include <glm/glm.hpp>
#include <MESHCOMPONENT/GMeshComponent.h>
#include <MESHCOMPONENT/GLoaderComponent.h>


int main(int argc, char* argv[])
{
	// Initialize Loader
	GLoaderComponent	Loader;
    GModelComponent*    pModel = Loader(std::string(RES_DIR), argc > 1 ? std::string(argv[1]):std::string("arwing.obj"));

	// Check to see if it loaded

	// If so continue
	if (pModel)
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		// Go through each loaded mesh and out its contents
		for (int i = 0; i < Loader.m_meshes.size(); i++)
		{
			// Copy one of the loaded meshes to be our current mesh
			GMeshComponent curMesh = Loader.m_meshes[i];

			// Print Mesh Name
			file << "Mesh " << i << ": " << curMesh.getComponentName() << "\n";

			// Print Vertices
			file << "Vertices:\n";

			// Go through each vertex and print its number,
			//  position, normal, and texture coordinate
			for (int j = 0; j < curMesh.m_vertices.size(); j++)
			{
				file << "V" << j << ": " <<
				"P(" << curMesh.m_vertices[j].m_position.x << ", " << curMesh.m_vertices[j].m_position.y << ", " << curMesh.m_vertices[j].m_position.z << ") " <<
				"N(" << curMesh.m_vertices[j].m_normal.x << ", " << curMesh.m_vertices[j].m_normal.y << ", " << curMesh.m_vertices[j].m_normal.z << ") " <<
				"TC(" << curMesh.m_vertices[j].m_tcoords.x << ", " << curMesh.m_vertices[j].m_tcoords.y << ")\n";
			}

			// Print Indices
			file << "Indices:\n";

			// Go through every 3rd index and print the
			//	triangle that these indices represent
			for (int j = 0; j < curMesh.m_indices.size(); j += 3)
			{
				file << "T" << j / 3 << ": " << curMesh.m_indices[j] << ", " << curMesh.m_indices[j + 1] << ", " << curMesh.m_indices[j + 2] << "\n";
			}

			// Print Material
			for ( int j = 0; j < curMesh.m_materials.size(); ++j )
			{
				file << "Material: " << curMesh.m_materials[j].getComponentName() << "\n";
				file << "Ambient Color: " << curMesh.m_materials[j].m_ka_ambientColor.x << ", " << curMesh.m_materials[j].m_ka_ambientColor.y << ", " << curMesh.m_materials[j].m_ka_ambientColor.z << "\n";
				file << "Diffuse Color: " << curMesh.m_materials[j].m_kd_diffuseColor.x << ", " << curMesh.m_materials[j].m_kd_diffuseColor.y << ", " << curMesh.m_materials[j].m_kd_diffuseColor.z << "\n";
				file << "Specular Color: " << curMesh.m_materials[j].m_ks_specularColor.x << ", " << curMesh.m_materials[j].m_ks_specularColor.y << ", " << curMesh.m_materials[j].m_ks_specularColor.z << "\n";
				file << "Specular Exponent: " << curMesh.m_materials[j].m_ns_specularExponent << "\n";
				file << "Optical Density: " << curMesh.m_materials[j].m_ni_opticalDensity << "\n";
				file << "Dissolve: " << curMesh.m_materials[j].m_d_dissolve << "\n";
				file << "Illumination: " << curMesh.m_materials[j].m_illumination << "\n";
				file << "Ambient Texture Map: " << curMesh.m_materials[j].m_ka_ambientTexture << "\n";
				file << "Diffuse Texture Map: " << curMesh.m_materials[j].m_kd_diffuseTexture << "\n";
				file << "Specular Texture Map: " << curMesh.m_materials[j].m_ks_specularTexture << "\n";
				file << "Alpha Texture Map: " << curMesh.m_materials[j].m_d_alphaTexture << "\n";
				file << "Bump Map: " << curMesh.m_materials[j].m_bumpMapTexture << "\n";
			}

			// Leave a space to separate from the next mesh
			file << "\n";
		}

		// Close File
		file.close();
	}
	// If not output an error
	else
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		// Output Error
		file << "Failed to Load File. May have failed to find it or it was not an .obj file.\n";

		// Close File
		file.close();
	}

	// Exit the program
	return 0;
}

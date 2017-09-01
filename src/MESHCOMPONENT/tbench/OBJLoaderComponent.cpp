


// OBJ_Loader.h - A Single Header OBJ Model Loader
#include <GLM/glm.hpp>
#include <MESHCOMPONENT/MeshComponent.h>

// Print progress to console while loading (large models)
#define OBJL_CONSOLE_OUTPUT

// Namespace: OBJL
//
// Description: The namespace that holds eveyrthing that
//	is needed and used for the OBJ Model Loader

	// Namespace: Algorithm
	//
	// Description: The namespace that holds all of the
	// Algorithms needed for OBJL
namespace algorithm
{
		// Check to see if a glm::vec3 Point is within a 3 glm::vec3 Triangle
	bool inTriangle(glm::vec3 point, glm::vec3 tri1, glm::vec3 tri2, glm::vec3 tri3)
	{
		// Starting vars
		glm::vec3 u = tri2 - tri1;
		glm::vec3 v = tri3 - tri1;
		glm::vec3 w = point - tri1;
		glm::vec3 n = glm::cross(u, v);
		float y = (glm::dot(glm::cross(u, w), n) / glm::dot(n, n));
		float b = (glm::dot(glm::cross(u, w), n) / glm::dot(n, n));
		float a = 1 - y - b;
			// Projected point
		// glm::vec3  p = (a * tri1) + (b * tri2) + (y * tri3);
		if (a >= 0 && a <= 1
			&& b >= 0 && b <= 1
			&& y >= 0 && y <= 1)
		{
			return true;
		}
		else
			return false;
	}
		// Split a String into a string array at a given token
	inline void split(const std::string &in,
		std::vector<std::string> &out,
		std::string token)
	{
		out.clear();
		std::string temp;
		for (int i = 0; i < int(in.size()); i++)
		{
			std::string test = in.substr(i, token.size());
			if (test == token)
			{
				if (!temp.empty())
				{
					out.push_back(temp);
					temp.clear();
					i += (int)token.size() - 1;
				}
				else
				{
					out.push_back("");
				}
			}
			else if (i + token.size() >= in.size())
			{
				temp += in.substr(i, token.size());
				out.push_back(temp);
				break;
			}
			else
			{
				temp += in[i];
			}
		}
	}

		// Get tail of string after first token and possibly following spaces
	inline std::string tail(const std::string &in)
	{
		size_t token_start = in.find_first_not_of(" \t");
		size_t space_start = in.find_first_of(" \t", token_start);
		size_t tail_start = in.find_first_not_of(" \t", space_start);
		size_t tail_end = in.find_last_not_of(" \t");
		if (tail_start != std::string::npos && tail_end != std::string::npos)
		{
			return in.substr(tail_start, tail_end - tail_start + 1);
		}
		else if (tail_start != std::string::npos)
		{
			return in.substr(tail_start);
		}
		return "";
	}

		// Get first token of string
	inline std::string firstToken(const std::string &in)
	{
		if (!in.empty())
		{
			size_t token_start = in.find_first_not_of(" \t");
			size_t token_end = in.find_first_of(" \t", token_start);
			if (token_start != std::string::npos && token_end != std::string::npos)
			{
				return in.substr(token_start, token_end - token_start);
			}
			else if (token_start != std::string::npos)
			{
				return in.substr(token_start);
			}
		}
		return "";
	}

		// Get element at given index position
		template <class T>
	inline const T & getElement(const std::vector<T> &elements, std::string &index)
	{
		int idx = std::stoi(index);
		if (idx < 0)
			idx = int(elements.size()) + idx;
		else
			idx--;
		return elements[idx];
	}
}

	// Class: Loader
	//
	// Description: The OBJ Model Loader
class Loader
{
public:
		// Default Constructor
	Loader()
	{

	}
	~Loader()
	{
		LoadedMeshes.clear();
	}

		// Load a file into the loader
		//
		// If file is loaded return true
		//
		// If the file is unable to be found
		// or unable to be loaded return false
	bool LoadFile(std::string Path)
	{
			// If the file is not an .obj file return false
		if (Path.substr(Path.size() - 4, 4) != ".obj")
			return false;


		std::ifstream file(Path);

		if (!file.is_open())
			return false;

		LoadedMeshes.clear();
		LoadedVertices.clear();
		LoadedIndices.clear();

		std::vector<glm::vec3> Positions;
		std::vector<glm::vec2> TCoords;
		std::vector<glm::vec3> Normals;

		std::vector<GVertexComponent> Vertices;
		std::vector<int> Indices;

		std::vector<std::string> MeshMatNames;

		bool listening = false;
		std::string meshname;

		GMeshComponent tempMesh;

			#ifdef OBJL_CONSOLE_OUTPUT
		const unsigned int outputEveryNth = 1000;
		unsigned int outputIndicator = outputEveryNth;
			#endif

		std::string curline;
		while (std::getline(file, curline))
		{
				#ifdef OBJL_CONSOLE_OUTPUT
			if ((outputIndicator = ((outputIndicator + 1) % outputEveryNth)) == 1)
			{
				if (!meshname.empty())
				{
					std::cout
					<< "\r- " << meshname
					<< "\t| vertices > " << Positions.size()
					<< "\t| texcoords > " << TCoords.size()
					<< "\t| normals > " << Normals.size()
					<< "\t| triangles > " << (Vertices.size() / 3)
					<< (!MeshMatNames.empty() ? "\t| material: " + MeshMatNames.back() : "");
				}
			}
				#endif

				// Generate a Mesh Object or Prepare for an object to be created
			if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g" || curline[0] == 'g')
			{
				if (!listening)
				{
					listening = true;

					if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
					{
						meshname = algorithm::tail(curline);
					}
					else
					{
						meshname = "unnamed";
					}
				}
				else
				{
						// Generate the mesh to put into the array

					if (!Indices.empty() && !Vertices.empty())
					{
							// Create Mesh
						tempMesh = GMeshComponent(Vertices, Indices);
						tempMesh.setComponentName(meshname);

							// Insert Mesh
						LoadedMeshes.push_back(tempMesh);

							// Cleanup
						Vertices.clear();
						Indices.clear();
						meshname.clear();

						meshname = algorithm::tail(curline);
					}
					else
					{
						if (algorithm::firstToken(curline) == "o" || algorithm::firstToken(curline) == "g")
						{
							meshname = algorithm::tail(curline);
						}
						else
						{
							meshname = "unnamed";
						}
					}
				}
					#ifdef OBJL_CONSOLE_OUTPUT
				std::cout << std::endl;
				outputIndicator = 0;
					#endif
			}
				// Generate a Vertex Position
			if (algorithm::firstToken(curline) == "v")
			{
				std::vector<std::string> spos;
				glm::vec3 vpos;
				algorithm::split(algorithm::tail(curline), spos, " ");

				vpos.x = std::stof(spos[0]);
				vpos.y = std::stof(spos[1]);
				vpos.z = std::stof(spos[2]);

				Positions.push_back(vpos);
			}
				// Generate a Vertex Texture Coordinate
			if (algorithm::firstToken(curline) == "vt")
			{
				std::vector<std::string> stex;
				glm::vec2 vtex;
				algorithm::split(algorithm::tail(curline), stex, " ");

				vtex.x = std::stof(stex[0]);
				vtex.y = std::stof(stex[1]);

				TCoords.push_back(vtex);
			}
				// Generate a Vertex Normal;
			if (algorithm::firstToken(curline) == "vn")
			{
				std::vector<std::string> snor;
				glm::vec3 vnor;
				algorithm::split(algorithm::tail(curline), snor, " ");

				vnor.x = std::stof(snor[0]);
				vnor.y = std::stof(snor[1]);
				vnor.z = std::stof(snor[2]);

				Normals.push_back(vnor);
			}
				// Generate a Face (vertices & indices)
			if (algorithm::firstToken(curline) == "f")
			{
					// Generate the vertices
				std::vector<GVertexComponent> vVerts;
				GenVerticesFromRawOBJ(vVerts, Positions, TCoords, Normals, curline);

					// Add Vertices
				for (int i = 0; i < int(vVerts.size()); i++)
				{
					Vertices.push_back(vVerts[i]);
					LoadedVertices.push_back(vVerts[i]);
				}

				std::vector<unsigned int> iIndices;

				VertexTriangluation(iIndices, vVerts);

					// Add Indices
				for (int i = 0; i < int(iIndices.size()); i++)
				{
					unsigned int indnum = (unsigned int)((Vertices.size()) - vVerts.size()) + iIndices[i];
					Indices.push_back(indnum);

					indnum = (unsigned int)((LoadedVertices.size()) - vVerts.size()) + iIndices[i];
					LoadedIndices.push_back(indnum);

				}
			}
				// Get Mesh Material Name
			if (algorithm::firstToken(curline) == "usemtl")
			{
				MeshMatNames.push_back(algorithm::tail(curline));

					// Create new Mesh, if Material changes within a group
				if (!Indices.empty() && !Vertices.empty())
				{
						// Create Mesh
					tempMesh = GMeshComponent(Vertices, Indices);
					tempMesh.setComponentName(meshname);
					int i = 2;
					while(1) {
						tempMesh.setComponentName(meshname + "_" + std::to_string(i));

						for (auto &m : LoadedMeshes)
							if (m.getComponentName() == tempMesh.getComponentName())
								continue;
							break;
						}

						// Insert Mesh
						LoadedMeshes.push_back(tempMesh);

						// Cleanup
						Vertices.clear();
						Indices.clear();
					}

					#ifdef OBJL_CONSOLE_OUTPUT
					outputIndicator = 0;
					#endif
				}
				// Load Materials
				if (algorithm::firstToken(curline) == "mtllib")
				{
					// Generate LoadedMaterial

					// Generate a path to the material file
					std::vector<std::string> temp;
					algorithm::split(Path, temp, "/");

					std::string pathtomat = "";

					if (temp.size() != 1)
					{
						for (int i = 0; i < temp.size() - 1; i++)
						{
							pathtomat += temp[i] + "/";
						}
					}


					pathtomat += algorithm::tail(curline);

					#ifdef OBJL_CONSOLE_OUTPUT
					std::cout << std::endl << "- find materials in: " << pathtomat << std::endl;
					#endif

					// Load Materials
					LoadMaterials(pathtomat);
				}
			}

			#ifdef OBJL_CONSOLE_OUTPUT
			std::cout << std::endl;
			#endif

			// Deal with last mesh

			if (!Indices.empty() && !Vertices.empty())
			{
				// Create Mesh
				tempMesh = GMeshComponent(Vertices, Indices);
				tempMesh.setComponentName(meshname);

				// Insert Mesh
				LoadedMeshes.push_back(tempMesh);
			}

			file.close();

			// Set Materials for each Mesh
			for (int i = 0; i < MeshMatNames.size(); i++)
			{
				std::string matname = MeshMatNames[i];

				// Find corresponding material name in loaded materials
				// when found copy material variables into mesh material
				for (int j = 0; j < LoadedMaterials.size(); j++)
				{
					if (LoadedMaterials[j].getComponentName() == matname)
					{
						LoadedMeshes[i].m_material = LoadedMaterials[j];
						break;
					}
				}
			}

			if (LoadedMeshes.empty() && LoadedVertices.empty() && LoadedIndices.empty())
			{
				return false;
			}
			else
			{
				return true;
			}
		}

		// Loaded Mesh Objects
		std::vector<GMeshComponent> LoadedMeshes;
		// Loaded Vertex Objects
		std::vector<GVertexComponent> LoadedVertices;
		std::vector<glm::vec3> LoadedNormals;
		std::vector<glm::vec2> LoadedTextureCoordinates;
		// Loaded Index Positions
		std::vector<unsigned int> LoadedIndices;
		// Loaded Material Objects
		std::vector<GMaterialComponent> LoadedMaterials;

	private:
		// Generate vertices from a list of positions, 
		//	tcoords, normals and a face line
		void GenVerticesFromRawOBJ(std::vector<GVertexComponent>& oVerts,
			const std::vector<glm::vec3>& iPositions,
			const std::vector<glm::vec2>& iTCoords,
			const std::vector<glm::vec3>& iNormals,
			std::string icurline)
		{
			std::vector<std::string> sface, svert;
			GVertexComponent vVert;
			algorithm::split(algorithm::tail(icurline), sface, " ");

			bool noNormal = false;

			// For every given vertex do this
			for (int i = 0; i < int(sface.size()); i++)
			{
				// See What type the vertex is.
				int vtype;

				algorithm::split(sface[i], svert, "/");

				// Check for just position - v1
				if (svert.size() == 1)
				{
					// Only position
					vtype = 1;
				}

				// Check for position & texture - v1/vt1
				if (svert.size() == 2)
				{
					// Position & Texture
					vtype = 2;
				}

				// Check for Position, Texture and Normal - v1/vt1/vn1
				// or if Position and Normal - v1//vn1
				if (svert.size() == 3)
				{
					if (svert[1] != "")
					{
						// Position, Texture, and Normal
						vtype = 4;
					}
					else
					{
						// Position & Normal
						vtype = 3;
					}
				}

				// Calculate and store the vertex
				switch (vtype)
				{
				case 1: // P
				{
					vVert.position = algorithm::getElement(iPositions, svert[0]);
					vVert.tcoords = glm::vec2(0.0f, 0.0f);
					noNormal = true;
					oVerts.push_back(vVert);
					break;
				}
				case 2: // P/T
				{
					vVert.position = algorithm::getElement(iPositions, svert[0]);
					vVert.tcoords = algorithm::getElement(iTCoords, svert[1]);
					noNormal = true;
					oVerts.push_back(vVert);
					break;
				}
				case 3: // P//N
				{
					vVert.position = algorithm::getElement(iPositions, svert[0]);
					vVert.tcoords = glm::vec2(0.0f, 0.0f);
					vVert.normal = algorithm::getElement(iNormals, svert[2]);
					oVerts.push_back(vVert);
					break;
				}
				case 4: // P/T/N
				{
					vVert.position = algorithm::getElement(iPositions, svert[0]);
					vVert.tcoords = algorithm::getElement(iTCoords, svert[1]);
					vVert.normal = algorithm::getElement(iNormals, svert[2]);
					oVerts.push_back(vVert);
					break;
				}
				default:
				{
					break;
				}
			}
		}

			// take care of missing normals
			// these may not be truly acurate but it is the 
			// best they get for not compiling a mesh with normals	
		if (noNormal)
		{
			glm::vec3 A = oVerts[0].position - oVerts[1].position;
			glm::vec3 B = oVerts[2].position - oVerts[1].position;

			glm::vec3 normal = glm::cross(A, B);

			for (int i = 0; i < int(oVerts.size()); i++)
			{
				oVerts[i].normal = normal;
			}
		}
	}

		// Triangulate a list of vertices into a face by printing
		//	inducies corresponding with triangles within it
	void VertexTriangluation(std::vector<unsigned int>& oIndices,
		const std::vector<GVertexComponent>& iVerts)
	{
			// If there are 2 or less verts,
			// no triangle can be created,
			// so exit
		if (iVerts.size() < 3)
		{
			return;
		}
			// If it is a triangle no need to calculate it
		if (iVerts.size() == 3)
		{
			oIndices.push_back(0);
			oIndices.push_back(1);
			oIndices.push_back(2);
			return;
		}

			// Create a list of vertices
		std::vector<GVertexComponent> tVerts = iVerts;

		while (true)
		{
				// For every vertex
			for (int i = 0; i < int(tVerts.size()); i++)
			{
					// pPrev = the previous vertex in the list
				GVertexComponent pPrev;
				if (i == 0)
				{
					pPrev = tVerts[tVerts.size() - 1];
				}
				else
				{
					pPrev = tVerts[i - 1];
				}

					// pCur = the current vertex;
				GVertexComponent pCur = tVerts[i];

					// pNext = the next vertex in the list
				GVertexComponent pNext;
				if (i == tVerts.size() - 1)
				{
					pNext = tVerts[0];
				}
				else
				{
					pNext = tVerts[i + 1];
				}

					// Check to see if there are only 3 verts left
					// if so this is the last triangle
				if (tVerts.size() == 3)
				{
						// Create a triangle from pCur, pPrev, pNext
					for (int j = 0; j < int(tVerts.size()); j++)
					{
						if (iVerts[j].position == pCur.position)
							oIndices.push_back(j);
						if (iVerts[j].position == pPrev.position)
							oIndices.push_back(j);
						if (iVerts[j].position == pNext.position)
							oIndices.push_back(j);
					}

					tVerts.clear();
					break;
				}
				if (tVerts.size() == 4)
				{
						// Create a triangle from pCur, pPrev, pNext
					for (int j = 0; j < int(iVerts.size()); j++)
					{
						if (iVerts[j].position == pCur.position)
							oIndices.push_back(j);
						if (iVerts[j].position == pPrev.position)
							oIndices.push_back(j);
						if (iVerts[j].position == pNext.position)
							oIndices.push_back(j);
					}

					glm::vec3 tempVec;
					for (int j = 0; j < int(tVerts.size()); j++)
					{
						if (tVerts[j].position != pCur.position
							&& tVerts[j].position != pPrev.position
							&& tVerts[j].position != pNext.position)
						{
							tempVec = tVerts[j].position;
							break;
						}
					}

						// Create a triangle from pCur, pPrev, pNext
					for (int j = 0; j < int(iVerts.size()); j++)
					{
						if (iVerts[j].position == pPrev.position)
							oIndices.push_back(j);
						if (iVerts[j].position == pNext.position)
							oIndices.push_back(j);
						if (iVerts[j].position == tempVec)
							oIndices.push_back(j);
					}

					tVerts.clear();
					break;
				}

					// If Vertex is not an interior vertex
				glm::vec3 a_origin = glm::normalize(pPrev.position - pCur.position);
				glm::vec3 b_origin = glm::normalize(pNext.position - pCur.position);
				float cosab = glm::dot(a_origin,b_origin);
				
				
				float angle = glm::acos(cosab) * (180 / 3.14159265359);
				if (angle <= 0 && angle >= 180)
					continue;

					// If any vertices are within this triangle
				bool inTri = false;
				for (int j = 0; j < int(iVerts.size()); j++)
				{
					if (algorithm::inTriangle(iVerts[j].position, pPrev.position, pCur.position, pNext.position)
						&& iVerts[j].position != pPrev.position
						&& iVerts[j].position != pCur.position
						&& iVerts[j].position != pNext.position)
					{
						inTri = true;
						break;
					}
				}
				if (inTri)
					continue;

					// Create a triangle from pCur, pPrev, pNext
				for (int j = 0; j < int(iVerts.size()); j++)
				{
					if (iVerts[j].position == pCur.position)
						oIndices.push_back(j);
					if (iVerts[j].position == pPrev.position)
						oIndices.push_back(j);
					if (iVerts[j].position == pNext.position)
						oIndices.push_back(j);
				}

					// Delete pCur from the list
				for (int j = 0; j < int(tVerts.size()); j++)
				{
					if (tVerts[j].position == pCur.position)
					{
						tVerts.erase(tVerts.begin() + j);
						break;
					}
				}

					// reset i to the start
					// -1 since loop will add 1 to it
				i = -1;
			}

				// if no triangles were created
			if (oIndices.size() == 0)
				break;

				// if no more vertices
			if (tVerts.size() == 0)
				break;
		}
	}

		// Load Materials from .mtl file
	bool LoadMaterials(std::string path)
	{
			// If the file is not a material file return false
		if (path.substr(path.size() - 4, path.size()) != ".mtl")
			return false;

		std::ifstream file(path);

			// If the file is not found return false
		if (!file.is_open())
			return false;

		GMaterialComponent tempMaterial;

		bool listening = false;

			// Go through each line looking for material variables
		std::string curline;
		while (std::getline(file, curline))
		{
				// new material and material name
			if (algorithm::firstToken(curline) == "newmtl")
			{
				if (!listening)
				{
					listening = true;

					if (curline.size() > 7)
					{
						tempMaterial.setComponentName(algorithm::tail(curline));
					}
					else
					{
						tempMaterial.setComponentName("none");
					}
				}
				else
				{
						// Generate the material

						// Push Back loaded Material
					LoadedMaterials.push_back(tempMaterial);

						// Clear Loaded Material
					tempMaterial = GMaterialComponent();

					if (curline.size() > 7)
					{
						tempMaterial.setComponentName(algorithm::tail(curline));
					}
					else
					{
						tempMaterial.setComponentName("none");
					}
				}
			}
				// Ambient Color
			if (algorithm::firstToken(curline) == "Ka")
			{
				std::vector<std::string> temp;
				algorithm::split(algorithm::tail(curline), temp, " ");

				if (temp.size() != 3)
					continue;

				tempMaterial.m_ka_ambientColor.x = std::stof(temp[0]);
				tempMaterial.m_ka_ambientColor.y = std::stof(temp[1]);
				tempMaterial.m_ka_ambientColor.z = std::stof(temp[2]);
			}
				// Diffuse Color
			if (algorithm::firstToken(curline) == "Kd")
			{
				std::vector<std::string> temp;
				algorithm::split(algorithm::tail(curline), temp, " ");

				if (temp.size() != 3)
					continue;

				tempMaterial.m_kd_diffuseColor.x = std::stof(temp[0]);
				tempMaterial.m_kd_diffuseColor.y = std::stof(temp[1]);
				tempMaterial.m_kd_diffuseColor.z = std::stof(temp[2]);
			}
				// Specular Color
			if (algorithm::firstToken(curline) == "Ks")
			{
				std::vector<std::string> temp;
				algorithm::split(algorithm::tail(curline), temp, " ");

				if (temp.size() != 3)
					continue;

				tempMaterial.m_ks_specularColor.x = std::stof(temp[0]);
				tempMaterial.m_ks_specularColor.y = std::stof(temp[1]);
				tempMaterial.m_ks_specularColor.z = std::stof(temp[2]);
			}
				// Specular Exponent
			if (algorithm::firstToken(curline) == "Ns")
			{
				tempMaterial.m_ns_specularExponent = std::stof(algorithm::tail(curline));
			}
				// Optical Density
			if (algorithm::firstToken(curline) == "Ni")
			{
				tempMaterial.m_ni_opticalDensity = std::stof(algorithm::tail(curline));
			}
				// Dissolve
			if (algorithm::firstToken(curline) == "d")
			{
				tempMaterial.m_d_dissolve = std::stof(algorithm::tail(curline));
			}
				// Illumination
			if (algorithm::firstToken(curline) == "illum")
			{
				tempMaterial.m_illumination = std::stoi(algorithm::tail(curline));
			}
				// Ambient Texture Map
			if (algorithm::firstToken(curline) == "map_Ka")
			{
				tempMaterial.m_ka_ambientTexture = algorithm::tail(curline);
			}
				// Diffuse Texture Map
			if (algorithm::firstToken(curline) == "map_Kd")
			{
				tempMaterial.m_kd_diffuseTexture = algorithm::tail(curline);
			}
				// Specular Texture Map
			if (algorithm::firstToken(curline) == "map_Ks")
			{
				tempMaterial.m_ks_specularTexture = algorithm::tail(curline);
			}
				// Specular Hightlight Map
			if (algorithm::firstToken(curline) == "map_Ns")
			{
				tempMaterial.m_ns_specularHighLightTexture = algorithm::tail(curline);
			}
				// Alpha Texture Map
			if (algorithm::firstToken(curline) == "map_d")
			{
				tempMaterial.m_d_alphaTexture = algorithm::tail(curline);
			}
				// Bump Map
			if (algorithm::firstToken(curline) == "map_Bump" || algorithm::firstToken(curline) == "map_bump")
			{
				tempMaterial.m_bumpMapTexture = algorithm::tail(curline);
			}
		}

			// Deal with last material

			// Push Back loaded Material
		LoadedMaterials.push_back(tempMaterial);

			// Test to see if anything was loaded
			// If not return false
		if (LoadedMaterials.empty())
			return false;
			// If so return true
		else
			return true;
	}
};

int main(int argc, char* argv[])
{
	// Initialize Loader
	Loader Loader;

	// Load .obj File
	bool loadout = Loader.LoadFile("/Users/julian.guarin/Code/modern-opengl/samples/Resources/arwing.obj");

	// Check to see if it loaded

	// If so continue
	if (loadout)
	{
		// Create/Open e1Out.txt
		std::ofstream file("e1Out.txt");

		// Go through each loaded mesh and out its contents
		for (int i = 0; i < Loader.LoadedMeshes.size(); i++)
		{
			// Copy one of the loaded meshes to be our current mesh
			GMeshComponent curMesh = Loader.LoadedMeshes[i];

			// Print Mesh Name
			file << "Mesh " << i << ": " << curMesh.getComponentName() << "\n";

			// Print Vertices
			file << "Vertices:\n";

			// Go through each vertex and print its number,
			//  position, normal, and texture coordinate
			for (int j = 0; j < curMesh.m_vertices.size(); j++)
			{
				file << "V" << j << ": " <<
				"P(" << curMesh.m_vertices[j].position.x << ", " << curMesh.m_vertices[j].position.y << ", " << curMesh.m_vertices[j].position.z << ") " <<
				"N(" << curMesh.m_vertices[j].normal.x << ", " << curMesh.m_vertices[j].normal.y << ", " << curMesh.m_vertices[j].normal.z << ") " <<
				"TC(" << curMesh.m_vertices[j].tcoords.x << ", " << curMesh.m_vertices[j].tcoords.y << ")\n";
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
			file << "Material: " << curMesh.m_material.getComponentName() << "\n";
			file << "Ambient Color: " << curMesh.m_material.m_ka_ambientColor.x << ", " << curMesh.m_material.m_ka_ambientColor.y << ", " << curMesh.m_material.m_ka_ambientColor.z << "\n";
			file << "Diffuse Color: " << curMesh.m_material.m_kd_diffuseColor.x << ", " << curMesh.m_material.m_kd_diffuseColor.y << ", " << curMesh.m_material.m_kd_diffuseColor.z << "\n";
			file << "Specular Color: " << curMesh.m_material.m_ks_specularColor.x << ", " << curMesh.m_material.m_ks_specularColor.y << ", " << curMesh.m_material.m_ks_specularColor.z << "\n";
			file << "Specular Exponent: " << curMesh.m_material.m_ns_specularExponent << "\n";
			file << "Optical Density: " << curMesh.m_material.m_ni_opticalDensity << "\n";
			file << "Dissolve: " << curMesh.m_material.m_d_dissolve << "\n";
			file << "Illumination: " << curMesh.m_material.m_illumination << "\n";
			file << "Ambient Texture Map: " << curMesh.m_material.m_ka_ambientTexture << "\n";
			file << "Diffuse Texture Map: " << curMesh.m_material.m_kd_diffuseTexture << "\n";
			file << "Specular Texture Map: " << curMesh.m_material.m_ks_specularTexture << "\n";
			file << "Alpha Texture Map: " << curMesh.m_material.m_d_alphaTexture << "\n";
			file << "Bump Map: " << curMesh.m_material.m_bumpMapTexture << "\n";

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

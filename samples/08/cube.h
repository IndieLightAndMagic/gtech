




class Cube {
	float m_scale;
	/**
	 * Local space coordinates array for the cube vertices.
	 */
	float * m_vertices;

	/**
	 * Texture coordinates for each vertex.
	 */
	float * m_vertices_textcoord;
	/**
	 * Indices to make the triangles. 
	 */
	unsigned int * m_indices;
	unsigned int * m_indices_textcoords;
public:
	Cube(float scale=0.5):m_scale(scale),m_vertices(0x0);
	~Cube();

};

/**
 * @brief      Class for cube object. Procure to have one depth on inheritance. Inherit also Protocols / Interfaces. This class inherits GObj and implements the behavior in GOb_Renderable.
 */
class CubeObj:public GOb, GOb_Renderable{
	
	/**
	 * A cube geometry data object. This object has all the vertices and texture coordinates for a cube. 
	 */
	Cube m_cube;

public:
	CubeObj();


}

#ifndef __CUBE_DATA_H__
#define __CUBE_DATA_H__

/* This class is only to calculate the geometry of a cube of m_fScale * [W=1,H=1,D=1]. */
class CubeData final {
	/* GL OBJECTS */ 
	float * m_pfData;
	unsigned int m_vbo,m_vao;
	unsigned int m_uiDataSize;

	/* Create a Cube and GEN VAO & VBO for it. */
	/* Build 8 cube's vertices */
	float vertices[8][3]{
		{ 0.5f, 0.5f, 0.5f},//0 
		{-0.5f, 0.5f, 0.5f},//1  
		{-0.5f,-0.5f, 0.5f},//2  
		{ 0.5f,-0.5f, 0.5f},//3  
		 
		{ 0.5f, 0.5f,-0.5f},//4 
		{-0.5f, 0.5f,-0.5f},//5  
		{-0.5f,-0.5f,-0.5f},//6  
		{ 0.5f,-0.5f,-0.5f}//7  
	};
	/* Front, Back, Top, Bottom, Left, Right */
	unsigned int faces[6][2][3]{
		{{0,1,2},{2,3,0}},
		{{5,4,7},{7,6,5}},
		{{4,5,1},{1,7,4}},
		{{6,7,3},{3,2,6}},
		{{1,5,6},{6,2,1}},
		{{4,0,3},{3,7,4}}};
	float normals[6][3]{{0.0f, 0.0f,1.0f},{0.0f, 0.0f,-1.0f},{0.0f,1.0f, 0.0f},{0.0f,-1.0f, 0.0f},{-1.0f, 0.0f, 0.0f},{1.0f, 0.0f, 0.0f}};
	float texture[2][3][2]{
		{
			{1.0f, 1.0f},
			{-1.0f, 1.0f}, 
			{-1.0f, -1.0f}
		},
		{
			{-1.0f, -1.0f}, 
			{1.0f,-1.0f},
			{1.0f, 1.0f}
		}
	};

	CubeData();

public:
	static CubeData * CreateCubeData();
	/* Dangerous */
	static void FinishCubeData();
	~CubeData();
	
	void Bind();
	void Draw();
};


#endif /*__CUBE_DATA_H__*/

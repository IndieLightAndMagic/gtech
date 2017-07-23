#ifndef _CUBE_H_
#define _CUBE_H_

Cube::Cube(){


	Cube(){
		m_vertices = new float[24];
		m_vertices_textcoord = new float[8];
		
		/* Build 8 cube vertices */
		for (auto index0 = 0; index0 <8; ++index0){
			auto indexprob = index0;
			for (unsigned int index1 = 2; index1>=0; index1++){
				m_vertices[index0*3+index1] = m_scale;
				m_vertices[index0*3+index1] *= indexprob & 0x1 ? -1.0f : 1.0f;
				indexprob = indexprob >> 1;
			}
		}

		/* Build 4 texture coordinates */
		for (auto index0 = 0; index0 <4; ++index0){
			m_vertices_textcoord[index0*2+0] = index0<2		? 0.0f : 1.0f;
			m_vertices_textcoord[index0*2+1] = index0&0x1	? 1.0f : 0.0f; 	
		}

		m_indices = new unsigned int[36];
		m_indices[0]=7;
		m_indices[1]=3;
		m_indices[2]=1;
		m_indices[3]=1;
		m_indices[4]=5;
		m_indices[5]=7;

		m_indices[6]=6;
		m_indices[7]=2;
		m_indices[8]=0;
		m_indices[9]=0;
		m_indices[10]=4;
		m_indices[11]=6;

		m_indices[12]=4;
		m_indices[13]=5;
		m_indices[14]=7;
		m_indices[15]=7;
		m_indices[16]=6;
		m_indices[17]=4;

		m_indices[18]=0;
		m_indices[19]=1;
		m_indices[20]=3;
		m_indices[21]=3;
		m_indices[22]=2;
		m_indices[23]=0;

		m_indices[24]=7;
		m_indices[25]=3;
		m_indices[26]=2;
		m_indices[27]=2;
		m_indices[28]=6;
		m_indices[29]=7;

		m_indices[30]=5;
		m_indices[31]=1;
		m_indices[32]=0;
		m_indices[33]=0;
		m_indices[34]=4;
		m_indices[35]=5;	

		m_indices_textcoords = new unsigned int[36];

		m_indices_textcoords[0] = 0;
		m_indices_textcoords[1] = 2;
		m_indices_textcoords[2] = 3;
		m_indices_textcoords[3] = 3;
		m_indices_textcoords[4] = 1;
		m_indices_textcoords[5] = 0;
		m_indices_textcoords[6] = 0;
		m_indices_textcoords[7] = 2;
		m_indices_textcoords[8] = 3;
		m_indices_textcoords[9] = 3;
		m_indices_textcoords[10] = 1;
		m_indices_textcoords[11] = 0;
		m_indices_textcoords[12] = 2;
		m_indices_textcoords[13] = 3;
		m_indices_textcoords[14] = 1;
		m_indices_textcoords[15] = 1;
		m_indices_textcoords[16] = 0;
		m_indices_textcoords[17] = 2;
		m_indices_textcoords[18] = 2;
		m_indices_textcoords[19] = 3;
		m_indices_textcoords[20] = 1;
		m_indices_textcoords[21] = 1;
		m_indices_textcoords[22] = 0;
		m_indices_textcoords[23] = 2;
		m_indices_textcoords[24] = 1;
		m_indices_textcoords[25] = 3;
		m_indices_textcoords[26] = 2;
		m_indices_textcoords[27] = 2;
		m_indices_textcoords[28] = 0;
		m_indices_textcoords[29] = 1;
		m_indices_textcoords[30] = 1;
		m_indices_textcoords[31] = 3;
		m_indices_textcoords[32] = 2;
		m_indices_textcoords[33] = 2;
		m_indices_textcoords[34] = 0;
		m_indices_textcoords[35] = 1;


	}

}

~Cube::Cube(){
	delete m_indices_textcoords;
	delete m_vertices_textcoord;
	delete m_indices;
	delete m_vertices;
}


#endif /* _CUBE_H_ */

CubeData::CubeData():
	m_fScale(scale),
	m_pVrtx(0x0),
	m_pVrtx_TxtrCoord(0x0),
	m_pIndx(0x0),
	p_pIndx_TxtrCoords(0x0)
{


	CubeData(){
		m_pVrtx = new float[24];
		m_pVrtx_TxtrCoord = new float[8];
		
		/* Build 8 cube vertices */
		for (auto index0 = 0; index0 <8; ++index0){
			auto indexprob = index0;
			for (int index1 = 0; index1<=2; index1++){
				m_pVrtx[index0*3+index1] = 0.5f*m_scale;
				m_pVrtx[index0*3+index1] *= indexprob & 0x1 ? -1.0f : 1.0f;
				indexprob = indexprob >> 1;
			}
		}

		/* Build 4 texture coordinates */
		for (auto index0 = 0; index0 <4; ++index0){
			m_pVrtx_TxtrCoord[index0*2+0] = index0<2		? 0.0f : 1.0f;
			m_pVrtx_TxtrCoord[index0*2+1] = index0&0x1	? 1.0f : 0.0f; 	
		}

		m_pIndx = new unsigned int[36];
		m_pIndx[0]=7;
		m_pIndx[1]=3;
		m_pIndx[2]=1;
		m_pIndx[3]=1;
		m_pIndx[4]=5;
		m_pIndx[5]=7;

		m_pIndx[6]=6;
		m_pIndx[7]=2;
		m_pIndx[8]=0;
		m_pIndx[9]=0;
		m_pIndx[10]=4;
		m_pIndx[11]=6;

		m_pIndx[12]=4;
		m_pIndx[13]=5;
		m_pIndx[14]=7;
		m_pIndx[15]=7;
		m_pIndx[16]=6;
		m_pIndx[17]=4;

		m_pIndx[18]=0;
		m_pIndx[19]=1;
		m_pIndx[20]=3;
		m_pIndx[21]=3;
		m_pIndx[22]=2;
		m_pIndx[23]=0;

		m_pIndx[24]=7;
		m_pIndx[25]=3;
		m_pIndx[26]=2;
		m_pIndx[27]=2;
		m_pIndx[28]=6;
		m_pIndx[29]=7;

		m_pIndx[30]=5;
		m_pIndx[31]=1;
		m_pIndx[32]=0;
		m_pIndx[33]=0;
		m_pIndx[34]=4;
		m_pIndx[35]=5;	

		p_pIndx_TxtrCoords = new unsigned int[36];

		p_pIndx_TxtrCoords[0] = 0;
		p_pIndx_TxtrCoords[1] = 2;
		p_pIndx_TxtrCoords[2] = 3;
		p_pIndx_TxtrCoords[3] = 3;
		p_pIndx_TxtrCoords[4] = 1;
		p_pIndx_TxtrCoords[5] = 0;
		p_pIndx_TxtrCoords[6] = 0;
		p_pIndx_TxtrCoords[7] = 2;
		p_pIndx_TxtrCoords[8] = 3;
		p_pIndx_TxtrCoords[9] = 3;
		p_pIndx_TxtrCoords[10] = 1;
		p_pIndx_TxtrCoords[11] = 0;
		p_pIndx_TxtrCoords[12] = 2;
		p_pIndx_TxtrCoords[13] = 3;
		p_pIndx_TxtrCoords[14] = 1;
		p_pIndx_TxtrCoords[15] = 1;
		p_pIndx_TxtrCoords[16] = 0;
		p_pIndx_TxtrCoords[17] = 2;
		p_pIndx_TxtrCoords[18] = 2;
		p_pIndx_TxtrCoords[19] = 3;
		p_pIndx_TxtrCoords[20] = 1;
		p_pIndx_TxtrCoords[21] = 1;
		p_pIndx_TxtrCoords[22] = 0;
		p_pIndx_TxtrCoords[23] = 2;
		p_pIndx_TxtrCoords[24] = 1;
		p_pIndx_TxtrCoords[25] = 3;
		p_pIndx_TxtrCoords[26] = 2;
		p_pIndx_TxtrCoords[27] = 2;
		p_pIndx_TxtrCoords[28] = 0;
		p_pIndx_TxtrCoords[29] = 1;
		p_pIndx_TxtrCoords[30] = 1;
		p_pIndx_TxtrCoords[31] = 3;
		p_pIndx_TxtrCoords[32] = 2;
		p_pIndx_TxtrCoords[33] = 2;
		p_pIndx_TxtrCoords[34] = 0;
		p_pIndx_TxtrCoords[35] = 1;


	}

}

~CubeData::CubeData(){
	delete p_pIndx_TxtrCoords;
	delete m_pVrtx_TxtrCoord;
	delete m_pIndx;
	delete m_pVrtx;
}
float * getCubeDataPack(void * ptr){


	float * cubeDataPack = ptr == 0x0 ? new float[5*3*2*6] : (float*) ptr; /* 6 faces, 2 triangles per face, 3 vertices per triangle, 5 components per vertex */ 
	
	for (auto surfaceIndex = 0; surfaceIndex < 6; ++surfaceIndex){
		auto offset = surfaceIndex * 30;
		for (auto triangleIndex = 0; triangleIndex < 2; ++triangleIndex){
			offset += triangleIndex * 15;
			for (auto vertexIndex = 0; vertexIndex < 3; ++vertexIndex){
				offset += vertexIndex*5;
				for (auto componentIndex = 0; componentIndex < 5; ++componentIndex){

					offset += componentIndex;
					cubeDataPack[offset] = componentIndex < 3 ? m_pVrtx[ m_pIndx[ surfaceIndex * 6 + triangleIndex * 3 + vertexIndex ] * 3 + componentIndex ] : m_pVrtx_TxtrCoord[ surfaceIndex * 6 + triangleIndex * 3 + vertexIndex ] * 2 + (componentIndex - 3);

				}
			}
		}
	}
	return cubeDataPack;
}

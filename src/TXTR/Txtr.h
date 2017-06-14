#ifndef __TXTR_H__
#define __TXTR_H__

class SimpleImageData{
	bool m_bValid;
	unsigned char * m_pucData;
public:
	int iWidth, iHeight, iChannels;
	SimpleImageData(const char * imageFilePath);
	~SimpleImageData();
	unsigned char * operator()();
};

class Txtr {
	
	unsigned int m_uiActiveTextureIndex;
	unsigned int m_uiNtextures;

	bool m_bValid;
	unsigned int * m_puiTextures;
public:
	/*!
		@brief Generate a number of texture handlers.
		@param nTextures The number of handlers to generate;
	*/
	Txtr(unsigned int nTextures);
	virtual ~Txtr();

	/* Select a texture */
	void TxtrSelect(unsigned int uiTextureIndex);
	/* By default texture config */
	void TxtrConfig();
	/* Assign Data for the texture */
	void TxtrImage(SimpleImageData * pxImg);
};
#endif/*__TXTR_H__*/
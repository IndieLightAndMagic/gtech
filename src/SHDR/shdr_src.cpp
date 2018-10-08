#include "shdr.h"

#include <string>
#include <sstream>
#include <fstream>
#include <sstream>
#include <iostream>

static std::string getShaderCode(const GLchar *shdrPath)
{
	std::ifstream shaderFile;

	// exceptions flag checks for read/write operations on i/o operations 
	shaderFile.exceptions(std::ifstream::badbit);
	shaderFile.open(shdrPath);
	if (!shaderFile.good())
	{
		std::string emptyString;
		return emptyString;
	}
	// Read Files into streams 
	std::stringstream shaderStream;
	shaderStream << shaderFile.rdbuf();
		
	// Close files 
	shaderFile.close();

	// Return the code
	return shaderStream.str();
} 

GTech::ShaderSource::ShaderSource(const GLchar*shdrPath):m_state(SOURCE_STATE_INVALID),m_shdrPath(new std::string(shdrPath)),m_shdrSrc(nullptr) {
	

	// Set stream into strings
	m_shaderCode = getShaderCode(shdrPath);

	if (!m_shaderCode.empty())
	{		
		// C character string shader source 
		m_shdrSrc = m_shaderCode.c_str();

		// Set valid State 
		m_state = SOURCE_STATE_VALID;

	}
	else 
	{
		// Warn error
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl; 
	} 

}

GTech::ShaderSource::ShaderSource(const std::string &shdrPath):m_state(SOURCE_STATE_INVALID),m_shdrPath(new std::string(shdrPath)),m_shdrSrc(nullptr)
{
	m_shaderCode = getShaderCode(shdrPath.c_str());
	if (!m_shaderCode.empty())
	{
		m_shdrSrc = m_shaderCode.c_str();
		m_state = SOURCE_STATE_VALID;
	}
	else 
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
}

const GLchar * GTech::ShaderSource::operator()(){ 
	return m_shdrSrc; 
}

GTech::ShaderSource::ShaderSourceState GTech::ShaderSource::state(){ 
	return m_state;
}


#ifdef TEST_BENCH
#include <TEST/tbench.h>
unsigned int shaderSourceTest(const GLchar*shdrPath){

	ShaderSource ss(shdrPath);

	if (ss.state()==GTech::ShaderSource::SOURCE_STATE_VALID){
	
		std::cout << ss() << std::endl; 
		return UINT_TEST_OK;
	
	}
	
	return UINT_TEST_FAIL;

}

int main (int argc, char ** argv){

	bool _0k = true;
	TEST_INT(_0k, shaderSourceTest("../../04/vs.vs"));
	TEST_INT(_0k, shaderSourceTest("../../04/fs.fs"));
	TEST_INT(_0k, shaderSourceTest("../../04/fs.fsx"));
	
	TEST_RESULT(_0k);

}

#endif

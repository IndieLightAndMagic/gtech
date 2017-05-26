#include "shdr.h"

#include <string>
#include <sstream>
#include <fstream>
#include <sstream>
#include <iostream>

ShaderSource::ShaderSource(const GLchar*shdrPath):m_state(SOURCE_STATE_INVALID),m_shdrPath(new std::string(shdrPath)),m_shdrSrc(nullptr) {
	
	std::ifstream shaderFile;

	/* exceptions flag checks for read/write operations on i/o operations */
	shaderFile.exceptions(std::ifstream::badbit);
	try {
		/* Open files */
		shaderFile.open(shdrPath);
		if (!shaderFile.good()){
			std::cout << "ifstream.good() = false" << std::endl;
			throw 1;
		} 

		/* Read Files into streams */
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		
		/* Close files */
		shaderFile.close();

		/* Ste stream into strings */
		m_shaderCode = shaderStream.str();

		/* C character string shader source */
		m_shdrSrc = m_shaderCode.c_str();

		/* Set valid State */
		m_state = SOURCE_STATE_VALID;

	}
	catch (int error){
		/* Warn error */
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl; 
	} 

}
const GLchar * ShaderSource::operator()(){ return m_shdrSrc; }
ShaderSource::ShaderSourceState ShaderSource::state(){ return m_state; }






#ifdef TEST_BENCH
#include <TEST/tbench.h>

unsigned int shaderSourceTest(const GLchar*shdrPath){

	ShaderSource ss(shdrPath);

	if (ss.state()==ShaderSource::SOURCE_STATE_VALID){
	
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

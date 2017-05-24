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
	

		/* Read Files into streams */
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		
		/* Close files */
		shaderFile.close();

		/* Ste stream into strings */
		m_shaderCode = shaderStream.str();
		std::cout << "@@@@" << "SHADER LOADED" << std::endl;
		std::cout << m_shaderCode << std::endl;			
		/* C character string shader source */
		m_shdrSrc = m_shaderCode.c_str();

		/* Set valid State */
		m_state = SOURCE_STATE_VALID;

	}
	catch (std::ifstream::failure e){
		/* Warn error */
		std::cout << m_shdrSrc << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

}
const GLchar * ShaderSource::operator()(){ return m_shdrSrc; }
ShaderSource::ShaderSourceState ShaderSource::state(){ return m_state; }






#ifdef TEST_BENCH
/* Yes this is my test scheme...  ill do it later */
#ifndef SHDR_CPP_NOTEST
#define PASSED TRUE
#define NOT_PASSED NOT_TRUE


unsigned int shaderSource(const GLchar*shdrPath){

	ShaderSource ss(shdrPath);
	if (ss.state()==ShaderSource::SOURCE_STATE_VALID) return 1;
	return 0;

}

int main (int argc, char ** argv){

	bool _0k = true;
	std::cout <<_0k << std::endl;
	_0k = _0k & (shaderSource("../../04/vsx.vs"));
	std::cout <<_0k << std::endl;
	return _0k == true ? 1 : 0;

}

#endif
#endif

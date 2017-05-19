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
		
		/* C character string shader source */
		m_shdrSrc = m_shaderCode.c_str();

		/* Set valid State */
		m_state = SOURCE_STATE_VALID;

	}
	catch (std::ifstream::failure e){
		/* Warn error */
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

}
const GLchar * ShaderSource::operator()(){ return m_shdrSrc; }







#ifdef TEST_BENCH
/* Yes this is my test scheme...  ill do it later */
#ifndef SHDR_CPP_NOTEST
#define PASSED TRUE
#define NOT_PASSED NOT_TRUE

#endif
#endif

#include "shdr.h"




Program::Program(){
	m_program = glCreateProgram();
	m_state = m_program ? PROGRAM_STATE_VOID : PROGRAM_STATE_INVALID;
}
void Program::pushShader(Shader*shader){
	glAttachShader(m_program,shader[0]());
}
void Program::pushShader(ShaderSource* pxSs, GLenum eShaderType){

	if (m_state == PROGRAM_STATE_INVALID) return;

	Shader xS(pxSs,eShaderType);
	if (xS.state() != Shader::SHADER_STATE_COMPILED) invalidateProgram();
	else pushShader(&xS);

	return;

}

void Program::pushShader(const char * pFilename, GLenum eShaderType){

	if (m_state == PROGRAM_STATE_INVALID) return;
	ShaderSource xSs(pFilename);
	if (xSs.state() != ShaderSource::SOURCE_STATE_VALID) invalidateProgram(); 
	else pushShader(&xSs,eShaderType);

}
void Program::use(){
	if (m_state == PROGRAM_STATE_SHADERS_ATTACHED) glUseProgram(m_program);
}

void Program::invalidateProgram(){
	if (m_state != PROGRAM_STATE_INVALID){
		m_state = PROGRAM_STATE_INVALID;
		glDeleteProgram(m_program);		
	}

}

void Program::link(){
	glLinkProgram(m_program);
}
const GLuint Program::operator()(){return m_program;}


#ifdef PERFORM_UNIT_TEST

	




#endif


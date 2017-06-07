#include "shdr.h"




Program::Program(){
	m_program = glCreateProgram();
	m_state = m_program ? PROGRAM_STATE_VOID : PROGRAM_STATE_INVALID;
}
void Program::pushShader(Shader*pS){
	if (m_state == PROGRAM_STATE_INVALID || pS->state() != Shader::SHADER_STATE_COMPILED) invalidateProgram();
	else {
		glAttachShader(m_program,pS[0]());
		m_state = (m_state == PROGRAM_STATE_LINKED_NOT_USED|| m_state == PROGRAM_STATE_LINKED_AND_USED) ? m_state : PROGRAM_STATE_SHADERS_ATTACHED;  
	}
}
void Program::pushShader(ShaderSource* pxSs, GLenum eShaderType){

	if (m_state == PROGRAM_STATE_INVALID || pxSs->state() != ShaderSource::SOURCE_STATE_VALID) invalidateProgram();
	else {
		Shader xS(pxSs,eShaderType);
		pushShader(&xS);
	}
}

void Program::pushShader(const char * pFilename, GLenum eShaderType){

	if (m_state == PROGRAM_STATE_INVALID) invalidateProgram();
	else { 
		ShaderSource xSs(pFilename);
		pushShader(&xSs,eShaderType);
	}
}
void Program::use(){
	if (m_state == PROGRAM_STATE_SHADERS_ATTACHED|| m_state == PROGRAM_STATE_LINKED_NOT_USED|| m_state == PROGRAM_STATE_LINKED_AND_USED) glUseProgram(m_program);
}

void Program::invalidateProgram(){
	/* TODO: Create a way to admon the shaders more effectively */
	if (m_state != PROGRAM_STATE_INVALID){
		m_state = PROGRAM_STATE_INVALID;
		glDeleteProgram(m_program);		
	}

}
bool Program::isLinked(){
	return (m_state == PROGRAM_STATE_LINKED_NOT_USED|| m_state == PROGRAM_STATE_LINKED_AND_USED) ? GL_TRUE : GL_FALSE;
}
void Program::link(){
	int iSuccess;
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &iSuccess);
	m_state = iSuccess ? PROGRAM_STATE_LINKED_NOT_USED : PROGRAM_STATE_INVALID;

}
const GLuint Program::operator()(){return m_program;}

Program::ProgramState Program::state(){
	return m_state;
}

#ifdef PERFORM_UNIT_TEST

	




#endif


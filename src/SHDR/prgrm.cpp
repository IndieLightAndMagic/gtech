#include "shdr.h"




Program::Program(){
	m_program = glCreateProgram();
	m_state = m_program ? PROGRAM_STATE_VOID : PROGRAM_STATE_INVALID;
}
void Program::PushShader(Shader*shader){
	glAttachShader(m_program,shader[0]());
}
void Program::Use(){
	if (m_state == PROGRAM_STATE_SHADERS_ATTACHED) glUseProgram(m_program);
}
void Program::Link(){
	glLinkProgram(m_program);
}
const GLuint Program::operator()(){return m_program;}


#ifdef PERFORM_UNIT_TEST

	




#endif


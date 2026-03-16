#ifdef _WIN32
	#define ENGINE_API_EXPORTS
#endif

#include "ogl_shader.hpp"

std::string OpenGLShader::_getSourceFromFile(const std::string file)
{
	std::string source;

	std::ifstream f(file);
	if(!f.is_open())
	{
		std::cerr << "Cant open " << file << std::endl;
		return "FILE IS NOT OPEN";
	}

	std::string buffer;
	while(std::getline(f, buffer))
	{
		source += buffer + '\n';
	}

	f.close();

	return source;
}

OpenGLShader::OpenGLShader(std::string v_path, std::string f_path)
{
	/* Ohh */
	GLint success;
	GLchar infoLogs[512];

	vertex_path = v_path;
	fragment_path = f_path;

	const std::string v_source_m = _getSourceFromFile(vertex_path);
	const std::string f_source_m = _getSourceFromFile(fragment_path);

	const char* v_source = v_source_m.c_str();
	const char* f_source = f_source_m.c_str();

	/* Vertex shader build */

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertex, 1, &v_source, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLogs);

		std::cerr << "Failed to build Vertex shader:\n" << infoLogs << "\n";
	}

	/* Fragment shader build */

	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragment, 1, &f_source, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLogs);

		std::cerr << "Failed to build Fragment shader:\n" << infoLogs << "\n";
	}

	/* Shader program build */

	program = glCreateProgram();

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, NULL, infoLogs);

		std::cerr << "Failed to link Program shader:\n" << infoLogs << "\n";
	}

	/* Clear memory */

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

ENGINE_API OpenGLShader::~OpenGLShader()
{
	if(program)
		glDeleteProgram(program);
}

ENGINE_API void OpenGLShader::bind()
{
	glUseProgram(program);
}

ENGINE_API void OpenGLShader::setInt(const char *uniform, GLint value)
{
	GLint uniformLocation = glGetUniformLocation(program, uniform);
	glUniform1i(uniformLocation, value);
}

ENGINE_API void OpenGLShader::setFloat(const char *uniform, GLfloat value)
{
	GLint uniformLocation = glGetUniformLocation(program, uniform);
	glUniform1f(uniformLocation, value);
}

ENGINE_API void OpenGLShader::setVec3(const char *uniform, vec3 value)
{
	GLint uniformLocation = glGetUniformLocation(program, uniform);
	glUniform3f(uniformLocation, value.x, value.y, value.z);
}

ENGINE_API void OpenGLShader::setVec4(const char *uniform, vec4 value)
{
	GLint uniformLocation = glGetUniformLocation(program, uniform);
	glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
}

ENGINE_API void OpenGLShader::setMat4(const char *uniform, mat4 value)
{
	GLint uniform_location = glGetUniformLocation(program, uniform);
	glUniformMatrix4fv(uniform_location, 1, GL_TRUE, (const GLfloat *)&value);
}

ENGINE_API GLuint OpenGLShader::getProgram()
{
	return program;
}
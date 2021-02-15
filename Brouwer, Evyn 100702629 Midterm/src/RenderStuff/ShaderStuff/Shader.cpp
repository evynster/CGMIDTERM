#include "Shader.h"

mte::Shader::Shader(std::string shaderName, std::string vs_source, std::string fs_source)
	:_shaderName(shaderName),_vs_source(vs_source),_fs_source(fs_source)
{
	myShaderHandle = glCreateProgram();
	Load(_vs_source.c_str(), _fs_source.c_str());
}

mte::Shader::~Shader()
{
	glDeleteProgram(myShaderHandle);
}

void mte::Shader::compile(const char* vs_source,const char* fs_source)
{
	// Compile our two shader programs
	GLuint vs = __CompileShaderPart(vs_source, GL_VERTEX_SHADER);
	GLuint fs = __CompileShaderPart(fs_source, GL_FRAGMENT_SHADER);
	// Attach our two shaders
	glAttachShader(myShaderHandle, vs);
	glAttachShader(myShaderHandle, fs);
	// Perform linking
	glLinkProgram(myShaderHandle);

	// Remove shader parts to save space
	glDetachShader(myShaderHandle, vs);
	glDeleteShader(vs);
	glDetachShader(myShaderHandle, fs);
	glDeleteShader(fs);

	// Get whether the link was successful
	GLint success = 0;
	glGetProgramiv(myShaderHandle, GL_LINK_STATUS, &success);

	{
		Error error;
		error._errorLocation = "Shader.cpp";
		if (success == GL_FALSE) {
			// TODO: Read the log file
			// Throw a runtime exception
			error._errorSeverity = mte::ErrorSeverityLevel::gameCrashing;
			error._errorMessage = "Failed to link shader program!";
			error._errorTypes.push_back(mte::ErrorType::Init);
		}
		else {
			error._errorSeverity = mte::ErrorSeverityLevel::great;
			error._errorTypes.push_back(mte::ErrorType::CheckPoint);
			error._errorMessage = "Shader has been linked";
		}
		_logger.sendError(error);
	}
	// If not, we need to grab the log and throw an exception
	{
		Error error;
		error._errorLocation = "Shader.cpp";
		error._errorSeverity = mte::ErrorSeverityLevel::gameCrashing;
		error._errorTypes.push_back(mte::ErrorType::Log);
		if (success == GL_FALSE) {
			// Get the length of the log
			GLint length = 0;
			glGetProgramiv(myShaderHandle, GL_INFO_LOG_LENGTH, &length);
			if (length > 0) {
				// Read the log from openGL
				
				char* log = new char[length];
				glGetProgramInfoLog(myShaderHandle, length, &length, log);
				std::string logString(log);
				error._errorMessage = "Shader failed to link: " + logString;
				delete[] log;
			}
			else {
				error._errorMessage = "Shader failed to link for an unknown reason!";
			}
			// Delete the partial program
			glDeleteProgram(myShaderHandle);
			// Throw a runtime exception
			error._errorMessage = "Failed to link shader program!";
			_logger.sendError(error);
		}
		
	}
	
}
char* mte::Shader::readFile(const char* filename) {
	// Declare and open the file stream
	std::ifstream file;
	file.open(filename, std::ios::binary);
	// Only read if the file is open
	if (file.is_open()) {
		// Get the starting location in the file
		uint64_t fileSize = file.tellg();
		// Seek to the end
		file.seekg(0, std::ios::end);
		// Calculate the file size from end to beginning
		fileSize = (uint64_t)file.tellg() - fileSize;
		// Seek back to the beginning of the file
		file.seekg(0, std::ios::beg);
		// Allocate space for our entire file, +1 byte at the end for null terminator
		char* result = new char[fileSize + 1];
		// Read the entire file to our memory
		file.read(result, fileSize);
		// Make our text null-terminated
		result[fileSize] = '\0';
		// Close the file before returning
		file.close();
		return result;
	}
	// Otherwise, we failed to open our file, throw a runtime error
	else {
		mte::Error error;
		error._errorLocation = "Shader.cpp";
		error._errorSeverity = mte::ErrorSeverityLevel::gameCrashing;
		std::string filenameString(filename);
		error._errorMessage = "We cannot open " + filenameString;
		error._errorTypes.push_back(mte::ErrorType::Init);
		_logger.sendError(error);
	}
}

void mte::Shader::Load(const char* vsFile,const  char* fsFile)
{
	// Load in our shaders
	char* vs_source = readFile(vsFile);
	char* fs_source = readFile(fsFile);
	// Compile our program
	compile(vs_source, fs_source);
	// Clean up our memory
	delete[] fs_source;
	delete[] vs_source;
}

void mte::Shader::Bind()
{
	glUseProgram(myShaderHandle);
}

void mte::Shader::SetUniform(const char* name, const glm::mat4& value) {
	GLint loc = glGetUniformLocation(myShaderHandle, name);
	if (loc != -1) {
		glProgramUniformMatrix4fv(myShaderHandle, loc, 1, false, &value[0][0]);
	}
}
void mte::Shader::SetUniform(const char* name, const glm::mat3& value) {
	GLint loc = glGetUniformLocation(myShaderHandle, name);
	if (loc != -1) {
		glProgramUniformMatrix3fv(myShaderHandle, loc, 1, false, &value[0][0]);
	}
}
void mte::Shader::SetUniform(const char* name, const glm::vec3& value) {
	GLint loc = glGetUniformLocation(myShaderHandle, name);
	if (loc != -1) {
		glProgramUniform3fv(myShaderHandle, loc, 1, &value[0]);
	}
}
void mte::Shader::SetUniform(const char* name, const float& value) {
	GLint loc = glGetUniformLocation(myShaderHandle, name);
	if (loc != -1) {
		glProgramUniform1fv(myShaderHandle, loc, 1, &value);
	}
}

void mte::Shader::SetUniform(const char* name, const int& value)
{
	GLint loc = glGetUniformLocation(myShaderHandle, name);
	if (loc != -1) {
		glProgramUniform1iv(myShaderHandle, loc, 1, &value);
	}
}


void mte::Shader::drawCubes(std::shared_ptr<Camera> camera)
{
	_lightCubeShader->Bind();
	for (auto x : _lightCubes) {
		if (x->_drawn != true) {
			_lightCubeShader->SetUniform("a_ModelViewProjection", camera->GetViewProjection());
			_lightCubeShader->SetUniform("a_colour", x->_diffuse);
			_lightCubeShader->SetUniform("a_pos",x->_pos);
			x->drawCube();
		}

		x->_drawn = true;
	}
}

void mte::Shader::updateCubes()
{
	for (auto x : _lightCubes) {
		x->_drawn = false;
	}
}

GLuint mte::Shader::__CompileShaderPart(const char* source, GLenum type)
{
	GLuint result = glCreateShader(type);
	// Load in our shader source and compile it
	glShaderSource(result, 1, &source, NULL);
	glCompileShader(result);

	// Check our compile status
	GLint compileStatus = 0;
	glGetShaderiv(result, GL_COMPILE_STATUS, &compileStatus);
	// If we failed to compile
	if (compileStatus == GL_FALSE) {
		// Get the size of the error log
		GLint logSize = 0;
		glGetShaderiv(result, GL_INFO_LOG_LENGTH, &logSize);
		// Create a new character buffer for the log
		char* log = new char[logSize];
		// Get the log
		glGetShaderInfoLog(result, logSize, &logSize, log);
		// Dump error log
		Error error;
		error._errorLocation = "Shader.cpp";
		error._errorSeverity = mte::ErrorSeverityLevel::gameCrashing;
		error._errorTypes.push_back(mte::ErrorType::Log);
		std::string logString(log);
		error._errorMessage ="Failed to compile shader part: " + logString;
		_logger.sendError(error);
		// Clean up our log memory
		delete[] log;
		// Delete the broken shader result
		glDeleteShader(result);
	}
	else {
		Error error;
		error._errorLocation = "Shader.cpp";
		error._errorSeverity = mte::ErrorSeverityLevel::great;
		std::string sourceString(source);
		error._errorMessage = "Shader part has been compiled: " + sourceString;
		error._errorTypes.push_back(mte::ErrorType::Log);
		_logger.sendError(error);
	}
	// Return the compiled shader part
	return result;

}

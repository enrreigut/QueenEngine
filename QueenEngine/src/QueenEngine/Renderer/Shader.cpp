#include "Shader.h"

namespace Queen
{
	namespace Renderer
	{

		GLuint Shader::LoadShaders(const char* vertex_file_path, const char* fragment_file_path)
		{
			m_VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
			m_FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertexCode;
			m_fr.GetFileContent(vertexCode, vertex_file_path);

			std::string fragmentCode;
			m_fr.GetFileContent(fragmentCode, fragment_file_path);

			CompileShader(m_VertexShaderID, vertexCode.c_str());
			CompileShader(m_FragmentShaderID, fragmentCode.c_str());

			LinkProgram();

			return m_ProgramID;
		}

		bool Shader::CompileShader(GLuint& shaderId, const char* code)
		{
			GLint result = GL_FALSE;
			int infoLogLength;

			CheckError(shaderId, result, infoLogLength);

			glShaderSource(shaderId, 1, &code, NULL);
			glCompileShader(shaderId);

			return true;
		}

		void Shader::CheckError(GLuint& shaderId, GLint& res, int& infoLength)
		{
			glGetShaderiv(shaderId, GL_COMPILE_STATUS, &res);
			glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLength);
			if (infoLength > 0) {
				std::vector<char> shaderErrorMessage(infoLength + 1);
				glGetShaderInfoLog(shaderId, infoLength, NULL, &shaderErrorMessage[0]);
				QE_LOG_PARAMS(QE_ERROR, "{v}", &shaderErrorMessage[0]);
			}
		}

		void Shader::CheckProgram(GLint& res, int& infoLength)
		{
			glGetProgramiv(m_ProgramID, GL_COMPILE_STATUS, &res);
			glGetProgramiv(m_ProgramID, GL_INFO_LOG_LENGTH, &infoLength);
			if (infoLength > 0) {
				std::vector<char> programErrorMessage(infoLength + 1);
				glGetShaderInfoLog(m_ProgramID, infoLength, NULL, &programErrorMessage[0]);
				QE_LOG_PARAMS(QE_ERROR, "Error Linking Program {v}", &programErrorMessage[0]);
			}
		}

		bool Shader::LinkProgram()
		{
			m_ProgramID = glCreateProgram();

			glAttachShader(m_ProgramID, m_VertexShaderID);
			glAttachShader(m_ProgramID, m_FragmentShaderID);

			glLinkProgram(m_ProgramID);


			GLint result = GL_FALSE;
			int infoLogLength;
			CheckProgram(result, infoLogLength);

			glDetachShader(m_ProgramID, m_VertexShaderID);
			glDetachShader(m_ProgramID, m_FragmentShaderID);

			glDeleteShader(m_VertexShaderID);
			glDeleteShader(m_FragmentShaderID);

			return true;
		}

		//Setters

		void Shader::SetBool(const char* name, bool&& value) const
		{
			glUniform1i(glGetUniformLocation(m_ProgramID, name), (int)value);
		}

		void Shader::SetInt(const char* name, int&& value) const
		{
			glUniform1i(glGetUniformLocation(m_ProgramID, name), value);
		}

		void Shader::SetFloat(const char* name, float&& value) const
		{
			glUniform1f(glGetUniformLocation(m_ProgramID, name), value);
		}

		void Shader::SetFloat(const char* name, float& value) const
		{
			glUniform1f(glGetUniformLocation(m_ProgramID, name), value);
		}

		void Shader::SetMat4(const char* name, glm::mat4& value) const
		{
			glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name), 1, GL_FALSE, &value[0][0]);
		}
	}
}
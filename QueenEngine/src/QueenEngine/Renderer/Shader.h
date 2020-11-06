#pragma once

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../Utils/FileReader.h"
#include "../Manager/LogManager.h"

namespace Queen
{
	namespace Renderer
	{
		class Shader
		{
		public:

			GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);
			
			//getters
			const inline GLuint GetVertexShaderID()& { return m_VertexShaderID; }
			const inline GLuint GetFragmentShaderID()& { return m_FragmentShaderID ; }
			const inline GLuint GetProgramID()& { return m_ProgramID; }

			//setters
			void SetBool(const char* name, bool&& value) const;
			void SetInt(const char* name, int&& value) const;
			void SetFloat(const char* name, float&& value) const;
			void SetFloat(const char* name, float& value) const;
			void SetMat4(const char* name, glm::mat4& value) const;

		protected:

			bool CompileShader(GLuint& shaderId, const char* code);
			void CheckError(GLuint& shaderId, GLint& res, int& infoLength);
			void CheckProgram(GLint& res, int& infoLength);
			bool LinkProgram();

		private:

			GLuint m_VertexShaderID;
			GLuint m_FragmentShaderID;

			GLuint m_ProgramID;

			Utils::FileReader m_fr;
		
		};
	}
}



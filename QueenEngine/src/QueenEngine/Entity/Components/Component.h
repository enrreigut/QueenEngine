#pragma once

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/IndexBuffer.h"
#include "../Renderer/Texture.h"

#include "../Utils/FileReader.h"

namespace Queen
{
	namespace Entity
	{
		namespace Component
		{
			struct Component
			{

			};

			struct Model : public Component
			{
				Utils::FileReader m_Reader;

				std::vector<glm::vec3> m_Vertices;
				std::vector<glm::vec3> m_Normals;
				std::vector<glm::vec2> m_Uvs;
				std::vector<unsigned int> m_Indexes;
				std::vector<Queen::Renderer::Vertex> m_Data;

				/*Renderer::VertexBuffer m_VBO;
				Renderer::IndexBuffer m_IBO;
				Renderer::Shader m_Shader;*/

				const char* m_Name;

				void ProcessData()
				{
					Queen::Renderer::Vertex v;
					for (int i = 0; i < m_Vertices.size(); i++)
					{
						v.position = m_Vertices.at(i);

						if(m_Normals.size() != 0)
							v.normals = m_Normals.at(i);
						
						if(m_Uvs.size() != 0)
							v.uvs = m_Uvs.at(i);

						m_Data.push_back(v);
					}
				}

				void LoadObj(const char* filePath)
				{
					m_Reader.GetModelData(filePath, m_Vertices, m_Indexes, m_Uvs, m_Normals);
					ProcessData();
				}

			};

			struct Transform : public Component
			{
				glm::vec3 m_Transform = glm::vec3(0.0f, 0.0, 0.0f);

				void SetTransform(glm::vec3 data) { m_Transform = data; }
			};

			struct Rotation : public Component
			{
				//Mouse X
				float m_Yaw = 0.0f;
				//Mouse Y
				float m_Pitch = 0.0f;

				//driections
				glm::vec3 m_VecUp = glm::vec3(0.0f, 1.0f, 0.0f);
				glm::vec3 m_Rotation = glm::vec3(0.0f, 0.0f, 0.0f);

				void SetRotation(glm::vec3 data) { m_Rotation = data; }
				void SetPitch(float pitch) { if (m_Pitch + pitch > 89.0f) m_Pitch = 89.0f; else if (m_Pitch + pitch < -89.0f) m_Pitch = -89.0f; else m_Pitch += pitch; }
			};

			struct Scale : public Component
			{
				glm::vec3 m_Scale = glm::vec3(1.0f, 1.0, 1.0f);

				void SetScale(glm::vec3 data) { m_Scale = data; }
			};

			struct Camera : public Component
			{
				//Config
				float m_FOV = 45.0f;
				float m_AspectRatio = 3.0f / 2.0f;
				float m_Near = 0.01f;
				float m_Far = 100.0f;

				float m_left = -1.0f;
				float m_right = 1.0f;
				float m_bottom = -1.0f;
				float m_top = 1.0f;

				float m_zoom = 1.0f;

				//Main Camera
				bool m_IsMainCamera = false;
				
				//Is orthopgrahic
				bool m_isOrthographic = false;

				//Movement
				float m_MoveSpeed = 10.0f;
				float m_ScrollSpeed = 50.0f;
				float m_Sensitivity = 1.0f;
				
				//Matrixes
				glm::mat4 m_perspective = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_Near, m_Far);
				glm::mat4 m_orthographic = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, m_Near, m_Far);

				glm::mat4 m_Projection = m_isOrthographic ? m_orthographic : m_perspective;
				
				glm::mat4 m_View = glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				
				//This should be in a system: Discussion to implemented or not because pattern says that component just contains data
				//Maybe move all this operations to entity manager

				bool isOrthographic() { return m_isOrthographic; }
				void SetProjectionOrthographic(bool& isOrtho) { this->m_isOrthographic = isOrtho; }
				void SetFov(float FOV) { if (m_FOV + FOV > 90.0F) m_FOV = 90.0f; else if (m_FOV + FOV < 1.0f) m_FOV = 1.0f; else m_FOV += FOV; }
				
				void UpdateProjection(float FOV, float aspectRatio, float near, float far) 
				{
					m_Projection = glm::perspective(glm::radians(FOV), aspectRatio, near, far);
				}

				void UpdateOrtho() {

					m_Projection = glm::ortho(m_left * m_zoom, m_right * m_zoom, m_bottom * m_zoom, m_top * m_zoom, -100.0f, m_Far);
				}

			};

			struct Texture : public Component
			{
				Renderer::Texture* m_Texture = nullptr;

				void LoadTexture(const char* filePath)
				{
					m_Texture = new Renderer::Texture(filePath);
				}

				void Bind(unsigned int slot)
				{
					m_Texture->Bind(slot);
				}

				void Unbind()
				{
					m_Texture->Unbind();
				}
			};

			struct PointLight : public Component
			{
				// Preset to white
				glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 255.0f);
			};

			struct Material : public Component
			{
				float ambientStrength = 0.1f;
				float specularStrength = 0.5f;

				Texture *texture = new Texture;
				
				void LoadTexture(const char* filepath)
				{
					if (filepath == nullptr)
					{
						texture->LoadTexture("Resources/Textures/Default/default01.png");
					}
					else
						texture->LoadTexture(filepath);
				}

			};
		}
		/*
		
		void OnStart()
		{
		fksofkseo
		}

		void OnUpdate()
		{
		fklskfs�
		}
		
		
		*/
	}
}


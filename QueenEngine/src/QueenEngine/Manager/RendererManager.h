#pragma once

#include "../Utils/Singleton.h"

#include "Manager.h"
#include "LogManager.h"

#include "../Renderer/Shader.h"

#include "../Renderer/VertexArray.h"
#include "../Renderer/VertexBuffer.h"
#include "../Renderer/IndexBuffer.h"
#include "../Renderer/FrameBuffer.h"

namespace Queen
{
	namespace Managers
	{
		class RendererManager : public Manager, public Utils::Singleton<RendererManager>
		{
			friend class Utils::Singleton<RendererManager>;
		public:

			void Start() override;
			void Shutdown() override;

			void SetUniformFloat(Renderer::Shader& shader, const char* name, float& value);

		private:

			RendererManager();
			~RendererManager();
		};
	}
}
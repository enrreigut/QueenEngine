#include "Window.h"

namespace Queen
{
	namespace Window
	{
		void Callback_Window_Resize(GLFWwindow* window, int width, int height);

		Window::Window()
		{
	
		}

		Window::~Window()
		{

		}

		bool Window::Init(const char* title, uint& width, uint& height)
		{
			m_Title = title;
			m_Width = width;
			m_Height = height;

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

			if (!m_Window)
				return m_Running;

			SetContext();

			//Callbacks
			glfwSetWindowUserPointer(m_Window, this);
			
			//RESIZE
			//glfwSetWindowSizeCallback(m_Window, Callback_Window_Resize);

			m_Running = true;
			return m_Running;
		}

		bool Window::Shutdown()
		{
			glfwDestroyWindow(m_Window);	
			return true;
		}

		void Window::SetContext()
		{
			glfwMakeContextCurrent(0);
			glfwMakeContextCurrent(m_Window);
		}

		void Window::Update()
		{
			glfwPollEvents();
		}

		void Window::Render(int vbo)
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			glClearColor(0.0f, 0.5f, 0.2f, 1.0f);
			
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glVertexAttribPointer(
				0,                  // atributo 0. No hay razón particular para el 0, pero debe corresponder en el shader.
				3,                  // tamaño
				GL_FLOAT,           // tipo
				GL_FALSE,           // normalizado?
				0,                    // Paso
				(void*)0            // desfase del buffer
			);
			// Dibujar el triángulo !
			glDrawArrays(GL_TRIANGLES, 0, 3); // Empezar desde el vértice 0S; 3 vértices en total -> 1 triángulo
			glDisableVertexAttribArray(0);
			
			glfwSwapBuffers(m_Window);
			
			std::this_thread::sleep_for(std::chrono::microseconds(5));
		}


		//Callacks
		void Callback_Window_Resize(GLFWwindow* window, int width, int height)
		{
			Window* w = (Window*)glfwGetWindowUserPointer(window);

			w->SetWidth((uint&)width);
			w->SetHeight((uint&)height);

			std::cout << w->GetWidth() << ", " << w->GetHeight() << std::endl;
		}
	}
}
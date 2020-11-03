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
			glfwSwapBuffers(m_Window);
			glfwPollEvents();

			std::this_thread::sleep_for(std::chrono::microseconds(5));
		}

		void Window::Render()
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
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
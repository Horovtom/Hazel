#pragma once

#include "Core.h"
#include "Window.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	/*
	 * This function has to be defined in the CLIENT.
	 * @return A class instance holding all of the application functionality
	 */
	Application* CreateApplication();

}


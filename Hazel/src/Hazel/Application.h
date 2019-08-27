#pragma once

#include "Core.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	/*
	 * This function has to be defined in the CLIENT.
	 * @return A class instance holding all of the application functionality
	 */
	Application* CreateApplication();

}


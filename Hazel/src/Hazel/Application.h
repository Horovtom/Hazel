#pragma once

#include "Core.h"
#include "Hazel/Events/ApplicationEvent.h"

#include "Window.h"

namespace Hazel {

class HAZEL_API Application {
public:
	Application();
	virtual ~Application();

	void Run();

	void OnEvent(Event& e);

private:
	bool OnWindowClosed(WindowCloseEvent& e);

	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
};

/*
 * This function has to be defined in the CLIENT.
 * @return A class instance holding all of the application functionality
 */
Application* CreateApplication();

}


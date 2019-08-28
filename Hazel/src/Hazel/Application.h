#pragma once

#include "Core.h"

#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"


namespace Hazel {

class HAZEL_API Application {
public:
	Application();
	virtual ~Application();

	void Run();

	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* layer);

private:
	bool OnWindowClosed(WindowCloseEvent& e);

	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
	LayerStack m_LayerStack;
};

/*
 * This function has to be defined in the CLIENT.
 * @return A class instance holding all of the application functionality
 */
Application* CreateApplication();

}


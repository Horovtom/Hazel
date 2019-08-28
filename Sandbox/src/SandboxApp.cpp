#include <Hazel.h>

// Example layer
class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer() : Layer("Example") {}

	void OnUpdate() override {
		HZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hazel::Event& event) override {
		HZ_TRACE("{0}", event);
	}
}

// This is a class that holds all of our application.
class Sandbox : public Hazel::Application {
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

// We need to define this function in order for the engine to recognize our Sandbox class as the
// one to run
Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox;
}
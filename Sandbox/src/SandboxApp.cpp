#include <Hazel.h>

// This is a class that holds all of our application.
class Sandbox : public Hazel::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

// We need to define this function in order for the engine to recognize our Sandbox class as the
// one to run
Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox;
}
#pragma once

#include "Hazel/Core.h"

#include <string>
#include <functional>

namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then and there
	// For the future, a better strategy might be to buffer events in an event 
	// bus and process them during the "event" part of the update stage.

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	/**
	 * This is an Event category for this event.
	 * Events can be grouped by their categories
	 * You can even group by multiple categories using bitwise or.
	 */
	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0), // This is BIT, so that we can OR them
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type; }\
								virtual EventType GetEventType() const override {return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


	class HAZEL_API Event {
		friend class EventDispatcher;

	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		/**
		 * @return Whether this event is in given category
		 */
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher {
		template<typename T>
		// EventFn is an alias for function pointer that returns bool and takes T reference as an argument
		using EventFn = std::function<bool(T&)>; 
	public:
		EventDispatcher(Event& event) : m_Event(event) {} // Create a dispatcher for some event

		/**
		 * This will only call the function if passed EventType matches with the Event contained in this dispatcher
		 * @return Whether the event has been dispatched to the function
		 * @example EventDispatcher dis(myMousePressedEvent); dis.Dispatch<MouseReleasedEvent>(a) || dis.Dispatch<MousePressedEvent>(b);
		 */
		template<typename T>
		bool Dispatch(EventFn<T> func) { // Then try to dispatch the event to some function with event type as T for filtering.
			if (m_Event.GetEventType() == T::GetStaticType()) {
				m_Event.m_Handled = func(*(T*)&m_Event); // Run the function with the event
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator <<(std::ostream& os, const Event& e) {
		return os << e.ToString();
	}
}
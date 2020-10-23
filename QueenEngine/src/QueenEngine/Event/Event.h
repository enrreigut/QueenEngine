#pragma once

#include <iostream>
#include <sstream>
#include <vector>

#define BIT(x) (1 << x)

namespace Queen
{
	namespace Event
	{

		enum class EventType
		{
			NONE = 0,
			WINDOW_RESIZE,
			MOUSE_PRESSED, MOSUE_RELEASED, MOUSE_MOVE
		};

		enum EventCategory
		{
			None =				0,
			EC_APPLICATION =	BIT(0),
			EC_INPUT =			BIT(1),
			EC_KEYBOARD =		BIT(2),
			EC_MOUSE =			BIT(3),
			EC_MOUSEBUTTON =	BIT(4)
		};

		#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::type;}\
								  virtual EventType GetEventType() const override {return GetStaticType();}\
								  virtual const char* GetName() const override {return #type;}
 

		#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

		class Event
		{
			friend class EventDispatcher;
		public:
		
			virtual ~Event() = default;
			
			bool Handled = false;

			virtual EventType GetEventType() const = 0;
			virtual const char* GetName() const = 0;
			virtual int GetCategoryFlags() const = 0;
			virtual std::string ToString() const { return GetName(); }

			bool IsInCategory(EventCategory category)
			{
				return GetCategoryFlags() & category;
			}
		};
		
		inline std::ostream& operator<<(std::ostream& os, const Event& e)
		{
			return os << e.ToString();
		}

		class EventDispatcher
		{
		public:

			EventDispatcher(Event& e)
				:m_Event(e)
			{

			}

			template<typename T, typename F>
			bool Dispatch(const F& func)
			{
				if (m_Event.GetEventType() == T::GetStaticType())
				{
					m_Event.Handled = func(static_cast<T&>(m_Event));
					return true;
				}

				return false;
			}

		private:

			Event& m_Event;

		};

	}
}


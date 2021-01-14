#pragma once

#include <memory>
#include <string>
#include <sstream>
#include <functional>

#define BIT(x) 1<<x

namespace Swan {
	
	// nice TheCherno's event system that i like :)
    // should i improve it ??? TODO
    // currently blocking events..

	enum class EventType
	{
		None = 0,
		WindowResize, WindowClose, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		InputCategory       = BIT(0),
		KeyboardCategory    = BIT(1),
		ApplicationCategory = BIT(2),
		MouseCategory       = BIT(3),
		MouseButtonCategory = BIT(4)
	};

#define EVENT_CLASS_TYPE(x) static EventType GetStaticType() { return EventType::x; }\
							virtual EventType GetEventType() const override { return GetStaticType();}\
							virtual const char* GetName() const override { return #x;}

#define EVENT_TYPE_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
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

	////////////// Window events ////////////////////////////////////////////////////////////////////////////////
	
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: s_Width(width), s_Height(height) 
		{
		}

		inline unsigned int GetWidth() const { return s_Width; }
		inline unsigned int GetHeight() const { return s_Height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << s_Width << ", " << s_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_TYPE_CATEGORY(ApplicationCategory)

	protected:
		unsigned int s_Width, s_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowCloseEvent";
			return ss.str();
		}
	
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_TYPE_CATEGORY(ApplicationCategory)
	};

	class WindowFocusEvent : public Event 
	{
	public:
		WindowFocusEvent()
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowFocusEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowFocus)
		EVENT_TYPE_CATEGORY(ApplicationCategory)
	};

	class WindowLostFocusEvent : public Event
	{
	public:
		WindowLostFocusEvent()
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowLostFocusEvent";
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowLostFocus)
		EVENT_TYPE_CATEGORY(ApplicationCategory)
	};

	class WindowMovedEvent : public Event
	{
	public:
		WindowMovedEvent(unsigned int xPos, unsigned int yPos)
			: s_XPos(xPos), s_YPos(yPos)
		{
		}

		inline unsigned int GetXPos() const { return s_XPos; }
		inline unsigned int GetYPos() const { return s_YPos; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowMovedEvent: " << s_XPos << ", " << s_YPos;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowMoved)
		EVENT_TYPE_CATEGORY(ApplicationCategory)
	private:
		unsigned int s_XPos, s_YPos;
	};


	////////////// Keyboard events ////////////////////////////////////////////////////////////////////////////////

	// general interface for keyboard events
	class KeyEvent : public Event
	{
	public:
		KeyEvent(int keycode)
			: s_KeyCode(keycode)
		{
		}

		inline int GetKeyCode() const { return s_KeyCode; }

		EVENT_TYPE_CATEGORY(InputCategory | KeyboardCategory)
	protected:
		int s_KeyCode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public: 
		KeyPressedEvent(int keycode, unsigned int repeatCount)
			:KeyEvent(keycode), s_RepeatCount(repeatCount)
		{
		}

		inline unsigned int GetRepeatCount() const { return s_RepeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << s_KeyCode << " [ Repeat count: " << s_RepeatCount << "]";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	protected:
		unsigned int s_RepeatCount;
	};

	class KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode)
			:KeyEvent(keycode)
		{
		}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << s_KeyCode ;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased);
	};

	////////////// Mouse events ////////////////////////////////////////////////////////////////////////////////

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(unsigned int xPos, unsigned int yPos)
			: s_XPos(xPos), s_YPos(yPos)
		{
		}

		inline unsigned int GetXPos() const { return s_XPos; }
		inline unsigned int GetYPos() const { return s_YPos; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << s_XPos << ", " << s_YPos;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_TYPE_CATEGORY(InputCategory | MouseCategory)
	protected:
		unsigned int s_XPos, s_YPos;
	};

	class MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(int keycode)
			: s_KeyCode(keycode)
		{
		}
		inline int GetKeyCode() const { return s_KeyCode; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << s_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
		EVENT_TYPE_CATEGORY(InputCategory | MouseCategory)
	protected:
		int s_KeyCode;
	};

	class MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(int keycode)
			: s_KeyCode(keycode)
		{
		}
		inline int GetKeyCode() const { return s_KeyCode; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << s_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
		EVENT_TYPE_CATEGORY(InputCategory | MouseCategory)
	protected:
		int s_KeyCode;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(int xOffset, int yOffset)
			: s_XOffset(xOffset), s_YOffset(yOffset)
		{
		}

		inline  int GetXOffset() const { return s_YOffset; }
		inline  int GetYOffset() const { return s_XOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << s_XOffset << ", " << s_YOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_TYPE_CATEGORY(InputCategory | MouseCategory)
	protected:
		int s_XOffset, s_YOffset;
	};


	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
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

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}
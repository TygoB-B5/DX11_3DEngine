#ifndef MOUSE_H
#define MOUSE_H

#include <utility>
#include <queue>

class Mouse
{
	friend class Window;

public:
	class Event
	{
	public:
		enum class Type
		{
			LPress, LRelease,
			RPress, RRelease,
			WheelUp, WheelDown,
			Move, Invalid
		};

	private:
		Type type;
		bool leftIsPressed = false;
		bool rightIsPressed = false;
		int x;
		int y;

	public:
		Event()
			:
			type(Type::Invalid),
			leftIsPressed(false),
			rightIsPressed(false),
			x(0),
			y(0) {}

		Event(Type type, const Mouse& parent)
			:
			type(type),
			leftIsPressed(parent.leftIsPressed),
			rightIsPressed(parent.rightIsPressed),
			x(parent.x),
			y(parent.y) {}

		int GetPosX() const noexcept
		{
			return x;
		}

		int GetPosY() const noexcept
		{
			return y;
		}

		bool IsValid() const noexcept
		{
			return type != Type::Invalid;
		}

		Type GetType() const noexcept
		{
			return type;
		}

		std::pair<int, int> GetPos()const noexcept
		{
			return { x, y };
		}

		bool LeftIsPressed() const noexcept
		{
			return leftIsPressed;
		}

		bool RightIsPressed() const noexcept
		{
			return rightIsPressed;
		}
	};

public:
	std::pair<int, int> GetPos() const noexcept;
	bool LeftIsPressed() const noexcept;
	bool RightIsPressed() const noexcept;
	Mouse::Event Read() noexcept;
	bool IsEmpty() const noexcept;
	void Flush() noexcept;

private:
	void OnMouseMove(int newX, int newY) noexcept;
	void OnLeftPressed(int x, int y) noexcept;
	void OnLeftReleased(int x, int y) noexcept;
	void OnRightPressed(int x, int y) noexcept;
	void OnRightRelease(int x, int y) noexcept;
	void OnWheelUp(int x, int y) noexcept;
	void OnWheelDown(int x, int y) noexcept;
	void TrimBuffer() noexcept;

private:
	static const unsigned int bufferSize = 16u;
	bool leftIsPressed = false;
	bool rightIsPressed = false;
	int x = 0;
	int y = 0;
	std::queue<Event> buffer;
};

#endif
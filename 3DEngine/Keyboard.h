#ifndef KEKYBOARD_H
#define KEYBOARD_H

#include <bitset>
#include <queue>

class Keyboard
{
	friend class Window;

public:
	class Event
	{
	public:
		enum class Type
		{
			Press, Release, Invalid
		};
	private:
		Type type;
		unsigned char code;
	public:
		Event()
			:
			type(Type::Invalid),
			code(0u) {}

		Event(Type type, unsigned char code)
			: type(type), code(code) {}

		bool IsPress() const noexcept
		{
			return type == Type::Press;
		}

		bool IsRelease() const noexcept
		{
			return type == Type::Release;
		}

		bool IsInvalid() const noexcept
		{
			return type == Type::Invalid;
		}

		unsigned char GetCode() const noexcept
		{
			return code;
		}
	};
public:
	bool KeyIsPressed(unsigned char keycode)const noexcept;
	Event ReadKey() noexcept;
	bool KeyIsEmpty()const noexcept;
	void FlushKey() noexcept;

	char ReadChar() noexcept;
	bool CharIsEmpty()const noexcept;
	void FlushChar() noexcept;
	void Flush() noexcept;

	void EnableautoRepeat() noexcept;
	void DisableAutoRepeat() noexcept;
	bool AutoRepeatIsEnabled()const noexcept;
private:
	void OnKeyPressed(unsigned char key) noexcept;
	void OnKeyReleased(unsigned char key) noexcept;
	void OnChar(char character) noexcept;
	void ClearState() noexcept;
	template<typename T>
	static void TrimBuffer(std::queue<T>& buffer);
private:
	static const unsigned int nKeys = 256u;
	static const unsigned int bufferSize = 16u;
	bool autoRepeatEnabled = false;
	std::bitset<nKeys> keyStates;
	std::queue<Event> keyBuffer;
	std::queue<char> charBuffer;
};

#endif

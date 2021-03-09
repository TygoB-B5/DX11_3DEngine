#include "Keyboard.h"

bool Keyboard::KeyIsPressed(unsigned char keycode)const noexcept
{
	return keyStates[keycode];
}

Keyboard::Event Keyboard::ReadKey() noexcept
{
	if (keyBuffer.size() > 0u)
	{
		Keyboard::Event e = keyBuffer.front();
		keyBuffer.pop();
		return e;
	}
	else
		return Keyboard::Event();
}

char Keyboard::ReadChar()noexcept
{
	if (charBuffer.size() > 0u)
	{
		char e = charBuffer.front();
		charBuffer.pop();
		return e;
	}
	else
		return 0;
}

bool Keyboard::KeyIsEmpty()const noexcept
{
	return keyBuffer.empty();
}

bool Keyboard::CharIsEmpty() const noexcept
{
	return charBuffer.empty();
}

void Keyboard::FlushKey() noexcept
{
	keyBuffer = std::queue<Event>();
}

void Keyboard::FlushChar() noexcept
{
	charBuffer = std::queue<char>();
}

void Keyboard::Flush() noexcept
{
	FlushChar();
	FlushKey();
}

void Keyboard::EnableautoRepeat() noexcept
{
	autoRepeatEnabled = true;
}

void Keyboard::DisableAutoRepeat() noexcept
{
	autoRepeatEnabled = false;
}

bool Keyboard::AutoRepeatIsEnabled()const noexcept
{
	return autoRepeatEnabled;
}

void Keyboard::OnKeyPressed(unsigned char key) noexcept
{
	keyStates[key] = true;
	keyBuffer.push(Keyboard::Event(Event::Type::Press, key));
	TrimBuffer(keyBuffer);
}

void Keyboard::OnKeyReleased(unsigned char key) noexcept
{
	keyStates[key] = false;
	keyBuffer.push(Keyboard::Event(Event::Type::Release, key));
	TrimBuffer(keyBuffer);
}

void Keyboard::OnChar(char character) noexcept
{
	charBuffer.push(character);
	TrimBuffer(charBuffer);
}

void Keyboard::ClearState() noexcept
{
	keyStates.reset();
}


template<typename T>
inline void Keyboard::TrimBuffer(std::queue<T>& buffer)
{

	while (bufferSize > bufferSize)
		buffer.pop();
}

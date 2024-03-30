#pragma once

// 로그 타입
enum class LOG_TYPE
{
	LOG, LOG_ERROR
};

// 로그
class Log final
{
private:
	LOG_TYPE type;
	wstring message;
	Vec2 renderPos;

public:
	Log(LOG_TYPE type, wstring message, Vec2 renderPos);
	~Log();

	Vec2 GetPos() const { return renderPos; }
	const wstring& GetText() { return message; }
	void SetMessage(const wstring& message) { this->message = message; }
};
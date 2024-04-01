#pragma once

// �α� Ÿ��
enum class LOG_TYPE
{
	LOG, LOG_ERROR
};

// �α�
class Log final
{
private:
	LOG_TYPE type;
	wstring message;
	Vec2 renderPos;

public:
	Log(LOG_TYPE type, wstring message, Vec2 renderPos=Vec2(0,0));
	~Log();

	Vec2 GetPos() const { return renderPos; }
	const wstring& GetText() { return message; }
	void SetMessage(const wstring& message) { this->message = message; }
};
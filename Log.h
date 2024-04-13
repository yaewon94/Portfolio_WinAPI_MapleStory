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
	Vec2<float> renderPos;

public:
	Log(LOG_TYPE type, wstring message, Vec2<float> renderPos=Vec2(0.f,0.f));
	~Log();

	Vec2<float> GetPos() const { return renderPos; }
	const wstring& GetText() { return message; }
	void SetMessage(const wstring& message) { this->message = message; }
};
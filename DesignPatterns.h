#pragma once

// ����, ���� ����
# define NO_COPY_CSTR(type) private:\
								type(const type&) = delete;\
								type(type&&) = delete;\
								type& operator=(const type&) = delete;\
								type& operator=(type&&) = delete;\

// [check] �Ҹ��� private���� �ϸ� ���α׷� ����ɶ� ���ҽ� ���� �ȵǳ�??
// �̱��� Ŭ����
#define SINGLETON(type) private:\
							type();\
							~type();\
							NO_COPY_CSTR(type);\
						public:\
							static type& GetInstance()\
							{\
								static type instance; \
								return instance; \
							}\
							//~type();
#pragma once

// ����, �̵� ����
# define NO_CSTR_COPY_ASSIGN(type) private:\
								type(const type&) = delete;\
								type(type&&) = delete;\
								type& operator=(const type&) = delete;\
								type& operator=(type&&) = delete;\

// [check] �Ҹ��� private���� �ϸ� ���α׷� ����ɶ� ���ҽ� ���� �ȵǳ�??
// �̱��� Ŭ����
#define SINGLETON(type) private:\
							type();\
							~type();\
							NO_CSTR_COPY_ASSIGN(type);\
						public:\
							static type& GetInstance()\
							{\
								static type instance; \
								return instance; \
							}\
							//~type();
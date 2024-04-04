#pragma once

// 복사, 이동 금지
# define NO_CSTR_COPY_ASSIGN(type) private:\
								type(const type&) = delete;\
								type(type&&) = delete;\
								type& operator=(const type&) = delete;\
								type& operator=(type&&) = delete;\

// [check] 소멸자 private으로 하면 프로그램 종료될때 리소스 해제 안되나??
// 싱글톤 클래스
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
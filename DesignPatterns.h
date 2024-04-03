#pragma once

// 복사, 이동 생성자, 할당연산자 추가
#define CSTR_COPY_ASSIGN(type) type(const type&);\
								type(type&&) noexcept;\
								type& operator=(const type&);\
								type& operator=(type&&) noexcept;\

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
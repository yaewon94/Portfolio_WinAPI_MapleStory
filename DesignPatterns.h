#pragma once

// �̱��� Ŭ����
#define SINGLETON(type) private:\
							type();\
							type(const type& other) = delete;\
						public:\
							static type* GetInstance()\
							{\
								static type instance;\
								return &instance;\
							}\
							~type();
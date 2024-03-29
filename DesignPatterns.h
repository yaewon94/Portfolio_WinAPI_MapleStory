#pragma once

// ΩÃ±€≈Ê ≈¨∑°Ω∫
#define SINGLETON(type) private:\
							type();\
							type(const type& other) = delete;\
							type& operator=(const type& other) = delete;\
						public:\
							static type& GetInstance()\
							{\
								static type* instance;\
								if(instance == nullptr) instance = new type;\
								return *instance;\
							}\
							~type();
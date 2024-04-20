#include "PCH.h"
#include "RandomManager.h"
#include "TimeManager.h"
#include <functional>
#include <random>
using namespace std;

// 랜덤값 생성
RandomResult RandomManager::Create(int mod)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	auto result = rand() % mod;

	//// 시드값 설정
	//random_device seeder;
	//const auto seed = seeder.entropy() ? seeder() : time(nullptr);
	//auto engine(static_cast<minstd_rand::result_type>(seed));

	//// 분포 지정
	//uniform_int_distribution<int> distribution(Min, Max+1);

	//// 랜덤값 생성, 저장
	//auto binder = bind(distribution, engine);
	//vector<int> vec(10);
	//generate(begin(vec), end(vec), binder);

	return result;
}
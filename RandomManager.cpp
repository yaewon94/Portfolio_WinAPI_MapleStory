#include "PCH.h"
#include "RandomManager.h"
#include "TimeManager.h"
#include <functional>
#include <random>
using namespace std;

// ������ ����
RandomResult RandomManager::Create(int mod)
{
	srand(static_cast<unsigned int>(time(nullptr)));
	auto result = rand() % mod;

	//// �õ尪 ����
	//random_device seeder;
	//const auto seed = seeder.entropy() ? seeder() : time(nullptr);
	//auto engine(static_cast<minstd_rand::result_type>(seed));

	//// ���� ����
	//uniform_int_distribution<int> distribution(Min, Max+1);

	//// ������ ����, ����
	//auto binder = bind(distribution, engine);
	//vector<int> vec(10);
	//generate(begin(vec), end(vec), binder);

	return result;
}
#pragma once

// �����Ҵ� �޸� ����
template <typename T>
void Delete(vector<T*>& vec)
{
	for (size_t i =0; i<vec.size(); ++i)
	{
		if (vec[i] != nullptr) delete vec[i];
	}

	vec.clear();
}
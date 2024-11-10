#pragma once
#include <functional>

/*
* @brief ���� ������, ���� ���� �����ڸ� �����մϴ�.
*/
#define FZ_DELETE_COPY(ClassName)                       \
    ClassName(const ClassName&) = delete;               \
    ClassName& operator=(const ClassName&) = delete;
/*
* @brief �̺�Ʈ �ݹ� ��� �Լ��� ����մϴ�.
*/
#define BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)

/*
* @brief ���� ����
*/
enum class Origins
{
	// T M B
	// L C R
	TL, TC, TR,
	ML, MC, MR,
	BL, BC, BR,
	Custom,
};
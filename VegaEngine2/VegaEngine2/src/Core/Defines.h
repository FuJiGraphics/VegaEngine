#include "pch.h"
#pragma once

// Macros

/*
* @brief ���� ������, ���� ���� �����ڸ� �����մϴ�.
*/
#define FZ_DELETE_COPY(ClassName)                       \
    ClassName(const ClassName&) = delete;               \
    ClassName& operator=(const ClassName&) = delete;


#include "pch.h"
#pragma once

// Macros

/*
* @brief 복사 생성자, 복사 대입 연산자를 삭제합니다.
*/
#define FZ_DELETE_COPY(ClassName)                       \
    ClassName(const ClassName&) = delete;               \
    ClassName& operator=(const ClassName&) = delete;


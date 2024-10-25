#include "pch.h"
#include "Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO 

namespace fz {
	namespace _internal {

		Log_internal& Log_internal::GetInstance()
		{
			static Log_internal instance;
			return instance;
		}

		Log_internal::Log_internal()
			: spdlog::logger(*spdlog::stdout_color_mt("VegaEngine"))
		{
			this->Init();
		}

		Log_internal::~Log_internal()
		{
			this->Release();
		}

		void Log_internal::Init()
		{
			this->set_pattern("%^[%T] %n: %v%$");
			this->set_level(spdlog::level::trace);
		}

		void Log_internal::Release()
		{
			// Empty
		}

	} // namespace _internal
} // namespace fz
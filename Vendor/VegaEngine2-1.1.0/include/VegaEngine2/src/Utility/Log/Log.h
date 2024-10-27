#pragma once

#include "Core/Core.h"
#include <spdlog/spdlog.h>
#include <format>

namespace fz {
	namespace _internal {

		class Log_internal final : protected spdlog::logger
		{
		protected:
			// Delete
			FZ_DELETE_COPY(Log_internal)

		public:
			static Log_internal& GetInstance();

            template<typename... Args>
			void Trace(fmt::format_string<Args...> fmt, Args &&...args);
            template<typename... Args>
            void Debug(fmt::format_string<Args...> fmt, Args &&...args);
			template<typename... Args>
            void Info(fmt::format_string<Args...> fmt, Args &&...args);
			template<typename... Args>
			void Warn(fmt::format_string<Args...> fmt, Args &&...args);
			template<typename... Args>
			void Error(fmt::format_string<Args...> fmt, Args &&...args);
			template<typename... Args>
			void Critical(fmt::format_string<Args...> fmt, Args &&...args);

		protected:
			Log_internal();
			virtual ~Log_internal();

			void Init();
			void Release();
		};

	} // namespace _internal

	// Á¢±Ù °´Ã¼
	static _internal::Log_internal& Log = _internal::Log_internal::GetInstance();

} // namespace fz

#include "Log.hpp"


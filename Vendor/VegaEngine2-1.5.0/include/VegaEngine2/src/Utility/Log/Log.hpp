#include "Log.h"

namespace fz {
	namespace _internal {

		template<typename ...Args>
		inline void Log_internal::Trace(fmt::format_string<Args...> fmt, Args && ...args)
		{
			spdlog::logger::trace(fmt, std::forward<Args>(args)...);
		}

		template<typename ...Args>
		inline void Log_internal::Debug(fmt::format_string<Args...> fmt, Args && ...args)
		{
			spdlog::logger::debug(fmt, std::forward<Args>(args)...);
		}

		template<typename ...Args>
		inline void Log_internal::Info(fmt::format_string<Args...> fmt, Args && ...args)
		{
			spdlog::logger::info(fmt, std::forward<Args>(args)...);
		}

		template<typename ...Args>
		inline void Log_internal::Warn(fmt::format_string<Args...> fmt, Args && ...args)
		{
			spdlog::logger::warn(fmt, std::forward<Args>(args)...);
		}

		template<typename ...Args>
		inline void Log_internal::Error(fmt::format_string<Args...> fmt, Args && ...args)
		{
			spdlog::logger::error(fmt, std::forward<Args>(args)...);
		}

		template<typename ...Args>
		inline void Log_internal::Critical(fmt::format_string<Args...> fmt, Args && ...args)
		{
			spdlog::logger::critical(fmt, std::forward<Args>(args)...);
		}

	} // namespace _internal
} // namespace fz
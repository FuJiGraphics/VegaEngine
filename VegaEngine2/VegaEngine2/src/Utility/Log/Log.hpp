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

		inline void Log_internal::Trace(const std::string& str)
		{
			spdlog::logger::trace(str);
		}

		inline void Log_internal::Debug(const std::string& str)
		{
			spdlog::logger::debug(str);
		}

		inline void Log_internal::Info(const std::string& str)
		{
			spdlog::logger::info(str);
		}

		inline void Log_internal::Warn(const std::string& str)
		{
			spdlog::logger::warn(str);
		}

		inline void Log_internal::Error(const std::string& str)
		{
			spdlog::logger::error(str);
		}

		inline void Log_internal::Critical(const std::string& str)
		{
			spdlog::logger::critical(str);
		}

	} // namespace _internal
} // namespace fz
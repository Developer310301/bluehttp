#ifndef BH_LOGGER_H
#define BH_LOGGER_H

#include <spdlog/spdlog.h>

#define BH_LOG_DEBUG spdlog::debug
#define BH_LOG_INFO spdlog::info
#define BH_LOG_ERROR spdlog::error
#define BH_LOG_WARN spdlog::warn
#define BH_LOG_CRITICAL spdlog::critical
#define BH_LOG_SET_LEVEL spdlog::set_level
#define BH_LOG_SET_PATTERN spdlog::set_pattern

#endif //BH_LOGGER_H
#include "log.hpp"

#include <cstdlib>

std::shared_ptr<spdlog::logger> loggerSetup(const std::string& name, spdlog::level::level_enum ll = spdlog::level::info)
{
    auto log = spdlog::stdout_color_mt(name);

    auto debug = std::getenv("MARS_DEBUG");

    if (!debug || ll != spdlog::level::info) {
        log->set_level(ll);
    } else {
        log->set_level(spdlog::level::debug);
    }
    return log;
}

std::shared_ptr<spdlog::logger> kDefaultLogger{ loggerSetup("mars") };
std::shared_ptr<spdlog::logger> uiLogger{ loggerSetup("mars-ui") };
std::shared_ptr<spdlog::logger> renderingLogger{ loggerSetup("mars-rendering") };
std::shared_ptr<spdlog::logger> videoLogger{ loggerSetup("mars-video") };
std::shared_ptr<spdlog::logger> ffmpegLibLogger{ loggerSetup("ffmpeg", spdlog::level::err) };
std::shared_ptr<spdlog::logger> htmlLogger{ loggerSetup("mars-html") };
std::shared_ptr<spdlog::logger> perfLogger{ loggerSetup("mars-perf") };

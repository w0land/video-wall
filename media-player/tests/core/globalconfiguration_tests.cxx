
#include <boost/filesystem.hpp>
#include <gtest/gtest.h>

#include "globalconfiguration.h"
#include "log.hpp"

TEST(GlobalConfigurationTests, fontPaths)
{
    mars::core::ConfigurationManager cfg;
    const std::string homeFontsPath
        = (boost::filesystem::path{ std::getenv("HOME") } / ".config" / "mars" / "fonts").string();
    std::vector<std::string> expectedFontPaths{ "/usr/share/fonts", "/opt/mars/fonts", homeFontsPath };
    EXPECT_EQ(cfg.fontsPaths(), expectedFontPaths);
}

TEST(GlobalConfigurationTests, uuid)
{
    mars::core::ConfigurationManager cfg;
    EXPECT_EQ(cfg.uuid(), "%UUID%");
}

TEST(GlobalConfigurationTests, adjustLoggers)
{
    mars::core::ConfigurationManager cfg;

    EXPECT_NO_THROW(cfg.adjustLoggers());

    EXPECT_EQ(kDefaultLogger->level(), spdlog::level::debug);
    EXPECT_EQ(perfLogger->level(), spdlog::level::info);
    EXPECT_EQ(ffmpegLibLogger->level(), spdlog::level::warn);
}

#include <iostream>
#include <sstream>
#include <stdio.h>

#include <SDL.h>
#include <unistd.h>

#include <cef_app.h>
#include <cef_client.h>
#include <cef_life_span_handler.h>
#include <cef_load_handler.h>
#include <cef_render_handler.h>
#include <wrapper/cef_helpers.h>

#include "fps.hpp"
#include "log.hpp"
#include "sdlrenderer.h"
#include "stopwatch.hpp"

#include "html/cefbrowserclient.h"
#include "html/cefrenderhandler.h"
#include "html/htmlwidget.h"

int main(int argc, char* argv[])
{
    mars_debug("Star rendering html content pid = {}", getpid());

    CefMainArgs args(argc, argv);

    {
        int result = CefExecuteProcess(args, nullptr, nullptr);
        if (result >= 0) {
            // child proccess has endend, so exit.
            return result;
        } else if (result == -1) {
            // we are here in the father proccess.
        }
    }

    {
        CefSettings settings;
        settings.no_sandbox = 1;
        // settings.log_severity = LOGSEVERITY_VERBOSE;

        {
            std::ostringstream ss;
            ss << SDL_GetBasePath() << "locales/";
            CefString(&settings.locales_dir_path) = ss.str();
        }

        // CefString(&settings.locales_dir_path).FromASCII("");
        CefString(&settings.resources_dir_path) = SDL_GetBasePath();

        bool result = CefInitialize(args, settings, nullptr, nullptr);
        if (!result) {
            // handle error
            return -1;
        }
    }

    mars::windowing::SDLRenderer::initialize();

    std::uint16_t width = 800;
    std::uint16_t height = 600;

    auto window = mars::windowing::SDLRenderer::createFullScreenWindow();
    mars_debug("SDL window = {}", static_cast<void*>(window.get()));
    if (window) {
        mars::windowing::SDLRenderer renderer{ window.get() };
        if (true) {
            // SDL_Event e;

            using mars::widgets::HTMLWidget;

            const std::string url{ std::string{ "file:///" } + std::string(HTML_DIR)
                + "/webgl-hello-world-master/webgl-demo.htm" };
            auto html = std::make_shared<HTMLWidget>(url, renderer, width, height);
            html->move(100, 100);
            renderer.addWidget(html);
            renderer.loop({ { []() { CefDoMessageLoopWork(); } } });
        }
    }

    CefShutdown();
    SDL_Quit();

    return 0;
}

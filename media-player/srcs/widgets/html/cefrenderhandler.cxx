#include "cefrenderhandler.h"

#include "irenderer.h"
#include "itexture.h"
#include "stopwatch.hpp"

#include "log.hpp"

namespace mars {
namespace webengine {

RenderHandler::RenderHandler(windowing::IRenderer* renderer, int w, int h)
    : _renderingTexture(renderer->createTexture(w, h, windowing::PixelFormat::Unknown))
{
}

RenderHandler::~RenderHandler() {}

bool RenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    rect = CefRect(0, 0, _renderingTexture->size().first, _renderingTexture->size().second);
    return true;
}

void RenderHandler::OnPaint(
    CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int w, int h)
{
    mars_trace_(ui, "OnPaint({}, {}, {}, {}, {}, {}", static_cast<void*>(browser), type, dirtyRects.size(),
        static_cast<const void*>(buffer), w, h);
    _renderingTexture->put(buffer, std::make_pair(w, h));
    // schedule refresh
}

void RenderHandler::render(std::uint32_t x, std::uint32_t y) { _renderingTexture->render(x, y); }
} // namespace webengine
} // namespace mars

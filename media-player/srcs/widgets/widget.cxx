#include "widget.h"
#include "log.hpp"
#include "renderer_types.hpp"

namespace mars {
namespace widgets {

bool Widget::event(const windowing::EventVariant& event) noexcept { return false; }

void Widget::requestRefresh() { mars_debug_(ui, "Scheduling refresh for widget {}", static_cast<void*>(this)); }
} // namespace widgets
} // namespace mars
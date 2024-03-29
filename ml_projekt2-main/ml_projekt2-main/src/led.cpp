#include "led.hpp"

namespace yrgo 
{
namespace rpi 
{

// -----------------------------------------------------------------------------
Led::Led() = default;

// -----------------------------------------------------------------------------
Led::Led(const std::uint8_t pin, const bool enabled) { init(pin, enabled); }

// -----------------------------------------------------------------------------
Led::~Led() { gpiod_line_release(myLine); }

// -----------------------------------------------------------------------------
std::uint8_t Led::pin() const { return gpiod_line_offset(myLine); }

// -----------------------------------------------------------------------------
bool Led::isEnabled() const { return gpiod_line_get_value(myLine) > 0; }


// -----------------------------------------------------------------------------
bool Led::init(const std::uint8_t pin, const bool enabled)
{
    if (myLine != nullptr) { return false; }
    myLine = gpiod_line_new(pin, GPIOD_LINE_DIRECTION_OUT);
    if (myLine != nullptr && enabled) { on(); }
    return myLine != nullptr;
}

// -----------------------------------------------------------------------------
void Led::on() { gpiod_line_set_value(myLine, 1); }

// -----------------------------------------------------------------------------
void Led::off() { gpiod_line_set_value(myLine, 0); }

// -----------------------------------------------------------------------------
void Led::toggle() { gpiod_line_set_value(myLine, !isEnabled()); }

// -----------------------------------------------------------------------------
void Led::blink(const std::uint16_t blinkSpeedMs)
{
    toggle();
    delay_ms(blinkSpeedMs);
}

} // namespace rpi
} // namespace yrgo
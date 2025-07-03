#pragma once

#include <Mosaic/Mosaic.hpp>

enum class ConsoleLogSeverity
{
    NOTICE,
    SUCCESS,
    WARNING,
    ERROR,
};

using ConsoleNotice = Mosaic::ConsoleSeverityLevel<ConsoleLogSeverity::NOTICE, Mosaic::ConsoleTextColour::Blue, Mosaic::ConsoleTextStyle::Bold>;
using ConsoleSuccess = Mosaic::ConsoleSeverityLevel<ConsoleLogSeverity::SUCCESS, Mosaic::ConsoleTextColour::Green, Mosaic::ConsoleTextStyle::Bold>;
using ConsoleWarning = Mosaic::ConsoleSeverityLevel<ConsoleLogSeverity::WARNING, Mosaic::ConsoleTextColour::Yellow, Mosaic::ConsoleTextStyle::Bold>;
using ConsoleError = Mosaic::ConsoleSeverityLevel<ConsoleLogSeverity::ERROR, Mosaic::ConsoleTextColour::Red, Mosaic::ConsoleTextStyle::Bold>;
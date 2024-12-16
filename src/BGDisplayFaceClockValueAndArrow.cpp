#include "BGDisplayFaceClockValueAndArrow.h"
#include "BGDisplayManager.h"
#include "ServerManager.h"
#include "globals.h"

void BGDisplayFaceClockValueAndArrow::showReadings(const std::list<GlucoseReading> &readings, bool dataIsOld) const {

    DisplayManager.clearMatrix();

    showClock();

    showReading(readings.back(), 0, 7, TEXT_ALIGNMENT::CENTER, FONT_TYPE::MEDIUM, dataIsOld);

    showTrendArrow(readings.back(), 32 - 5, 1);
}

void BGDisplayFaceClockValueAndArrow::showClock() const {
    // Show current time

    tm timeinfo = ServerManager.getTimezonedTime();

    char timeStr[6];

    auto time_format = SettingsManager.settings.time_format;
    if (time_format == TIME_FORMAT::HOURS_12) {
        bool is_pm = timeinfo.tm_hour >= 12;
        if (timeinfo.tm_hour == 0) {
            timeinfo.tm_hour = 12;
        } else if (timeinfo.tm_hour > 12) {
            timeinfo.tm_hour -= 12;
        }

        for (int i = 0; i < 17; i++) {
            DisplayManager.drawPixel(i, 7, is_pm ? COLOR_BLUE : COLOR_CYAN);
        }
    }

    sprintf(timeStr, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);

    DisplayManager.setTextColor(COLOR_WHITE);
    DisplayManager.printText(0, 6, timeStr, TEXT_ALIGNMENT::LEFT, 2);
}

#pragma region Show arrow

// Glucose trends
const uint8_t symbol_doubleUp[] PROGMEM = {
    0x50, 0xF8, 0x50, 0x50, 0x50,
};
const uint8_t symbol_singleUp[] PROGMEM = {
    0x20, 0x70, 0xA8, 0x20, 0x20,
};
const uint8_t symbol_fortyFiveUp[] PROGMEM = {
    0x38, 0x18, 0x28, 0x40, 0x80,
};
const uint8_t symbol_flat[] PROGMEM = {
    0x20, 0x10, 0xF8, 0x10, 0x20,
};
const uint8_t symbol_fortyFiveDown[] PROGMEM = {
    0x80, 0x40, 0x28, 0x18, 0x38,
};
const uint8_t symbol_singleDown[] PROGMEM = {
    0x20, 0x20, 0xA8, 0x70, 0x20,
};
const uint8_t symbol_doubleDown[] PROGMEM = {
    0x50, 0x50, 0x50, 0xF8, 0x50,
};

const uint8_t symbol_empty[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00,
};

const std::map<BG_TREND, const uint8_t *> glucoseTrendSymbols = {
    {BG_TREND::NONE, symbol_empty},
    {BG_TREND::DOUBLE_UP, symbol_doubleUp},
    {BG_TREND::SINGLE_UP, symbol_singleUp},
    {BG_TREND::FORTY_FIVE_UP, symbol_fortyFiveUp},
    {BG_TREND::FLAT, symbol_flat},
    {BG_TREND::FORTY_FIVE_DOWN, symbol_fortyFiveDown},
    {BG_TREND::SINGLE_DOWN, symbol_singleDown},
    {BG_TREND::DOUBLE_DOWN, symbol_doubleDown},
    {BG_TREND::NOT_COMPUTABLE, symbol_empty},
    {BG_TREND::RATE_OUT_OF_RANGE, symbol_doubleUp},
};

void BGDisplayFaceClockValueAndArrow::showTrendArrow(const GlucoseReading reading, int16_t x, int16_t y) const {

    DisplayManager.drawBitmap(x, y, glucoseTrendSymbols.at(reading.trend), 5, 5, COLOR_WHITE);
}

#pragma endregion Show arrow

void BGDisplayFaceClockValueAndArrow::showNoData() const {
    DisplayManager.clearMatrix();
    showClock();

    String noData = "---";
    if (SettingsManager.settings.bg_units == BG_UNIT::MMOLL) {
        noData = "--.-";
    }

    DisplayManager.setTextColor(BG_COLOR_OLD);
    DisplayManager.printText(33, 6, noData.c_str(), TEXT_ALIGNMENT::RIGHT, 2);
}
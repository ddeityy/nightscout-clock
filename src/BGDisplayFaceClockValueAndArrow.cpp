#include "BGDisplayFaceClockValueAndArrow.h"
#include "BGDisplayManager.h"
#include "ServerManager.h"
#include "globals.h"

void BGDisplayFaceClockValueAndArrow::showReadings(const std::list<GlucoseReading> &readings, bool dataIsOld) const {

    DisplayManager.clearMatrix();

    showClock();

    showReading(readings.back(), 0, 7, TEXT_ALIGNMENT::RIGHT, FONT_TYPE::MEDIUM, dataIsOld);

    showTrendVerticalLine(31, readings.back().trend);
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

void BGDisplayFaceClockValueAndArrow::showTrendVerticalLine(int x, BG_TREND trend) const {
    switch (trend) {
        case BG_TREND::DOUBLE_UP:
            DisplayManager.drawPixel(x, 0, COLOR_RED);
            DisplayManager.drawPixel(x, 1, COLOR_YELLOW);
            DisplayManager.drawPixel(x, 2, COLOR_GREEN);
            DisplayManager.drawPixel(x, 3, COLOR_WHITE);
            break;
        case BG_TREND::DOUBLE_DOWN:
            DisplayManager.drawPixel(x, 4, COLOR_WHITE);
            DisplayManager.drawPixel(x, 5, COLOR_GREEN);
            DisplayManager.drawPixel(x, 6, COLOR_YELLOW);
            DisplayManager.drawPixel(x, 7, COLOR_RED);
            break;
        case BG_TREND::SINGLE_UP:
            DisplayManager.drawPixel(x, 1, COLOR_YELLOW);
            DisplayManager.drawPixel(x, 2, COLOR_GREEN);
            DisplayManager.drawPixel(x, 3, COLOR_WHITE);
            break;
        case BG_TREND::SINGLE_DOWN:
            DisplayManager.drawPixel(x, 4, COLOR_WHITE);
            DisplayManager.drawPixel(x, 5, COLOR_GREEN);
            DisplayManager.drawPixel(x, 6, COLOR_YELLOW);
            break;
        case BG_TREND::FORTY_FIVE_UP:
            DisplayManager.drawPixel(x, 2, COLOR_GREEN);
            DisplayManager.drawPixel(x, 3, COLOR_WHITE);
            break;
        case BG_TREND::FORTY_FIVE_DOWN:
            DisplayManager.drawPixel(x, 4, COLOR_WHITE);
            DisplayManager.drawPixel(x, 5, COLOR_GREEN);
            break;
        case BG_TREND::FLAT:
            DisplayManager.drawPixel(x, 3, COLOR_WHITE);
            DisplayManager.drawPixel(x, 4, COLOR_WHITE);
            break;
        default:
            DisplayManager.setTextColor(COLOR_BLACK);
            break;
    }
    DisplayManager.update();
}

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
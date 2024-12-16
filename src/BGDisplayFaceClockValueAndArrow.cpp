#include "BGDisplayFaceClockValueAndArrow.h"
#include "BGDisplayManager.h"
#include "globals.h"

void BGDisplayFaceClockValueAndArrow::showReadings(const std::list<GlucoseReading> &readings, bool dataIsOld) const {

    DisplayManager.clearMatrix();

    showClock();

    showReading(readings.back(), 0, 7, TEXT_ALIGNMENT::CENTER, FONT_TYPE::MEDIUM, dataIsOld);

    // show arrow in the right part of the screen
    showTrendArrow(readings.back(), 32 - 5, 1);
}

#ifndef BGDISPLAYFACECLOCKVALUEARROW_H
#define BGDISPLAYFACECLOCKVALUEARROW_H

#include "BGDisplayFaceTextBase.h"
#include "BGSource.h"

class BGDisplayFaceClockValueAndArrow : public BGDisplayFaceTextBase {
  public:
    void showReadings(const std::list<GlucoseReading> &readings, bool dataIsOld = false) const override;
    void showNoData() const override;

  private:
    void showClock() const;
    void showTrendArrow(const GlucoseReading reading, int16_t x, int16_t y) const;
};

#endif

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
    void showTrendVerticalLine(int x, BG_TREND trend) const;
};

#endif

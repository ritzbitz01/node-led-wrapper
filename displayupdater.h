#ifndef DISPLAYUPDATER_H
#define DISPLAYUPDATER_H
#include "rgbmatrixmanipulator.h"

class DisplayUpdater : public RGBMatrixManipulator {
public:
  DisplayUpdater(RGBMatrix* m) : RGBMatrixManipulator(m) {}

  void Run() {
    while (running_) {
      matrix_->UpdateScreen();
    }
  }
};
#endif
#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <wx/wx.h>

class Battleship : public wxApp {
public:
  auto OnInit() -> bool override;
};

#endif // BATTLESHIP_H
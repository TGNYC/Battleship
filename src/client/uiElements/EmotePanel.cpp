#include "EmotePanel.h"
#include "Logger.h"

#include <iostream>
#include "../GameController.h"

EmotePanel::EmotePanel(wxWindow *parent, wxPoint pos) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(100, 600)) {
  _parent = parent;
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);
  wxBitmap emoteBitmaps[4] = {wxBitmap(wxImage(EmoteHandler::getImage(EmoteType::MiddleFinger))),
                              wxBitmap(wxImage(EmoteHandler::getImage(EmoteType::RussianWarshipGoFuckYourself))),
                              wxBitmap(wxImage(EmoteHandler::getImage(EmoteType::Mocking))),
                              wxBitmap(wxImage(EmoteHandler::getImage(EmoteType::BestPirate)))};
  for (int i = 0; i < 4; ++i) {
    _emoteBitmaps[i] = new wxStaticBitmap(this, wxID_ANY, emoteBitmaps[i], wxPoint(20, 90 + 90 * i), wxSize(80, 80), 0);
    _emoteBitmaps[i]->Bind(wxEVT_LEFT_DOWN, [this, i](wxMouseEvent &event) {
      LOG("clicked on emote " + std::to_string(i));
      auto now = std::chrono::system_clock::now();
      if (now - _lastClick < std::chrono::seconds(5)) {
        LOG("too fast");
        return;
      }
      _lastClick = now;
      GameController::sendEmote(EmoteType(i));
    });
  }
  // displayEmote(EmoteType::MiddleFinger);
}

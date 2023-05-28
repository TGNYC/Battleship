#include "EmotePanel.h"
#include "../GameController.h"
#include "Logger.h"

EmotePanel::EmotePanel(wxWindow *parent, wxPoint) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(100, 600)) {
  wxColor backgroundColor = wxColor(255, 255, 255);
  this->SetBackgroundColour(backgroundColor);

  for (int i = 0; i < 6; ++i) {
    _emoteBitmaps[i] = new wxStaticBitmap(this, wxID_ANY, wxBitmap(EmoteHandler::getImage(EmoteType(i))),
                                          wxPoint(20, 50 + 90 * i), wxSize(80, 80), 0);
    _emoteBitmaps[i]->Bind(wxEVT_LEFT_DOWN, [this, i](wxMouseEvent &) {
      LOG("clicked on emote " + std::to_string(i));
      auto now = std::chrono::system_clock::now();
      if (now - _lastClick < std::chrono::seconds(5)) { // prevent spamming
        LOG("too fast");
        return;
      }
      _lastClick = now;
      GameController::sendEmote(EmoteType(i));
    });
  }
}

#include "EmotePopup.h"
#include "Logger.h"

EmotePopup::EmotePopup(wxWindow *parent, wxPoint pos, EmoteType emote) : wxPopupWindow(parent) {
    this->SetSize(400, 400);
    wxColor backgroundColor = wxColor(255, 0, 255);
    this->SetBackgroundColour(backgroundColor);

    wxImage image(EmoteHandler::getImageLarge(emote));

    _currentEmote = new wxStaticBitmap(this, wxID_ANY, wxBitmap(image), wxPoint(0, 0), wxSize(400, 400), 0);
    _currentEmote->Bind(wxEVT_LEFT_DOWN, [this](wxMouseEvent &event) {
        LOG("Hide current emote");
        // one of these ought to do the trick
        this->_currentEmote->Hide();
        this->Hide();
        this->Destroy();
    });
}
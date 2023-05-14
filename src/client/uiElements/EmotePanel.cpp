#include "EmotePanel.h"

EmotePanel::EmotePanel(wxWindow *parent, wxPoint pos) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(100, 600)) {
    _parent = parent;
    // wxColor backgroundColor = wxColor(255, 0, 255);
    // this->SetBackgroundColour(backgroundColor);
    // display emotes that can be sent at the bottom of the box
    wxBitmap emoteBitmaps[3] = {
        wxBitmap(wxImage(filepath.at(EmoteType::MiddleFinger))),
        wxBitmap(wxImage(filepath.at(EmoteType::RussianWarshipGoFuckYourself))),
        wxBitmap(wxImage(filepath.at(EmoteType::Mocking)))
    };
    for (int i=0; i<3; ++i) {
        _emoteBitmaps[i] = new wxStaticBitmap(_parent, wxID_ANY, emoteBitmaps[i], wxPoint(20, 90 + 90*i), wxSize(80, 80), 0);
    }
}

void EmotePanel::displayEmote(EmoteType emote) {
    _currentEmote = new wxStaticBitmap(_parent, wxID_ANY, wxBitmap(wxImage(filepath.at(emote))), wxPoint(200, 200), wxSize(80, 80));
}
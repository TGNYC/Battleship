#ifndef EMOTEPANEL_H
#define EMOTEPANEL_H

#include <wx/wx.h>
#include <map>
#include "../../common/network/responses/EmoteEvent.h"

class EmotePanel : public wxPanel {
public:
    EmotePanel(wxWindow *parent, wxPoint pos);

    void displayEmote(EmoteType emote);

    wxStaticBitmap* getCurrentEmote() const {
        return _currentEmote;
    }
    
private:
    wxWindow* _parent;
    wxStaticBitmap* _emoteBitmaps[3];
    wxStaticBitmap* _currentEmote;
    const std::map<EmoteType, std::string> filepath = {
        {EmoteType::MiddleFinger,                   "../assets/emotes/middlefinger.png"},
        {EmoteType::RussianWarshipGoFuckYourself,   "../assets/emotes/gofuckyourself.png"},
        {EmoteType::Mocking,                        "../assets/emotes/mocking.png"}
    };
};

#endif // EMOTEPANEL_H
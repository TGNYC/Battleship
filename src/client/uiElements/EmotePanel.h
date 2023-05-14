#ifndef EMOTEPANEL_H
#define EMOTEPANEL_H

#include <wx/wx.h>
#include "../EmoteHandler.h"
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
};

#endif // EMOTEPANEL_H
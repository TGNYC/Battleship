#ifndef EMOTEPANEL_H
#define EMOTEPANEL_H

#include <wx/wx.h>
#include <chrono>
#include "../EmoteHandler.h"
#include "../../common/network/responses/EmoteEvent.h"

class EmotePanel : public wxPanel {
public:
    EmotePanel(wxWindow *parent, wxPoint pos);
private:
    wxWindow* _parent;
    wxStaticBitmap* _emoteBitmaps[3];
    std::chrono::system_clock::time_point _lastClick;
};

#endif // EMOTEPANEL_H
#ifndef EMOTEPANEL_H
#define EMOTEPANEL_H

#include <wx/wx.h>
#include <chrono>
#include "../EmoteHandler.h"
#include "../GameController.h"
#include "../../common/network/responses/EmoteEvent.h"

/*!
 * Panel to display the available emotes the user can use to communicate with the opponent
 */
class EmotePanel : public wxPanel {
public:
    EmotePanel(wxWindow *parent, wxPoint pos);
private:
    wxStaticBitmap* _emoteBitmaps[6]; ///< contains the visuals for the 6 emotes
    std::chrono::system_clock::time_point _lastClick; ///< timestamp used to prevent emote-spamming
};

#endif // EMOTEPANEL_H
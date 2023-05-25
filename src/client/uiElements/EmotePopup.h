#ifndef EMOTEPOPUP_H
#define EMOTEPOPUP_H

#include <wx/wx.h>
#include <wx/popupwin.h>
#include "../EmoteHandler.h"
#include "Logger.h"

/*!
 * Popup window to display emotes on screen.
 * They disappear when clicking on the image.
 */
class EmotePopup : public wxPopupWindow {
public:
    EmotePopup(wxWindow *parent, wxPoint pos, EmoteType emote);
private:
    wxStaticBitmap* _currentEmote = nullptr;
};

#endif // EMOTEPOPUP_H
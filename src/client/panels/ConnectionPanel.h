#ifndef CONNECTIONPANEL_H
#define CONNECTIONPANEL_H

#include <wx/wx.h>
#include "../uiElements/InputField.h"

// form Lama template

class ConnectionPanel : public wxPanel {
public:
  ConnectionPanel(wxWindow *parent);

  wxString getServerAddress();
  wxString getServerPort();
  wxString getUserName();

private:
  InputField *_serverAddressField;
  InputField *_serverPortField;
  InputField *_userNameField;

};

#endif // CONNECTIONPANEL_H
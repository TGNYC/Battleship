#ifndef CONNECTIONPANEL_H
#define CONNECTIONPANEL_H

#include "../uiElements/InputField.h"
#include <wx/wx.h>

// from Lama template

class ConnectionPanel : public wxPanel {
public:
  ConnectionPanel(wxWindow *parent);
  void onConnectButtonClicked(wxCommandEvent &event);

  wxString getServerAddress();
  wxString getServerPort();
  wxString getUserName();

private:
  InputField *_serverAddressField;
  InputField *_serverPortField;
  InputField *_userNameField;
};

#endif // CONNECTIONPANEL_H
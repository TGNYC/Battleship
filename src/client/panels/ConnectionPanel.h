#ifndef CONNECTIONPANEL_H
#define CONNECTIONPANEL_H

#include <wx/wx.h>
#include "../uiElements/InputField.h"

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
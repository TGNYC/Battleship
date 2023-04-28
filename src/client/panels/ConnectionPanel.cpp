#include "ConnectionPanel.h"
#include "../uiElements/ImagePanel.h"

ConnectionPanel::ConnectionPanel(wxWindow *parent) : wxPanel(parent, wxID_ANY) {
  wxColor white = wxColor(255, 255, 255);
  this->SetBackgroundColour(white);

  wxBoxSizer *verticalLayout = new wxBoxSizer(wxVERTICAL);

  ImagePanel *logo =
    new ImagePanel(this, "../assets/battleship_logo.png", wxBITMAP_TYPE_PNG, wxDefaultPosition, wxSize(300, 300), 0.0);
  verticalLayout->Add(logo, 0, wxALIGN_CENTER | wxTOP, 10);

  const int labelWidth = 100;
  const int fieldWidth = 240;
  // to be implemented in common/network/default.conf
  const int      defaultPort     = 8080;
  const wxString defaultAddress  = "localhost";
  const wxString defaultUsername = "";

  this->_serverAddressField = new InputField(this, "Server address:", labelWidth, defaultAddress, fieldWidth);
  verticalLayout->Add(this->_serverAddressField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

  this->_serverPortField = new InputField(this, "Server port:", labelWidth, std::to_string(defaultPort), fieldWidth);
  verticalLayout->Add(this->_serverPortField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

  this->_userNameField = new InputField(this, "Username:", labelWidth, defaultUsername, fieldWidth);
  verticalLayout->Add(this->_userNameField, 0, wxTOP | wxLEFT | wxRIGHT, 10);

  wxButton *connectButton = new wxButton(this, wxID_ANY, "Connect", wxDefaultPosition, wxSize(100, 40));
  connectButton->Bind(wxEVT_BUTTON, &ConnectionPanel::onConnectButtonClicked, this);
  verticalLayout->Add(connectButton, 0, wxALIGN_RIGHT | wxALL, 10);

  this->SetSizerAndFit(verticalLayout);
}

void ConnectionPanel::onConnectButtonClicked(wxCommandEvent &event) {

}

wxString ConnectionPanel::getServerAddress() {
  return this->_serverAddressField->getValue();
}

wxString ConnectionPanel::getServerPort() {
  return this->_serverPortField->getValue();
}

wxString ConnectionPanel::getUserName() {
  return this->_userNameField->getValue();
}
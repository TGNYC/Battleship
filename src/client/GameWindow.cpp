#include "GameWindow.h"

#include <wx/wx.h>
#include "../common/Logger.h"
#include "GameController.h"

GameWindow::GameWindow(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, wxID_ANY, title, pos, size) {

  this->_mainLayout       = new wxBoxSizer(wxVERTICAL);
  wxBoxSizer *outerLayout = new wxBoxSizer(wxHORIZONTAL);
  outerLayout->Add(this->_mainLayout, 1, wxCENTER);
  this->SetSizerAndFit(outerLayout);
  this->_currentPanel = nullptr;

  // setup status bar
  this->_statusBar = this->CreateStatusBar(1);

  // set background
  wxColor lightBlue = wxColor(213, 231, 239);
  this->SetBackgroundColour(lightBlue);

  // set minimum size of window
  this->SetMinSize(wxSize(1000, 720));

  // close window event
  Bind(wxEVT_CLOSE_WINDOW, &GameWindow::onClose, this);

}

void GameWindow::showPanel(wxPanel *panel) {
  if(this->_currentPanel == panel) {
    return;
  }

  // remove previous panel
  if (this->_currentPanel != nullptr) {
    this->_mainLayout->Detach(this->_currentPanel);
    this->_currentPanel->Show(false);
    this->_currentPanel = nullptr;
  }

  // add new panel
  this->_mainLayout->Add(panel, 0, wxALIGN_CENTER | wxALL, 20);
  panel->Show(true);
  this->_currentPanel = panel;

  this->_mainLayout->Layout();

  this->Fit();
  // update window
  this->Layout();
}

void GameWindow::setStatus(const std::string &message) {
  this->_statusBar->SetStatusText(message, 0);
}

void GameWindow::onClose(wxCloseEvent &event) {
  LOG("Closing window");
  GameController::quitGame();
  Destroy();
}
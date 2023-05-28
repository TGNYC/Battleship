//
// Created by robin on 23.04.23.
//

#ifndef BATTLESHIP_INPUTFIELD_H
#define BATTLESHIP_INPUTFIELD_H

#include <wx/wx.h>

// from Lama template

class InputField : public wxPanel {
public:
  InputField(wxWindow *parent, const wxString &labelText, int labelWidth, const wxString &fieldValue, int fieldWidth);
  wxString getValue();

private:
  wxStaticText *_label;
  wxTextCtrl   *_field;
};

#endif // BATTLESHIP_INPUTFIELD_H

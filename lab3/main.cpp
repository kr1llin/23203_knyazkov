#include <wx/wx.h>

/*

*/


//base class for wxWidgets applications
class MyApp : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame(const wxString& title);

private:
    void OnPaint(wxPaintEvent& event);
    void OnTimer(wxTimerEvent& event);

    wxTimer timer;
    wxDECLARE_EVENT_TABLE();
};

//event table
wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_PAINT(MyFrame::OnPaint)
    EVT_TIMER(wxID_ANY, MyFrame::OnTimer)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(MyApp);

//init application on start
bool MyApp::OnInit() {
    MyFrame* frame = new MyFrame("Space Invaders");
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)),
      timer(this) {
    timer.Start(1000 / 60); //for 60 fps
}

//draw sprites and etc.
void MyFrame::OnPaint(wxPaintEvent& event) {
    wxPaintDC dc(this);
    SetBackgroundColour({0,0,0});
}

void MyFrame::OnTimer(wxTimerEvent& event) {
    // Game update logic will go here
    Refresh(); // Trigger a repaint
}

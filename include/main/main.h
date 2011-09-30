#ifndef MAIN_H
#define MAIN_H
 
#include "app.h"
#include "wxOgre.h"
 
class MyFrame: public wxFrame
{
    public:
        MyFrame(wxFrame *frame, const wxString& title);
        ~MyFrame();
        void UpdateOgre()
    {
        wxOgrePane->update();
    }
    private:
        wxOgre* wxOgrePane;
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
		void OnOpen(wxCommandEvent& event);
        DECLARE_EVENT_TABLE();
};
 
#endif // MAIN_H
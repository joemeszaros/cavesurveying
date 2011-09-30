#include "main.h"
 
int idMenuQuit = wxNewId();
int idMenuAbout = wxNewId();
int idMenuOpen = wxNewId();
 
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
    EVT_MENU(idMenuQuit, MyFrame::OnQuit)
    EVT_MENU(idMenuAbout, MyFrame::OnAbout)
	EVT_MENU(idMenuOpen, MyFrame::OnOpen)
END_EVENT_TABLE()
 
MyFrame::MyFrame(wxFrame *frame, const wxString& title)
    : wxFrame(frame, -1, title)
{
 
    // create a menu bar
    wxMenuBar* mbar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu(_T(""));
    fileMenu->Append(idMenuQuit, _("&Quit\tAlt-F4"), _("Quit the application"));
	fileMenu->Append(idMenuOpen, _("&Open\tCtrl-O"), _("Open a mesh"));
    mbar->Append(fileMenu, _("&File"));
 
	
    
    
 

    wxMenu* helpMenu = new wxMenu(_T(""));
    helpMenu->Append(idMenuAbout, _("&About\tF1"), _("Show info about this application"));
    mbar->Append(helpMenu, _("&Help"));
 
    SetMenuBar(mbar);
 
    // create a status bar with some information about the used wxWidgets version
    CreateStatusBar(2);
    SetStatusText(_("Hello Code::Blocks user !"),0);
    SetStatusText("Hello Code::Blocks user !",1);
 
 
	
	//wxPanel *panel = new wxPanel(this, wxID_ANY,wxPoint(0,0),wxSize(200,200));

	//wxButton *button = new wxButton(panel, wxID_EXIT, wxT("Quit"), wxPoint(100,100));
  //Connect(wxID_EXIT, wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MyFrame::OnQuit));
   //button->SetFocus();
    wxOgrePane = new wxOgre(this);
 
}
 
MyFrame::~MyFrame()
{
}
 
void MyFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}
 
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = _("Welcome to...");
    wxMessageBox(msg, _("Welcome to..."));
}

void MyFrame::OnOpen(wxCommandEvent& event)
{

	wxFileDialog* OpenDialog = new wxFileDialog(
		this, _("Choose a file to open"), wxEmptyString, wxEmptyString, 
		_("Ogre mesh files (*.mesh)|*.mesh"),
		wxFD_OPEN, wxDefaultPosition);
 
	wxString CurrentDocPath;
	// Creates a "open file" dialog with 4 file types
	if (OpenDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
		CurrentDocPath = OpenDialog->GetPath();
		// Sets our current document to the file the user selected
		wxOgrePane->OnOpen(OpenDialog->GetFilename());
		
		SetTitle(wxString("Edit - ") << CurrentDocPath); // Set the Title to reflect the file open
	}
 
	// Clean up after ourselves
	OpenDialog->Destroy();
    //wxString msg = _("Welcome to...");
    //wxMessageBox(msg, _("Welcome to..."));
}
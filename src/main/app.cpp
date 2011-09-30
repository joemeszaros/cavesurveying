#include "app.h"
#include "main.h"
 
#include "wxOgre.h"
 
IMPLEMENT_APP(MyApp);
 
bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame(0L, _("wxWidgets Application Template"));
    frame->Show();
    frame->UpdateOgre();
    return true;
}
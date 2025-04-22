///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ui.h"

#include "res/black.png.h"
#include "res/red.png.h"

///////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bgSizer;
	bgSizer = new wxBoxSizer( wxVERTICAL );

	bgPanel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* borderSizer;
	borderSizer = new wxStaticBoxSizer( new wxStaticBox( bgPanel, wxID_ANY, wxEmptyString ), wxVERTICAL );

	wxBoxSizer* topSizer;
	topSizer = new wxBoxSizer( wxHORIZONTAL );

	welcomeText = new wxStaticText( borderSizer->GetStaticBox(), wxID_ANY, _("Welcome to Beat Revival"), wxDefaultPosition, wxDefaultSize, 0 );
	welcomeText->Wrap( -1 );
	topSizer->Add( welcomeText, 0, wxALIGN_CENTER|wxALL, 5 );


	borderSizer->Add( topSizer, 1, wxALIGN_CENTER, 5 );


	mainSizer->Add( borderSizer, 1, wxALL|wxEXPAND, 10 );

	wxBoxSizer* middleSizer;
	middleSizer = new wxBoxSizer( wxHORIZONTAL );

	connectButton = new wxButton( bgPanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );

	connectButton->SetBitmap( black_png_to_wx_bitmap() );
	connectButton->SetBitmapMargins( wxSize( 5,5 ) );
	middleSizer->Add( connectButton, 0, wxALIGN_CENTER|wxALL, 5 );


	mainSizer->Add( middleSizer, 1, wxALIGN_CENTER, 5 );

	wxBoxSizer* bottomSizer;
	bottomSizer = new wxBoxSizer( wxHORIZONTAL );

	helpText = new wxStaticText( bgPanel, wxID_ANY, _("Ensure that Mirror's Edge™ Catalyst is running\nthen click the button to connect to the server"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	helpText->Wrap( -1 );
	bottomSizer->Add( helpText, 0, wxALIGN_CENTER|wxALL, 5 );


	mainSizer->Add( bottomSizer, 1, wxALIGN_CENTER, 5 );


	bgPanel->SetSizer( mainSizer );
	bgPanel->Layout();
	mainSizer->Fit( bgPanel );
	bgSizer->Add( bgPanel, 1, wxEXPAND, 5 );


	this->SetSizer( bgSizer );
	this->Layout();
	statusBar = this->CreateStatusBar( 1, 0, wxID_ANY );
	statusBar->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxEmptyString ) );


	this->Centre( wxBOTH );

	wxIcon runnerIcon;
	runnerIcon.CopyFromBitmap( red_png_to_wx_bitmap() );
	this->SetIcon( runnerIcon );

	connectButton->Bind( wxEVT_BUTTON, &MainWindow::ApplyPatches, this );
}

MainWindow::~MainWindow()
{
}

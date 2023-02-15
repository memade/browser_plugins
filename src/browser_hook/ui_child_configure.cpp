#include "stdafx.h"

namespace local {
	wxBEGIN_EVENT_TABLE(IChildConfigure, wxMDIChildFrame)
		EVT_SIZE(IChildConfigure::OnSize)
		EVT_MOVE(IChildConfigure::OnMove)
		EVT_CLOSE(IChildConfigure::OnCloseWindow)
		EVT_ACTIVATE(IChildConfigure::OnActivate)
		EVT_AUI_PANE_CLOSE(IChildConfigure::OnPaneClose)
		wxEND_EVENT_TABLE();

	IChildConfigure::IChildConfigure(wxMDIParentFrame* parent,
		wxWindowID id /*= wxID_ANY*/,
		const wxString& title /*= ""*/,
		const wxPoint& pos /*= wxDefaultPosition*/,
		const wxSize& size /*= wxDefaultSize*/,
		long style /*= wxDEFAULT_FRAME_STYLE*/,
		const wxString& name /*= wxASCII_STR(wxFrameNameStr)*/) :
		wxMDIChildFrame(parent, id, title, pos, size, style, name) {
		m_AuiManager.SetManagedWindow(this);

//auto tree = new TreeCtrlMain(this);
//m_AuiManager.AddPane(
// tree,
// wxAuiPaneInfo().Layer(1).Position(1).CloseButton(false).MaxSize(110, 0).Left().Maximize());
//
//auto window = new wxTextCtrl(
// this, wxID_ANY, wxString("asdflkhasglhasdg"));
//m_AuiManager.AddPane(window,
// wxAuiPaneInfo().Layer(1).Position(2).CloseButton(false).Right().Maximize());
//
////m_AuiManager.AddPane(new wxWindow, wxAuiPaneInfo().
//// /*Name("test9").Caption("Text Pane with Hide Prompt").*/
//// Right().Layer(0).Position(2).Maximize().CloseButton(false).CenterPane());
//
//
//m_AuiManager.Update();
		//auto m_pSizerboxMain = new wxBoxSizer(wxVERTICAL);

		//auto h = new wxBoxSizer(wxHORIZONTAL);
		//auto static_text_hook_main_switch = new wxStaticText();
		//static_text_hook_main_switch->SetLabelText(wxString("总开关: "));
		//h->Add(static_text_hook_main_switch);

		//m_pSizerboxMain->Add(h);
		//m_AuiManager.AddPane()
		//m_AuiManager.Update();
		//this->AddNode(m_pSizerboxMain);
		//SetSizerAndFit(m_pSizerboxMain);
#if 1

		m_pTreeCtrlMain = new TreeCtrlMain(this);

		m_AuiManager.AddPane(m_pTreeCtrlMain,
			wxAuiPaneInfo().
			Name("").
			Caption("").
			Layer(1).
			Position(1).
			CloseButton(false).
			MaximizeButton(false).Center().MinSize(110, 0));

		//auto m_pSizerboxMain = new wxBoxSizer(wxVERTICAL);

		//wxSizer* const vertical = new wxStaticBoxSizer(wxVERTICAL, this);
		//vertical->Add(new wxStaticText(this, wxID_ANY, "sdag"));
		//auto m_pTextResourceUpdateUrl = new wxTextCtrl(this, wxID_ANY, "CPU核心数[66].");
		////m_pTextResourceUpdateUrl->SetMaxSize(wxSize(m_EditCtrlMaxWidth, m_pTextResourceUpdateUrl->GetMinHeight()));
		////vertical->Add(m_pTextResourceUpdateUrl, wxSizerFlags().Expand());
		//m_pSizerboxMain->Add(vertical, wxSizerFlags().Expand().Border(wxBOTTOM));

		auto text_pane_2 = new wxTextCtrl(this, wxID_ANY, "263473457", wxDefaultPosition, wxSize(200, 0));

		m_AuiManager.AddPane(text_pane_2,
			wxAuiPaneInfo().
			Name("").
			Caption("").
			Right().
			Layer(1).
			Position(2).
			CloseButton(false).
			MaximizeButton(false));

		m_AuiManager.Update();
#endif
	}

	IChildConfigure::~IChildConfigure() {

	}

	void IChildConfigure::OnPaneClose(wxAuiManagerEvent& evt) {
		evt.Veto();
	}

	void IChildConfigure::OnActivate(wxActivateEvent& evt) {
		evt.Skip();
	}

	void IChildConfigure::OnSize(wxSizeEvent& evt) {
		//if (m_pTreeCtrlMain) {
		//	auto client_size = GetClientSize();
		//	m_pTreeCtrlMain->SetSize(110, client_size.y);

		//	m_AuiManager.Update();
		//}
		evt.Skip();
	}

	void IChildConfigure::OnMove(wxMoveEvent& evt) {
		evt.Skip();
	}

	void IChildConfigure::OnCloseWindow(wxCloseEvent& evt) {
		auto auis = m_AuiManager.GetAllPanes();
		for (size_t i = 0; i < auis.GetCount(); ++i) {
			auis[i].window->Close();
		}
		evt.Skip();
	}
	void IChildConfigure::OnUpdateUI(wxUpdateUIEvent& evt) {
		evt.Skip();
	}
}///namespace local
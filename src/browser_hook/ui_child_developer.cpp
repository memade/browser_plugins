#include "stdafx.h"

namespace local {
	wxBEGIN_EVENT_TABLE(IChildConfigureDeveloper, wxMDIChildFrame)
		EVT_SIZE(IChildConfigureDeveloper::OnSize)
		EVT_MOVE(IChildConfigureDeveloper::OnMove)
		EVT_CLOSE(IChildConfigureDeveloper::OnCloseWindow)
		EVT_ACTIVATE(IChildConfigureDeveloper::OnActivate)
		EVT_AUI_PANE_CLOSE(IChildConfigureDeveloper::OnPaneClose)
		wxEND_EVENT_TABLE();

	IChildConfigureDeveloper::IChildConfigureDeveloper(wxMDIParentFrame* parent,
		const wxWindowID& id,
		const wxString& title,
		const wxPoint& pos,
		const wxSize& size) :
		wxMDIChildFrame(parent, id, title, pos, size) {


		//auto m_pSizerboxMain = new wxBoxSizer(wxVERTICAL);

		//wxSizer* const vertical = new wxStaticBoxSizer(wxVERTICAL, this);
		//vertical->Add(new wxStaticText(this, wxID_ANY, "sdag"));
		//auto m_pTextResourceUpdateUrl = new wxTextCtrl(this, wxID_ANY, "CPU核心数[66].");
		////m_pTextResourceUpdateUrl->SetMaxSize(wxSize(m_EditCtrlMaxWidth, m_pTextResourceUpdateUrl->GetMinHeight()));
		////vertical->Add(m_pTextResourceUpdateUrl, wxSizerFlags().Expand());
		//m_pSizerboxMain->Add(vertical, wxSizerFlags().Expand().Border(wxBOTTOM));



	}

	IChildConfigureDeveloper::~IChildConfigureDeveloper() {

	}

	void IChildConfigureDeveloper::OnPaneClose(wxAuiManagerEvent& evt) {
		evt.Veto();
	}

	void IChildConfigureDeveloper::OnActivate(wxActivateEvent& evt) {
		evt.Skip();
	}

	void IChildConfigureDeveloper::OnSize(wxSizeEvent& evt) {
		evt.Skip();
	}

	void IChildConfigureDeveloper::OnMove(wxMoveEvent& evt) {
		evt.Skip();
	}

	void IChildConfigureDeveloper::OnCloseWindow(wxCloseEvent& evt) {
		auto auis = m_AuiManager.GetAllPanes();
		for (size_t i = 0; i < auis.GetCount(); ++i) {
			auis[i].window->Close();
		}
		evt.Skip();
	}
	void IChildConfigureDeveloper::OnUpdateUI(wxUpdateUIEvent& evt) {
		evt.Skip();
	}
}///namespace local
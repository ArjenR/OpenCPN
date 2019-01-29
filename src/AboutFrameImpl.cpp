/***************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  About Dialog
 * Author:   David Register
 *
 ***************************************************************************
 *   Copyright (C) 2019 by David S. Register                               *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,  USA.         *
 **************************************************************************/

#include "AboutFrameImpl.h"
#include "config.h"
#include "OCPNPlatform.h"

extern OCPNPlatform  *g_Platform;

AboutFrameImpl::AboutFrameImpl( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : AboutFrame( parent, id, title, pos, size, style )
{
    m_staticTextVersion->SetLabel(VERSION_FULL);
    m_staticTextCopyYears->SetLabel("\u00A9 2000-2019");
    m_hyperlinkIniFile->SetLabel(g_Platform->GetConfigFileName());
    m_hyperlinkIniFile->SetURL(g_Platform->GetConfigFileName());
    m_hyperlinkLogFile->SetLabel(g_Platform->GetLogFileName());
    m_hyperlinkLogFile->SetURL(g_Platform->GetLogFileName());
    m_htmlWinAuthors->Hide();
    m_htmlWinLicense->Hide();
    m_htmlWinHelp->Hide();
    m_btnBack->Hide();
    m_htmlWinLicense->LoadFile(wxString::Format("%s/license.txt", g_Platform->GetSharedDataDir().c_str()));
    m_htmlWinAuthors->LoadFile(wxString::Format("%s/authors.txt", g_Platform->GetSharedDataDir().c_str()));
    wxBitmap logo(wxString::Format("%s/opencpn.png", g_Platform->GetSharedDataDir().c_str()), wxBITMAP_TYPE_ANY);
    m_hyperlinkHelp->SetURL(wxString::Format("file://%s/doc/help_en_US.html", g_Platform->GetSharedDataDir().c_str()));
    m_htmlWinHelp->LoadFile(wxString::Format("%s/doc/help_en_US.html", g_Platform->GetSharedDataDir().c_str()));
    m_bitmapLogo->SetBitmap(logo);
    
    int width = m_scrolledWindowAbout->GetSizer()->GetSize().GetWidth() + m_bitmapLogo->GetSize().GetWidth() + 20;
    int height = m_scrolledWindowAbout->GetSizer()->GetSize().GetHeight() + m_panelMainLinks->GetSizer()->GetSize().GetHeight() + 20;

    SetMinSize(wxSize(width, height));
    Layout();
    Fit();
}


void AboutFrameImpl::OnLinkHelp( wxHyperlinkEvent& event )
{
    m_htmlWinAuthors->Hide();
    m_htmlWinLicense->Hide();
    m_htmlWinHelp->Show();
    m_scrolledWindowAbout->Hide();
    m_btnBack->Show();
    m_btnBack->Enable(m_htmlWinHelp->HistoryCanBack());
    SetSize(m_parent->GetSize());
    Centre();
}

void AboutFrameImpl::OnLinkLicense( wxHyperlinkEvent& event )
{
    m_htmlWinAuthors->Hide();
    m_htmlWinLicense->Show();
    m_htmlWinHelp->Hide();
    m_btnBack->Hide();
    m_scrolledWindowAbout->Hide();
    Layout();
}

void AboutFrameImpl::OnLinkAuthors( wxHyperlinkEvent& event )
{
    m_htmlWinAuthors->Show();
    m_htmlWinLicense->Hide();
    m_htmlWinHelp->Hide();
    m_btnBack->Hide();
    m_scrolledWindowAbout->Hide();
    Layout();
}

void AboutFrameImpl::AboutFrameOnActivate( wxActivateEvent& event )
{
    m_htmlWinAuthors->Hide();
    m_htmlWinLicense->Hide();
    m_htmlWinHelp->Hide();
    m_btnBack->Hide();
    m_scrolledWindowAbout->Show();
    Layout();
}

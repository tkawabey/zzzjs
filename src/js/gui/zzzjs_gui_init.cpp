/*
 * wxJavaScript - init.cpp
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://zzzJs.sourceforge.net
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 * $Id$
 */
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 
// main.cpp
#include <wx/setup.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/intl.h>

#if defined(__WXMSW__)
	#include <wx/msw/private.h>
#endif
#include <wx/calctrl.h>

#if defined(__WXMSW__)
    #include <wx/msw/ole/automtn.h>
#endif

#include <jsapi.h>
#include "js/common/jsutil.h"
#include "js/common/index.h"
 
// All wxJS objects
#include "js/gui/control/window.h"
#include "js/gui/control/toplevel.h"
#include "js/gui/control/frame.h"
#include "js/gui/control/mdi.h"
#include "js/gui/control/mdichild.h"
#include "js/gui/control/dialog.h"
#include "js/gui/control/menu.h"
#include "js/gui/control/menuitem.h"
#include "js/gui/control/menubar.h"

// Controls
#include "js/gui/control/control.h"
#include "js/gui/control/textctrl.h"
#include "js/gui/control/button.h"
#include "js/gui/control/bmpbtn.h"
#include "js/gui/control/sttext.h"
#include "js/gui/control/staticbx.h"
#include "js/gui/control/checkbox.h"
#include "js/gui/control/ctrlitem.h"
#include "js/gui/control/item.h"
#include "js/gui/control/listbox.h"
#include "js/gui/control/chklstbx.h"
#include "js/gui/control/chklstbxchk.h"
#include "js/gui/control/choice.h"
#include "js/gui/control/combobox.h"
#include "js/gui/control/calendar.h"
#include "js/gui/control/caldate.h"
#include "js/gui/control/gauge.h"
#include "js/gui/control/radiobox.h"
#include "js/gui/control/radioboxit.h"
#include "js/gui/control/radiobtn.h"
#include "js/gui/control/slider.h"
#include "js/gui/control/helpbtn.h"
#include "js/gui/control/splitwin.h"
#include "js/gui/control/statbar.h"
#include "js/gui/control/toolbar.h"
#include "js/gui/control/txtdlg.h"
#include "js/gui/control/pwdlg.h"
#include "js/gui/control/scrollwnd.h"
#include "js/gui/control/htmlwin.h"
#include "js/gui/control/spinctrl.h"
#include "js/gui/control/spinbtn.h"

// Validators
#include "js/gui/misc/validate.h"
#include "js/gui/misc/genval.h"
#include "js/gui/misc/textval.h"

// Sizers
#include "js/gui/misc/sizer.h"
#include "js/gui/misc/gridszr.h"
#include "js/gui/misc/flexgrid.h"
#include "js/gui/misc/boxsizer.h"
#include "js/gui/misc/stsizer.h"

// Dialogs
#include "js/gui/control/panel.h"
#include "js/gui/control/filedlg.h"
#include "js/gui/control/dirdlg.h"
#include "js/gui/control/coldata.h"
#include "js/gui/control/coldlg.h"
#include "js/gui/control/fontdata.h"
#include "js/gui/control/fontdlg.h"
#include "js/gui/control/findrdlg.h"
#include "js/gui/control/finddata.h"

// Miscellaneous wxWindow classes
#include "js/gui/misc/size.h"
#include "js/gui/misc/rect.h"
#include "js/gui/misc/region.h"
#include "js/gui/misc/accentry.h"
#include "js/gui/misc/acctable.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/brush.h"
#include "js/gui/misc/pen.h"
#include "js/gui/misc/font.h"
#include "js/gui/misc/fontenum.h"
#include "js/gui/misc/fontlist.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/mask.h"
#include "js/gui/misc/art_provider.h"
#include "js/gui/misc/pallet.h"
#include "js/gui/misc/image.h"
#include "js/gui/misc/imghand.h"
#include "js/gui/misc/icon.h"
#include "js/gui/misc/colourdb.h"
#include "js/gui/misc/cshelp.h"
#include "js/gui/misc/constant.h"
#if defined(__WXMSW__)
    #include "js/gui/misc/autoobj.h"
#endif
#include "js/gui/misc/settings.h"

// Events
#include "js/gui/event/jsevent.h"

// Common Controls
#include "js/gui/misc/cmnconst.h"
#include "js/gui/misc/imagelst.h"
#include "js/gui/control/listctrl.h"
#include "js/gui/control/listhit.h"
#include "js/gui/control/listitem.h"
#include "js/gui/control/listitattr.h"
#include "js/gui/control/treectrl.h"
#include "js/gui/control/treeitem.h"
#include "js/gui/control/treeid.h"
#include "js/gui/control/treehit.h"
// bookctrl
#include "js/gui/control/bookctrlbase.h"
#include "js/gui/control/notebook.h"
#include "js/gui/control/treebook.h"
#include "js/gui/control/toolbook.h"
#include "js/gui/control/simplebook.h"
#include "js/gui/control/choicebook.h"

// Header Colmn
#include "js/gui/control/headercolumn.h"
#include "js/gui/control/setableheadercolumn.h"


// aui
#include "js/gui/aui/auimanager.h"
#include "js/gui/aui/auinotebook.h"
#include "js/gui/aui/auipanelinfo.h"

// dataview
#include "js/gui/dataview/dataviewrender.h"
#include "js/gui/dataview/dataviewbitmaprender.h"
#include "js/gui/dataview/dataviewchoicerender.h"
#include "js/gui/dataview/dataviewchoicebyindexrender.h"
#include "js/gui/dataview/dataviewcustomrender.h"
#include "js/gui/dataview/dataviewspinrender.h"
#include "js/gui/dataview/dataviewdaterender.h"
#include "js/gui/dataview/dataviewicontextrender.h"
#include "js/gui/dataview/dataviewprogressrender.h"
#include "js/gui/dataview/dataviewtextrender.h"
#include "js/gui/dataview/dataviewtogglerender.h"
#include "js/gui/dataview/dataviewctrl.h"
#include "js/gui/dataview/dataviewlistctrl.h"
#include "js/gui/dataview/dataviewtreectrl.h"
#include "js/gui/dataview/dataviewitem.h"
#include "js/gui/dataview/dataviewitemattr.h"
#include "js/gui/dataview/dataviewmodel.h"
#include "js/gui/dataview/dataviewtreestore.h"
#include "js/gui/dataview/dataviewvirtuallistmodel.h"
#include "js/gui/dataview/dataviewindexlistmodel.h"
#include "js/gui/dataview/dataviewliststore.h"

#include "js/gui/aui/constant.h"


#include "js/gui/misc/globfun.h"
#include "js/gui/zzzjs_gui_init.h"
#include "js/gui/pg/pg_init.h"
#include "js/gui/gdi/gdi_init.h"

using namespace zzzJs;
using namespace zzzJs::gui;

bool zzzJs::gui::InitClass(JSContext *cx, JSObject *global)
{
    InitGuiConstants(cx, global);

    JSObject *obj = NULL;

    // Initialize wxJS JavaScript objects
	obj = Window::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxWindow prototype creation failed"));
	if (! obj)
		return false;

	obj = Control::define_Class(cx, global, Window::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxControl prototype creation failed"));
	if (! obj)
		return false;


	obj = TopLevelWindow::define_Class(cx, global, Window::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxTopLevelWindow prototype creation failed"));
	if (! obj )
		return false;

	obj = Frame::define_Class(cx, global, TopLevelWindow::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxFrame prototype creation failed"));
	if (! obj )
		return false;

    obj = MDIParentFrame::define_Class(cx, global, Frame::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxMDIParentFrame prototype creation failed"));
	if (! obj )
		return false;

    obj = MDIChildFrame::define_Class(cx, global, Frame::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxMDIChildFrame prototype creation failed"));
	if (! obj )
		return false;

	obj = Menu::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxMenu prototype creation failed"));
	if (! obj )
		return false;

	obj = MenuItem::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxMenuItem prototype creation failed"));
	if (! obj )
		return false;

	obj = MenuBar::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxMenuBar prototype creation failed"));
	if (! obj )
		return false;

	obj = TextCtrl::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxTextCtrl prototype creation failed"));
	if (! obj )
		return false;

	obj = Button::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxButton prototype creation failed"));
	if (! obj )
		return false;

	obj = BitmapButton::define_Class(cx, global, Button::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxBitmapButton prototype creation failed"));
	if (! obj )
		return false;

	obj = ContextHelpButton::define_Class(cx, global, BitmapButton::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxContextHelptButton prototype creation failed"));
	if (! obj )
		return false;

    obj = StaticText::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxStaticText prototype creation failed"));
	if (! obj )
		return false;

	obj = StaticBox::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxStaticBox prototype creation failed"));
	if (! obj )
		return false;

	obj = CheckBox::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxCheckBox prototype creation failed"));
	if (! obj )
		return false;

	obj = ControlWithItems::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxControlWithItems prototype creation failed"));
	if (! obj )
		return false;
	
	obj = ControlItem::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxControlItem prototype creation failed"));
	if (! obj )
		return false;


	obj = ListBox::define_Class(cx, global, ControlWithItems::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxListBox prototype creation failed"));
	if (! obj )
		return false;

	obj = CheckListBox::define_Class(cx, global, ListBox::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxCheckListBox prototype creation failed"));
	if (! obj )
		return false;
	
	obj = CheckListBoxItem::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxCheckListBoxItem prototype creation failed"));
	if (! obj )
		return false;

	obj = Choice::define_Class(cx, global, ControlWithItems::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxChoice prototype creation failed"));
	if (! obj )
		return false;

	obj = CalendarCtrl::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxCalendarCtrl prototype creation failed"));
	if (! obj )
		return false;

	obj = Gauge::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxGauge prototype creation failed"));
	if (! obj )
		return false;

	obj = RadioBox::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxRadioBox prototype creation failed"));
	if (! obj )
		return false;
	
	obj = RadioBoxItem::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxRadioBoxItem prototype creation failed"));
	if (! obj )
		return false;


	obj = RadioButton::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxRadioButton prototype creation failed"));
	if (! obj )
		return false;

	obj = Panel::define_Class(cx, global, Window::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxPanel prototype creation failed"));
	if (! obj )
		return false;

	obj = Dialog::define_Class(cx, global, TopLevelWindow::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxDialog prototype creation failed"));
	if (! obj )
		return false;

	obj = CalendarDateAttr::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxCalendarDateAttr prototype creation failed"));
	if (! obj )
		return false;

	obj = ComboBox::define_Class(cx, global, ControlWithItems::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxComboBox prototype creation failed"));
	if (! obj )
		return false;

	obj = Slider::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSlider prototype creation failed"));
	if (! obj )
		return false;

	obj = Size::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("Size prototype creation failed"));
	if (! obj )
		return false;

	obj = Rect::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("Rect prototype creation failed"));
	if (! obj )
		return false;

	obj = Region::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("Region prototype creation failed"));
	if (! obj )
		return false;

	obj = FileDialog::define_Class(cx, global, Dialog::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxFileDialog prototype creation failed"));
	if (! obj )
		return false;

	if ( ! InitEventClasses(cx, global) )
		return false;

	obj = Sizer::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxSizer prototype creation failed"));
	if (! obj )
		return false;

	obj = GridSizer::define_Class(cx, global, Sizer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxGridSizer prototype creation failed"));
	if (! obj )
		return false;

	obj = FlexGridSizer::define_Class(cx, global, GridSizer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxFlexGridSizer prototype creation failed"));
	if (! obj )
		return false;

	obj = BoxSizer::define_Class(cx, global, Sizer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxBoxSizer prototype creation failed"));
	if (! obj )
		return false;

	obj = StaticBoxSizer::define_Class(cx, global, BoxSizer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxStaticBoxSizer prototype creation failed"));
	if (! obj )
		return false;

	obj = Validator::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxValidator prototype creation failed"));
	if (! obj )
		return false;

	obj = GenericValidator::define_Class(cx, global, Validator::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxGenericValidator prototype creation failed"));
	if (! obj )
		return false;

	obj = TextValidator::define_Class(cx, global, Validator::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxTextValidator prototype creation failed"));
	if (! obj )
		return false;

    obj = AcceleratorEntry::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxAcceleratorEntry prototype creation failed"));
	if (! obj )
		return false;

	obj = AcceleratorTable::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxAcceleratorTable prototype creation failed"));
	if (! obj )
		return false;

	obj = Colour::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxColour prototype creation failed"));
	if (! obj )
		return false;

	obj = Brush::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxBrush prototype creation failed"));
	if (! obj )
		return false;

	obj = Pen::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("Pen prototype creation failed"));
	if (! obj )
		return false;

	obj = ColourDatabase::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxColourDatabase prototype creation failed"));
	if (! obj )
		return false;

    obj = Font::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxFont prototype creation failed"));
	if (! obj )
		return false;

	obj = ColourData::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxColourData prototype creation failed"));
	if (! obj )
		return false;

	obj = ColourDialog::define_Class(cx, global, Dialog::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxColourDialog prototype creation failed"));
	if (! obj )
		return false;

	obj = FontData::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxFontData prototype creation failed"));
	if (! obj )
		return false;

	obj = FontDialog::define_Class(cx, global, Dialog::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxFontDialog prototype creation failed"));
	if (! obj )
		return false;

	obj = FontList::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("FontList prototype creation failed"));
	if (! obj )
		return false;

	obj = DirDialog::define_Class(cx, global, Dialog::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DirDialog prototype creation failed"));
	if (! obj )
		return false;

	obj = FindReplaceData::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("FindReplaceData prototype creation failed"));
	if (! obj )
		return false;

	obj = FindReplaceDialog::define_Class(cx, global, Dialog::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("FindReplaceDialog prototype creation failed"));
	if (! obj )
		return false;

	obj = FontEnumerator::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("FontEnumerator prototype creation failed"));
	if (! obj )
		return false;

	obj = Bitmap::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("Bitmap prototype creation failed"));
	if (! obj )
		return false;

	obj = Mask::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("Bitmap prototype creation failed"));
	if (! obj )
		return false;

	obj = ArtProvider::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("ArtProvider prototype creation failed"));
	if (! obj )
		return false;

	obj = Palette::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("Palette prototype creation failed"));
	if (! obj )
		return false;

	obj = Icon::define_Class(cx, global, Bitmap::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("Icon prototype creation failed"));
	if (! obj )
		return false;

    obj = ContextHelp::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("File prototype creation failed"));
	if (! obj )
		return false;

    InitCommonConst(cx, global);

    obj = ImageList::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("ImageList prototype creation failed"));
	if (! obj )
		return false;

    obj = ListCtrl::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("ListCtrl prototype creation failed"));
	if (! obj )
		return false;

    obj = ListItem::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("ListItem prototype creation failed"));
	if (! obj )
		return false;
    
    obj = ListItemAttr::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxListItemAttr prototype creation failed"));
	if (! obj )
		return false;

    obj = ListHitTest::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxListHitTest prototype creation failed"));
	if (! obj )
		return false;

    obj = TreeCtrl::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxTreeCtrl prototype creation failed"));
	if (! obj )
		return false;

    obj = TreeItem::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxTreeItem prototype creation failed"));
	if (! obj )
		return false;
    
    obj = TreeItemId::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxTreeItemId prototype creation failed"));
	if (! obj )
		return false;

    obj = TreeHitTest::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxTreeHitTest prototype creation failed"));
	if (! obj )
		return false;

    obj = SplitterWindow::define_Class(cx, global, Window::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSplitterWindow prototype creation failed"));
	if (! obj )
		return false;

    obj = StatusBar::define_Class(cx, global, Window::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxStatusBar prototype creation failed"));
	if (! obj )
		return false;

    obj = ToolBar::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxToolBar prototype creation failed"));
	if (! obj )
		return false;

#ifdef __WXMSW__
    obj = AutomationObject::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxAutomationObject prototype creation failed"));
	if (! obj )
		return false;
#endif

    obj = Image::define_Class(cx, global);
    wxASSERT_MSG(obj != NULL, wxT("wxImage prototype creation failed"));
    if (! obj )
        return false;

    obj = ImageHandler::define_Class(cx, global);
    wxASSERT_MSG(obj != NULL, wxT("wxImageHandler prototype creation failed"));
    if (! obj )
        return false;

	obj = BMPHandler::define_Class(cx, global, ImageHandler::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxBMPHandler prototype creation failed"));
    if (! obj )
        return false;

    obj = GIFHandler::define_Class(cx, global, ImageHandler::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxGIFHandler prototype creation failed"));
    if (! obj )
        return false;

    obj = ICOHandler::define_Class(cx, global, ImageHandler::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxICOHandler prototype creation failed"));
    if (! obj )
        return false;

    obj = JPEGHandler::define_Class(cx, global, ImageHandler::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxJPEGHandler prototype creation failed"));
    if (! obj )
        return false;

    obj = PCXHandler::define_Class(cx, global, ImageHandler::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxPCXHandler prototype creation failed"));
    if (! obj )
        return false;

    obj = PNGHandler::define_Class(cx, global, ImageHandler::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxPNGHandler prototype creation failed"));
    if (! obj )
        return false;

    obj = PNMHandler::define_Class(cx, global, ImageHandler::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxPNMHandler prototype creation failed"));
    if (! obj )
        return false;

    obj = TIFFHandler::define_Class(cx, global, ImageHandler::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxTIFFHandler prototype creation failed"));
    if (! obj )
        return false;

    obj = XPMHandler::define_Class(cx, global, ImageHandler::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxXPMHandler prototype creation failed"));
    if (! obj )
        return false;

    obj = TextEntryDialog::define_Class(cx, global, Dialog::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxTextEntryDialog prototype creation failed"));
    if (! obj )
        return false;

    obj = PasswordEntryDialog::define_Class(cx, global, TextEntryDialog::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxPasswordEntryDialog prototype creation failed"));
    if (! obj )
        return false;

    obj = ScrolledWindow::define_Class(cx, global, Panel::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxScrollWindow prototype creation failed"));
    if (! obj )
        return false;

    obj = HtmlWindow::define_Class(cx, global, ScrolledWindow::GetClassPrototype());
    wxASSERT_MSG(obj != NULL, wxT("wxHtmlWindow prototype creation failed"));
    if (! obj )
        return false;

	obj = SpinCtrl::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSpinCtrl prototype creation failed"));
	if (! obj )
		return false;

    obj = SpinButton::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSpinButton prototype creation failed"));
	if (! obj )
		return false;

    obj = SystemSettings::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("wxSystemSettings prototype creation failed"));
	if (! obj )
		return false;

	// Header Column
    obj = HeaderColumn::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("HeaderColumn prototype creation failed"));
	if (! obj )
		return false;
    obj = SettableHeaderColumn::define_Class(cx, global, HeaderColumn::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("SettableHeaderColumn prototype creation failed"));
	if (! obj )
		return false;
	

	// bookctrl
    obj = BookCtrlBase::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("BookCtrlBase prototype creation failed"));
	if (! obj )
		return false;
    obj = Notebook::define_Class(cx, global, BookCtrlBase::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("Notebook prototype creation failed"));
	if (! obj )
		return false;
    obj = Toolbook::define_Class(cx, global, BookCtrlBase::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("Toolbook prototype creation failed"));
	if (! obj )
		return false;
    obj = Toolbook::define_Class(cx, global, BookCtrlBase::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("Toolbook prototype creation failed"));
	if (! obj )
		return false;
    obj = Simplebook::define_Class(cx, global, BookCtrlBase::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("Simplebook prototype creation failed"));
	if (! obj )
		return false;
    obj = Choicebook::define_Class(cx, global, BookCtrlBase::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("Choicebook prototype creation failed"));
	if (! obj )
		return false;


	// dataview
    obj = dataview::DataViewRenderer::define_Class(cx, global,NULL);
	wxASSERT_MSG(obj != NULL, wxT("DataViewRenderer prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewBitmapRenderer::define_Class(cx, global, dataview::DataViewRenderer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewBitmapRenderer prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewChoiceRenderer::define_Class(cx, global, dataview::DataViewRenderer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewRenderer prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewChoiceByIndexRenderer::define_Class(cx, global, dataview::DataViewChoiceRenderer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewChoiceByIndexRenderer prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewCustomRenderer::define_Class(cx, global, dataview::DataViewRenderer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewCustomRenderer prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewSpinRenderer::define_Class(cx, global, dataview::DataViewCustomRenderer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewSpinRenderer prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewDateRenderer::define_Class(cx, global, dataview::DataViewRenderer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewDateRenderer prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewIconTextRenderer::define_Class(cx, global, dataview::DataViewRenderer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewIconTextRenderer prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewProgressRenderer::define_Class(cx, global, dataview::DataViewRenderer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewProgressRenderer prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewTextRenderer::define_Class(cx, global, dataview::DataViewRenderer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewTextRenderer prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewToggleRenderer::define_Class(cx, global, dataview::DataViewRenderer::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewToggleRenderer prototype creation failed"));
	if (! obj )
		return false;
	
    obj = dataview::DataViewCtrl::define_Class(cx, global, Control::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewCtrl prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewListCtrl::define_Class(cx, global, dataview::DataViewCtrl::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewListCtrl prototype creation failed"));
	if (! obj )
		return false;
    obj = dataview::DataViewTreeCtrl::define_Class(cx, global, dataview::DataViewCtrl::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewTreeCtrl prototype creation failed"));
	if (! obj )
		return false;
	
    obj = dataview::DataViewItem::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("DataViewItem prototype creation failed"));
	if (! obj )
		return false;
	
    obj = dataview::DataViewItemAttr::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("DataViewItemAttr prototype creation failed"));
	if (! obj )
		return false;
	
    obj = dataview::DataViewModel::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("DataViewModel prototype creation failed"));
	if (! obj )
		return false;
	
    obj = dataview::DataViewTreeStore::define_Class(cx, global, dataview::DataViewModel::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewTreeStore prototype creation failed"));
	if (! obj )
		return false;
	
    obj = dataview::DataViewVirtualListModel::define_Class(cx, global, dataview::DataViewModel::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewVirtualListModel prototype creation failed"));
	if (! obj )
		return false;
	
    obj = dataview::DataViewIndexListModel::define_Class(cx, global, dataview::DataViewModel::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewIndexListModel prototype creation failed"));
	if (! obj )
		return false;
	
    obj = dataview::DataViewListStore::define_Class(cx, global, dataview::DataViewIndexListModel::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("DataViewListStore prototype creation failed"));
	if (! obj )
		return false;


	// AUI
	JSObject *constObjAui = JS_DefineObject(cx, global, "Aui", 
										 NULL, NULL,
										 JSPROP_READONLY | JSPROP_PERMANENT);

	zzzJs::gui::aui::InitAuiConstants(cx,  constObjAui);

    obj = aui::AuiManager::define_Class(cx, constObjAui, NULL);
	wxASSERT_MSG(obj != NULL, wxT("wxAuiManager prototype creation failed"));
	if (! obj )
		return false;
	
    obj = aui::AuiNotebook::define_Class(cx, constObjAui, BookCtrlBase::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxAuiNotebook prototype creation failed"));
	if (! obj )
		return false;
	
    obj = aui::AuiPaneInfo::define_Class(cx, constObjAui, NULL);
	wxASSERT_MSG(obj != NULL, wxT("wxAuiPaneInfo prototype creation failed"));
	if (! obj )
		return false;


	// Property Grid
	zzzJs::gui::pg::InitClass(cx, global);
	

	// GDI
	zzzJs::gui::gdi::InitClass(cx, global);

    // Define the global functions
	InitFunctions(cx, global);

	DefineGlobals(cx, global);

	return true;
}


bool zzzJs::gui::InitObject(JSContext *cx, JSObject *obj)
{
  return true;
}

void zzzJs::gui::Destroy()
{
}

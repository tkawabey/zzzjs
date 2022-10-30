/*
 * wxJavaScript - jsevent.cpp
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://wxjs.sourceforge.net
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
 * $Id: jsevent.cpp 744 2007-06-11 19:57:09Z fbraem $
 */
#include "precompile.h"
#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/gui/event/jsevent.h"

#include "js/gui/event/event.h"
#include "js/gui/event/command.h"
#include "js/gui/event/iconize.h"
#include "js/gui/event/close.h"
#include "js/gui/event/key.h"
#include "js/gui/event/activate.h"
#include "js/gui/event/mouse.h"
#include "js/gui/event/move.h"
#include "js/gui/event/cal.h"
#include "js/gui/event/findr.h"
#include "js/gui/event/scroll.h"
#include "js/gui/event/scrollwin.h"
#include "js/gui/event/help.h"
#include "js/gui/event/sizeevt.h"
#include "js/gui/event/htmllink.h"
#include "js/gui/event/split.h"
#include "js/gui/event/spinevt.h"

#include "js/gui/event/notify.h"
#include "js/gui/event/listevt.h"
#include "js/gui/event/treeevt.h"
#include "js/gui/event/evt_paint.h"
#include "js/gui/event/bookctrlevt.h"

using namespace zzzJs;
using namespace zzzJs::gui;

bool zzzJs::gui::InitEventClasses(JSContext *cx, JSObject *global)
{
	JSObject *obj = Event::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxEvent creation prototype failed"));
	if ( !obj )
		return false;

	obj = CommandEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxCommandEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = KeyEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxKeyEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = ActivateEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxActivateEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = CloseEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxCloseEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = FocusEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxFocusEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = InitDialogEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxInitDialogEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = MouseEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxMouseEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = MoveEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxMoveEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = SizeEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSizeEvent prototype creation failed"));
	if (! obj )
		return false;

    obj = CalendarEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxCalendarEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = IconizeEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxIconizeEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = MaximizeEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxMaximizeEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = FindDialogEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxFindDialogEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = ScrollEvent::define_Class(cx, global, CommandEvent::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxScrollEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = ScrollWinEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxScrollWinEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = SysColourChangedEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSysColourChangedEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = HelpEvent::define_Class(cx, global, CommandEvent::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxHelpEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = NotifyEvent::define_Class(cx, global, CommandEvent::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxNotifyEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = ListEvent::define_Class(cx, global, NotifyEvent::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxListEvent prototype creation failed"));
	if (! obj )
		return false;

    obj = TreeEvent::define_Class(cx, global, NotifyEvent::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxTreeEvent prototype creation failed"));
	if (! obj )
		return false;

    obj = HtmlLinkEvent::define_Class(cx, global, CommandEvent::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxHtmlLinkEvent prototype creation failed"));
	if (! obj )
		return false;

    obj = SplitterEvent::define_Class(cx, global, NotifyEvent::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSplitterEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = SpinEvent::define_Class(cx, global, NotifyEvent::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSpinEvent prototype creation failed"));
	if (! obj )
		return false;

	obj = PaintEvent::define_Class(cx, global, Event::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("PaintEvent prototype creation failed"));
	if (! obj )
		return false;
	
	obj = BookCtrlEvent::define_Class(cx, global, NotifyEvent::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("BookCtrlEvent prototype creation failed"));
	if (! obj )
		return false;


    return true;
}

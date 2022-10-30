/*
 * wxJavaScript - initdlg.cpp
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
 * $Id: initdlg.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// jsevent.cpp
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


using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/initdlg</file>
 * <module>gui</module>
 * <class name="wxInitDialogEvent" prototype="@wxEvent">
 *  A wxInitDialogEvent is sent as a dialog or panel is being initialised. 
 *  Handlers for this event can transfer data to the window.
 *  See @wxWindow#onInitDialog.
 * </class>
 */
WXJS_INIT_CLASS(InitDialogEvent, "InitDialogEvent", 0)

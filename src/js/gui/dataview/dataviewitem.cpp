/*
 * wxJavaScript - bmpbtn.cpp
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
 * $Id: bmpbtn.cpp 810 2007-07-13 20:07:05Z fbraem $
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
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"

#include "js/gui/errors.h"
#include "js/gui/dataview/dataviewitem.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;


//--------------------------------------------------------
//	DataViewItem
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewItem, "DataViewItem", 0)

WXJS_BEGIN_PROPERTY_MAP(DataViewItem)
  WXJS_PROPERTY(P_ISOK, "isOk")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxDataViewItem, DataViewItem)
	switch (id) 
	{
	case P_ISOK:
		ToJSVal(cx, vp, p->IsOk());
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_CONSTRUCTOR(wxDataViewItem, DataViewItem)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxDataViewItem *p = new wxDataViewItem();
	return p;
WXJS_END_CONSTRUCTOR

WXJS_BEGIN_DESTRUCTOR(wxDataViewItem, DataViewItem)

WXJS_END_DESTRUCTOR


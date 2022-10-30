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

#include "js/gui/misc/size.h"
#include "js/gui/control/bmpbtn.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/validate.h"
#include "js/gui/control/window.h"
#include "js/gui/control/headercolumn.h"
#include "js/gui/errors.h"




using namespace zzzJs;
using namespace zzzJs::gui;



//--------------------------------------------------------
//	HeaderColumn
//--------------------------------------------------------
WXJS_INIT_CLASS(HeaderColumn, "HeaderColumn", 0)


	

WXJS_BEGIN_PROPERTY_MAP(HeaderColumn)
  WXJS_READONLY_PROPERTY(P_TITLE, "title")
  WXJS_READONLY_PROPERTY(P_BITMAP, "bitmap")
  WXJS_READONLY_PROPERTY(P_WIDTH, "width")
  WXJS_READONLY_PROPERTY(P_MINWIDTH, "minWidth")
  WXJS_READONLY_PROPERTY(P_ALIGNMENT, "alignment")
  WXJS_READONLY_PROPERTY(P_FLAGS, "flags")
  WXJS_READONLY_PROPERTY(P_IS_RESIZEABLE, "isResizeAble")
  WXJS_READONLY_PROPERTY(P_IS_REORDERABLE, "isReorderAble")
  WXJS_READONLY_PROPERTY(P_IS_HIDDEN, "isHidden")
  WXJS_READONLY_PROPERTY(P_IS_SORTABLE, "isSortable")
  WXJS_READONLY_PROPERTY(P_IS_SHOWN, "isShown")
  WXJS_READONLY_PROPERTY(P_IS_SORTKEY, "isSortKet")
  WXJS_READONLY_PROPERTY(P_IS_SORT_ORDER_ASCENDLING, "isSortOrderAscendling")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxHeaderColumn, HeaderColumn)
	switch (id) 
	{
	case P_TITLE:
		ToJSVal(cx, vp, p->GetTitle());
		break;
	case P_BITMAP:
		vp.set( Bitmap::CreateObject(cx, new wxBitmap(p->GetBitmap())) );
		break;
	case P_WIDTH:
		ToJSVal(cx, vp, p->GetWidth());
		break;
	case P_MINWIDTH:
		ToJSVal(cx, vp, p->GetMinWidth());
		break;
	case P_ALIGNMENT:
		ToJSVal(cx, vp, (int)p->GetAlignment());
		break;
	case P_FLAGS:
		ToJSVal(cx, vp, p->GetFlags());
		break;
	case P_IS_RESIZEABLE:
		ToJSVal(cx, vp, p->IsResizeable());
		break;
	case P_IS_REORDERABLE:
		ToJSVal(cx, vp, p->IsReorderable());
		break;
	case P_IS_HIDDEN:
		ToJSVal(cx, vp, p->IsHidden());
		break;
	case P_IS_SORTABLE:
		ToJSVal(cx, vp, p->IsSortable());
		break;
	case P_IS_SHOWN:
		ToJSVal(cx, vp, p->IsShown());
		break;
	case P_IS_SORTKEY:
		ToJSVal(cx, vp, p->IsSortKey());
		break;
	case P_IS_SORT_ORDER_ASCENDLING:
		ToJSVal(cx, vp, p->IsSortOrderAscending());
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxHeaderColumn, HeaderColumn)

	//switch (id) 
	//{
	//case P_FLAG:
	//	{
	//		int value = 0;
	//		if ( FromJS(cx, vp, value) )
	//		{

	//		}
	//	}
	//	break;
	//}
	return true;
WXJS_END_SET_PROP


WXJS_BEGIN_CONSTRUCTOR(wxHeaderColumn, HeaderColumn)
	JS_ReportError(cx, "HeaderColumn is abstruct class.");
	return NULL;
WXJS_END_CONSTRUCTOR

	
WXJS_BEGIN_DESTRUCTOR(wxHeaderColumn, HeaderColumn)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(HeaderColumn)
	WXJS_METHOD("hasFlag", hasFlag, 1)
WXJS_END_METHOD_MAP()



JSBool HeaderColumn::hasFlag(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		

    wxHeaderColumn *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int flag = false;

	// 1.
    if ( ! FromJS(cx, argv[0], flag) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	
	// –ß‚è’l
	vp->setBoolean(
		p->HasFlag(flag)	
	);
	
	return JS_TRUE;
}


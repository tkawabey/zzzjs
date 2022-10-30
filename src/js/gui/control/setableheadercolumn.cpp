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
#include "js/gui/misc/bitmap.h"
#include "js/gui/errors.h"
#include "js/gui/control/headercolumn.h"
#include "js/gui/control/setableheadercolumn.h"




using namespace zzzJs;
using namespace zzzJs::gui;



//--------------------------------------------------------
//	SettableHeaderColumn
//--------------------------------------------------------
WXJS_INIT_CLASS(SettableHeaderColumn, "SettableHeaderColumn", 1)


WXJS_BEGIN_PROPERTY_MAP(SettableHeaderColumn)
  WXJS_READONLY_PROPERTY(P_TITLE, "title")
  WXJS_READONLY_PROPERTY(P_BITMAP, "bitmap")
  WXJS_READONLY_PROPERTY(P_WIDTH, "width")
  WXJS_READONLY_PROPERTY(P_MINWIDTH, "minWidth")
  WXJS_READONLY_PROPERTY(P_ALIGNMENT, "alignment")
  WXJS_READONLY_PROPERTY(P_FLAGS, "flags")
  WXJS_READONLY_PROPERTY(P_FLAG, "flag")
  WXJS_READONLY_PROPERTY(P_RESIZEABLE, "resizeAble")
  WXJS_READONLY_PROPERTY(P_SORTABLE, "sortAble")
  WXJS_READONLY_PROPERTY(P_REORDERABLE, "reorderAble")
  WXJS_READONLY_PROPERTY(P_HIDDEN, "hidden")
  WXJS_READONLY_PROPERTY(P_SORT_ORDER, "sortOrder")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxSettableHeaderColumn, SettableHeaderColumn)
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
	case P_RESIZEABLE:
		ToJSVal(cx, vp, p->IsResizeable());
		break;
	case P_REORDERABLE:
		ToJSVal(cx, vp, p->IsReorderable());
		break;
	case P_HIDDEN:
		ToJSVal(cx, vp, p->IsHidden());
		break;
	case P_SORT_ORDER:
		ToJSVal(cx, vp, p->IsSortOrderAscending());
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxSettableHeaderColumn, SettableHeaderColumn)

	switch (id) 
	{
	case P_TITLE:
		{
			wxString value;
			if ( FromJS(cx, vp, value) )
			{
				p->SetTitle( value );
			}
		}
		break;
	case P_BITMAP:
		{
			zzzJsPtr<wxBitmap> apBitmap;
			if( apBitmap.set(Bitmap::getObject2Instance(cx, vp, apBitmap.bAllocation)) == true ) {
				p->SetBitmap( *(apBitmap.get()) );
			}
		}
		break;
	case P_WIDTH:
		{
			int value;
			if ( FromJS(cx, vp, value) )
			{
				p->SetWidth( value );
			}
		}
		break;
	case P_MINWIDTH:
		{
			int value;
			if ( FromJS(cx, vp, value) )
			{
				p->SetMinWidth( value );
			}
		}
		break;
	case P_ALIGNMENT:
		{
			int value;
			if ( FromJS(cx, vp, value) )
			{
				p->SetAlignment( (wxAlignment )value );
			}
		}
		break;
	case P_FLAGS:
		{
			int value;
			if ( FromJS(cx, vp, value) )
			{
				p->SetFlags( value );
			}
		}
		break;
	case P_FLAG:
		{
			int value;
			if ( FromJS(cx, vp, value) )
			{
				p->SetFlag ( value );
			}
		}
		break;
	case P_RESIZEABLE:
		{
			bool value;
			if ( FromJS(cx, vp, value) )
			{
				p->SetResizeable( value );
			}
		}
		break;
	case P_HIDDEN:
		{
			bool value;
			if ( FromJS(cx, vp, value) )
			{
				p->SetHidden( value );
			}
		}
		break;
	case P_SORT_ORDER:
		{
			bool value;
			if ( FromJS(cx, vp, value) )
			{
				p->SetSortOrder( value );
			}
		}
		break;
	}
	return true;
WXJS_END_SET_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxSettableHeaderColumn, SettableHeaderColumn)
	HeaderColumn::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_CONSTRUCTOR(wxSettableHeaderColumn, SettableHeaderColumn)
	JS_ReportError(cx, "SettableHeaderColumn is abstruct class.");
	return NULL;
WXJS_END_CONSTRUCTOR

	
WXJS_BEGIN_DESTRUCTOR(wxSettableHeaderColumn, SettableHeaderColumn)

WXJS_END_DESTRUCTOR




WXJS_BEGIN_METHOD_MAP(SettableHeaderColumn)
	WXJS_METHOD("changeFlag", changeFlag, 2)
	WXJS_METHOD("clearFlag", clearFlag, 1)
	WXJS_METHOD("toggleFlag", toggleFlag, 2)
	WXJS_METHOD("unsetAsSortKey", unsetAsSortKey, 0)
	WXJS_METHOD("toggleSortOrder", toggleSortOrder, 0)
WXJS_END_METHOD_MAP()



JSBool SettableHeaderColumn::changeFlag(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		

    wxSettableHeaderColumn *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int flag = 0;
	int bSet = false;

	// 1.
    if ( ! FromJS(cx, argv[0], flag) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	// 2.
    if ( ! FromJS(cx, argv[1], bSet) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Boolean");
        return JS_FALSE;
    }
	
	// 戻り値
	p->ChangeFlag (flag, bSet);
	
	return JS_TRUE;
}

JSBool SettableHeaderColumn::clearFlag(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		

    wxSettableHeaderColumn *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int flag = 0;

	// 1.
    if ( ! FromJS(cx, argv[0], flag) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	
	// 戻り値
	p->ClearFlag (flag);
	
	return JS_TRUE;
}

JSBool SettableHeaderColumn::toggleFlag(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		

    wxSettableHeaderColumn *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	int flag = 0;

	// 1.
    if ( ! FromJS(cx, argv[0], flag) )
    {
        JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
        return JS_FALSE;
    }
	
	// 戻り値
	p->ToggleFlag (flag);
	
	return JS_TRUE;
}

JSBool SettableHeaderColumn::unsetAsSortKey(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		

    wxSettableHeaderColumn *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	// 戻り値
	p->UnsetAsSortKey ();
	
	return JS_TRUE;
}

JSBool SettableHeaderColumn::toggleSortOrder(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
		

    wxSettableHeaderColumn *p = GetPrivate(cx, obj);
	if( p == NULL ) {
		return JS_FALSE;
	}
	
	// 戻り値
	p->ToggleSortOrder ();
	
	return JS_TRUE;
}


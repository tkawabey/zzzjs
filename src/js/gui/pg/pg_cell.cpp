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
#include "js/gui/pg/pg_cell.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/font.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



//--------------------------------------------------------
//	Cell
//--------------------------------------------------------
WXJS_INIT_CLASS(Cell, "Cell", 1)
	
// プロパティー
WXJS_BEGIN_PROPERTY_MAP(Cell)
  WXJS_PROPERTY(P_TEXT, "text")
  WXJS_READONLY_PROPERTY(P_HAS_TEXT, "hasText")
  WXJS_PROPERTY(P_BITMAP, "bitmap")
  WXJS_PROPERTY(P_FG_COLOR, "fgColor")
  WXJS_PROPERTY(P_BG_COLOR, "bgColor")
  WXJS_PROPERTY(P_FG_FONT, "font")
WXJS_END_PROPERTY_MAP()

// プロパティー get の実装
WXJS_BEGIN_GET_PROP(wxPGCell, Cell)
	switch (id) 
	{
	case P_TEXT:
		ToJSVal(cx, vp, p->GetText());
		break;
	case P_HAS_TEXT:
		ToJSVal(cx, vp, p->HasText());
		break;
	case P_BITMAP:
		{
			const wxBitmapBundle& bundle = p->GetBitmap();
			
			wxBitmap bmp = bundle.GetBitmap(bundle.GetDefaultSize()); //p->GetBitmap();
			if(bmp.IsOk() ) {
				Bitmap::CreateObject(cx, new wxBitmap(bmp));
			} else {
				vp.setUndefined();
			}
		}
		break;
	case P_FG_COLOR:
		{
			wxColour fgc = p->GetFgCol ();
			if(fgc.IsOk() ) {
				Colour::CreateObject(cx, new wxColour(fgc));
			} else {
				vp.setUndefined();
			}
		}
		break;
	case P_BG_COLOR:
		{
			wxColour fgc = p->GetBgCol();
			if(fgc.IsOk() ) {
				Colour::CreateObject(cx, new wxColour(fgc));
			} else {
				vp.setUndefined();
			}
		}
		break;
	case P_FG_FONT:
		{
			wxFont fv = p->GetFont();
			if(fv.IsOk() ) {
				Font::CreateObject(cx, new wxFont(fv));
			} else {
				vp.setUndefined();
			}
		}
		break;
	}
	return true;
WXJS_END_GET_PROP

// プロパティー set の実装
WXJS_BEGIN_SET_PROP(wxPGCell, Cell)
{
	switch (id) 
	{
	case P_TEXT:
		{
			wxString val;
			if( FromJS(cx, vp, val) == false ) {
				return false;
			}
			p->SetText( val );
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
	case P_FG_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetFgCol( *(apColour.get()) );
			}
		}
		break;
	case P_BG_COLOR:
		{
			zzzJsPtr<wxColour> apColour;
			if( apColour.set( Colour::getObject2Instance(cx, vp, apColour.bAllocation) ) == true ) 
			{
				p->SetBgCol( *(apColour.get()) );
			}
		}
		break;
	case P_FG_FONT:
		{
			zzzJsPtr<wxFont> apFont;
			if( ZZZJS_PROP_GET_AP(apFont, Font, vp) == true ) {
				p->SetFont( *(apFont.get()) );
			}
		}
		break;
	}
	return true;
}
WXJS_END_SET_PROP

// コンストラクタ
WXJS_BEGIN_CONSTRUCTOR(wxPGCell, Cell)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	Cell *p = NULL;

	
	if( argc == 0 ) {
		p = new Cell();
		return new Cell();
	} 
		
	int argIndex = 0;
	wxString text(_T(""));
//	wxColour fgCol  = wxNullColour;
//	wxColour bgCol  = wxNullColour;
	zzzJsPtr<wxColour> apfgCol(NULL, &wxNullColour);
	zzzJsPtr<wxColour> apbgCol(NULL, &wxNullColour);
	zzzJsPtr<wxBitmap> apBitmap;

	if( argv[argIndex].isString() == true ) {
		if( argc > 4 ) {
			argc = 4;
		}
		argIndex = argc - 1;
		switch( argc ) {
		case 4:
			if( !(argv[argIndex].isNull() || argv[argIndex].isUndefined()) ) {
//				wxColour* pColor = Colour::GetPrivate(cx, argv[argIndex], false);
//				if( pColor != NULL ) {
				if( ZZZJS_ARG_GET_AP(apfgCol, Colour ) == false ) {
					//.set( Colour::getObject2Instance(cx, argv[argIndex], apfgCol.bAllocation) ) == false ) 
					JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Color");
					return NULL;
				}
//				bgCol = *pColor;
			}
			argIndex--;
		case 3:
			if( !(argv[argIndex].isNull() || argv[argIndex].isUndefined()) ) {
//				wxColour* pColor = Colour::GetPrivate(cx, argv[argIndex], false);
//				if( pColor != NULL ) {
				if( ZZZJS_ARG_GET_AP(apbgCol, Colour ) == false ) {
					JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Color");
					return NULL;
				}
//				fgCol = *pColor;
			}
			argIndex--;
		case 2:
			if( !(argv[argIndex].isNull() || argv[argIndex].isUndefined()) ) {
				if( ZZZJS_ARG_GET_AP(apBitmap, Bitmap) == false ) {
					JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "Bitmap");
					return NULL;
				}
			}
			argIndex--;
		}
		
		argIndex = 0;
		// 0
		if( FromJS(cx, argv[0], text) == false ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
			return NULL;
		}
		p = new Cell(text, apBitmap.get() != NULL ? *(apBitmap.get()) : wxNullBitmap, *(apfgCol.get()), *(apbgCol.get()));
	}
	else 
	if( argv[0].isObject() == true ) {
		wxPGCell* pCell = Cell::GetPrivate(cx, argv[0]);
		if( pCell == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Cell");
			return JS_FALSE;
		}
		p = new Cell(*pCell);
	} else {
			JS_ReportError(cx, "invalid arguments.");
		return NULL;
	}


	return p;
}
WXJS_END_CONSTRUCTOR

// デストラクタ
WXJS_BEGIN_DESTRUCTOR(wxPGCell, Cell)
{
	if( p->IsKindOf( CLASSINFO(Cell) ) ) {
		delete p;
	}
}
WXJS_END_DESTRUCTOR
	


// メソッドの定義
WXJS_BEGIN_METHOD_MAP(Cell)
	WXJS_METHOD("setEmptyData", setEmptyData, 0)
	WXJS_METHOD("mergeFrom", mergeFrom, 1)
WXJS_END_METHOD_MAP()

JSBool Cell::setEmptyData(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGCell *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	p->SetEmptyData();

	return JS_TRUE;
}


JSBool Cell::mergeFrom(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGCell *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	wxPGCell* pCell = Cell::GetPrivate(cx, argv[0]);
	if( pCell == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Cell");
		return JS_FALSE;
	}

	p->MergeFrom(*pCell);

	return JS_TRUE;
}

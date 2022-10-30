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
#include "js/gui/misc/colour.h"
#include "js/gui/misc/font.h"
#include "js/gui/control/window.h"
#include "js/gui/control/setableheadercolumn.h"
#include "js/gui/errors.h"
#include "js/gui/dataview/dataviewcolmn.h"
#include "js/gui/dataview/dataviewctrl.h"
#include "js/gui/dataview/dataviewrender.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;


//--------------------------------------------------------
//	DataViewColumn
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewColumn, "DataViewColumn", 0)


/***
 * <properties>
 *  <property name="bitmapDisabled" type="@wxBitmap">Bitmap to show when the button is disabled.</property>
 *  <property name="bitmapFocus" type="@wxBitmap">Bitmap to show when the button has the focus.</property>
 *  <property name="bitmapLabel" type="@wxBitmap">The default bitmap.</property>
 *  <property name="bitmapSelected" type="@wxBitmap">Bitmap to show when the button is selected.</property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(DataViewColumn)
  WXJS_PROPERTY(P_ModelColumn, "modelColumn")
  WXJS_PROPERTY(P_OWNER, "owner")
  WXJS_PROPERTY(P_RENDER, "render")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_PROP(wxDataViewColumn, DataViewColumn)
	switch (id) 
	{
	case P_ModelColumn:
		ToJSVal(cx, vp, p->GetModelColumn());
		break;
	case P_OWNER:
		{
			vp.set( DataViewCtrl::CreateObject(cx, p->GetOwner()) );
		}
		break;
	case P_RENDER:
		{
			vp.set( DataViewRenderer::CreateObject(cx, p->GetRenderer()) );
		}
		break;
	}
	return true;
WXJS_END_GET_PROP

WXJS_BEGIN_SET_PROP(wxDataViewColumn, DataViewColumn)
	//switch (id) 
	//{
	//case P_BOLD:
	//	{
	//		bool value = false;
	//		if ( FromJS(cx, vp, value) )
	//		{
	//			p->SetBold( value );
	//		}
	//	}
	//	break;
	//}
	return true;
WXJS_END_SET_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxDataViewColumn, DataViewColumn)
	SettableHeaderColumn::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_CONSTRUCTOR(wxDataViewColumn, DataViewColumn)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxString label;
	zzzJsPtr<wxBitmap> apBitmap;
	wxDataViewRenderer *renderer = NULL;
	unsigned int model_column = 0;
	int width = -1;
	int align = wxALIGN_CENTER;
	int flags = wxDATAVIEW_COL_RESIZABLE;
	int iOr = 0;
	wxDataViewColumn* p = NULL;
	
	
	if( argc > 6 ) {
		argc = 6;
	}
	switch( argc ) {
	case 6:
		if ( ! FromJS(cx, argv[5], flags) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 6, WXJS_TYPE_NUMBER);
			return NULL;
		}
	case 5:
		if ( ! FromJS(cx, argv[4], align) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 5, WXJS_TYPE_NUMBER);
			return NULL;
		}
	case 4:
		if ( ! FromJS(cx, argv[3], width) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, WXJS_TYPE_NUMBER);
			return NULL;
		}
	case 3:
		if ( ! FromJS(cx, argv[2], model_column) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return NULL;
		}
	default:
		// 2.
		renderer = DataViewRenderer::GetPrivate(cx, argv[1]);
		if ( ! FromJS(cx, argv[1], model_column) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, "DataViewRenderer");
			return NULL;
		}
		// 1.
		if( argv[0].isString() ) {
			iOr = 0;
			if ( ! FromJS(cx, argv[0], label) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
				return NULL;
			}
		} else {
			iOr = 1;
			if( apBitmap.set(Bitmap::getObject2Instance(cx, argv[0], apBitmap.bAllocation)) == false ) {
				return NULL;
			}
		}
	}
	if( iOr == 0 ) {
		p = new wxDataViewColumn(label, renderer, model_column, width, (wxAlignment)align, flags);
	} else {
		p = new wxDataViewColumn(*(apBitmap.get()), renderer, model_column, width, (wxAlignment)align, flags);
	}
	return p;
WXJS_END_CONSTRUCTOR

	
WXJS_BEGIN_DESTRUCTOR(wxDataViewColumn, DataViewColumn)

WXJS_END_DESTRUCTOR

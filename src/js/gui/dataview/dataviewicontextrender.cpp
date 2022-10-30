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
#include "js/gui/dataview/dataviewrender.h"
#include "js/gui/dataview/dataviewcustomrender.h"
#include "js/gui/dataview/dataviewicontextrender.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;



//--------------------------------------------------------
//	DataViewIconTextRenderer
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewIconTextRenderer, "DataViewIconTextRenderer", 0)



WXJS_BEGIN_GET_SET_STR_PROP(wxDataViewIconTextRenderer, DataViewIconTextRenderer)
	DataViewRenderer::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_CONSTRUCTOR(wxDataViewIconTextRenderer, DataViewIconTextRenderer)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxString				varianttype = wxDataViewIconTextRenderer::GetDefaultType();
	int				 		mode = wxDATAVIEW_CELL_EDITABLE;
	int 					align = wxDVR_DEFAULT_ALIGNMENT;
		
	if( argc > 3 ) {
		argc = 3;
	}
	switch( argc ) {
	case 3:
		if ( ! FromJS(cx, argv[2], align) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		break;
	case 2:
		if ( ! FromJS(cx, argv[1], mode) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		break;
	case 1:
		if ( ! FromJS(cx, argv[0], varianttype) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		break;
	}

	wxDataViewIconTextRenderer *p = new wxDataViewIconTextRenderer(varianttype, (wxDataViewCellMode)mode, align);
	
	return p;
WXJS_END_CONSTRUCTOR

	
WXJS_BEGIN_DESTRUCTOR(wxDataViewIconTextRenderer, DataViewIconTextRenderer)

WXJS_END_DESTRUCTOR



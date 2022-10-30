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
#include "js/gui/dataview/dataviewchoicebyindexrender.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;



//--------------------------------------------------------
//	DataViewChoiceByIndexRenderer
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewChoiceByIndexRenderer, "DataViewChoiceByIndexRenderer", 1)


WXJS_BEGIN_GET_SET_STR_PROP(wxDataViewChoiceByIndexRenderer, DataViewChoiceByIndexRenderer)
	DataViewRenderer::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_CONSTRUCTOR(wxDataViewChoiceByIndexRenderer, DataViewChoiceByIndexRenderer)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxArrayString			choices;
	int				 		mode = wxDATAVIEW_CELL_INERT;
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
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		break;
	default:
		{

			JSObject *objItems = JSVAL_TO_OBJECT(argv[0]);
			if (    objItems != (JSObject *) NULL
				 && JS_IsArrayObject(cx, objItems) )
			{
				uint32_t length = 0;
				JS_GetArrayLength(cx, objItems, &length);
				
				for(uint32_t i =0; i < length; i++)
				{
					wxString str;
					JS::Value element;
					JS_GetElement(cx, objItems, i, &element);
					zzzJs::FromJS(cx, element, str);

					choices.Add(str);
				}
			}
		}
		break;
	}



	wxDataViewChoiceByIndexRenderer *p = new wxDataViewChoiceByIndexRenderer(choices, (wxDataViewCellMode)mode, align);
	
	return p;
WXJS_END_CONSTRUCTOR

	
WXJS_BEGIN_DESTRUCTOR(wxDataViewChoiceByIndexRenderer, DataViewChoiceByIndexRenderer)

WXJS_END_DESTRUCTOR


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
#include "js/gui/dataview/dataviewchoicerender.h"




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;



//--------------------------------------------------------
//	DataViewChoiceRenderer
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewChoiceRenderer, "DataViewChoiceRenderer", 0)

void DataViewChoiceRenderer::InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto)
{

}

WXJS_BEGIN_GET_PROP(wxDataViewChoiceRenderer, DataViewChoiceRenderer)
	if ( id == P_Choices )
	{
		wxArrayString choices = p->GetChoices();

		JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
		JS::RootedObject jsvaArray(cx, objArray);
		for(size_t i = 0; i < choices.GetCount(); i++)
		{
			JS::Value element = ToJS(cx, choices.Item(i));
			JS_SetElement(cx, objArray, i, &element);
		}
		vp.setObjectOrNull(objArray);
	}
	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_ADD_PROP(wxDataViewChoiceRenderer, DataViewChoiceRenderer)
	return true;
WXJS_END_ADD_PROP
	
WXJS_BEGIN_DEL_PROP(wxDataViewChoiceRenderer, DataViewChoiceRenderer)
  return true;
WXJS_END_DEL_PROP



WXJS_BEGIN_GET_SET_STR_PROP(wxDataViewChoiceRenderer, DataViewChoiceRenderer)
	DataViewRenderer::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_CONSTRUCTOR(wxDataViewChoiceRenderer, DataViewChoiceRenderer)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxArrayString			choices;
	int				 		mode = wxDATAVIEW_CELL_INERT;
	int 					align = wxDVR_DEFAULT_ALIGNMENT;
		

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



	wxDataViewChoiceRenderer *p = new wxDataViewChoiceRenderer(choices, (wxDataViewCellMode)mode, align);
	
	return p;
WXJS_END_CONSTRUCTOR

	
WXJS_BEGIN_DESTRUCTOR(wxDataViewChoiceRenderer, DataViewChoiceRenderer)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(DataViewChoiceRenderer)
  WXJS_METHOD("getChoice", getChoice, 1)
WXJS_END_METHOD_MAP()



JSBool DataViewChoiceRenderer::getChoice(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxDataViewChoiceRenderer *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;


	int index = 0;

	if( zzzJs::FromJS(cx, argv[0], index) == false ) {
		return JS_FALSE;
	}

	*vp = ToJS(cx, p->GetChoice(index) );

  return JS_TRUE;
}
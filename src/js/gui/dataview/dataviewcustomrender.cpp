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




using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::dataview;



//--------------------------------------------------------
//	DataViewCustomRenderer
//--------------------------------------------------------
WXJS_INIT_CLASS(DataViewCustomRenderer, "DataViewCustomRenderer", 0)

void DataViewCustomRenderer::InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto)
{

}

WXJS_BEGIN_GET_PROP(wxDataViewCustomRenderer, DataViewCustomRenderer)
	if ( id == P_Choices )
	{
	}
	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_ADD_PROP(wxDataViewCustomRenderer, DataViewCustomRenderer)
	return true;
WXJS_END_ADD_PROP
	
WXJS_BEGIN_DEL_PROP(wxDataViewCustomRenderer, DataViewCustomRenderer)
  return true;
WXJS_END_DEL_PROP



WXJS_BEGIN_GET_SET_STR_PROP(wxDataViewCustomRenderer, DataViewCustomRenderer)
	DataViewRenderer::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_CONSTRUCTOR(wxDataViewCustomRenderer, DataViewCustomRenderer)

	JS_ReportError(cx, "DataViewCustomRenderer is abstruct class.");
	
	return NULL;
WXJS_END_CONSTRUCTOR

	
WXJS_BEGIN_DESTRUCTOR(wxDataViewCustomRenderer, DataViewCustomRenderer)

WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(DataViewCustomRenderer)
  WXJS_METHOD("getChoice", getChoice, 1)
WXJS_END_METHOD_MAP()



JSBool DataViewCustomRenderer::getChoice(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxDataViewCustomRenderer *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

/*
	int index = 0;

	if( zzzJs::FromJS(cx, argv[0], index) == false ) {
		return JS_FALSE;
	}

	*vp = ToJS(cx, p->GetChoice(index) );*/

  return JS_TRUE;
}
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
#include "js/gui/pg/pg_evt_grid.h"
#include "js/gui/pg/pg_prop.h"
#include "js/gui/event/command.h"
#include <wx/propgrid/propgrid.h>



using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;



WXJS_INIT_CLASS(GridEvent, "GridEvent", 0)
	
WXJS_BEGIN_PROPERTY_MAP(GridEvent)
    WXJS_PROPERTY(P_CAN_VETO, "canVeto")
    WXJS_READONLY_PROPERTY(P_COLUMN, "column")
    WXJS_READONLY_PROPERTY(P_MAIN_PARENT, "mainParent")
    WXJS_PROPERTY(P_PROPERTY, "property")
    WXJS_PROPERTY(P_VALIDATION_FAILURE_BEHAVIOR, "validationFailureBehavior")
    WXJS_PROPERTY(P_VALIDATION_FAILURE_MESSAGE, "validationFailureMessage")
    WXJS_READONLY_PROPERTY(P_PROPERTY_NAME, "propertyName")
	WXJS_READONLY_PROPERTY(P_PROPERTY_VALUE, "propertyValue")
	WXJS_PROPERTY(P_VETO, "veto")
WXJS_END_PROPERTY_MAP()



bool GridEvent::GetProperty(PrivGridEvent *p, 
                                  JSContext *cx, 
                                  JSObject *obj, 
                                  int id, 
                                  JS::MutableHandle<JS::Value>& vp)
{
    wxPropertyGridEvent *event = p->GetEvent();
	
	switch (id) 
	{
    case P_CAN_VETO:
        ToJSVal(cx, vp, event->CanVeto());
        break;
    case P_COLUMN:
		ToJSVal(cx, vp, event->GetColumn());
        break;
    case P_MAIN_PARENT:
		{
			wxPGProperty* pProp = event->GetMainParent();
			if( pProp == NULL ) {
				vp.setNull();
			} else {
				vp.set( Property::CreateObject(cx, pProp, NULL) );
			}
		}
        break;
    case P_PROPERTY:
		{
			wxPGProperty* pProp = event->GetProperty();
			if( pProp == NULL ) {
				vp.setNull();
			} else {
				vp.set( Property::CreateObject(cx, pProp, NULL) );
			}
		}
        break;
    case P_VALIDATION_FAILURE_BEHAVIOR:
		ToJSVal(cx, vp, (unsigned int)event->GetValidationFailureBehavior ());
        break;
    case P_PROPERTY_NAME:
		ToJSVal(cx, vp, event->GetPropertyName());
        break;
    case P_PROPERTY_VALUE:
		ToJSVal(cx, vp, event->GetPropertyValue());
        break;
    case P_VETO:
		ToJSVal(cx, vp, event->WasVetoed());
        break;
	}
	return true;
}

bool GridEvent::SetProperty(PrivGridEvent *p, 
                                  JSContext *cx, 
                                  JSObject *obj, 
                                  int id, 
                                  JS::MutableHandle<JS::Value>& vp)
{
    wxPropertyGridEvent *event = p->GetEvent();
	
	switch (id) 
	{
    case P_CAN_VETO:
		{
			bool val;
			if( FromJS(cx, vp, val) == true ) {
				event->SetCanVeto( val );
			}
		}
        break;
    case P_PROPERTY:
		{
			wxPGProperty* pProp = Property::GetPrivate(cx, vp, false);
			if( pProp != NULL ) {
				event->SetProperty( pProp );
			}
		}
        break;
    case P_VALIDATION_FAILURE_BEHAVIOR:
		{
			unsigned int val;
			if( FromJS(cx, vp, val) == true ) {
				event->SetValidationFailureBehavior( val );
			}
		}
        break;
    case P_VALIDATION_FAILURE_MESSAGE:
		{
			wxString val;
			if( FromJS(cx, vp, val) == true ) {
				event->SetValidationFailureMessage( val );
			}
		}
        break;
    case P_VETO:
		{
			bool val;
			if( FromJS(cx, vp, val) == true ) {
				event->Veto( val );
			}
		}
        break;
	}
	return true;
}
	
WXJS_BEGIN_GET_SET_STR_PROP(PrivGridEvent, GridEvent)
	CommandEvent::SetStringProperty((PrivCommandEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP




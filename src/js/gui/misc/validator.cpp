/*
 * wxJavaScript - validator.cpp
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
 * $Id: validator.cpp 784 2007-06-25 18:34:22Z fbraem $
 */
// validator.cpp
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
#include "js/common/jsutil.h"
#include "js/gui/misc/validate.h"
#include "js/gui/control/window.h"

using namespace zzzJs;
using namespace zzzJs::gui;

Validator::Validator() : wxValidator()
{
}

Validator::Validator(const Validator &copy) : wxValidator()
{
  JavaScriptClientData *data 
    = dynamic_cast<JavaScriptClientData*>(copy.GetClientObject());
  if ( data != NULL )
  {
    SetClientObject(new JavaScriptClientData(*data));
    data->Protect(false);
  }
}

bool Validator::TransferToWindow()
{
  JavaScriptClientData *data
    = dynamic_cast<JavaScriptClientData*>(GetClientObject());
  if ( data == NULL )
    return true;

  JSContext *cx = data->GetContext();
  JSObject *obj = data->GetObject();

  jsval fval;
  if ( GetFunctionProperty(cx, obj, "transferToWindow", &fval) == JS_TRUE )
  {
    jsval rval;
    if ( JS_CallFunctionValue(cx, obj, fval, 0, NULL, &rval) == JS_FALSE )
    {
      if ( JS_IsExceptionPending(cx) )
      {
          JS_ReportPendingException(cx);
      }
      return false;
    }
    else
    {
      return JSVAL_IS_BOOLEAN(rval) ? JSVAL_TO_BOOLEAN(rval) == JS_TRUE : false;
    }
  }

  return true;
}

bool Validator::TransferFromWindow()
{
  JavaScriptClientData *data
    = dynamic_cast<JavaScriptClientData*>(GetClientObject());
  if ( data == NULL )
    return true;

  JSContext *cx = data->GetContext();
  JSObject *obj = data->GetObject();

  jsval fval;
  if ( GetFunctionProperty(cx, obj, "transferFromWindow", &fval) == JS_TRUE )
  {
    jsval rval;
    if ( JS_CallFunctionValue(cx, obj, fval, 0, NULL, &rval) == JS_FALSE )
    {
      if ( JS_IsExceptionPending(cx) )
      {
        JS_ReportPendingException(cx);
      }
      return false;
    }
    else
    {
      return JSVAL_IS_BOOLEAN(rval) ? JSVAL_TO_BOOLEAN(rval) == JS_TRUE : false;
    }
  }
  return true;
}

bool Validator::Validate(wxWindow *parent)
{
  JavaScriptClientData *data
    = dynamic_cast<JavaScriptClientData*>(GetClientObject());
  if ( data == NULL )
    return true;

  JSContext *cx = data->GetContext();
  JSObject *obj = data->GetObject();

  JavaScriptClientData *parentData = NULL;
  if ( parent != NULL )
  {
    parentData = dynamic_cast<JavaScriptClientData*>(parent->GetClientObject());
  }

  jsval fval;
  if ( GetFunctionProperty(cx, obj, "validate", &fval) == JS_TRUE )
  {
    jsval argv[] = 
    { 
      parentData == NULL ? JSVAL_VOID 
                         : OBJECT_TO_JSVAL(parentData->GetObject()) 
    };

	jsval rval;
	if ( JS_CallFunctionValue(cx, obj, fval, 1, argv, &rval) == JS_FALSE )
	{
      if ( JS_IsExceptionPending(cx) )
      {
          JS_ReportPendingException(cx);
      }
	  return false;
	}
	else
    {
	  return JSVAL_IS_BOOLEAN(rval) ? JSVAL_TO_BOOLEAN(rval) == JS_TRUE : false;
    }
  }

	return false;
}

/***
 * <file>misc/validator</file>
 * <module>gui</module>
 * <class name="wxValidator">
 *  Use wxValidator to create your own validators.  
 * </class>
 */

ZZZJS_INIT_CLASS(Validator, "Validator", 0)

/***
 * <properties>
 *  <property name="bellOnError" type="Boolean" />
 *  <property name="transferFromWindow" type="Function">
 *   Assign a function to this property that transfers the content of the window
 *   to a variable. You must return true on success, false on failure. 
 *  </property>
 *  <property name="transferToWindow" type="Function">
 *   Assign a function to this property that transfers the variable to the window.
 *   You must return true on success, false on failure. 
 *  </property>
 *  <property name="validate" type="Function">
 *   Assign a function to this property that checks the content of the associated window. The function
 *   can have one argument: the parent of the associated window. This function should return false
 *   when the content is invalid, true when it is valid.
 *  </property>
 *  <property name="window" type="@wxWindow">
 *   The window associated with this validator.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(Validator)
	ZZZJS_PROPERTY(P_WINDOW, "window")
	ZZZJS_PROPERTY(P_BELL_ON_ERROR, "bellOnError")
ZZZJS_END_PROPERTY_MAP()

//bool Validator::GetProperty(wxValidator *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxValidator, Validator)
{
  switch (id) 
  {
  case P_BELL_ON_ERROR:
    ToJSVal(cx, vp, p->IsSilent());
    break;
  case P_WINDOW:
    {
      wxWindow *win = p->GetWindow();
      if ( win != NULL )
      {
        JavaScriptClientData *data
          = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
		if( data == NULL ) {
			vp.setNull();
		} else {
			vp.set( OBJECT_TO_JSVAL(data->GetObject()) );
		}
//        *vp = data == NULL ? JSVAL_VOID 
 //                          : OBJECT_TO_JSVAL(data->GetObject());
      }
      break;
    }
  }
  return true;
}
ZZZJS_END_GET_PROP

//bool Validator::SetProperty(wxValidator *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_SET_PROP(wxValidator, Validator)
{
    switch (id) 
	{
	case P_BELL_ON_ERROR:
		{
			bool bell;
			if ( FromJS(cx, vp, bell) ) {
//				p->SetBellOnError(bell);
				p->SuppressBellOnError( bell );
			}
			break;
		}
	case P_WINDOW:
        {
            wxWindow *win = Window::GetPrivate(cx, vp);
            if ( win != NULL )
				p->SetWindow(win);
		}
		break;
	}
    
	return true;
}
ZZZJS_END_SET_PROP

/**
 * <ctor>
 *  <function />
 *  <desc>
 *   Constructs a new wxValidator object
 *  </desc>
 * </ctor>
 */
//wxValidator *Validator::Construct(JSContext *cx,
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);

ZZZJS_BEGIN_CONSTRUCTOR(wxValidator, Validator)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	Validator *v = new Validator();
	v->SetClientObject(new JavaScriptClientData(cx, obj, false, true));
	return v;
}
ZZZJS_END_CONSTRUCTOR

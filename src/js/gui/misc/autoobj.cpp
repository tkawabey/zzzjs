/*
 * wxJavaScript - autoobj.cpp
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
 * $Id: autoobj.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// wxJSAutomationObject.cpp
#include "precompile.h"
#ifdef __WXMSW__


#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <wx/msw/ole/automtn.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/gui/misc/autoobj.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>misc/autoobj</file>
 * <module>gui</module>
 * <class name="wxAutomationObject">
 *  The wxAutomationObject class represents an OLE automation object containing 
 *  a single data member, an IDispatch pointer. It contains a number of functions
 *  that make it easy to perform automation operations, and set and get properties. 
 *  The wxVariant class will not be ported, because wxJS translates every type to
 *  the corresponding JavaScript type.
 *  This class is only available on a Windows platform.
 * </class>
 */
ZZZJS_INIT_CLASS(AutomationObject, "AutomationObject", 0)

/***
 * <ctor>
 *  <function />
 *  <desc>
 *   Constructs a new wxAutomationObject object. Unlike
 *   wxWidgets, this constructor can't take an 
 *   IDispatch pointer because this type can't be used in
 *   JavaScript.
 *  </desc>
 * </ctor>
 */
ZZZJS_BEGIN_CONSTRUCTOR(wxAutomationObject, AutomationObject)
{
    return new wxAutomationObject();
}
ZZZJS_END_CONSTRUCTOR

	
ZZZJS_BEGIN_DESTRUCTOR(wxAutomationObject, AutomationObject)
{
    p->SetDispatchPtr(NULL);
    delete p;
}
ZZZJS_END_DESTRUCTOR

ZZZJS_BEGIN_METHOD_MAP(AutomationObject)
    ZZZJS_METHOD("callMethod", callMethod, 1)
    ZZZJS_METHOD("createInstance", createInstance, 1)
    ZZZJS_METHOD("getInstance", getInstance, 1)
    ZZZJS_METHOD("getObject", getObject, 2)
    ZZZJS_METHOD("getProperty", getProperty, 1)
    ZZZJS_METHOD("putProperty", putProperty, 2)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="callMethod">
 *  <function returns="Any">
 *   <arg name="Method" type=WXJS_TYPE_STRING>
 *    The name of the method to call.
 *   </arg>
 *   <arg name="Arg1" type="...">
 *    A variable list of arguments passed to the method.
 *   </arg>
 *  </function>
 *  <desc>
 *  Calls an automation method for this object. When the method
 *  returns a value it is not returned as a wxVariant but it is converted
 *  to its corresponding JavaScript type.
 *  <br /><br />
 *  The following example opens a workbook into Microsoft Excel:
 *  <pre><code class="whjs">
 *   var objExcel = new wxAutomationObject();
 *
 *   if ( objExcel.createInstance("Excel.Application") )
 *   {
 *      objExcel.putProperty("visible", true);
 *      var objBooks = new wxAutomationObject();
 *      objExcel.getObject(objBooks, "workbooks");
 *      objBooks.callMethod("open", "c:\\temp\\wxjs.xls");
 *   }
 *  </code></pre>
 *  The name of the method can contain dot-separated property names,
 *  to save the application needing to call @wxAutomationObject#getProperty
 *  several times using several temporary objects.
 *  For example:
 *  <code class="whjs">objExcel.callMethod("workbooks.open", "c:\\temp\\wxjs.xls");</code>
 *  </desc>
 * </method>
 */
//JSBool AutomationObject::callMethod(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(AutomationObject, callMethod )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxAutomationObject *p = GetPrivate(cx, obj);
	ZZZJS_CHECK_PRIM_NULL(p);

	/*
		wxVariant 	CallMethod (const wxString &method, int noArgs, wxVariant args[]) const
 			Calls an automation method for this object. More...
	*/	
	unsigned argIndex = 0;
    wxString method;

	// 0:method
    if( FromJS(cx, argv[argIndex], method) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}

    wxVariant res;
    if ( argc == 0 )
    {
		*vp = CreateJSVal(cx, p->CallMethod(method));
    }
    else
    {
        const wxVariant **vars = new const wxVariant*[argc - 1];
        unsigned i;
        for(i = 1; i < argc; i++)
        {
            vars[i-1] = CreateVariant(cx, argv[i]);
        }

        *vp = CreateJSVal(cx, p->CallMethodArray(method, argc - 1, vars));

        for(i = 0; i < argc - 1; i++)
            delete vars[i];
        delete[] vars;
    }
    
    return JS_TRUE;
}
ZZZJS_END_METHOD

/***
 * <method name="createInstance">
 *  <function returns="Boolean">
 *   <arg name="classId" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Creates a new object based on the class id, returning true if the
 *   object was successfully created, or false if not.
 *   <br /><br />
 *  The following example starts Microsoft Excel:
 *  <pre><code class="whjs">
 *  var obj = new wxAutomationObject();
 *  if ( obj.createInstance("Excel.Application") )
 *  {
 *    // Excel object is created
 *  }
 *  </code></pre>
 *  </desc>   
 * </method>
 */
//JSBool AutomationObject::createInstance(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(AutomationObject, createInstance )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxAutomationObject *p = GetPrivate(cx, obj);
	ZZZJS_CHECK_PRIM_NULL(p);
	
	unsigned argIndex = 0;
    wxString classId;
    if ( FromJS(cx, argv[argIndex], classId) == false )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	*vp = ToJS(cx, p->CreateInstance(classId));
	return JS_TRUE;
}
ZZZJS_END_METHOD

/***
 * <method name="getInstance">
 *  <function returns="Boolean">
 *   <arg name="classId" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *  Retrieves the current object associated with a class id, and attaches 
 *  the IDispatch pointer to this object. Returns true if a pointer was 
 *  successfully retrieved, false otherwise.
 *  </desc>
 * </method>
 */
//JSBool AutomationObject::getInstance(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(AutomationObject, getInstance )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxAutomationObject *p = GetPrivate(cx, obj);
	ZZZJS_CHECK_PRIM_NULL(p);
	
	unsigned argIndex = 0;
    wxString classId;


    if ( FromJS(cx, argv[argIndex], classId) == false )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	*vp = ToJS(cx, p->GetInstance(classId));
	return JS_TRUE;
}
ZZZJS_END_METHOD

/***
 * <method name="putProperty">
 *  <function returns="Boolean">
 *   <arg name="Property" type=WXJS_TYPE_STRING>
 *    The name of the property.
 *   </arg>
 *   <arg name="Arg1" type="..." />
 *  </function>
 *  <desc>
 *   Puts a property value into this object.
 *   The following example starts Microsoft Excel and makes it visible.
 *   <pre><code class="whjs">
 *  var obj = new wxAutomationObject();
 *  if ( obj.createInstance("Excel.Application") )
 *  {
 *     obj.putProperty("visible", true);
 *  }
 *  </code></pre>
 *  The name of the property can contain dot-separated property names,
 *  to save the application needing to call @wxAutomationObject#getProperty
 *  several times using several temporary objects.
 *  </desc>
 * </method>
 */
//JSBool AutomationObject::putProperty(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(AutomationObject, putProperty )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxAutomationObject *p = GetPrivate(cx, obj);
	ZZZJS_CHECK_PRIM_NULL(p);
	
	unsigned argIndex = 0;
    wxString prop;


	
	// 0:prop
    if( FromJS(cx, argv[argIndex], prop) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;

    const wxVariant **vars = new const wxVariant*[argc - 1];
    for(; argIndex < argc; argIndex++)
    {
        vars[argIndex-1] = CreateVariant(cx, argv[argIndex]);
    }

    wxVariant res = p->PutPropertyArray(prop, argc - 1, vars);
	argIndex = 0;
    for(argIndex = 0; argIndex < argc - 1; argIndex++)
        delete vars[argIndex];
    delete[] vars;
    
    return JS_TRUE;
}
ZZZJS_END_METHOD

/***
 * <method name="getProperty">
 *  <function returns="Any">
 *   <arg name="Property" type=WXJS_TYPE_STRING>
 *    The name of the property.
 *   </arg>
 *   <arg name="Arg1" type="..." />
 *  </function>
 *  <desc>
 *   Gets a property from this object. The return type depends on the type of the property.
 *   Use @wxAutomationObject#getObject when the property is an object.
 *
 *   The name of the method can contain dot-separated property names,
 *   to save the application needing to call @wxAutomationObject#getProperty
 *   several times using several temporary objects.
 *  </desc>
 * </method>
 */
//JSBool AutomationObject::getProperty(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(AutomationObject, getProperty )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxAutomationObject *p = GetPrivate(cx, obj);
	ZZZJS_CHECK_PRIM_NULL(p);
	
	unsigned argIndex = 0;
    wxString prop;

	
	// 0:prop
    if( FromJS(cx, argv[argIndex], prop) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;
    
    const wxVariant **vars = new const wxVariant*[argc - 1];
    for(; argIndex < argc; argIndex++)
    {
        vars[argIndex-1] = CreateVariant(cx, argv[argIndex]);
    }

    wxVariant res = p->GetPropertyArray(prop, argc - 1, vars);
    *vp = CreateJSVal(cx, res);

    for(argIndex = 0; argIndex < argc - 1; argIndex++)
        delete vars[argIndex];
    delete[] vars;
    
    return JS_TRUE;
}
ZZZJS_END_METHOD

/***
 * <method name="getObject">
 *  <function returns="Boolean">
 *   <arg name="Object" type="@wxAutomationObject">
 *    The automation object that receives the property.
 *   </arg>
 *   <arg name="Property" type=WXJS_TYPE_STRING>
 *    The name of the property.
 *   </arg>
 *   <arg name="Arg1" type="..." />
 *  </function>
 *  <desc>
 *   Gets a property from this object. The type of the property is also an object.
 *   The following example retrieves the object Workbooks from an Excel application:
 *   <pre><code class="whjs">
 *  var objExcel = new wxAutomationObject();
 *  if ( objExcel.createInstance("Excel.Application") )
 *  {
 *    objExcel.putProperty("visible", true);
 *    var objBooks = new wxAutomationObject();
 *    objExcel.getObject(objBooks, "workbooks");
 *  }
 *  </code></pre>
 *   The name of the method can contain dot-separated property names,
 *   to save the application needing to call @wxAutomationObject#getProperty
 *   several times using several temporary objects.
 *  </desc>
 * </method>
 */
//JSBool AutomationObject::getObject(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(AutomationObject, getObject )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxAutomationObject *p = GetPrivate(cx, obj);
	ZZZJS_CHECK_PRIM_NULL(p);
	/*
		bool 	GetObject (
				wxAutomationObject &obj, 
				const wxString &property, 
				int noArgs=0, 
				wxVariant args[]=NULL) const
 			Retrieves a property from this object, assumed to be a dispatch pointer, and initialises obj with it. More...
	*/
    wxAutomationObject *autoObj = new wxAutomationObject();//GetPrivate(cx, argv[0]);
    if ( autoObj == NULL )
        return JS_FALSE;
	
	unsigned argIndex = 0;
    wxString prop;
    if( FromJS(cx, argv[argIndex], prop) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;

    if ( argc > 1 )
    {
        const wxVariant **vars = new const wxVariant*[argc - 1];
        for(; argIndex < argc; argIndex++)
        {
            vars[argIndex-1] = CreateVariant(cx, argv[argIndex]);
        }

		if( p->GetObject(*autoObj, prop, argc - 1, vars) == false ) {
			vp->setNull();
		} else {
			*vp = AutomationObject::CreateObject(cx, autoObj);
		}
        //*vp = ToJS(cx, p->GetObject(*autoObj, prop, argc - 1, vars));

        for(argIndex = 0; argIndex < argc - 1; argIndex++)
        {
            delete vars[argIndex];
        }
        delete[] vars;
    }
    else
	{
		if( p->GetObject(*autoObj, prop) == false ) {
			vp->setNull();
		} else {
			*vp = AutomationObject::CreateObject(cx, autoObj);
		}
	}

 
    return JS_TRUE;
}
ZZZJS_END_METHOD

wxVariant *AutomationObject::CreateVariant(JSContext *cx, jsval v)
{
ZZZJS_FUNC_ENT
    switch(JS_TypeOfValue(cx, v))
    {
    case JSTYPE_VOID:
        break;
    case JSTYPE_OBJECT:
        {
	        JSObject *obj = JSVAL_TO_OBJECT(v);
	        //if ( js_DateIsValid(cx, obj) )
			if ( js_DateIsValid(obj) )
            {
                wxDateTime date;
                FromJS(cx, v, date);
                return new wxVariant(date);
            }
           
            wxAutomationObject *o = GetPrivate(cx, obj);
            if ( o != NULL )
            {
                return new wxVariant((void *) o);
            }

            if ( JS_IsArrayObject(cx, obj) == JS_TRUE )
            {
            }
            break;
        }
    case JSTYPE_FUNCTION:
        break;
    case JSTYPE_STRING:
        {
            wxString str;
            FromJS(cx, v, str);
            return new wxVariant(str);
            break;
        }
    case JSTYPE_NUMBER:
        if ( JSVAL_IS_INT(v) )
        {
            long value;
            FromJS(cx, v, value);
            return new wxVariant(value);
        }
        else if ( JSVAL_IS_DOUBLE(v) )
        {
            double value;
            FromJS(cx, v, value);
            return new wxVariant(value);
        }
        break;
    case JSTYPE_BOOLEAN:
        {
            bool b;
            FromJS(cx, v, b);
            return new wxVariant(b);
        }
    }
ZZZJS_FUNC_EXIT
    return new wxVariant();
}

jsval AutomationObject::CreateJSVal(JSContext *cx, const wxVariant &var)
{
ZZZJS_FUNC_ENT
    if ( var.IsNull() )
        return JSVAL_VOID;

    wxString type(var.GetType());

    if ( type.CompareTo(wxT("string")) == 0 )
    {
        return ToJS(cx, var.GetString());
    }
    else if ( type.CompareTo(wxT("bool")) == 0 )
    {
        return ToJS(cx, var.GetBool());
    }
    else if ( type.CompareTo(wxT("list")) == 0 )
    {
        wxLogDebug(wxT("List"));
    }
    else if ( type.CompareTo(wxT("long")) == 0 )
    {
        return ToJS(cx, var.GetLong());
    }
    else if ( type.CompareTo(wxT("double")) == 0 )
    {
        return ToJS(cx, var.GetDouble());
    }
    else if ( type.CompareTo(wxT("char")) == 0 )
    {
		return ToJS(cx, wxString::FromAscii(var.GetChar()));
    }
    else if ( type.CompareTo(wxT("time")) == 0 )
    {
        return ToJS(cx, var.GetDateTime());
    }
    else if ( type.CompareTo(wxT("date")) == 0 )
    {
        return ToJS(cx, var.GetDateTime());
    }
    else if ( type.CompareTo(wxT("void*")) == 0 )
    {
        // void* means an object
        void* p = var.GetVoidPtr();
        if ( p != NULL )
        {
            // We need to create a new wxAutomationObject because
            // otherwise the object is released to early.
            wxAutomationObject *o = static_cast<wxAutomationObject*>(p);
            wxAutomationObject *newObj = new wxAutomationObject();
            newObj->SetDispatchPtr(o->GetDispatchPtr());
            return CreateObject(cx, newObj);
        }
    }
    else if ( type.CompareTo(wxT("datetime")) == 0 )
    {
        return ToJS(cx, var.GetDateTime());
    }
    else if ( type.CompareTo(wxT("arrstring")) == 0 )
    {
		return ToJS(cx, var.GetArrayString());
    }
 
ZZZJS_FUNC_EXIT
    return JSVAL_VOID;
}

#endif // ZZZJS_FOR_UNIX

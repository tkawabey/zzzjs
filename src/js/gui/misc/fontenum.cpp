/*
 * wxJavaScript - fontenum.cpp
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
 * $Id: fontenum.cpp 784 2007-06-25 18:34:22Z fbraem $
 */
// fontenum.cpp
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
#include "js/gui/misc/fontenum.h"

using namespace zzzJs;
using namespace zzzJs::gui;

#define PROP_NM_encoding				"encoding"
#define PROP_NM_fixedWidthOnly			"fixedWidthOnly"
#define PROP_NM_font					"font"

/***
 * <file>misc/fontenum</file>
 * <module>gui</module>
 * <class name="wxFontEnumerator">
 *  Use wxFontEnumerator to enumerate all available fonts.
 *  See @wxFont, @wxFontEncoding
 *  <br /><br />
 *  The following example shows a dialog which contains a listbox with the names of all the available fonts.
 *  <pre><code class="whjs">
 *   var dlg = new wxDialog(null,
 *                          -1,
 *                         "Font Enumerating example");
 *
 *   // Create a wxFontEnumerator
 *   var enumerator = new wxFontEnumerator();
 *   // Set a funtion to onFacename. To get all available fonts return true. 
 *   // No arguments need to be specified, because they are not used.
 *
 *   enumerator.onFacename = function()
 *   {
 *     return true;
 *   };
 *
 *   // Use enumerateFaceNames to start the enumeration.
 *   enumerator.enumerateFacenames();
 *
 *   // Now the property facenames contains all the font names.
 *   var listbox = new wxListBox(dlg, -1, wxDefaultPosition, wxDefaultSize, enumerator.facenames);
 *  </code></pre>
 * </class>
 */

ZZZJS_INIT_CLASS(FontEnumerator, "FontEnumerator", 0)

/***
 * <class_properties>
 *  <property name="encodings" type="Array" readonly="Y">
 *   Array of strings containing all encodings found by @wxFontEnumerator#enumerateEncodings. 
 *   Returns undefined when this function is not called.
 *  </property>
 *  <property name="facenames" type="Array" readonly="Y">
 *   Array of strings containing all facenames found by @wxFontEnumerator#enumerateFacenames.
 *   Returns undefined when this function is not called.
 *  </property>
 *  <property name="onFontEncoding" type="Function">
 *   A function which receives the encoding as argument. The encoding is added
 *   to @wxFontEnumerator#encodings when the function returns true.
 *  </property>
 *  <property name="onFacename" type="Function">
 *   A function which receives the font and encoding as arguments.
 *   When the function returns true, the font is added to @wxFontEnumerator#facenames.
 *   When no function is set, all available fonts are added.
 *  </property>
 * </class_properties>
 */
ZZZJS_BEGIN_STATIC_PROPERTY_MAP(FontEnumerator)
	ZZZJS_READONLY_STATIC_PROPERTY(P_FACENAMES, "facenames")
	ZZZJS_READONLY_STATIC_PROPERTY(P_ENCODINGS, "encodings")
ZZZJS_END_PROPERTY_MAP()

FontEnumerator::FontEnumerator(JSContext *cx, JSObject *obj)
{
  m_data = new JavaScriptClientData(cx, obj, false);
}

FontEnumerator::~FontEnumerator()
{
  delete m_data;
}

bool FontEnumerator::OnFacename(const wxString& faceName)
{
	JSObject *enumObj = m_data->GetObject();

	jsval fval;
    JSContext *cx = m_data->GetContext();
	if ( GetFunctionProperty(cx, enumObj, "onFacename", &fval) == JS_TRUE )
	{
		jsval rval;
		jsval argv[] = { ToJS(cx, faceName) };
		JSBool result = JS_CallFunctionValue(cx, enumObj, fval, 1, argv, &rval);
		if ( result == JS_FALSE )
		{
            if ( JS_IsExceptionPending(cx) )
            {
                JS_ReportPendingException(cx);
            }
			return false;
		}
		else
		{
			bool ret;
			if (    ! FromJS(cx, rval, ret)
                 || ! ret                   )
                return false;
		}
	}
	
	return wxFontEnumerator::OnFacename(faceName);
}

bool FontEnumerator::OnFontencoding(const wxString& faceName, const wxString &encoding)
{
	JSObject *enumObj = m_data->GetObject();
    JSContext *cx = m_data->GetContext();

	jsval fval;
	if ( GetFunctionProperty(cx, enumObj, "onFontEncoding", &fval) == JS_TRUE )
	{
		jsval rval;
		jsval argv[] = {  ToJS(cx, faceName)
						, ToJS(cx, encoding) };
		JSBool result = JS_CallFunctionValue(cx, enumObj, fval, 2, argv, &rval);
		if ( result == JS_FALSE )
		{
            if ( JS_IsExceptionPending(cx) )
            {
                JS_ReportPendingException(cx);
            }
			return false;
		}
		else
		{
			bool ret;
			if (    ! FromJS(cx, rval, ret)
                 || ! ret                   )
                return false;
		}
	}
	
	return wxFontEnumerator::OnFontEncoding(faceName, encoding);
}

bool FontEnumerator::GetStaticProperty(JSContext* cx,
                                    int id,
                                    JS::MutableHandle<JS::Value>& vp)
{
    switch (id) 
	{
	case P_FACENAMES:
		{
            wxArrayString faceNames = wxFontEnumerator::GetFacenames();
			if( faceNames.GetCount() == 0 ) {
				vp.setNull();
			} else {
				ToJSVal(cx, vp, faceNames);
			}
		}
		break;
	case P_ENCODINGS:
		{
            wxArrayString encodings = wxFontEnumerator::GetEncodings();
			if( encodings.GetCount() == 0 ) {
				vp.setNull();
			} else {
				ToJSVal(cx, vp, encodings);
			}
		}
		break;
    }
    return true;
}

/***
 * <ctor>
 *  <function />
 *  <desc>
 *   Creates a wxFontEnumerator object.
 *  </desc>
 * </ctor>
 */
ZZZJS_BEGIN_CONSTRUCTOR(FontEnumerator, FontEnumerator)
{
	return new FontEnumerator(cx, obj);
}
ZZZJS_END_CONSTRUCTOR

ZZZJS_BEGIN_METHOD_MAP(FontEnumerator)
    ZZZJS_METHOD("enumerateFacenames", enumerateFacenames, 0)
    ZZZJS_METHOD("enumerateEncodings", enumerateEncodings, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="enumerateFaceNames">
 *  <function returns="Boolean">
 *	 <arg name="FontEncoding" type=ZZZJS_TYPE_NUMBER default="wxFontEncoding.SYSTEM">
 *    The encoding.
 *   </arg>
 *   <arg name="FixedWidthOnly" type="Boolean" default="false">
 *    Only report fonts with fixed width or not.
 *   </arg>
 *  </function>
 *  <desc>
 *   This will call the function which is set to the @wxFontEnumerator#onFacename property
 *   for each font which supports the given encoding. When this function returns true for the
 *   the given font, it will be added to @wxFontEnumerator#facenames.
 *   When no function is specified, all fonts will be added to @wxFontEnumerator#facenames.
 *   See also @wxFontEncoding, @wxFontEnumerator#facenames, @wxFontEnumerator#onFacename
 *  </desc>
 * </method>
 */
//JSBool FontEnumerator::enumerateFacenames(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(FontEnumerator, enumerateFacenames )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    FontEnumerator *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data for wxFontEnumerator"));

	/*
	 bool 	EnumerateFacenames (
			wxFontEncoding encoding=wxFONTENCODING_SYSTEM, 
			bool fixedWidthOnly=false)
 		Call OnFacename() for each font which supports given encoding (only if it is not wxFONTENCODING_SYSTEM) and is of fixed width (if fixedWidthOnly is true).
	*/
	int argIndex = 0;
	if ( argc == 0 )
	{
		p->EnumerateFacenames();
		return JS_TRUE;
	}

	// 0
	if( argv[argIndex].isNumber() == true ) {

		int encoding = wxFONTENCODING_SYSTEM;
		bool fixedWidthOnly=false;
		
		ZZZJS_CHECK_ARG_COUNT(1, 2)
		// encoding
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(encoding, WXJS_TYPE_NUMBER);

		argIndex = argc - 1;
		switch( argc ) 
		{
		case 2:
			// encoding
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(fixedWidthOnly, WXJS_TYPE_BOOLEAN);
			argIndex--;
		}
		
		vp->setBoolean( p->EnumerateFacenames((wxFontEncoding)encoding, fixedWidthOnly) );
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Object�̏ꍇ	
		/*
		{
			encoding:Number
			, fixedWidthOnly:Boolean[option. default=false]
		}
		*/
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}
			int encoding = wxFONTENCODING_SYSTEM;
			bool fixedWidthOnly=false;
			// encoding
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(encoding, pObj, PROP_NM_encoding, WXJS_TYPE_NUMBER)
			// fixedWidthOnly
			ZZZJS_PROP_FROMJS_IF_EXIST(fixedWidthOnly, pObj, PROP_NM_fixedWidthOnly, WXJS_TYPE_BOOLEAN);

			
			vp->setBoolean( p->EnumerateFacenames((wxFontEncoding)encoding, fixedWidthOnly) );
			return JS_TRUE;
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD

/***
 * <method name="enumerateEncodings">
 *	<function returns="Boolean">
 *	 <arg name="Font" type=ZZZJS_TYPE_STRING default="">
 *    A font name.
 *   </arg>
 *  </function>
 *  <desc>
 *	 The function set on the @wxFontEnumerator#onFontEncoding is called for each
 *   encoding supported by the given font.
 *   When no function is set all encodings are reported.
 *   See @wxFontEnumerator#onFontEncoding, @wxFontEnumerator#encodings
 *  </desc>
 * </method>
 */
//JSBool FontEnumerator::enumerateEncodings(JSContext *cx, unsigned argc, JS::Value *vp)
ZZZJS_BEGIN_METHOD(FontEnumerator, enumerateEncodings )
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    FontEnumerator *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data for wxFontEnumerator"));
	/*
		bool 	EnumerateEncodings (const wxString &font=wxEmptyString)
 			Call OnFontEncoding() for each encoding supported by the given font - or for each encoding supported by at least some font if font is not specified. 
	*/

	
	int argIndex = 0;
	if ( argc == 0 )
	{
		p->EnumerateEncodings();
		return JS_TRUE;
	}
	
	// 0
	if( argv[argIndex].isString() == true ) 
	{
		wxString font=wxEmptyString;
		
		// encoding
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(font, WXJS_TYPE_NUMBER);
		
		vp->setBoolean( p->EnumerateEncodings(font) );
		return JS_TRUE;
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		// Object�̏ꍇ	
		/*
		{
			font:String
		}
		*/
		jsval v;
		JSObject* pObj = argv[argIndex].toObjectOrNull();
		do {
			if( pObj == NULL ) {
				break;
			}
			wxString font=wxEmptyString;
			// font
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(font, pObj, PROP_NM_encoding, WXJS_TYPE_STRING)
							
			vp->setBoolean( p->EnumerateEncodings(font) );
			return JS_TRUE;
		} while( 0 );
	}
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return JS_FALSE;
}
ZZZJS_END_METHOD

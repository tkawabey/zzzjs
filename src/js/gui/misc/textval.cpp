/*
 * wxJavaScript - textval.cpp
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://zzzJs.sourceforge.net
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
 * $Id: textval.cpp 782 2007-06-24 20:23:23Z fbraem $
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
#include "js/gui/misc/validate.h"
#include "js/gui/misc/textval.h"
using namespace zzzJs;
using namespace zzzJs::gui;
// プロパティー名
#define PROP_NM_EXCLUDES			"excludes"
#define PROP_NM_INCLUDES			"includes"
#define PROP_NM_STYLE				"style"
#define PROP_NM_VALUE				"value"




TextValidator::TextValidator(long style,
                             const wxString &value) : wxTextValidator(style)
{
    m_value = value;
    m_stringValue = &m_value;
}

TextValidator::TextValidator(const TextValidator &copy) : wxTextValidator(copy)
{
  JavaScriptClientData *data 
    = dynamic_cast<JavaScriptClientData*>(copy.GetClientObject());
  if ( data != NULL )
  {
    SetClientObject(new JavaScriptClientData(*data));
    data->Protect(false);
  }
}

wxObject* TextValidator::Clone() const
{
	return new TextValidator(*this);
}

/***
 * <file>misc/textval</file>
 * <module>gui</module>
 * <class name="wxTextValidator" prototype="@wxValidator">
 *  wxTextValidator validates text controls, providing a variety of filtering
 *  behaviours. The following example shows a dialog with a textfield. It's 
 *  only allowed to enter numeric characters. The textfield is initialised 
 *  using the validator.
 *  <pre><code class="whjs">
 *   function init()
 *   {
 *     var dlg = new wxDialog(null, -1);
 *     var txtField = new wxTextCtrl(dlg, -1);
 *
 *     txtField.validator = new wxTextValidator(wxFilter.NUMERIC, "10");
 *
 *     dlg.fit();
 *     dlg.showModal();
 *
 *     wxMessageBox("You have entered: " + txtField.value);
 *
 *     return false;
 *   }
 *
 *   wxTheApp.onInit = init;
 *  </code></pre>
 * </class>
 */
ZZZJS_INIT_CLASS(TextValidator, "TextValidator", 0)

/***
 * <properties>
 *  <property name="excludes" type="Array">
 *   Get/Set an array of invalid values.
 *  </property>
 *  <property name="includes" type="Array">
 *   Get/Set an array of valid values.
 *  </property>
 *  <property name="style" type=ZZZJS_TYPE_NUMBER>
 *   Get/Set the filter style. See @wxFilter
 *  </property>
 *  <property name="value" type=ZZZJS_TYPE_STRING readonly="Y">
 *   Get the value entered in the textfield.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(TextValidator)
    ZZZJS_PROPERTY(P_EXCLUDE_LIST, PROP_NM_EXCLUDES)
    ZZZJS_PROPERTY(P_INCLUDE_LIST, PROP_NM_INCLUDES)
    ZZZJS_PROPERTY(P_STYLE, PROP_NM_STYLE)
    ZZZJS_READONLY_PROPERTY(P_VALUE, PROP_NM_VALUE)
ZZZJS_END_PROPERTY_MAP()

//bool TextValidator::GetProperty(wxTextValidator *p,
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxTextValidator, TextValidator)
{
    switch (id)
    {
    case P_EXCLUDE_LIST:
        ToJSVal(cx, vp, p->GetExcludes());
        break;
    case P_INCLUDE_LIST:
        ToJSVal(cx, vp, p->GetIncludes());
        break;
    case P_STYLE:
        ToJSVal(cx, vp, p->GetStyle());
        break;
    case P_VALUE:
        {
            TextValidator *val = dynamic_cast<TextValidator *>(p);
            if ( val )
				vp.set( ToJS(cx, val->m_value) );
        }
        break;
    }
    return true;
}
ZZZJS_END_GET_PROP

//bool TextValidator::SetProperty(wxTextValidator *p,
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_SET_PROP(wxTextValidator, TextValidator)
{
    switch (id)
    {
    case P_EXCLUDE_LIST:
        {
			wxArrayString list;
            if ( FromJS(cx, vp, list) )
                p->SetExcludes(list);
        }
        break;
    case P_INCLUDE_LIST:
        {
            wxArrayString list;
            if ( FromJS(cx, vp, list) )
                p->SetIncludes(list);
        }
        break;
    case P_STYLE:
        {
            long style;
            if ( FromJS(cx, vp, style) )
                p->SetStyle(style);
        }
        break;
    }
    return true;
}
ZZZJS_END_SET_PROP

/***
 * <ctor>
 *  <function>
 *   <arg name="Style" type=ZZZJS_TYPE_NUMBER default="wxFilter.NONE" />
 *   <arg name="Value" type=ZZZJS_TYPE_STRING default="">
 *    Value used to initialize the textfield.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxTextValidator object.
 *  </desc>
 * </ctor>
 */
ZZZJS_BEGIN_CONSTRUCTOR(wxTextValidator, TextValidator)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	int argIndex = 0;
    long filter = wxFILTER_NONE;
	wxString	strValue = wxEmptyString;
    wxTextValidator *p = NULL;

	/*
		wxTextValidator(long style = wxFILTER_NONE, wxString *val = NULL);
		wxTextValidator(const wxTextValidator& val);
	*/
	
	ZZZJS_CHECK_ARG_COUNT(0, 2);
	argIndex = argc -1;

    switch(argc)
    {
    case 2:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(strValue, WXJS_TYPE_STRING);
		argIndex--;
	case 1:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(filter, WXJS_TYPE_NUMBER);
		argIndex--;		
	}
	
	p = new TextValidator(filter, strValue);
	
    return p;
}
ZZZJS_END_CONSTRUCTOR




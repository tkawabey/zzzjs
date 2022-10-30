/*
 * wxJavaScript - genval.cpp
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
 * $Id: genval.cpp 783 2007-06-24 20:36:30Z fbraem $
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
#include "js/common/jsutil.h"
#include "js/common/clntdata.h"
#include "js/gui/misc/genval.h"
#include "js/gui/control/window.h"

using namespace zzzJs;
using namespace zzzJs::gui;

IMPLEMENT_CLASS(GenericValidator, wxGenericValidator)

/***
 * <file>misc/genval</file>
 * <module>gui</module>
 * <class name="wxGenericValidator" prototype="@wxValidator">
 *  wxGenericValidator performs data transfer (but not validation or filtering) 
 *  for the following basic controls: @wxButton, @wxCheckBox, @wxListBox,
 *  @wxStaticText, @wxRadioButton, @wxRadioBox, @wxChoice, @wxComboBox,
 *  @wxGauge, @wxSlider, @wxScrollBar, @wxSpinButton, @wxTextCtrl,
 *  @wxCheckListBox.
 *  <br /><br />
 *  There's a difference between the wxWidgets implementation and the wxJS implementation:
 *  wxWidgets automatically transfer the data to the given pointer variable when validation
 *  succeeds. In JavaScript this is not possible. wxJS solves this with the 
 *  @wxGenericValidator#value property. This property returns the value of the control.
 *  The type of this value is the same as the type of the argument of the constructor.
 *  <br /><br />
 *  The following example shows how to use this class:
 *  <pre><code class="whjs">
 *   var user = "Demo";
 *   var pwd = "";
 *
 *   function Application()
 *   {
 *      var dlg = new wxDialog(null, -1, "wxValidator Example",
 *                            wxDefaultPosition, new wxSize(200, 150));
 *
 *      var userText = new wxTextCtrl(dlg, -1);
 *      var pwdText = new wxTextCtrl(dlg, -1);
 *      var okButton = new wxButton(dlg, wxId.OK, "Ok");
 *      var cancelButton = new wxButton(dlg, wxId.CANCEL, "Cancel");
 *
 *      dlg.sizer = new wxFlexGridSizer(4, 2, 10, 10);
 *      dlg.sizer.add(new wxStaticText(dlg, -1, "Username"));
 *      dlg.sizer.add(userText);
 *      dlg.sizer.add(new wxStaticText(dlg, -1, "Password"));
 *      dlg.sizer.add(pwdText);
 *      dlg.sizer.add(okButton);
 *      dlg.sizer.add(cancelButton);
 *
 *      // Create validator
 *      var validator = new wxGenericValidator(user);
 *
 *      validator.validate = function()
 *      {
 *        if ( this.window.value.length == 0 )
 *        {
 *          wxMessageBox("Please give a username");
 *          return false;
 *      }
 *      return true;
 *   }
 *   userText.validator = validator; 
 *
 *   dlg.autoLayout = true;
 *   dlg.layout();
 *   dlg.showModal();
 * 
 *   user = validator.value;
 *
 *   return false;
 *  }
 *
 *  wxTheApp.onInit = Application;
 *  </code></pre>
 * </class>
 */
GenericValidator::GenericValidator(bool val) : m_boolValue(val)
                                             , wxGenericValidator(&m_boolValue)
{
}

GenericValidator::GenericValidator(int val) : m_intValue(val)
                                            , wxGenericValidator(&m_intValue)
{
}

GenericValidator::GenericValidator(wxString val) : m_stringValue(val)
                                                 , wxGenericValidator(&m_stringValue)
{
}

GenericValidator::GenericValidator(wxArrayInt val) : m_arrayIntValue(val)
                                                   , wxGenericValidator(&m_arrayIntValue)
{
}

GenericValidator::GenericValidator(const GenericValidator &copy) : wxGenericValidator(copy)
{
	JavaScriptClientData *data 
		= dynamic_cast<JavaScriptClientData*>(copy.GetClientObject());
	if ( data != NULL )
	{
		SetClientObject(new JavaScriptClientData(*data));
		data->Protect(false);
	}
}

wxObject* GenericValidator::Clone() const
{
	return new GenericValidator(*this);
}

bool GenericValidator::Validate(wxWindow *parent)
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	if ( data == NULL )
	{
		return false;
	}

	JSContext *cx = data->GetContext();
	wxASSERT_MSG(cx != NULL, wxT("No application object available"));

	JavaScriptClientData *winParentData = dynamic_cast<JavaScriptClientData*>(parent->GetClientObject());

	jsval fval;
	if ( GetFunctionProperty(cx, data->GetObject(),  "validate", &fval) == JS_TRUE )
	{
		jsval argv[] = 
		{ 
			winParentData == NULL ? JSVAL_VOID 
			: OBJECT_TO_JSVAL(winParentData->GetObject()) 
		};

		jsval rval;
		JSBool result = JS_CallFunctionValue(cx, data->GetObject(),
				fval, 1, argv, &rval);
		if ( result == JS_FALSE )
		{
			if ( JS_IsExceptionPending(cx) )
			{
				JS_ReportPendingException(cx);
			}
			return false;
		}
		else
			return JSVAL_IS_BOOLEAN(rval) ? JSVAL_TO_BOOLEAN(rval) == JS_TRUE : false;
	}

	return false;
}

ZZZJS_INIT_CLASS(GenericValidator, "GenericValidator", 1)

/***
 * <properties>
 *  <property name="value" type="Any" readonly="Y">
 *   Gets the value. The same type as the argument of the @wxGenericValidator#ctor.
 *  </property>
 *  <property name="validate" type="Function">
 *   Assign a function to this property that checks the content of the associated window. The function
 *   can have one argument: the parent of the associated window. This function should return false
 *   when the content is invalid, true when it is valid. To get the associated window, 
 *   use <code>this.window</code>.
 *  </property>
 * </properties> 
 */
ZZZJS_BEGIN_PROPERTY_MAP(GenericValidator)
	ZZZJS_READONLY_PROPERTY(P_VALUE, "value")
ZZZJS_END_PROPERTY_MAP()


ZZZJS_BEGIN_GET_PROP(GenericValidator, GenericValidator)
{
    GenericValidator *val = dynamic_cast<GenericValidator*>(p);

    if (   val != NULL 
        && id == P_VALUE )
	{
        if ( val->m_pBool != NULL )
        {
            ToJSVal(cx, vp, val->m_boolValue);
        }
        else if ( val->m_pInt != NULL )
        {
            ToJSVal(cx, vp, val->m_intValue);
        }
        else if ( val->m_pString != NULL )
        {
            ToJSVal(cx, vp, val->m_stringValue);
        }
        else if ( val->m_pArrayInt != NULL )
        {
            // TODO
        }
        else {
//            *vp = JSVAL_VOID;
			vp.setNull();
		}
    }
    return true;
}
ZZZJS_END_GET_PROP

/***
 * <ctor>
 *  <function>
 *   <arg name="Value" type="Any">
 *    This value is used to transfer to the control.
 *    The type of value is important.
 *    <ul><li>Boolean: used for @wxCheckBox and @wxRadioBox.</li>
 *        <li>String: used for @wxButton, @wxComboBox, @wxStaticText and @wxTextCtrl.</li>
 *        <li>Integer: used for @wxGauge, @wxScrollBar, @wxRadioBox, @wxSpinButton and @wxChoice.</li>
 *        <li>Array of Integers: used for @wxListBox and @wxCheckListBox.</li>
 *    </ul>
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxGenericValidator object
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(GenericValidator, GenericValidator)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	 GenericValidator *v = NULL;


    if ( JSVAL_IS_BOOLEAN(argv[0]) )
    {
        bool value;
        FromJS(cx, argv[0], value);
	    v = new GenericValidator(value);
    }
    else if ( JSVAL_IS_INT(argv[0]) )
    {
        int value;
        FromJS(cx, argv[0], value);
	    v = new GenericValidator(value);
    }

    if ( v == NULL )
    {
      // Default: assume a string value
      wxString value;
      FromJS(cx, argv[0], value);
	  v = new GenericValidator(value);
    }

    return v;
}
ZZZJS_END_CONSTRUCTOR
	
ZZZJS_BEGIN_O2I(GenericValidator, GenericValidator)
{

	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}



	return NULL;
}
ZZZJS_END_O2I
/*
 * wxJavaScript - stsizer.cpp
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
 * $Id: stsizer.cpp 733 2007-06-05 21:17:25Z fbraem $
 */
// stsizer.cpp
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
#include "js/gui/misc/sizer.h"
#include "js/gui/misc/stsizer.h"
#include "js/gui/control/staticbx.h"
#include "js/gui/control/window.h"

//#include "../control/staticbx.h"
using namespace zzzJs;
using namespace zzzJs::gui;


// プロパティー名
#define PROP_NM_BOX			"box"
#define PROP_NM_ORIENT		"orient"
#define PROP_NM_PARENT		"parent"
#define PROP_NM_LABEL		"label"




/***
 * <file>misc/stsizer</file>
 * <module>gui</module>
 * <class name="wxStaticBoxSizer" prototype="@wxBoxSizer">
 *	wxStaticBoxSizer is a sizer derived from wxBoxSizer but adds
 *	a static box around the sizer. Note that this static box has to be created separately.
 *	See @wxBoxSizer, @wxSizer and @wxStaticBox
 * </class>
 */
ZZZJS_INIT_CLASS(StaticBoxSizer, "StaticBoxSizer", 1)

/***
 * <properties>
 *	<property name="staticBox" type="@wxStaticBox" readonly="Y">
 *	 The associated static box.
 *  </property>
 * </properties>
 */

ZZZJS_BEGIN_PROPERTY_MAP(StaticBoxSizer)
	ZZZJS_READONLY_PROPERTY(P_STATIC_BOX, "staticBox")
ZZZJS_END_PROPERTY_MAP()


ZZZJS_BEGIN_GET_PROP(wxStaticBoxSizer, StaticBoxSizer)
{
	if ( id == P_STATIC_BOX )
	{
		wxStaticBox *staticBox = p->GetStaticBox();
        if ( staticBox != NULL )
        {
			JavaScriptClientData *data
				= dynamic_cast<JavaScriptClientData*>(staticBox->GetClientObject());
			vp.set( data == NULL ? JSVAL_VOID : OBJECT_TO_JSVAL(data->GetObject()) );
        }
	}
	return true;
}
ZZZJS_END_GET_PROP

/***
 * <ctor>
 *	<function>
 *   <arg name="StaticBox" type="@wxStaticBox">
 *	  The staticbox associated with the sizer.
 *   </arg>
 *   <arg name="Orientation" type=ZZZJS_TYPE_NUMBER>
 *	  Orientation wxVERTICAL or wxHORIZONTAL for creating either a column 
 *	  or row sizer. See @wxOrientation
 *   </arg>
 *  </function>
 *  <desc>
 *	 Constructs a new wxStaticBoxSizer object.
 *  </desc>
 * </ctor>
 */
ZZZJS_BEGIN_CONSTRUCTOR(wxStaticBoxSizer, StaticBoxSizer)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	wxStaticBoxSizer *p = NULL;

	/*
 	wxStaticBoxSizer (wxStaticBox *box, int orient)
 		This constructor uses an already existing static box. More...
 
 	wxStaticBoxSizer (int orient, wxWindow *parent, const wxString &label=wxEmptyString)
		This constructor creates a new static box with the given label and parent window
	*/
	int argIndex = 0;
	int orient = 0;
	
	ZZZJS_CHECK_ARG_COUNT(2, 3);
	
	if ( StaticBox::HasPrototype(cx, argv[argIndex]) == true )
	{
		// wxStaticBoxSizer (wxStaticBox *box, int orient)
		ZZZJS_CHECK_ARG_COUNT(2, 2);
		
		wxStaticBox *pStBx = StaticBox::GetPrivate(cx, argv[argIndex], false);
		argIndex++;		

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(orient, WXJS_TYPE_NUMBER);
		argIndex++;

		p = new wxStaticBoxSizer(pStBx, orient);
	}
	else if( argv[argIndex].isNumber() == true )
	{
		// wxStaticBoxSizer (int orient, wxWindow *parent, const wxString &label=wxEmptyString)
		wxString label = wxEmptyString;
		wxWindow *parent = NULL;

		
		ZZZJS_CHECK_ARG_COUNT(2, 3);

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(orient, WXJS_TYPE_NUMBER);
		argIndex++;

		if( (ZZZJS_ARG_GET_PRIVATE(parent, Window)) == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window" );
			return NULL;
		}
		argIndex++;

	
		argIndex = argc -1;
		switch( argc )
		{
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(label, WXJS_TYPE_STRING);
			argIndex--;
		}

		p = new wxStaticBoxSizer(orient, parent, label);
	}
	else 
	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			
		} while( 0 );
	}

    if ( p != NULL )
    {
		p->SetClientObject(new JavaScriptClientData(cx, obj, false, true));
    }

	return p;
}
ZZZJS_END_CONSTRUCTOR
	
ZZZJS_BEGIN_O2I(wxStaticBoxSizer, StaticBoxSizer)
{
	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}

	/*
	wxStaticBoxSizer (wxStaticBox *box, int orient)
 		This constructor uses an already existing static box. More...
 
	wxStaticBoxSizer (int orient, wxWindow *parent, const wxString &label=wxEmptyString)
 		This constructor creates a new static box with the given label and parent window.
	*/

	// wxStaticBoxSizer (wxStaticBox *box, int orient)
	/*
	{
		box : StaticBox,
		orient : Number
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_BOX), &v) == JS_TRUE )  
	{
		wxStaticBox *pStBox = StaticBox::GetPrivate(cx, v);
		int orient = 0;


		if( pStBox == NULL ) 
		{
			ReportError_PropTypeError(cx, PROP_NM_BOX, "StaticBox");
			return NULL;
		}
		// depth		
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(orient, obj, PROP_NM_ORIENT, WXJS_TYPE_NUMBER)	
			

		bAllocation = true;
		return new wxStaticBoxSizer(pStBox, orient);
	}

	// wxStaticBoxSizer (int orient, wxWindow *parent, const wxString &label=wxEmptyString)
	/*
	{
		orient : Number,
		parent : Window,
		label : String[ default: wx.EmptyString]
	}
	*/
	if( GetPropertyWhenPresent( cx, obj, _T(PROP_NM_PARENT), &v) == JS_TRUE )  
	{
		wxWindow *pWindow = Window::GetPrivate(cx, v);
		int orient = 0;
		wxString label = wxEmptyString;

		// orient
		ZZZJS_PROP_FROMJS_CHK_AND_ERROR(orient, obj, PROP_NM_ORIENT, WXJS_TYPE_NUMBER)	
		
		// label
		ZZZJS_PROP_FROMJS_IF_EXIST(label, obj, PROP_NM_LABEL, WXJS_TYPE_NUMBER)	
			

		bAllocation = true;
		return new wxStaticBoxSizer(orient, pWindow, label);
	}
	return NULL;
}
ZZZJS_END_O2I

ZZZJS_BEGIN_DESTRUCTOR(wxStaticBoxSizer, StaticBoxSizer)
ZZZJS_END_DESTRUCTOR

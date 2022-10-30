/*
 * wxJavaScript - boxsizer.cpp
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
 * $Id: boxsizer.cpp 733 2007-06-05 21:17:25Z fbraem $
 */
// boxsizer.cpp
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
#include "js/gui/misc/sizer.h"
#include "js/gui/misc/boxsizer.h"

using namespace zzzJs;
using namespace zzzJs::gui;


// プロパティー名
#define PROP_ORIENTATION    "orientation"


/***
 * <file>misc/boxsizer</file>
 * <module>gui</module>
 * <class name="wxBoxSizer" prototype="@wxSizer">
 *	The basic idea behind a box sizer is that windows will most often be laid out in 
 *  rather simple basic geometry, typically in a row or a column or several hierarchies of either.
 * </class>
 */
ZZZJS_INIT_CLASS(BoxSizer, "BoxSizer", 1)
 
/***
 * <properties>
 *	<property name="orientation" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Gets the orientation. See @wxOrientation
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(BoxSizer)
  ZZZJS_READONLY_PROPERTY(P_ORIENTATION, PROP_ORIENTATION)
ZZZJS_END_PROPERTY_MAP()


ZZZJS_BEGIN_GET_PROP(wxBoxSizer, BoxSizer)
{
	if ( id == P_ORIENTATION )
	{
		ToJSVal(cx, vp, p->GetOrientation());
	}
	return true;
}
ZZZJS_END_GET_PROP

/***
 * <ctor>
 *	<function>
 *	 <arg name="orientation" type=WXJS_TYPE_NUMBER>
 *	  Orientation VERTICAL or HORIZONTAL for creating either a column 
 *	  or row sizer. See @wxOrientation
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a new wxBoxSizer object
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxBoxSizer, BoxSizer)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	int orient = wxVERTICAL;
	
	int argIndex = 0;
	if ( FromJS(cx, argv[argIndex], orient) )
	{
		wxBoxSizer *p = new wxBoxSizer(orient);
		p->SetClientObject(new JavaScriptClientData(cx, obj, false, true));
		return p;
	} else 	if( argv[argIndex].isObjectOrNull() == true ) {
		do {
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			zzzJsPtr<wxBoxSizer> apRet;
			if( apRet.set( 
				BoxSizer::getObject2Instance(cx, pObj, apRet.bAllocation) ) == true 
			) {
				if( apRet.bAllocation == true ) {
					return apRet.release();
				} else {
					return new wxBoxSizer(*apRet.get());
				}
			}
		} while( 0 );
	}
	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return NULL;
}
ZZZJS_END_CONSTRUCTOR
	
ZZZJS_BEGIN_DESTRUCTOR(wxBoxSizer, BoxSizer)
ZZZJS_END_DESTRUCTOR

// Object 2 Instatance
ZZZJS_BEGIN_O2I(wxBoxSizer, BoxSizer)
{
	pRet = GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}

	if( GetPropertyWhenPresent( cx, obj, PROP_ORIENTATION, &v) == JS_TRUE )  
	{
		int orient = wxVERTICAL;
	
		if( FromJS(cx, v, orient) == false ) {
			ReportError_PropTypeError(cx, PROP_ORIENTATION, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}	
		bAllocation = true;
		return new wxBoxSizer(orient);
	}


	return NULL;
}
ZZZJS_END_O2I




/*
 * wxJavaScript - finddata.cpp
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
 * $Id: finddata.cpp 672 2007-04-12 20:29:39Z fbraem $
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



#include "js/gui/control/finddata.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/finddata</file>
 * <module>gui</module>
 * <class name="wxFindReplaceData">
 *   wxFindReplaceData holds the data for @wxFindReplaceDialog.
 *	 It is used to initialize the dialog with the default values and 
 *   will keep the last values from the dialog when it is closed.
 *   It is also updated each time a @wxFindDialogEvent is generated so 
 *   instead of using the @wxFindDialogEvent methods 
 *   you can also directly query this object.
 * </class>
 */
WXJS_INIT_CLASS(FindReplaceData, "FindReplaceData", 0)

/***
 * <properties>
 *  <property name="findString" type=WXJS_TYPE_STRING>
 *   Get/Set the string to find
 *  </property>
 *  <property name="flags" type=WXJS_TYPE_NUMBER>
 *   Get/Set the flags. 
 *  </property>
 *  <property name="replaceString" type=WXJS_TYPE_STRING>
 *   Get/Set the replacement string
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(FindReplaceData)
  WXJS_PROPERTY(P_FINDSTRING, "findString")
  WXJS_PROPERTY(P_REPLACESTRING, "replaceString")
  WXJS_PROPERTY(P_FLAGS, "flags")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxFindReplaceData, FindReplaceData)
    switch(id) 
	{
	case P_FLAGS:
		ToJSVal(cx, vp, p->GetFlags());
		break;
	case P_FINDSTRING:
		ToJSVal(cx, vp, p->GetFindString());
		break;
	case P_REPLACESTRING:
		ToJSVal(cx, vp, p->GetReplaceString());
		break;
    }
    return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxFindReplaceData, FindReplaceData)
    switch(id) 
	{
	case P_FLAGS:
		{
			int flag;
			if ( FromJS(cx, vp, flag) )
				p->SetFlags(flag);
			break;
		}
	case P_FINDSTRING:
		{
			wxString str;
			FromJS(cx, vp, str);
			p->SetFindString(str);
			break;
		}
	case P_REPLACESTRING:
		{
			wxString str;
			FromJS(cx, vp, str);
			p->SetReplaceString(str);
			break;
		}
	}
    return true;
WXJS_END_SET_PROP

/***
 * <constants>
 *  <type name="Flags">
 *   <constant name="FR_DOWN" />
 *   <constant name="FR_WHOLEWORD" />
 *   <constant name="FR_MATCHCASE" />
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(FindReplaceData)
  WXJS_CONSTANT(wx, FR_DOWN)
  WXJS_CONSTANT(wx, FR_WHOLEWORD)
  WXJS_CONSTANT(wx, FR_MATCHCASE)
WXJS_END_CONSTANT_MAP()

/***
 * <ctor>
 *  <function>
 *   <arg name="Flags" type=WXJS_TYPE_NUMBER default="0" />
 *  </function>
 *  <desc>
 *   Constructs a new wxFindReplaceData object.
 *  </desc>
 * </ctor>
 */
WXJS_BEGIN_CONSTRUCTOR(wxFindReplaceData, FindReplaceData)

	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( argc == 0 )
        return new wxFindReplaceData();
    else
    {
	    int flags = 0;
        if ( FromJS(cx, argv[0], flags) )
            return new wxFindReplaceData(flags);
    }
    
    return NULL;
WXJS_END_CONSTRUCTOR

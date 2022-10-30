/*
 * wxJavaScript - listhit.cpp
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
 * $Id: listhit.cpp 688 2007-04-27 20:45:09Z fbraem $
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

#include "js/gui/control/listhit.h"
#include "js/gui/misc/constant.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/listhit</file>
 * <module>gui</module>
 * <class name="wxListHitTest">
 *  Helper class for returning information from @wxListCtrl#hitTest.
 *  This class is specific for wxJavaScript. It doesn't exist in wxWidgets.
 * </class>
 */
WXJS_INIT_CLASS(ListHitTest, "ListHitTest", 0)

/***
 * <properties>
 *  <property name="item" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Get the item.
 *  </property>
 *  <property name="flags" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Get the flags. These flags give details about the position and the list 
 *   control item.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(ListHitTest)
    WXJS_READONLY_PROPERTY(P_ITEM, "item")
    WXJS_READONLY_PROPERTY(P_FLAGS, "flags")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxListHitTest, ListHitTest)
    switch (id)
    {
    case P_ITEM:
        ToJSVal(cx, vp, p->GetItem());
        break;
    case P_FLAGS:
        ToJSVal(cx, vp, p->GetFlags());
        break;
    }
    return true;
WXJS_END_GET_PROP

/***
 * <constants>
 *  <type name="HitTest">
 *   <constant name="ABOVE">Above the client area.</constant>
 *   <constant name="BELOW">Below the client area.</constant>
 *   <constant name="NOWHERE">In the client area but below the last item.</constant>
 *   <constant name="ONITEMICON">On the bitmap associated with an item.</constant>
 *   <constant name="ONITEMLABEL">On the label (string) associated with an item.</constant>
 *   <constant name="ONITEMRIGHT">In the area to the right of an item.</constant>
 *   <constant name="ONITEMSTATEICON">On the state icon for a tree view item that is in a user-defined state.</constant>
 *   <constant name="TOLEFT">To the left of the client area.</constant>
 *   <constant name="TORIGHT">To the right of the client area.</constant>
 *   <constant name="ONITEM">(ONITEMICON | ONITEMLABEL | ONITEMSTATEICON)</constant>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(ListHitTest)
    WXJS_CONSTANT(wxLIST_HITTEST_, ABOVE)
    WXJS_CONSTANT(wxLIST_HITTEST_, BELOW)
    WXJS_CONSTANT(wxLIST_HITTEST_, NOWHERE)
    WXJS_CONSTANT(wxLIST_HITTEST_, ONITEMICON)
    WXJS_CONSTANT(wxLIST_HITTEST_, ONITEMLABEL)
    WXJS_CONSTANT(wxLIST_HITTEST_, ONITEMRIGHT)
    WXJS_CONSTANT(wxLIST_HITTEST_, ONITEMSTATEICON)
    WXJS_CONSTANT(wxLIST_HITTEST_, TOLEFT)
    WXJS_CONSTANT(wxLIST_HITTEST_, TORIGHT)
    WXJS_CONSTANT(wxLIST_HITTEST_, ONITEM)
WXJS_END_CONSTANT_MAP()

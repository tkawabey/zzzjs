/*
 * wxJavaScript - treeid.cpp
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
 * $Id: treeid.cpp 696 2007-05-07 21:16:23Z fbraem $
 */
#include "precompile.h"
#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 




#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/treebase.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"


#include "js/gui/control/treeid.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/treeid</file>
 * <module>gui</module>
 * <class name="wxTreeItemId">
 *  wxTreeItemId identifies an element of the tree.
 *  See @wxTreeCtrl and @wxTreeEvent
 * </class>
 */
WXJS_INIT_CLASS(TreeItemId, "TreeItemId", 0)

/***
 * <properties>
 *  <property name="ok" type="Boolean" readonly="Y">
 *   Returns true when the item is valid.
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(TreeItemId)
    WXJS_READONLY_PROPERTY(P_OK, "ok")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxTreeItemId, TreeItemId)
    if ( id == P_OK )
    {
        ToJSVal(cx, vp, p->IsOk());
    }
    return true;
WXJS_END_GET_PROP

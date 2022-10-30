/*
 * wxJavaScript - chklstbxchk.cpp
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
 * $Id: chklstbxchk.cpp 711 2007-05-14 20:59:29Z fbraem $
 */
// chklstbx.cpp
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

#include "js/common/index.h"

#include "js/gui/control/chklstbxchk.h"
#include "js/gui/control/chklstbx.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/chklstbxchk</file>
 * <module>gui</module>
 * <class name="wxCheckListBoxItem">
 *  wxCheckListBoxItem is a helper class used by wxJS to
 *  provide the use of an array to check or uncheck an item
 *  of a @wxCheckListBox. The following sample shows a @wxCheckListBox with the first item checked.
 *  <pre><code class="whjs">
 *   dlg = new wxDialog(null, -1, "Test", new wxPoint(0, 0), new wxSize(200, 200));
 *   items = new Array();
 *   items[0] = "item 1";
 *   items[1] = "item 2";
 *   items[2] = "item 3";
 *   choice = new wxCheckListBox(dlg, -1, wxDefaultPosition, new wxSize(150, 150), items);
 *   choice.checked[0] = true;
 *   dlg.showModal();
 *  </code></pre>
 * </class>
 */
WXJS_INIT_CLASS(CheckListBoxItem, "CheckListBoxItem", 0)


WXJS_BEGIN_GET_PROP(Index, CheckListBoxItem)
    JSObject *parent = JS_GetParent(obj);//JS_GetParent(cx, obj);
    wxASSERT_MSG(parent != NULL, wxT("No parent found for wxCheckListBoxItem"));

	if ( id >= 0 )
	{
        p->SetIndex(id);
        wxCheckListBox *box = CheckListBox::GetPrivate(cx, parent);
        if ( box == NULL )
            return false;
		
		ToJSVal(cx, vp, box->IsChecked(id));
	}
	return true;
WXJS_END_GET_PROP
	
WXJS_BEGIN_SET_PROP(Index, CheckListBoxItem)
    JSObject *parent = JS_GetParent(obj);//JS_GetParent(cx, obj);
    wxASSERT_MSG(parent != NULL, wxT("No parent found for CheckListBoxItem"));

	if ( id >= 0 )
	{
        wxCheckListBox *box = CheckListBox::GetPrivate(cx, parent);
        if ( box == NULL )
            return false;

        bool check;
		if ( FromJS(cx, vp, check) )
			box->Check(id, check);
	}
	return true;
WXJS_END_SET_PROP

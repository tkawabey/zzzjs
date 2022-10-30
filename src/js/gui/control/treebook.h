/*
 * wxJavaScript - treebook.h
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
 * $Id: control.h 672 2007-04-12 20:29:39Z fbraem $
 */
#ifndef _ZZZJS_GUI_CONTROL_TreeBook_H
#define _ZZZJS_GUI_CONTROL_TreeBook_H

#include "js/common/evtconn.h"
#include "js/common/jswrap.h"
#include <wx/treebook.h>

namespace zzzJs
{
    namespace gui
    {
        class Treebook : public JsWrapper<Treebook, wxTreebook>
        {
        public:
			
			static void InitClass(JSContext* cx,
								  JSObject* obj,
								  JSObject* proto);
			ZZZJS_DECLARE_SET_STR_PROP(wxTreebook)
			ZZZJS_DECLARE_DESTRUCTOR(wxTreebook)
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxTreebook)



            ZZZJS_DECLARE_METHOD_MAP()
			ZZZJS_DECLARE_METHOD(create);
//			ZZZJS_DECLARE_METHOD(insertPage);	<- ”h¶Œ³‚ÉŽÀ‘•—L‚è
			ZZZJS_DECLARE_METHOD(insertSubPage);
//			ZZZJS_DECLARE_METHOD(addPage);	<- ”h¶Œ³‚ÉŽÀ‘•—L‚è
			ZZZJS_DECLARE_METHOD(addSubPage);
			// Tree operations
			// ---------------
			ZZZJS_DECLARE_METHOD(isNodeExpanded);
			ZZZJS_DECLARE_METHOD(expandNode);
			ZZZJS_DECLARE_METHOD(collapseNode);
			ZZZJS_DECLARE_METHOD(getPageParent);
			ZZZJS_DECLARE_METHOD(getTreeCtrl);

			// inner functions
			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
 

        };
		

		class TreeBookEventHandler : public EventConnector<wxTreebook>
						   		     , public wxEvtHandler
		{
		public:
			void OnPageChanged(wxBookCtrlEvent &event);
			void OnPageChanging(wxBookCtrlEvent &event);
			void OnNodeCollapsed(wxBookCtrlEvent &event);
			void OnNodeExpanded(wxBookCtrlEvent &event);
			static void InitConnectEventMap();
		private:
			static void ConnectPageChanged(wxTreebook *p, bool connect);
			static void ConnectPageChanging(wxTreebook *p, bool connect);
			static void ConnectNodeCollapsed(wxTreebook *p, bool connect);
			static void ConnectNodeExpanded(wxTreebook *p, bool connect);
		};
    }; // namespace gui
}; // namespace wxjs

#endif //_ZZZJS_GUI_CONTROL_NoteBook_H

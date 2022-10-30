/*
 * wxJavaScript - listbook.h
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
#ifndef _ZZZJS_GUI_CONTROL_Listbook_H
#define _ZZZJS_GUI_CONTROL_Listbook_H

#include "js/common/evtconn.h"
#include "js/common/jswrap.h"
#include <wx/listbook.h>


namespace zzzJs
{
    namespace gui
    {
        class Listbook : public JsWrapper<Listbook, wxListbook>
        {
        public:
			
			static void InitClass(JSContext* cx,
								  JSObject* obj,
								  JSObject* proto);
			ZZZJS_DECLARE_SET_STR_PROP(wxListbook  )
			ZZZJS_DECLARE_DESTRUCTOR(wxListbook)
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxListbook)




            ZZZJS_DECLARE_METHOD_MAP()
			ZZZJS_DECLARE_METHOD(create);





			// inner functions
			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
 

        };
		

		class ListbookEventHandler : public EventConnector<wxListbook >
						   		     , public wxEvtHandler
		{
		public:
			void OnPageChanged(wxBookCtrlEvent &event);
			void OnPageChanging(wxBookCtrlEvent &event);
			static void InitConnectEventMap();
		private:
			static void ConnectNotebookPageChanged(wxListbook  *p, bool connect);
			static void ConnectNotebookPageChanging(wxListbook  *p, bool connect);
		};
    }; // namespace gui
}; // namespace wxjs

#endif //_ZZZJS_GUI_CONTROL_Listbook_H

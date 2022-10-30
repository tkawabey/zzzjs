/*
 * wxJavaScript - chklstbx.h
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
 * $Id: chklstbx.h 678 2007-04-19 20:12:31Z fbraem $
 */
#ifndef _WXJSCheckListBox_H
#define _WXJSCheckListBox_H


#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        class CheckListBox : public ApiWrapper<CheckListBox, wxCheckListBox>
        {
        public:

          static void InitClass(JSContext* cx, 
                                JSObject* obj, 
                                JSObject* proto);

			WXJS_DECLARE_ADD_PROP(wxCheckListBox)
			WXJS_DECLARE_DEL_PROP(wxCheckListBox)
			WXJS_DECLARE_GET_PROP(wxCheckListBox)
			WXJS_DECLARE_SET_STR_PROP(wxCheckListBox)
			WXJS_DECLARE_CONSTRUCTOR(wxCheckListBox)
			WXJS_DECLARE_DESTRUCTOR(wxCheckListBox)
	        WXJS_DECLARE_PROPERTY_MAP()

	        /**
	         * Property Ids.
	         */
	        enum
	        {
		        P_CHECKED = WXJS_START_PROPERTY_ID
	        };

            WXJS_DECLARE_METHOD_MAP()
            WXJS_DECLARE_METHOD(create)

			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
        };

        class CheckListBoxEventHandler : public EventConnector<wxCheckListBox>
                                       , public wxEvtHandler
        {
        public:
          // Events
          void OnCheckListBox(wxCommandEvent &event);
          static void InitConnectEventMap();
        private:
          static void ConnectCheckListBox(wxCheckListBox *p, bool connect);
        };

    }; // namespace gui
}; // namespace wxjs
#endif //_WXJSCheckListBox_H

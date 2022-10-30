/*
 * wxJavaScript - checkbox.h
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
 * $Id: checkbox.h 678 2007-04-19 20:12:31Z fbraem $
 */
#ifndef _WXJSCheckBox_H
#define _WXJSCheckBox_H

#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        class CheckBox : public ApiWrapper<CheckBox, wxCheckBox>
        {
        public:

            static void InitClass(JSContext* cx, 
                                  JSObject* obj, 
                                  JSObject* proto);

			WXJS_DECLARE_ADD_PROP(wxCheckBox)
			WXJS_DECLARE_DEL_PROP(wxCheckBox)
			WXJS_DECLARE_GET_PROP(wxCheckBox)
			WXJS_DECLARE_SET_PROP(wxCheckBox)
			WXJS_DECLARE_SET_STR_PROP(wxCheckBox)
			WXJS_DECLARE_CONSTRUCTOR(wxCheckBox)
			WXJS_DECLARE_DESTRUCTOR(wxCheckBox)

	        WXJS_DECLARE_PROPERTY_MAP()
	        enum
	        {
		        P_VALUE
	        };

            WXJS_DECLARE_METHOD_MAP()
            WXJS_DECLARE_METHOD(create)

			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
        };

        class CheckBoxEventHandler : public EventConnector<wxCheckBox>
                                   , public wxEvtHandler
        {
        public:
          // Events
	      void OnCheckBox(wxCommandEvent &event);
          static void InitConnectEventMap();
        private:
          static void ConnectCheckBox(wxCheckBox *p, bool connect);
        };

    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSCheckBox_H

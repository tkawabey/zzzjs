/*
 * wxJavaScript - combobox.h
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
 * $Id: combobox.h 682 2007-04-24 20:38:18Z fbraem $
 */
#ifndef _WXJSComboBox_H
#define _WXJSComboBox_H

#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        class ComboBox : public ApiWrapper<ComboBox, wxComboBox>
        {
        public:
          static void InitClass(JSContext* cx, 
                                JSObject* obj, 
                                JSObject* proto);


			WXJS_DECLARE_ADD_PROP(wxComboBox)
			WXJS_DECLARE_DEL_PROP(wxComboBox)
			WXJS_DECLARE_GET_PROP(wxComboBox)
			WXJS_DECLARE_SET_PROP(wxComboBox)
			WXJS_DECLARE_SET_STR_PROP(wxComboBox)
			WXJS_DECLARE_CONSTRUCTOR(wxComboBox)
			WXJS_DECLARE_DESTRUCTOR(wxComboBox)

	        WXJS_DECLARE_CONSTANT_MAP()

            WXJS_DECLARE_PROPERTY_MAP()
	        enum
	        {
		        P_VALUE
		        , P_INSERTION_POINT
		        , P_LAST_POSITION
                , P_CAN_COPY
                , P_CAN_CUT
                , P_CAN_PASTE
                , P_CAN_REDO
                , P_CAN_UNDO
	        };

            WXJS_DECLARE_METHOD_MAP()
	        WXJS_DECLARE_METHOD(create)
	        WXJS_DECLARE_METHOD(copy)
	        WXJS_DECLARE_METHOD(cut)
	        WXJS_DECLARE_METHOD(paste)
	        WXJS_DECLARE_METHOD(replace)
	        WXJS_DECLARE_METHOD(remove)
	        WXJS_DECLARE_METHOD(redo)
	        WXJS_DECLARE_METHOD(undo)


			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
        };

        class ComboBoxEventHandler : public EventConnector<wxComboBox>
                                   , public wxEvtHandler
        {
        public:
          // Events
            void OnText(wxCommandEvent &event);
            void OnTextEnter(wxCommandEvent &event);
	        void OnComboBox(wxCommandEvent &event);
            static void InitConnectEventMap();
        private:
            static void ConnectText(wxComboBox *p, bool connect);
            static void ConnectTextEnter(wxComboBox *p, bool connect);
            static void ConnectComboBox(wxComboBox *p, bool connect);
        };

    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSComboBox_H

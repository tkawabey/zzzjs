/*
 * wxJavaScript - button.h
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
 * $Id: button.h 678 2007-04-19 20:12:31Z fbraem $
 */
#ifndef _WXJSButton_H
#define _WXJSButton_H

#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {

        class Button : public ApiWrapper<Button, wxButton>
        {
        public:

          static void InitClass(JSContext* cx, 
                                JSObject* obj, 
                                JSObject* proto);
		  
			WXJS_DECLARE_ADD_PROP(wxButton)
			WXJS_DECLARE_DEL_PROP(wxButton)
			WXJS_DECLARE_GET_PROP(wxButton)
			WXJS_DECLARE_SET_PROP(wxButton)
			WXJS_DECLARE_SET_STR_PROP(wxButton)
			WXJS_DECLARE_GET_STATIC_PROP() 
			WXJS_DECLARE_CONSTRUCTOR(wxButton)
            WXJS_DECLARE_DESTRUCTOR(wxButton)
//          static bool GetStaticProperty(JSContext *cx, int id,JS::MutableHandle<JS::Value>& vp);



          WXJS_DECLARE_PROPERTY_MAP()
          WXJS_DECLARE_STATIC_PROPERTY_MAP()
          enum
          {
            P_LABEL
            , P_DEFAULT_SIZE
          };

          WXJS_DECLARE_CONSTANT_MAP()

          WXJS_DECLARE_METHOD_MAP()
          WXJS_DECLARE_METHOD(setDefault)
          WXJS_DECLARE_METHOD(create)


			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
        };

        class ButtonEventHandler : public EventConnector<wxButton>
                                 , public wxEvtHandler
        {
        public:
          // Events
          void OnClicked(wxCommandEvent &event);
          static void InitConnectEventMap();
        private:
          static void ConnectClicked(wxButton *p, bool connect);
        };
    }; // namespace gui
}; // namespace wxjs
#endif //_WXJSButton_H

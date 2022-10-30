/*
 * wxJavaScript - ipaddr.h
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
 * $Id: ipaddr.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _wxjs_io_ipaddr_h
#define _wxjs_io_ipaddr_h

#include <wx/socket.h>

#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
        class IPaddress : public JsWrapper<IPaddress, wxIPaddress>
        {
        public:
	        //static bool GetProperty(wxIPaddress *p, 
         //                         JSContext *cx, 
         //                         JSObject *obj, 
         //                         int id, 
         //                         JS::MutableHandle<JS::Value>& vp);
	        //static bool SetProperty(wxIPaddress *p, 
         //                         JSContext *cx, 
         //                         JSObject *obj, 
         //                         int id, 
         //                         JS::MutableHandle<JS::Value>& vp);
			
			ZZZJS_DECLARE_GET_PROP(wxIPaddress)
			ZZZJS_DECLARE_SET_PROP(wxIPaddress)
			ZZZJS_DECLARE_SET_STR_PROP(wxIPaddress)
	        ZZZJS_DECLARE_PROPERTY_MAP()
	        ZZZJS_DECLARE_METHOD_MAP()

	        static JSBool anyAddress(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool localhost(JSContext *cx, unsigned argc, JS::Value *vp);

	        enum
	        {
		        P_HOSTNAME = WXJS_START_PROPERTY_ID
		        , P_LOCALHOST
		        , P_IPADDRESS
		        , P_SERVICE
	        };
        };
    }; // namespace io
}; // namespace wxjs
#endif // _wxjs_io_ipaddr_h

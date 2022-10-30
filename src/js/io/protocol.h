/*
 * wxJavaScript - protocol.h
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
 * $Id: protocol.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _wxjs_io_protocol_h
#define _wxjs_io_protocol_h

#include <wx/protocol/protocol.h>
#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
        class Protocol : public JsWrapper<Protocol, SocketBasePrivate>
        {
        public:
	        static void InitClass(JSContext *cx, JSObject *obj, JSObject *proto);

	        //static bool GetProperty(SocketBasePrivate *p,   
         //                         JSContext *cx, 
         //                         JSObject *obj, 
         //                         int id, 
         //                         JS::MutableHandle<JS::Value>& vp);
			ZZZJS_DECLARE_GET_PROP(SocketBasePrivate)
			ZZZJS_DECLARE_SET_STR_PROP(SocketBasePrivate)
        	
	        ZZZJS_DECLARE_PROPERTY_MAP()
	        enum
	        {
		        P_CONTENT_TYPE = WXJS_START_PROPERTY_ID
		        , P_ERROR
	        };
	        ZZZJS_DECLARE_METHOD_MAP()

	        static JSBool abort(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool getInputStream(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool reconnect(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool setUser(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool setPassword(JSContext *cx, unsigned argc, JS::Value *vp);
        };
    }; // namespace io
}; // namespace wxjs
#endif //  _wxjs_io_protocol_h

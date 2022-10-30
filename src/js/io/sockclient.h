/*
 * wxJavaScript - sockclient.h
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
 * $Id: sockclient.h 716 2007-05-20 17:57:22Z fbraem $
 */
#ifndef _wxjs_io_sockclient_h
#define _wxjs_io_sockclient_h

#include <wx/event.h>
#include <wx/socket.h>

#include "js/io/sockbase.h"
#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
        class SocketEventHandler;

        class SocketClient : public JsWrapper<SocketClient, SocketBasePrivate>
					       , public wxSocketClient
        {
        public:
	        SocketClient(JSContext *cx, JSObject *obj, wxSocketFlags flags = wxSOCKET_NONE);
	        virtual ~SocketClient();

	        //static SocketBasePrivate *Construct(JSContext *cx, 
									//	unsigned int argc, 
									//	JS::Value *vp, 
									//	bool constructing);
			ZZZJS_DECLARE_SET_STR_PROP(SocketBasePrivate)
			ZZZJS_DECLARE_CONSTRUCTOR(SocketBasePrivate)
			ZZZJS_DECLARE_DESTRUCTOR(SocketBasePrivate)

	        ZZZJS_DECLARE_METHOD_MAP()

	        static JSBool connect(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool waitOnConnect(JSContext *cx, unsigned argc, JS::Value *vp);

        private:
	        SocketEventHandler *m_evtHandler;
        };
    }; // namespace io
}; // namespace wxjs
#endif // _wxjs_io_sockclient_h

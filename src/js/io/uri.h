/*
 * wxJavaScript - uri.h
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
 * $Id: uri.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _wxjs_io_uri_h
#define _wxjs_io_uri_h

#include <wx/uri.h>

#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
        class URI : public JsWrapper<URI, wxURI>
        {
        public:


			ZZZJS_DECLARE_CONSTRUCTOR(wxURI)
			ZZZJS_DECLARE_GET_PROP(wxURI)

	        ZZZJS_DECLARE_CONSTANT_MAP()
	        ZZZJS_DECLARE_PROPERTY_MAP()
	        enum
	        {
		        P_FRAGMENT = WXJS_START_PROPERTY_ID
		        , P_HOST_TYPE
		        , P_PASSWORD
		        , P_PATH
		        , P_PORT
		        , P_QUERY
		        , P_SCHEME
		        , P_SERVER
		        , P_USER
		        , P_USERINFO
		        , P_HAS_PATH
		        , P_HAS_PORT
		        , P_HAS_QUERY
		        , P_HAS_SCHEME
		        , P_HAS_SERVER
		        , P_HAS_USER
		        , P_IS_REFERENCE
	        };

	        ZZZJS_DECLARE_METHOD_MAP()
	        static JSBool buildURI(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool buildUnescapedURI(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool create(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool resolve(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool unescape(JSContext *cx, unsigned argc, JS::Value *vp);
        };
    }; // namespace io
}; // namespace wxjs
#endif // _wxjs_io_uri_h

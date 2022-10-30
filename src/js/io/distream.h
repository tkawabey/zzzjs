/*
 * wxJavaScript - distream.h
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
 * $Id: distream.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJSDataInputStream_H
#define _WXJSDataInputStream_H

#include <wx/datstrm.h>
#include "js/common/apiwrap.h"

namespace zzzJs
{
    namespace io
    {
        class DataInputStream: public ApiWrapper<DataInputStream, wxDataInputStream>
        {
        public:
            /**
             * Callback for when a wxTextInputStream object is created
             */
          //  static wxDataInputStream *Construct(JSContext *cx, 
										//unsigned int argc, 
										//JS::Value *vp, 
										//bool constructing);
			WXJS_DECLARE_CONSTRUCTOR(wxDataInputStream)

            WXJS_DECLARE_METHOD_MAP()
            static JSBool bigEndianOrdered(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool read64(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool read32(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool read16(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool read8(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool readDouble(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool readString(JSContext *cx, unsigned argc, JS::Value *vp);

        };
    }; // namespace io
}; // namespace wxjs
#endif //_WXJSDataInputStream_H

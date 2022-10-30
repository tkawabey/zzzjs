/*
 * wxJavaScript - textline.h
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
 * $Id: textline.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _wxjs_io_textline_h
#define _wxjs_io_textline_h

// Helper class for text lines
#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
        class TextLine : public JsWrapper<TextLine, Index>
        {	
        public:

            //static bool GetProperty(Index *p,  
            //                      JSContext *cx, 
            //                      JSObject *obj, 
            //                      int id, 
            //                      JS::MutableHandle<JS::Value>& vp);
            //static bool SetProperty(Index *p, 
            //                      JSContext *cx, 
            //                      JSObject *obj, 
            //                      int id, 
            //                      JS::MutableHandle<JS::Value>& vp);
			ZZZJS_DECLARE_GET_PROP(Index)
			ZZZJS_DECLARE_SET_PROP(Index)

	        static bool Enumerate(Index *p, JSContext *cx, JSObject *obj, JSIterateOp enum_op, jsval *statep, jsid *idp);
	        static bool Resolve(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id);

	        ZZZJS_DECLARE_PROPERTY_MAP()
	        ZZZJS_DECLARE_METHOD_MAP()

	        enum
	        {
		        P_LINE_TYPE = WXJS_START_PROPERTY_ID
		        , P_CONTENT
	        };

	        static JSBool removeLine(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool insertLine(JSContext *cx, unsigned argc, JS::Value *vp);
        };
    }; // namespace io
}; // namespace wxjs
#endif // _wxjs_io_textline_h

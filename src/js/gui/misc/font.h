/*
 * wxJavaScript - font.h
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
 * $Id: font.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJSFont_H
#define _WXJSFont_H

#include "js/common/jswrap.h"
/////////////////////////////////////////////////////////////////////////////
// Name:        font.h
// Purpose:		Font ports wxFont to JavaScript.
// Author:      Franky Braem
// Modified by:
// Created:     05.07.02
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////
namespace zzzJs
{
    namespace gui
    {
        class Font : public JsWrapper<Font, wxFont>
        {
        public:
			ZZZJS_DECLARE_GET_PROP(wxFont)
			ZZZJS_DECLARE_SET_PROP(wxFont)
            static bool GetStaticProperty(JSContext* cx,
                                    int id,
                                    JS::MutableHandle<JS::Value>& vp);
            static bool SetStaticProperty(JSContext* cx, 
                                    int id,
                                    JS::MutableHandle<JS::Value> &vp);		
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxFont)


			// コンスタント値の定義
			ZZZJS_DECLARE_CONSTRUCTOR(wxFont)
				
			//// Object 2 Instatance
			//static wxFont* getObject2Instance(JSContext *cx, JS::Value v, wxFont& workData);
			//static wxFont* getObject2Instance(JSContext *cx, JSObject *obj, wxFont& workData);


	        ZZZJS_DECLARE_STATIC_PROPERTY_MAP()
	        ZZZJS_DECLARE_CONSTANT_MAP()
			
			// Propeties
	        enum
	        {
		        P_DEFAULT_ENCODING
		        , P_FACE_NAME
		        , P_FAMILY
		        , P_POINT_SIZE
		        , P_STYLE
		        , P_UNDERLINED
		        , P_WEIGHT
                , P_OK
	        };
	        ZZZJS_DECLARE_PROPERTY_MAP()


        };

		// グローバルオブジェクトを登録する関数
		void DefineGlobalFonts(JSContext *cx, JSObject *obj);
		void DefineGlobalFont(JSContext *cx, JSObject *obj,
								const char *name, const wxFont*pFont);
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSFont_H

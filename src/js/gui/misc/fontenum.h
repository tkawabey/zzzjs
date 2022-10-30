/*
 * wxJavaScript - fontenum.h
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
 * $Id: fontenum.h 715 2007-05-18 20:38:04Z fbraem $
 */
#ifndef _WXJSFontEnumerator_H
#define _WXJSFontEnumerator_H

#include <wx/fontenum.h>
#include "js/common/jswrap.h"

namespace zzzJs
{
	namespace gui
	{

		class FontEnumerator : public wxFontEnumerator
			, public JsWrapper<FontEnumerator, FontEnumerator>
		{
		public:
			/**
			* Constructor
			*/
			FontEnumerator(JSContext *cx, JSObject *obj);

			/**
			* Destructor
			*/
			virtual ~FontEnumerator();

			static bool GetStaticProperty(JSContext* cx,
						int id,
						JS::MutableHandle<JS::Value>& vp);
			
			ZZZJS_DECLARE_CONSTRUCTOR(FontEnumerator)
        	

			bool OnFacename(const wxString &faceName);
			bool OnFontencoding(const wxString &faceName, const wxString &encoding);

			
			// Static Propeties
			enum
			{
				  P_FACENAMES
				, P_ENCODINGS
			};
			ZZZJS_DECLARE_STATIC_PROPERTY_MAP()

			// Methods
			ZZZJS_DECLARE_METHOD_MAP()
			ZZZJS_DECLARE_METHOD(enumerateFacenames);
			ZZZJS_DECLARE_METHOD(enumerateEncodings);
		private:
			JavaScriptClientData *m_data;
		};
	}; // namespace gui
}; // namespace wxjs

#endif //_WXJSFontEnumerator_H

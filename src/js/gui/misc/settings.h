#ifndef _WXJSSettings_H
#define _WXJSSettings_H

/*
 * wxJavaScript - settings.h
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
 * Remark: This class was donated by Philip Taylor
 *
 * $Id$
 */
#include "js/common/apiwrap.h"



namespace zzzJs
{
	namespace gui
	{
		class SystemSettings : public ApiWrapper<SystemSettings, wxSystemSettings>
		{
		public:
			enum
			{
				P_SCREEN_TYPE
			};

			WXJS_DECLARE_CONSTANT_MAP()

			WXJS_DECLARE_STATIC_PROPERTY_MAP()
			static bool GetStaticProperty(JSContext *cx, int id, JS::MutableHandle<JS::Value>& vp);
			static bool SetStaticProperty(JSContext *cx, int id, JS::MutableHandle<JS::Value>& vp);

			WXJS_DECLARE_STATIC_METHOD_MAP()
			static JSBool getColour(JSContext *cx, unsigned argc, JS::Value *vp);
			static JSBool getFont(JSContext *cx, unsigned argc, JS::Value *vp);
			static JSBool getMetric(JSContext *cx, unsigned argc, JS::Value *vp);
			static JSBool hasFeature(JSContext *cx, unsigned argc, JS::Value *vp);
		};
	}; // namespace gui
}; // namespace wxjs

#endif //_WXJSSettings_H

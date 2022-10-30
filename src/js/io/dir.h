/*
 * wxJavaScript - dir.h
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
 * $Id: dir.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJSDir_H
#define _WXJSDir_H

#include "js/common/jswrap.h"
/////////////////////////////////////////////////////////////////////////////
// Name:        dir.h
// Purpose:     wxJSDir ports wxDir to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     27.09.2002
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

#include <wx/dir.h>

namespace zzzJs
{
    namespace io
    {

        class Dir : public JsWrapper<Dir, wxDir>
        {
        public:
            /**
             * Callback for retrieving properties of wxDir
             */
			ZZZJS_DECLARE_GET_PROP(wxDir)
            //static bool GetProperty(wxDir *p, 
            //                      JSContext *cx, 
            //                      JSObject *obj, 
            //                      int id, 
            //                      JS::MutableHandle<JS::Value>& vp);

            /**
             * Callback for when a wxDir object is created
             */
			ZZZJS_DECLARE_CONSTRUCTOR(wxDir)
          //  static wxDir* Construct(JSContext *cx, 
										//unsigned int argc, 
										//JS::Value *vp, 
										//bool constructing);

            static JSBool open(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool getFirst(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool getNext(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool hasFiles(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool hasSubDirs(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool traverse(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool exists(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool getAllFiles(JSContext *cx, unsigned argc, JS::Value *vp);

            ZZZJS_DECLARE_PROPERTY_MAP()
            ZZZJS_DECLARE_CONSTANT_MAP()
            ZZZJS_DECLARE_METHOD_MAP()
            ZZZJS_DECLARE_STATIC_METHOD_MAP()

            /**
             * Property Ids.
             */
            enum
            {
                P_OPENED,
		        P_NAME
            };
        };
    }; // namespace io
}; // namespace wxjs
#endif //_WXJSDir_H


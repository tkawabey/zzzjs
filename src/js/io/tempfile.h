/*
 * wxJavaScript - tempfile.h
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
 * $Id: tempfile.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJS_TEMPFILE_H
#define _WXJS_TEMPFILE_H

/////////////////////////////////////////////////////////////////////////////
// Name:        tempfile.h
// Purpose:		Ports wxFile to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     25.12.05
// Copyright:   (c) 2001-2005 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

#include <wx/file.h>

#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
        class TempFile : public JsWrapper<TempFile, wxTempFile>
        {
        public:
        	
	        //static bool GetProperty(wxTempFile *f, 
         //                         JSContext *cx, 
         //                         JSObject *obj, 
         //                         int id, 
         //                         JS::MutableHandle<JS::Value>& vp);
			ZZZJS_DECLARE_GET_PROP(wxTempFile)

	        enum
	        { 
	          P_OPENED
	          , P_LENGTH
	          , P_TELL
	        };

	        ZZZJS_DECLARE_PROPERTY_MAP()
	        ZZZJS_DECLARE_METHOD_MAP()


			ZZZJS_DECLARE_CONSTRUCTOR(wxTempFile)

	        static JSBool commit(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool open(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool seek(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool write(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool discard(JSContext *cx, unsigned argc, JS::Value *vp);
        };
    }; // namespace io
}; // namespace wxjs
#endif

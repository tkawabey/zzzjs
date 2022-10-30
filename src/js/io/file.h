/*
 * wxJavaScript - file.h
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
 * $Id: file.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJS_FILE_H
#define _WXJS_FILE_H

/////////////////////////////////////////////////////////////////////////////
// Name:        file.h
// Purpose:		Ports wxFile to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     30.08.02
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

#include <wx/file.h>

#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
    class File : public JsWrapper<File, wxFile>
    {
    public:
    	
			ZZZJS_DECLARE_GET_PROP(wxFile)
	    //static bool GetProperty(wxFile *f, 
     //                             JSContext *cx, 
     //                             JSObject *obj, 
     //                             int id, 
     //                             JS::MutableHandle<JS::Value>& vp);

	    enum
	    { 
	      P_EOF
	      , P_OPENED
	      , P_LENGTH
	      , P_TELL
	      , P_KIND
	    };

	    ZZZJS_DECLARE_PROPERTY_MAP()
	    ZZZJS_DECLARE_METHOD_MAP()
	    ZZZJS_DECLARE_CONSTANT_MAP()
	    ZZZJS_DECLARE_STATIC_METHOD_MAP()

	    static void InitClass(JSContext *cx, JSObject *obj, JSObject *proto);

	    //static wxFile *Construct(JSContext *cx, 
					//					unsigned int argc, 
					//					JS::Value *vp, 
					//					bool constructing);
			ZZZJS_DECLARE_CONSTRUCTOR(wxFile)

	    static JSBool attach(JSContext *cx, unsigned argc, JS::Value *vp);
	    static JSBool detach(JSContext *cx, unsigned argc, JS::Value *vp);
	    static JSBool close(JSContext *cx, unsigned argc, JS::Value *vp);
	    static JSBool create(JSContext *cx, unsigned argc, JS::Value *vp);
	    static JSBool flush(JSContext *cx, unsigned argc, JS::Value *vp);
	    static JSBool open(JSContext *cx, unsigned argc, JS::Value *vp);
	    static JSBool read(JSContext *cx, unsigned argc, JS::Value *vp);
	    static JSBool seek(JSContext *cx, unsigned argc, JS::Value *vp);
	    static JSBool seekEnd(JSContext *cx, unsigned argc, JS::Value *vp);
	    static JSBool write(JSContext *cx, unsigned argc, JS::Value *vp);
	    static JSBool exists(JSContext *cx, unsigned argc, JS::Value *vp);
	    static JSBool access(JSContext *cx, unsigned argc, JS::Value *vp);
    };
    }; // namespace io
}; // namespace wxjs
#endif

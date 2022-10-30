/*
 * wxJavaScript - filename.h
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
 * $Id: filename.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJSFileName_H
#define _WXJSFileName_H

/////////////////////////////////////////////////////////////////////////////
// Name:        filename.h
// Purpose:     wxJSFileName ports wxFileName to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     14-01-2003
// Copyright:   (c) 2001-2003 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

#include <wx/filename.h>

#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
        class FileName : public JsWrapper<FileName, wxFileName>
        {
        public:
            /**
             * Callback for retrieving properties of wxFileName
             */
            //static bool GetProperty(wxFileName *p, 
            //                      JSContext *cx, 
            //                      JSObject *obj, 
            //                      int id, 
            //                      JS::MutableHandle<JS::Value>& vp);
			ZZZJS_DECLARE_GET_PROP(wxFileName)

            /**
             * Callback for setting properties
             */
            //static bool SetProperty(wxFileName *p,   
            //                      JSContext *cx, 
            //                      JSObject *obj, 
            //                      int id, 
            //                      JS::MutableHandle<JS::Value>& vp);
			ZZZJS_DECLARE_SET_PROP(wxFileName)

            static bool GetStaticProperty(JSContext *cx, int id, JS::MutableHandle<JS::Value>& vp);
            static bool SetStaticProperty(JSContext *cx, int id, JS::MutableHandle<JS::Value>& vp);
            
            static void InitClass(JSContext *cx, JSObject *obj, JSObject *proto);
            
            /**
             * Callback for when a wxFileName object is created
             */
          //  static wxFileName* Construct(JSContext *cx, 
										//unsigned int argc, 
										//JS::Value *vp, 
										//bool constructing);
			ZZZJS_DECLARE_CONSTRUCTOR(wxFileName)

            static JSBool appendDir(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool assign(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool assignCwd(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool assignDir(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool assignHomeDir(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool assignTempFileName(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool clear(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool getFullPath(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool getPath(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool getPathSeparator(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool getPathSeparators(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool getTimes(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool setTimes(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool getVolumeSeparator(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool insertDir(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool isAbsolute(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool isCaseSensitive(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool isPathSeparator(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool isRelative(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool makeRelativeTo(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool mkdir(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool normalize(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool prependDir(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool removeDir(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool removeLastDir(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool rmdir(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool sameAs(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool setCwd(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool touch(JSContext *cx, unsigned argc, JS::Value *vp);

            ZZZJS_DECLARE_PROPERTY_MAP()
            ZZZJS_DECLARE_METHOD_MAP()
	        ZZZJS_DECLARE_STATIC_PROPERTY_MAP()
            ZZZJS_DECLARE_STATIC_METHOD_MAP()

            static JSBool createTempFileName(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool dirExists(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool dirName(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool fileExists(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool fileName(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool getCwd(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool getFormat(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool smkdir(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool srmdir(JSContext *cx, unsigned argc, JS::Value *vp);
            static JSBool splitPath(JSContext *cx, unsigned argc, JS::Value *vp);

            /**
             * Property Ids.
             */
            enum
            {
                P_CWD = -128
                , P_DIRS
                , P_DIR_COUNT
                , P_DIR_EXISTS
                , P_EXT
                , P_HAS_EXT
                , P_HAS_NAME
                , P_HAS_VOLUME
                , P_FILE_EXISTS
                , P_FULL_NAME
                , P_FULL_PATH
                , P_HOME_DIR
                , P_LONG_PATH
                , P_MODIFICATION_TIME
                , P_NAME
                , P_PATH_SEPARATOR
                , P_PATH_SEPARATORS
                , P_SHORT_PATH
                , P_ACCESS_TIME
                , P_CREATE_TIME
                , P_VOLUME
                , P_VOLUME_SEPARATOR
                , P_OK
                , P_IS_DIR
            };

            static bool SetDate(JSContext *cx, jsval v, const wxDateTime &date);
        };
    }; // namespace io
}; // namespace wxjs
#endif //_WXJSFileName_H

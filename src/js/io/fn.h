/*
 * wxJavaScript - fn.h
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
 * $Id: fn.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef wxjs_io_fn_h
#define wxjs_io_fn_h

// Common functions

#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
        JSBool concatFiles(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool copyFile(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool renameFile(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool removeFile(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool fileExists(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool getCwd(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool getFreeDiskSpace(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool getTotalDiskSpace(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool getOSDirectory(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool isAbsolutePath(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool isWild(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool dirExists(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool matchWild(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool mkDir(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool rmDir(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool setWorkingDirectory(JSContext *cx, unsigned argc, JS::Value *vp);
        
        // Process functions
        JSBool execute(JSContext *cx, unsigned argc, JS::Value *vp);
        JSBool shell(JSContext *cx, unsigned argc, JS::Value *vp);
    }; // namespace io
}; // namespace wxjs
#endif //wxjs_io_fn_h

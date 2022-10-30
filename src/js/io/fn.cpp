/*
 * wxJavaScript - fn.cpp
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
 * $Id: fn.cpp 732 2007-06-05 19:39:26Z fbraem $
 */
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/wfstream.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/jsutil.h"
#include "js/io/fn.h"
#include "js/io/process.h"



using namespace zzzJs;

/***
 * <file>fn</file>
 * <module>io</module>
 * <class name="Global Functions" version="0.8.5">
 *  A list of global IO functions
 * </class>
 */

/***
 * <method name="wxConcatFiles">
 *  <function returns="Boolean">
 *   <arg name="File1" type=WXJS_TYPE_STRING />
 *   <arg name="File2" type=WXJS_TYPE_STRING />
 *   <arg name="File3" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Concatenates file1 and file2 to file3, returning true if successful.
 *  </desc>
 * </method>
 */
JSBool io::concatFiles(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString file1;
	wxString file2;
	wxString file3;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[2], file3);
	FromJS(cx, argv[1], file2);
	FromJS(cx, argv[0], file1);

	*vp = ToJS(cx, wxConcatFiles(file1, file2, file3));
	return JS_TRUE;
}

/***
 * <method name="wxCopyFile">
 *  <function returns="Boolean">
 *   <arg name="SourceFile" type=WXJS_TYPE_STRING />
 *   <arg name="TargetFile" type=WXJS_TYPE_STRING />
 *   <arg name="Overwrite" type="Boolean" default="true" />
 *  </function>
 *  <desc>
 *   Copies SourceFile to TargetFile, returning true if successful.
 *   If overwrite parameter is true (default), the destination file 
 *   is overwritten if it exists, but if overwrite is false, the 
 *   functions fails in this case.
 *  </desc>
 * </method>
 */
JSBool io::copyFile(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString file1;
	wxString file2;
	bool overwrite = true;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	if ( argc == 3 )
	{
		if ( ! FromJS(cx, argv[2], overwrite) )
		{
			return JS_FALSE;
		}
	}

	FromJS(cx, argv[1], file2);
	FromJS(cx, argv[0], file1);

	*vp = ToJS(cx, wxCopyFile(file1, file2, overwrite));
	return JS_TRUE;
}

/***
 * <method name="wxDirExists">
 *  <function returns="Boolean">
 *   <arg name="Dir" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Returns true if the directory exists
 *  </desc>
 * </method>
 */
JSBool io::dirExists(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString file;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[0], file);
	*vp = ToJS(cx, wxDirExists(file));
	return JS_TRUE;
}

/***
 * <method name="wxGetCwd">
 *  <function returns=WXJS_TYPE_STRING />
 *  <desc>
 *   Returns a string containing the current (or working) directory.
 *  </desc>
 * </method>
 */
JSBool io::getCwd(JSContext *cx, unsigned argc, JS::Value *vp)
{
	*vp = ToJS(cx, wxGetCwd());
	return JS_TRUE;
}

/***
 * <method name="wxGetFreeDiskSpace">
 *  <function returns=WXJS_TYPE_DOUBLE>
 *   <arg name="File" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Returns the free diskspace. Returns -1 if the path doesn't exist.
 *   Unlike wxWidgets, which implements this function as wxGetDiskSpace, 
 *   wxJS has to separate this into two functions.
 *  </desc>
 * </method>
 */
JSBool io::getFreeDiskSpace(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString path;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[0], path);

	wxLongLong free;
	if ( wxGetDiskSpace(path, NULL, &free) )
	{
		*vp = ToJS(cx, free.ToDouble());
	}
	else
	{
		*vp = ToJS(cx, (double) -1);
	}
	return JS_TRUE;
}

/***
 * <method name="wxGetTotalDiskSpace">
 *  <function returns=WXJS_TYPE_DOUBLE>
 *   <arg name="File" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Returns the free diskspace. Returns -1 if the path doesn't exist.
 *   Unlike wxWidgets, which implements this function as wxGetDiskSpace, 
 *   wxJS has to separate this into two functions.
 *  </desc>
 * </method>
 */
JSBool io::getTotalDiskSpace(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString path;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[0], path);

	wxLongLong total;
	if ( wxGetDiskSpace(path, &total) )
	{
		*vp = ToJS(cx, total.ToDouble());
	}
	else
	{
		*vp = ToJS(cx, (double) -1);
	}
	return JS_TRUE;
}

/***
 * <method name="wxFileExists">
 *  <function returns="Boolean">
 *   <arg name="File" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Returns true if the file exists.
 *  </desc>
 * </method>
 */
JSBool io::fileExists(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString file1;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[0], file1);

	*vp = ToJS(cx, wxFileExists(file1));
	return JS_TRUE;
}

/***
 * <method name="wxGetOSDirectory">
 *  <function returns=WXJS_TYPE_STRING />
 *  <desc>
 *   Returns the Windows directory under Windows; on other platforms returns the empty string.
 *  </desc>
 * </method>
 */
JSBool io::getOSDirectory(JSContext *cx, unsigned argc, JS::Value *vp)
{
	*vp = ToJS(cx, wxGetOSDirectory());
	return JS_TRUE;
}

/***
 * <method name="wxIsAbsolutePath">
 *  <function returns="Boolean">
 *   <arg name="File" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Returns true if the argument is an absolute filename, i.e. with a slash or drive name at the beginning.
 *  </desc>
 * </method>
 */
JSBool io::isAbsolutePath(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString file;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[0], file);
	*vp = ToJS(cx, wxIsAbsolutePath(file));
	return JS_TRUE;
}

/***
 * <method name="wxIsWild">
 *  <function returns="Boolean">
 *   <arg name="Pattern" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Returns true if the pattern contains wildcards.
 *  </desc>
 * </method>
 */
JSBool io::isWild(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString pattern;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[0], pattern);

	*vp = ToJS(cx, wxIsWild(pattern));
	return JS_TRUE;
}


/***
 * <method name="wxMatchWild">
 *  <function returns="Boolean">
 *   <arg name="Pattern" type=WXJS_TYPE_STRING />
 *   <arg name="Text" type=WXJS_TYPE_STRING />
 *   <arg name="DotSpecial" type="Boolean" />
 *  </function>
 *  <desc>
 *   Returns true if the pattern matches the text; if DotSpecial is true, filenames beginning with 
 *   a dot are not matched with wildcard characters.
 *  </desc>
 * </method>
 */
JSBool io::matchWild(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString pattern;
	wxString text;
	bool dotSpecial;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[2], dotSpecial);
	FromJS(cx, argv[1], text);
	FromJS(cx, argv[0], pattern);

	*vp = ToJS(cx, wxMatchWild(pattern, text, dotSpecial));
	return JS_TRUE;
}

/***
 * <method name="wxMkDir">
 *  <function returns="Boolean">
 *   <arg name="Dir" type=WXJS_TYPE_STRING />
 *   <arg name="Perm" type=WXJS_TYPE_NUMBER default="0777" />
 *  </function>
 *  <desc>
 *   Makes the directory dir, returning true if successful.
 *   perm is the access mask for the directory for the systems on which it is
 *   supported (Unix) and doesn't have effect for the other ones. 
 *  </desc>
 * </method>
 */
JSBool io::mkDir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString dir;
	int perm = 777;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	if ( argc > 0 )
	{
		if ( ! FromJS(cx, argv[1], perm) )
			return JS_FALSE;
	}

	*vp = ToJS(cx, wxMkdir(dir, perm));
	return JS_TRUE;
}

/***
 * <method name="wxRenameFile">
 *  <function returns="Boolean">
 *   <arg name="From" type=WXJS_TYPE_STRING />
 *   <arg name="To" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Renames the file <i>From</i> to <i>To</i>, returning true if successful.
 *  </desc>
 * </method>
 */
JSBool io::renameFile(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString file1;
	wxString file2;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[1], file2);
	FromJS(cx, argv[0], file1);

	*vp = ToJS(cx, wxRenameFile(file1, file2));
	return JS_TRUE;
}

/***
 * <method name="wxRemoveFile">
 *  <function returns="Boolean">
 *   <arg name="File" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Removes the file, return true on success.
 *  </desc>
 * </method>
 */
JSBool io::removeFile(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString file;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[0], file);

	*vp = ToJS(cx, wxRemoveFile(file));
	return JS_TRUE;
}

/***
 * <method name="wxRmDir">
 *  <function returns="Boolean">
 *   <arg name="Dir" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Removes the directory. Returns true on success. 
 *  </desc>
 * </method>
 */
JSBool io::rmDir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString dir;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    FromJS(cx, argv[0], dir);
    #if defined( __WXMAC__)  || defined(__WXGTK__)
      *vp = ToJS(cx, wxRmDir(dir.mb_str()));
    #else
      *vp = ToJS(cx, wxRmDir(dir));
    #endif 
    return JS_TRUE;
}

/***
 * <method name="wxSetWorkingDirectory">
 *  <function returns="Boolean">
 *   <arg name="Dir" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Sets the current working directory, returning true if the operation succeeded. 
 *   Under MS Windows, the current drive is also changed if dir contains a drive specification.
 *  </desc>
 * </method>
 */
JSBool io::setWorkingDirectory(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString dir;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[0], dir);

	*vp = ToJS(cx, wxSetWorkingDirectory(dir));
	return JS_TRUE;
}

/***
 * <method name="wxExecute">
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="Cmd" type=WXJS_TYPE_STRING />
 *   <arg name="Flags" type="@wxExecFlag" default="wxExecFlag.ASYNC" />
 *   <arg name="Process" type="@wxProcess" default="null" />
 *  </function>
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="Argv" type="Array String" />
 *   <arg name="Flags" type="@wxExecFlag" default="wxExecFlag.ASYNC" />
 *   <arg name="Process" type="@wxProcess" default="null" />
 *  </function>
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="Cmd" type=WXJS_TYPE_STRING />
 *   <arg name="Output" type="Array String" />
 *   <arg name="Flags" type="@wxExecFlag" default="wxExecFlag.ASYNC" />
 *  </function>
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="Cmd" type=WXJS_TYPE_STRING />
 *   <arg name="Output" type="Array String" />
 *   <arg name="Errors" type="Array String" />
 *   <arg name="Flags" type="@wxExecFlag" default="wxExecFlag.ASYNC" />
 *  </function>
 *  <desc>
 *  </desc>
 * </method>
 */
JSBool io::execute(JSContext *cx, unsigned argc, JS::Value *vp)
{
    int flags = wxEXEC_ASYNC;
    wxString cmd;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( JSVAL_IS_STRING(argv[0]) )
    {
        FromJS(cx, argv[0], cmd);
        if ( argc == 1 )
        {
            *vp = ToJS(cx, wxExecute(cmd));
            return JS_TRUE;
        }

        if ( JSVAL_IS_INT(argv[1]) )
        {
            wxProcess *p = NULL;
            if ( argc > 2 )
            {
                p = Process::GetPrivate(cx, argv[2]);
            }
            if ( FromJS(cx, argv[1], flags) )
            {
                *vp = ToJS(cx, wxExecute(cmd, flags, p));
            }
            return JS_TRUE;
        }
		else if ( argv[1].isObject() )
        {
            wxArrayString output;
            wxArrayString error;

            if ( argc > 3 )
            {
                if ( ! FromJS(cx, argv[3], flags) )
                    return JS_FALSE;
            }
            if (    argc > 2
                 && JSVAL_IS_INT(argv[2]) )
            {
                if ( ! FromJS(cx, argv[2], flags) )
                    return JS_FALSE;
            }
            *vp = ToJS(cx, wxExecute(cmd, output, error, flags));

			if ( argc > 2 && argv[2].isObject() )
            {
                JSObject *objArr = JSVAL_TO_OBJECT(argv[2]);
                if ( JS_IsArrayObject(cx, objArr) )
                {
                    for(wxArrayString::size_type i = 0; i < error.size(); i++)
                    {
                        jsval element = ToJS(cx, error[i]);
                        JS_SetElement(cx, objArr, i, &element);
                    }
                }
            }

			if ( argc > 1 && argv[1].isObject() )
            {
                JSObject *objArr = JSVAL_TO_OBJECT(argv[1]);
                if ( JS_IsArrayObject(cx, objArr) )
                {
                    for(wxArrayString::size_type i = 0; i < output.size(); i++)
                    {
                        jsval element = ToJS(cx, output[i]);
                        JS_SetElement(cx, objArr, i, &element);
                    }
                }
            }
            return JS_TRUE;
        }
    }
	else if ( argv[0].isObject() )
    {
        JSObject *objArr = JSVAL_TO_OBJECT(argv[0]);
        if ( JS_IsArrayObject(cx, objArr) )
        {
            wxProcess *p = NULL;
            switch(argc)
            {
            case 3:
                p = (wxProcess *) Process::GetPrivate(cx, argv[2]);
                // Fall through
            case 2:
                if ( ! FromJS(cx, argv[1], flags) )
                    break;
                // Fall through
            default:
                {
                    uint32_t length;
                    JS_GetArrayLength(cx, objArr, &length);
                    if ( length > 0 )
                    {
                        wxChar **cmdArgv = new wxChar*[length + 1];
                        for(uint32_t i = 0; i < length; i++)
                        {
                            jsval element;
                            if ( JS_GetElement(cx, objArr, i, &element) == JS_TRUE )
                            {
                                wxString arg;
                                FromJS(cx, element, arg);

                                cmdArgv[i] = new wxChar[arg.Length() + 1];
                                wxStrncpy(cmdArgv[i], arg.c_str(), arg.Length());
                                cmdArgv[i][arg.Length()] = '\0';
                            }
                        }
                        cmdArgv[length] = NULL;
                        *vp = ToJS(cx, wxExecute(cmdArgv, flags, p));
                        delete[] cmdArgv;
                    }
                    return JS_TRUE;
                }
            }
        }
    }
	return JS_FALSE;
}

/***
 * <method name="wxShell">
 *  <function returns="Boolean">
 *   <arg name="Cmd" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Executes a command in an interactive shell window. If no command is specified,
 *   then just the shell is spawned.
 *  </desc>
 * </method>
 */
JSBool io::shell(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString cmd;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	FromJS(cx, argv[0], cmd);

	*vp = ToJS(cx, wxShell(cmd));
	return JS_TRUE;
}

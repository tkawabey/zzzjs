/*
 * wxJavaScript - filename.cpp
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
 * $Id: filename.cpp 730 2007-06-05 19:29:52Z fbraem $
 */
// filename.cpp
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
#include "js/io/filename.h"
#include "js/io/file.h"



using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>filename</file>
 * <module>io</module>
 * <class name="wxFileName" version="0.8.2">
 *  wxFileName encapsulates a file name. This class serves two purposes: first, it provides 
 *  the functions to split the file names into components and to recombine these components 
 *  in the full file name which can then be passed to the OS file functions (and wxWindows 
 *  functions wrapping them). Second, it includes the functions for working with the files 
 *  itself. 
 *  <br /><br />
 *  <b>Remark:</b> To change the file data you should use @wxFile class instead. 
 *  wxFileName provides functions for working with the file attributes. 
 *  <br /><br />
 *  <b>Remark:</b> Some of the properties of wxFileName causes IO processing. For example: 
 *  @wxFileName#accessTime will execute an IO API to retrieve the last access time
 *  of the file. This can result in performance issues when you use this property
 *  frequently. The best solution for this is to put the property in a variable and
 *  use that variable instead of the property:
 *  <pre><code class="whjs">
 *   // Do this
 *   var fileName = new wxFileName("test.txt");
 *   var acc = fileName.accessTime;
 *   // From now on use var acc instead of fileName.accessTime
 *  </code></pre>
 * </class>
 */
ZZZJS_INIT_CLASS(FileName, "FileName", 0)

/***
 * <constants>
 *  <type name="wxPathFormat">
 *   <constant name="NATIVE" />
 *   <constant name="UNIX" />
 *   <constant name="MAC" />
 *   <constant name="DOS" />
 *   <constant name="VMS" />
 *   <constant name="BEOS" />
 *   <constant name="WIN" />
 *   <constant name="OS2" />
 *   <desc>
 *    wxPathFormat is ported as a separate JavaScript object.
 *    Many wxFileName methods accept the path format argument which is 
 *    wxPathFormat.NATIVE by default meaning to use the path format native for
 *    the current platform.
 *    <br /><br />
 *    The path format affects the operation of wxFileName functions in 
 *    several ways: first and foremost, it defines the path separator character 
 *    to use, but it also affects other things such as whether the path has 
 *    the drive part or not.
 *   </desc>
 *  </type>
 *  <type name="wxPathNormalize">
 *   <constant name="ENV_VARS">Replace env vars with their values</constant>
 *   <constant name="DOTS">Squeeze all .. and . and prepend cwd</constant>
 *   <constant name="TILDE">Unix only: replace ~ and ~user</constant>
 *   <constant name="CASE">Case insensitive => tolower</constant>
 *   <constant name="ABSOLUTE">Make the path absolute</constant>
 *   <constant name="LONG">Make the path the long form</constant>
 *   <constant name="SHORTCUT">Resolve if it is a shortcut (Windows only)</constant>
 *   <constant name="ALL" />
 *   <desc>
 *    wxPathNormalize is ported as a separate JavaScript object.
 *    The kind of normalization to do with the file name: these values can be or'd
 *    together to perform several operations at once in @wxFileName#normalize.
 *   </desc>
 *  </type>
 *  <type name="wxPathGet">
 *   <constant name="VOLUME">Return the path with the volume (does nothing for the filename formats without volumes)</constant>
 *   <constant name="SEPARATOR">Return the path with the trailing separator, if this flag is not given 
 *    there will be no separator at the end of the path.</constant>
 *   <desc>
 *    wxPathGet is ported as a separate JavaScript object.
 *   </desc>
 *  </type>
 *  <type name="wxPathMkdir">
 *   <constant name="FULL">Try to create each directory in the path and also don't return an error
 *    if the target directory already exists.</constant>
 *   <desc>
 *    wxPathMkDir is ported as a separate JavaScript object.
 *   </desc>
 *  </type>
 * </constants>
 */
void FileName::InitClass(JSContext *cx, JSObject *obj, JSObject *proto)
{
    JSConstDoubleSpec wxPathFormatMap[] = 
    {
        ZZZJS_CONSTANT(wxPATH_, NATIVE)
        ZZZJS_CONSTANT(wxPATH_, UNIX)
        ZZZJS_CONSTANT(wxPATH_, MAC)
        ZZZJS_CONSTANT(wxPATH_, DOS)
        ZZZJS_CONSTANT(wxPATH_, VMS)
        ZZZJS_CONSTANT(wxPATH_, BEOS)
        ZZZJS_CONSTANT(wxPATH_, WIN)
        ZZZJS_CONSTANT(wxPATH_, OS2)
	    { 0 }
    };

    JSObject *constObj = JS_DefineObject(cx, obj, "wxPathFormat", 
									 	 NULL, NULL,
							             JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineConstDoubles(cx, constObj, wxPathFormatMap);

    JSConstDoubleSpec wxPathNormalizeMap[] = 
    {
        ZZZJS_CONSTANT(wxPATH_NORM_, ENV_VARS)
        ZZZJS_CONSTANT(wxPATH_NORM_, DOTS)
        ZZZJS_CONSTANT(wxPATH_NORM_, TILDE)
        ZZZJS_CONSTANT(wxPATH_NORM_, CASE)
        ZZZJS_CONSTANT(wxPATH_NORM_, ABSOLUTE)
        ZZZJS_CONSTANT(wxPATH_NORM_, LONG)
        ZZZJS_CONSTANT(wxPATH_NORM_, SHORTCUT)
        ZZZJS_CONSTANT(wxPATH_NORM_, ALL)
	    { 0 }
    };
    constObj = JS_DefineObject(cx, obj, "wxPathNormalize", 
		                       NULL, NULL,
							   JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineConstDoubles(cx, constObj, wxPathNormalizeMap);

    JSConstDoubleSpec wxPathGetMap[] = 
    {
        ZZZJS_CONSTANT(wxPATH_GET_, VOLUME)
        ZZZJS_CONSTANT(wxPATH_GET_, SEPARATOR)
	    { 0 }
    };
    constObj = JS_DefineObject(cx, obj, "wxPathGet", 
	 			               NULL, NULL,
							   JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineConstDoubles(cx, constObj, wxPathGetMap);

    JSConstDoubleSpec wxPathMkdirMap[] = 
    {
        ZZZJS_CONSTANT(wxPATH_MKDIR_, FULL)
	    { 0 }
    };
    constObj = JS_DefineObject(cx, obj, "wxPathMkdir", 
	 			               NULL, NULL,
							   JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineConstDoubles(cx, constObj, wxPathMkdirMap);
}

/***
 * <class_properties>
 *	<property name="cwd" type=ZZZJS_TYPE_STRING>Get/Set the current working directory.</property>
 *	<property name="homeDir" type=ZZZJS_TYPE_STRING>Get/Set the home directory.</property>
 *  <property name="pathSeparator" type=ZZZJS_TYPE_STRING readonly="Y">
 *   Returns the usually used path separator for the native platform.
 *   For all platforms but DOS and Windows there is only one path separator anyhow,
 *   but for DOS and Windows there are two of them.
 *  </property>
 *  <property name="pathSeparators" type=ZZZJS_TYPE_STRING readonly="Y"> 
 *   Gets the path separator of the native platform
 *  </property>
 *  <property name="volumeSeparator" type=ZZZJS_TYPE_STRING>
 *   Gets the string separating the volume from the path for the native format.
 *  </property>
 * </class_properties>
 */
ZZZJS_BEGIN_STATIC_PROPERTY_MAP(FileName)
  ZZZJS_STATIC_PROPERTY(P_CWD, "cwd")
  ZZZJS_STATIC_PROPERTY(P_HOME_DIR, "homeDir")
  ZZZJS_READONLY_STATIC_PROPERTY(P_PATH_SEPARATOR, "pathSeparator")
  ZZZJS_READONLY_STATIC_PROPERTY(P_PATH_SEPARATORS, "pathSeparators")
  ZZZJS_READONLY_STATIC_PROPERTY(P_VOLUME_SEPARATOR, "volumeSeparator")
ZZZJS_END_PROPERTY_MAP()

bool FileName::GetStaticProperty(JSContext *cx, int id, JS::MutableHandle<JS::Value>& vp)
{
    switch(id)
    {
    case P_CWD:
        ToJSVal(cx, vp, wxFileName::GetCwd());
        break;
    case P_HOME_DIR:
        ToJSVal(cx, vp, wxFileName::GetHomeDir());
        break;
    case P_PATH_SEPARATOR:
        ToJSVal(cx, vp, wxString(wxFileName::GetPathSeparator()));
        break;
    case P_PATH_SEPARATORS:
        ToJSVal(cx, vp, wxFileName::GetPathSeparators());
        break;
    case P_VOLUME_SEPARATOR:
        ToJSVal(cx, vp, wxFileName::GetVolumeSeparator());
        break;
    }
    return true;
}

bool FileName::SetStaticProperty(JSContext *cx, int id, JS::MutableHandle<JS::Value>& vp)
{
    switch(id)
    {
    case P_CWD:
        {
            wxString cwd;
            FromJS(cx, vp, cwd);
            wxFileName::SetCwd(cwd);
        }
	}
	return JS_TRUE;
}

/***
 * <properties>
 *  <property name="accessTime" type="Date">Get/Set the last access time</property>
 *  <property name="createTime" type="Date">Get/Set the creation time</property>
 *  <property name="dirCount" type=ZZZJS_TYPE_NUMBER readonly="Y">Returns the number of directories in the file name.</property>
 *  <property name="dirExists" type="Boolean" readonly="Y">Returns true when the directory exists.</property>
 *  <property name="ext" type=ZZZJS_TYPE_STRING>Get/Set the extension</property>
 *  <property name="fileExists" type="Boolean" readonly="Y">Returns true when the file exists.</property>
 *  <property name="fullName" type=ZZZJS_TYPE_STRING>Get/Set the full name (including extension but without directories).</property>
 *  <property name="fullPath" type=ZZZJS_TYPE_STRING>Returns the full path with name and extension for the native platform.</property>
 *  <property name="hasExt" type="boolean" readonly="Y">Returns true when an extension is present.</property>
 *  <property name="isDir" type="boolean" readonly="Y">Returns true if this object represents a directory, false otherwise (i.e. if it is a file).
 *  This property doesn't test whether the directory or file really exists, 
 *  you should use @wxFileName#dirExists or @wxFileName#fileExists for this.</property>
 *  <property name="longPath" type=ZZZJS_TYPE_STRING readonly="Y">Return the long form of the path (returns identity on non-Windows platforms).</property>
 *  <property name="modificationTime" type="Date">Get/Set the time the file was last modified</property>
 *  <property name="ok" type="Boolean" readonly="Y">
 *    Returns true if the filename is valid, false if it is not initialized yet. 
 *    The assignment functions and @wxFileName#clear may reset the object to
 *    the uninitialized, invalid state.</property>
 *  <property name="shortPath" type=ZZZJS_TYPE_STRING readonly="Y">
 *   Return the short form of the path (returns identity on non-Windows platforms).
 *  </property>
 *  <property name="volume" type=ZZZJS_TYPE_STRING>Get/Set the volume name for this file name.</property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(FileName)
    ZZZJS_READONLY_PROPERTY(P_DIR_COUNT, "dirCount")
    ZZZJS_READONLY_PROPERTY(P_DIRS, "dirs")
    ZZZJS_READONLY_PROPERTY(P_DIR_EXISTS, "dirExists")
    ZZZJS_PROPERTY(P_EXT, "ext")
    ZZZJS_READONLY_PROPERTY(P_FILE_EXISTS, "fileExists")
    ZZZJS_READONLY_PROPERTY(P_FULL_NAME, "fullName")
    ZZZJS_READONLY_PROPERTY(P_FULL_PATH, "fullPath")
    ZZZJS_READONLY_PROPERTY(P_HAS_EXT, "hasExt")
    ZZZJS_READONLY_PROPERTY(P_LONG_PATH, "longPath")
    ZZZJS_PROPERTY(P_MODIFICATION_TIME, "modificationTime")
    ZZZJS_PROPERTY(P_NAME, "name")
    ZZZJS_READONLY_PROPERTY(P_SHORT_PATH, "shortPath")
    ZZZJS_PROPERTY(P_ACCESS_TIME, "accessTime")
    ZZZJS_PROPERTY(P_CREATE_TIME, "createTime")
    ZZZJS_PROPERTY(P_VOLUME, "volume")
    ZZZJS_READONLY_PROPERTY(P_OK, "ok")
    ZZZJS_READONLY_PROPERTY(P_IS_DIR, "isDir")
ZZZJS_END_PROPERTY_MAP()

//bool FileName::GetProperty(wxFileName *p,  
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxFileName, FileName)
    switch (id)
    {
    case P_DIR_COUNT:
        ToJSVal(cx, vp, p->GetDirCount());
        break;
    case P_DIR_EXISTS:
        ToJSVal(cx, vp, p->DirExists());
        break;
    case P_DIRS:
        ToJSVal(cx, vp, p->GetDirs());
        break;
    case P_EXT:
        ToJSVal(cx, vp, p->GetExt());
        break;
    case P_FILE_EXISTS:
        ToJSVal(cx, vp, p->FileExists());
        break;
    case P_FULL_NAME:
        ToJSVal(cx, vp, p->GetFullName());
        break;
    case P_FULL_PATH:
        ToJSVal(cx, vp, p->GetFullPath());
        break;
    case P_HAS_EXT:
        ToJSVal(cx, vp, p->HasExt());
        break;
    case P_LONG_PATH:
        ToJSVal(cx, vp, p->GetLongPath());
        break;
    case P_MODIFICATION_TIME:
        ToJSVal(cx, vp, p->GetModificationTime());
        break;
    case P_NAME:
        ToJSVal(cx, vp, p->GetName());
        break;
    case P_SHORT_PATH:
        ToJSVal(cx, vp, p->GetShortPath());
        break;
    case P_ACCESS_TIME:
        {
            wxDateTime date;
            p->GetTimes(&date, NULL, NULL);
            ToJSVal(cx, vp, date);
            break;
        }
    case P_CREATE_TIME:
        {
            wxDateTime date;
            p->GetTimes(NULL, NULL, &date);
            ToJSVal(cx, vp, date);
            break;
        }
    case P_VOLUME:
        ToJSVal(cx, vp, p->GetVolume());
        break;
    case P_OK:
        ToJSVal(cx, vp, p->IsOk());
        break;
    case P_IS_DIR:
        ToJSVal(cx, vp, p->IsDir());
        break;
    }
    return true;
ZZZJS_END_GET_PROP

//bool FileName::SetProperty(wxFileName *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_SET_PROP(wxFileName, FileName)
    switch (id)
    {
    case P_EXT:
        {
            wxString ext;
            FromJS(cx, vp, ext);
            p->SetExt(ext);
            break;
        }
    case P_FULL_NAME:
        {
            wxString fullName;
            FromJS(cx, vp, fullName);
            p->SetFullName(fullName);
            break;
        }
    case P_NAME:
        {
            wxString name;
            FromJS(cx, vp, name);
            p->SetName(name);
            break;
        }
    case P_ACCESS_TIME:
        {
            wxDateTime date;
            if ( FromJS(cx, vp, date) )
                p->SetTimes(&date, NULL, NULL);
            break;
        }
    case P_CREATE_TIME:
        {
            wxDateTime date;
            if ( FromJS(cx, vp, date) )
                p->SetTimes(NULL, NULL, &date);
            break;
        }
    case P_MODIFICATION_TIME:
        {
            wxDateTime date;
            if ( FromJS(cx, vp, date) )
                p->SetTimes(NULL, &date, NULL);
            break;
        }
    case P_VOLUME:
        {
            wxString vol;
            FromJS(cx, vp, vol);
            p->SetVolume(vol);
            break;
        }
    }
    return true;
ZZZJS_END_SET_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="FileName" type="wxFileName" />
 *  </function>
 *  <function>
 *   <arg name="FullPath" type=ZZZJS_TYPE_STRING>
 *    A full path. When it terminates with a pathseparator, a directory path is constructed,
 *    otherwise a filename and extension is extracted from it.
 *   </arg>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <function>
 *   <arg name="Path" type=ZZZJS_TYPE_STRING>A directory name</arg>
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>A filename</arg>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <function>
 *   <arg name="Path" type=ZZZJS_TYPE_STRING>A directory name</arg>
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>A filename</arg>
 *   <arg name="Ext" type=ZZZJS_TYPE_STRING>An extension</arg>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <function>
 *   <arg name="Volume" type=ZZZJS_TYPE_STRING>A volume name</arg>
 *   <arg name="Path" type=ZZZJS_TYPE_STRING>A directory name</arg>
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>A filename</arg>
 *   <arg name="Ext" type=ZZZJS_TYPE_STRING>An extension</arg>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Constructs a new wxFileName object.
 *  </desc>
 * </ctor>
 */
//wxFileName* FileName::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(wxFileName, FileName)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( argc == 0 )
        return new wxFileName();

    if ( argc == 1 )
    {
        if ( FileName::HasPrototype(cx, argv[0]) )
        {
            return new wxFileName(*GetPrivate(cx, argv[0], false));
        }

        wxString filename;
        FromJS(cx, argv[0], filename);
        return new wxFileName(filename);
    }

    wxFileName *p = NULL;

    // Argc > 1
    int format = wxPATH_NATIVE;
    uintN stringCount = argc;
    if ( JSVAL_IS_INT(argv[argc-1]) )
    {
        FromJS(cx, argv[argc-1], format);
        stringCount--;
    }

    wxString *str = new wxString[stringCount];
    for(uintN i = 0; i < stringCount; i++)
        FromJS(cx, argv[i], str[i]);

    switch(stringCount)
    {
    case 1:
        p = new wxFileName(str[0], (wxPathFormat) format);
        break;
    case 2:
        p = new wxFileName(str[0], str[1], (wxPathFormat) format);
        break;
    case 3:
        p = new wxFileName(str[0], str[1], str[2], (wxPathFormat) format);
        break;
    case 4:
        p = new wxFileName(str[0], str[1], str[2], str[3], (wxPathFormat) format);
        break;
    }

    delete[] str;

    return p;
ZZZJS_END_CONSTRUCTOR

ZZZJS_BEGIN_METHOD_MAP(FileName)
    ZZZJS_METHOD("appendDir", appendDir, 1)
    ZZZJS_METHOD("assign", assign, 1)
    ZZZJS_METHOD("assignDir", assignDir, 1)
    ZZZJS_METHOD("assignHomeDir", assignHomeDir, 0)
    ZZZJS_METHOD("assignTempFileName", assignTempFileName, 1)
    ZZZJS_METHOD("clear", clear, 0)
    ZZZJS_METHOD("getFullPath", getFullPath, 0)
    ZZZJS_METHOD("getPath", getPath, 0)
    ZZZJS_METHOD("getPathSeparator", getPathSeparator, 0)
    ZZZJS_METHOD("getPathSeparators", getPathSeparators, 0)
    ZZZJS_METHOD("getTimes", getTimes, 3)
    ZZZJS_METHOD("setTimes", setTimes, 3)
    ZZZJS_METHOD("getVolumeSeparator", getVolumeSeparator, 0)
    ZZZJS_METHOD("insertDir", insertDir, 2)
    ZZZJS_METHOD("isAbsolute", isAbsolute, 0)
    ZZZJS_METHOD("isPathSeparator", isPathSeparator, 1)
    ZZZJS_METHOD("isRelative", isRelative, 0)
    ZZZJS_METHOD("makeRelativeTo", makeRelativeTo, 0)
    ZZZJS_METHOD("mkdir", mkdir, 0)
    ZZZJS_METHOD("normalize", normalize, 0)
    ZZZJS_METHOD("prependDir", prependDir, 1)
    ZZZJS_METHOD("removeDir", removeDir, 1)
    ZZZJS_METHOD("removeLastDir", removeLastDir, 0)
    ZZZJS_METHOD("rmdir", rmdir, 0)
    ZZZJS_METHOD("sameAs", sameAs, 1)
    ZZZJS_METHOD("setCwd", setCwd, 0)
    ZZZJS_METHOD("touch", touch, 0)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="appendDir">
 *  <function>
 *   <arg name="Dir" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Appends a directory component to the path. This component 
 *   should contain a single directory name level, i.e. not contain 
 *   any path or volume separators nor should it be empty, otherwise the function does nothing
 *  </desc>
 * </method>
 */
JSBool FileName::appendDir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxString dir;
    FromJS(cx, argv[0], dir);
    p->AppendDir(dir);
    return JS_TRUE;
}

/***
 * <method name="assign">
 *  <function>
 *   <arg name="FileName" type="wxFileName" />
 *  </function>
 *  <function>
 *   <arg name="FullPath" type=ZZZJS_TYPE_STRING>
 *    A full path. When it terminates with a pathseparator, a directory path is constructed,
 *    otherwise a filename and extension is extracted from it.
 *   </arg>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <function>
 *   <arg name="Path" type=ZZZJS_TYPE_STRING>A directory name</arg>
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>A filename</arg>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <function>
 *   <arg name="Path" type=ZZZJS_TYPE_STRING>A directory name</arg>
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>A filename</arg>
 *   <arg name="Ext" type=ZZZJS_TYPE_STRING>An extension</arg>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <function>
 *   <arg name="Volume" type=ZZZJS_TYPE_STRING>A volume name</arg>
 *   <arg name="Path" type=ZZZJS_TYPE_STRING>A directory name</arg>
 *   <arg name="Name" type=ZZZJS_TYPE_STRING>A filename</arg>
 *   <arg name="Ext" type=ZZZJS_TYPE_STRING>An extension</arg>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Creates the file name from various combinations of data.
 *  </desc>
 * </method>
 */
JSBool FileName::assign(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    if ( argc == 1 )
    {
        if ( HasPrototype(cx, argv[0]) )
        {
            p->Assign(*GetPrivate(cx, argv[0], false));
            return JS_TRUE;
        }

        wxString filename;
        FromJS(cx, argv[0], filename);
        p->Assign(filename);
        return JS_TRUE;
    }

    // Argc > 1
    int format = wxPATH_NATIVE;
    uintN stringCount = argc;
    if ( JSVAL_IS_INT(argv[argc-1]) )
    {
        FromJS(cx, argv[argc-1], format);
        stringCount--;
    }

    wxString *str = new wxString[stringCount];
    for(uintN i = 0; i < stringCount; i++)
        FromJS(cx, argv[i], str[i]);

    switch(stringCount)
    {
    case 1:
        p->Assign(str[0], (wxPathFormat) format);
        break;
    case 2:
        p->Assign(str[0], str[1], (wxPathFormat) format);
        break;
    case 3:
        p->Assign(str[0], str[1], str[2], (wxPathFormat) format);
        break;
    case 4:
        p->Assign(str[0], str[1], str[2], str[3], (wxPathFormat) format);
        break;
    }

    delete[] str;

    return JS_TRUE;
}

/***
 * <method name="assignDir">
 *  <function>
 *   <arg name="Dir" type=ZZZJS_TYPE_STRING />
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Sets this file name object to the given directory name. 
 *   The name and extension will be empty.
 *  </desc>
 * </method>
 */
JSBool FileName::assignDir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxString dir;
    FromJS(cx, argv[0], dir);

    int format = wxPATH_NATIVE;
    if (     argc > 1 
        && ! FromJS(cx, argv[1], format) )
        return JS_FALSE;

    p->AssignDir(dir, (wxPathFormat) format);
    return JS_TRUE;
}

/***
 * <method name="assignHomeDir">
 *  <function />
 *  <desc>
 *   Sets this file name object to the home directory.
 *  </desc>
 * </method>
 */
JSBool FileName::assignHomeDir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    p->AssignHomeDir();
    return JS_TRUE;
}

/***
 * <method name="assignTempFileName">
 *  <function>
 *   <arg name="Prefix" type=ZZZJS_TYPE_STRING />
 *   <arg name="File" type="@wxFile" default="undefined">
 *    Object with wil get the file pointer to the temp file.
 *   </arg>
 *  </function>
 *  <desc>
 *   The function calls @wxFileName#createTempFileName to create
 *   a temporary file and sets this object to the name of the file.
 *   If a temporary file couldn't be created, the object is put into the invalid state.
 *   See also @wxFile.
 *   <br /><br />
 *   The following sample shows how to create a file with a temporary filename:
 *   <pre><code class="whjs">
 *    var name = new wxFileName();
 *    var file = new wxFile();
 * 
 *    name.assignTempFileName('wxjs', file);
 *    file.write('This is a test');
 *    file.close();
 *
 *    wxMessageBox('Filename: ' + name.fullPath);
 *   </code></pre>
 *  </desc>
 * </method>
 */
JSBool FileName::assignTempFileName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxString prefix;
    FromJS(cx, argv[0], prefix);

    wxFile *file = NULL;
    if (     argc > 1 
        && (file = File::GetPrivate(cx, argv[1])) == NULL )
        return JS_FALSE;

    p->AssignTempFileName(prefix, file);
    return JS_TRUE;
}

/***
 * <method name="clear">
 *  <function />
 *  <desc>Reset all components to default, uninitialized state.</desc>
 * </method>
 */
JSBool FileName::clear(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    p->Clear();
    return JS_TRUE;
}

/***
 * <method name="getFullPath">
 *  <function returns=ZZZJS_TYPE_STRING>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Returns the full path with name and extension.
 *  </desc>
 * </method>
 */
JSBool FileName::getFullPath(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    int format = wxPATH_NATIVE;
    if (     argc > 0
        && ! FromJS(cx, argv[0], format) )
        return JS_FALSE;

    *vp = ToJS(cx, p->GetFullPath((wxPathFormat) format));
    return JS_TRUE;
}

/***
 * <method name="getPath">
 *  <function returns=ZZZJS_TYPE_STRING>
 *   <arg name="Flag" type="@wxFileName#wxPathGet" default="wxPathGet.VOLUME" />
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Returns the path part of the filename (without the name or extension).
 *  </desc>
 * </method>
 */
JSBool FileName::getPath(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    int flag = wxPATH_GET_VOLUME;
    int format = wxPATH_NATIVE;
    if (     argc > 0
        && ! FromJS(cx, argv[0], flag) )
        return JS_FALSE;

    if (      argc > 1
         && ! FromJS(cx, argv[0], format) )
        return JS_FALSE;

    *vp = ToJS(cx, p->GetPath(flag, (wxPathFormat) format));
    return JS_TRUE;
}

/***
 * <method name="getTimes">
 *  <function returns="Boolean">
 *   <arg name="AccessTime" type="Date" />
 *   <arg name="ModTime" type="Date" default="null" />
 *   <arg name="CreateTime" type="Date" default="null" />
 *  </function>
 *  <desc>
 *  Gets the last access, last modification and creation times. 
 *  The last access time is updated whenever the file is read 
 *  or written (or executed in the case of Windows), last modification 
 *  time is only changed when the file is written to. Finally, 
 *  the creation time is indeed the time when the file was created under 
 *  Windows and the inode change time under Unix (as it is impossible to 
 *  retrieve the real file creation time there anyhow) which can also be 
 *  changed by many operations after the file creation.
 *  <br /><br />
 *  Any of the arguments may be null if the corresponding time is not needed.
 *  </desc>
 * </method>
 */
JSBool FileName::getTimes(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxDateTime access;
    wxDateTime mod;
    wxDateTime create;

    if ( p->GetTimes(&access, &mod, &create) )
    {
        if ( argv[0] != JSVAL_VOID )
        {
            if ( ! SetDate(cx, argv[0], access) )
                return JS_FALSE;
        }
        
        if ( argv[1] != JSVAL_VOID )
        {
            if ( ! SetDate(cx, argv[1], mod) )
                return JS_FALSE;
        }

        if ( argv[2] != JSVAL_VOID )
        {
            if ( ! SetDate(cx, argv[2], create) )
                return JS_FALSE;
        }
        *vp = JSVAL_TRUE;
    }
    else
        *vp = JSVAL_FALSE;

    return JS_TRUE;
}

/***
 * <method name="setTimes">
 *  <function returns="Boolean">
 *   <arg name="AccessTime" type="Date" />
 *   <arg name="ModTime" type="Date" default="null" />
 *   <arg name="CreateTime" type="Date" default="null" />
 *  </function>
 *  <desc>
 *   Sets the file creation and last access/modification times.
 *   Any of the arguments may be null if the corresponding time is not needed.
 *  </desc>
 * </method>
 */
JSBool FileName::setTimes(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxDateTime acc;
    wxDateTime mod;
    wxDateTime create;
        
    if ( argv[0] == JSVAL_VOID )
    {
        if ( ! FromJS(cx, argv[0], acc) )
            return JS_FALSE;
    }

    if ( argv[1] != JSVAL_VOID )
    {
        if ( ! FromJS(cx, argv[1], mod) )
            return JS_FALSE;
    }

    if ( argv[2] != JSVAL_VOID )
    {
        if ( ! FromJS(cx, argv[2], create) )
            return JS_FALSE;
    }

    *vp = ToJS(cx, p->SetTimes(acc.IsValid() ? &acc : NULL,
                                 mod.IsValid() ? &mod : NULL,
                                 create.IsValid() ? &create : NULL));
    return JS_TRUE;
}

/***
 * <method name="insertDir">
 *  <function>
 *   <arg name="Pos" type=ZZZJS_TYPE_NUMBER />
 *   <arg name="Dir" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Inserts a directory before the zero-based position in the directory list.
 *  </desc>
 * </method>
 */
JSBool FileName::insertDir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    int pos;
    wxString dir;

    if (    FromJS(cx, argv[0], pos) 
         && FromJS(cx, argv[1], dir) )
        p->InsertDir(pos, dir);
    else
        return JS_FALSE;

    return JS_TRUE;
}

/***
 * <method name="isAbsolute">
 *  <function returns="Boolean">
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Returns true if this filename is absolute.
 *  </desc>
 * </method>
 */
JSBool FileName::isAbsolute(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    int format = wxPATH_NATIVE;
    if (     argc > 0
        && ! FromJS(cx, argv[0], format) )
        return JS_FALSE;

    *vp = ToJS(cx, p->IsAbsolute((wxPathFormat) format));
    return JS_TRUE;
}

/***
 * <method name="isRelative">
 *  <function returns="Boolean">
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Returns true if this filename is not absolute.
 *  </desc> 
 * </method>
 */
JSBool FileName::isRelative(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    int format = wxPATH_NATIVE;
    if (     argc > 0
        && ! FromJS(cx, argv[0], format) )
        return JS_FALSE;

    *vp = ToJS(cx, p->IsRelative((wxPathFormat) format));
    return JS_TRUE;
}

/***
 * <method name="makeRelativeTo">
 *  <function returns="Boolean">
 *   <arg name="Base" type=ZZZJS_TYPE_STRING default="">
 *    The directory to use as root. When not given, the current directory is used.
 *   </arg>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   This function tries to put this file name in a form relative to Base.
 *   In other words, it returns the file name which should be used to access
 *   this file if the current directory were Base.
 *   <br /><br />
 *   Returns true if the file name has been changed, false if we failed to do anything
 *   with it (currently this only happens if the file name is on a volume different from 
 *   the volume specified by Base).
 *  </desc>
 * </method>
 */
JSBool FileName::makeRelativeTo(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxString base = wxEmptyString;
    int format = wxPATH_NATIVE;
    switch(argc)
    {
    case 2:
        if ( ! FromJS(cx, argv[1], format) )
            return JS_FALSE;
        // Fall through
    case 1:
        FromJS(cx, argv[0], base);
    }

    *vp = ToJS(cx, p->MakeRelativeTo(base, (wxPathFormat) format));
    return JS_TRUE;
}

/***
 * <method name="mkdir">
 *  <function returns="Boolean">
 *   <arg name="Perm" type=ZZZJS_TYPE_NUMBER default="777">Permission for the directory</arg>
 *   <arg name="Flags" type="@wxFileName#wxPathMkdir" default="0">
 *    Default is 0. If the flags contain wxPathMkdir.FULL flag,
 *    try to create each directory in the path and also don't return 
 *    an error if the target directory already exists.
 *  </arg>
 *  </function>
 *  <desc>
 *   Creates a directory. Returns true on success.
 *  </desc>
 * </method>
 */
JSBool FileName::mkdir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    int perm = 777;
    int flag = 0;
    switch(argc)
    {
    case 2:
        if ( ! FromJS(cx, argv[1], flag) )
            return JS_FALSE;
        // Fall through
    case 1:
        if ( ! FromJS(cx, argv[1], perm) )
            return JS_FALSE;
    }

    *vp = ToJS(cx, p->Mkdir(perm, flag));
    return JS_TRUE;
}

/***
 * <method name="normalize">
 *  <function returns="Boolean">
 *   <arg name="Flags" type="@wxFileName#wxPathNormalize" default="wxPathNormalize.ALL" />
 *   <arg name="Cwd" type=ZZZJS_TYPE_STRING default="" />
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Normalize the path: with the default flags value, the path will be made absolute,
 *   without any ".." and "." and all environment variables will be expanded in it this 
 *   may be done using another (than current) value of cwd.
 *  </desc>
 * </method>
 */
JSBool FileName::normalize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxString cwd = wxEmptyString;
    int format = wxPATH_NATIVE;
    int flag = wxPATH_NORM_ALL;

    switch(argc)
    {
    case 3:
        if ( ! FromJS(cx, argv[2], format) )
            return JS_FALSE;
        // Fall through
    case 2:
        FromJS(cx, argv[1], cwd);
        // Fall through
    case 1:
        // Fall through
        if ( ! FromJS(cx, argv[0], flag) )
            return JS_FALSE;
    case 0:
        *vp = ToJS(cx, p->Normalize(flag, cwd, (wxPathFormat) format));
        return JS_TRUE;
    }

    return JS_FALSE;
}

/***
 * <method name="prependDir">
 *  <function>
 *   <arg name="Dir" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Prepends a directory name.
 *  </desc>
 * </method>
 */
JSBool FileName::prependDir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxString dir;

    FromJS(cx, argv[1], dir);
    p->PrependDir(dir);

    return JS_TRUE;
}

/***
 * <method name="removeDir">
 *  <function>
 *   <arg name="Pos" type=ZZZJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *   Removes a directory name.
 *  </desc>
 * </method>
 */
JSBool FileName::removeDir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    int pos;

    if ( FromJS(cx, argv[0], pos) )
        p->RemoveDir(pos);
    else
        return JS_FALSE;

    return JS_TRUE;
}

/***
 * <method name="removeLastDir">
 *  <function />
 *  <desc>
 *   Removes the last directory component from the path.
 *  </desc>
 * </method>
 */
JSBool FileName::removeLastDir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    p->RemoveLastDir();

    return JS_TRUE;
}

/***
 * <method name="rmdir">
 *  <function />
 *  <desc>
 *   Deletes the directory from the file system.
 *  </desc>
 * </method>
 */
JSBool FileName::rmdir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    p->Rmdir();

    return JS_TRUE;
}

/***
 * <method name="sameAs">
 *  <function returns="Boolean">
 *   <arg name="FileName" type=ZZZJS_TYPE_STRING />
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Compares the filename using the rules of the format.
 *  </desc>
 * </method>
 */
JSBool FileName::sameAs(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxFileName *compareTo = GetPrivate(cx, argv[0]);
    if ( compareTo == NULL )
        return JS_FALSE;

    int format = wxPATH_NATIVE;
    if (     argc > 1
        && ! FromJS(cx, argv[1], format) )
        return JS_FALSE;

    *vp = ToJS(cx, p->SameAs(*compareTo, (wxPathFormat) format));
    return JS_TRUE;
}

/***
 * <method name="setCwd">
 *  <function />
 *  <desc>
 *   Set this to the current directory.
 *  </desc>
 * </method>
 */
JSBool FileName::setCwd(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    p->SetCwd();

    return JS_TRUE;
}

/***
 * <method name="touch">
 *  <function />
 *  <desc>
 *   Sets the access and modification times to the current moment.
 *  </desc>
 * </method>
 */
JSBool FileName::touch(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    p->Touch();

    return JS_TRUE;
}

ZZZJS_BEGIN_STATIC_METHOD_MAP(FileName)
    ZZZJS_METHOD("assignCwd", assignCwd, 0)
    ZZZJS_METHOD("createTempFileName", createTempFileName, 2)
    ZZZJS_METHOD("dirExists", dirExists, 1)
    ZZZJS_METHOD("dirName", dirName, 1)
    ZZZJS_METHOD("fileExists", fileExists, 1)
    ZZZJS_METHOD("fileName", fileName, 1)
    ZZZJS_METHOD("getCwd", getCwd, 0)
    ZZZJS_METHOD("getFormat", getFormat, 0)
    ZZZJS_METHOD("mkdir", smkdir, 1)
    ZZZJS_METHOD("rmdir", srmdir, 1)
    ZZZJS_METHOD("splitPath", splitPath, 1)
    ZZZJS_METHOD("getPathSeparator", getPathSeparator, 0)
    ZZZJS_METHOD("getPathSeparators", getPathSeparators, 0)
    ZZZJS_METHOD("getVolumeSeparator", getVolumeSeparator, 0)
    ZZZJS_METHOD("isCaseSensitive", isAbsolute, 0)
    ZZZJS_METHOD("isPathSeparator", isPathSeparator, 1)
ZZZJS_END_METHOD_MAP()

/***
 * <class_method name="assignCwd">
 *  <function>
 *   <arg name="Volume" type=ZZZJS_TYPE_STRING default="" />
 *  </function>
 *  <desc>
 *   Makes this object refer to the current working directory on the 
 *   specified volume (or current volume if volume is not specified).
 *  </desc>
 * </class_method>
 */
JSBool FileName::assignCwd(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxFileName *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

    wxString volume = wxEmptyString;
    if ( argc > 0 )
        FromJS(cx, argv[0], volume);

    p->AssignCwd(volume);
    return JS_TRUE;
}

/***
 * <class_method name="createTempFileName">
 *  <function returns=ZZZJS_TYPE_STRING>
 *   <arg name="Prefix" type=ZZZJS_TYPE_STRING />
 *   <arg name="File" type="@wxFile" default="null">
 *    Object which wil get the file pointer to the temp file.
 *   </arg>
 *  </function>
 *  <desc>
 *  Returns a temporary file name starting with the given prefix. 
 *  If the prefix is an absolute path, the temporary file is created 
 *  in this directory, otherwise it is created in the default system 
 *  directory for the temporary files or in the current directory.
 *  <br /><br />
 *  If the function succeeds, the temporary file is actually created. 
 *  When <i>File</i> is not omitted, this file will be opened using the name
 *  of the temporary file. When possible, this is done in an atomic way ensuring 
 *  that no race condition occurs between the temporary file name generation and 
 *  opening it which could often lead to security compromise on the multiuser systems.
 *  If file is omitted, the file is only created, but not opened.
 *  <br /><br />
 *  Under Unix, the temporary file will have read and write permissions for the owner 
 *  only to minimize the security problems.
 *  </desc>
 * </class_method>
 */
JSBool FileName::createTempFileName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString prefix;
    FromJS(cx, argv[0], prefix);

    wxFile *file = NULL;
    if (     argc > 1 
        && (file = File::GetPrivate(cx, argv[1])) == NULL )
        return JS_FALSE;

    wxFileName::CreateTempFileName(prefix, file);
    return JS_TRUE;
}

/***
 * <class_method name="dirExists">
 *  <function returns="Boolean">
 *   <arg name="Dir" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Returns true when the directory exists.
 *  </desc>
 * </class_method>
 */
JSBool FileName::dirExists(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString dir;
    FromJS(cx, argv[0], dir);

    *vp = ToJS(cx, wxFileName::DirExists(dir));
    return JS_TRUE;
}

/***
 * <class_method name="dirName">
 *  <function returns="wxFileName">
 *   <arg name="Dir" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Creates a new wxFileName object based on the given directory.
 *  </desc>
 * </class_method>
 */
JSBool FileName::dirName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString dir;
    FromJS(cx, argv[0], dir);

    *vp = CreateObject(cx, new wxFileName(wxFileName::DirName(dir)));
    return JS_TRUE;
}

/***
 * <class_method name="fileExists">
 *  <function returns="Boolean">
 *   <arg name="File" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Returns true when the file exists.
 *  </desc>
 * </class_method>
 */
JSBool FileName::fileExists(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString file;
    FromJS(cx, argv[0], file);

    *vp = ToJS(cx, wxFileName::FileExists(file));
    return JS_TRUE;
}

/***
 * <class_method name="fileName">
 *  <function returns="@wxFileName">
 *   <arg name="File" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Creates a new wxFileName object based on the given file.
 *  </desc>
 * </class_method>
 */
JSBool FileName::fileName(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString file;
    FromJS(cx, argv[0], file);

    *vp = CreateObject(cx, new wxFileName(wxFileName::FileName(file)));
    return JS_TRUE;
}

/***
 * <class_method name="getCwd">
 *  <function returns=ZZZJS_TYPE_STRING>
 *   <arg name="Volume" type=ZZZJS_TYPE_STRING default="" />
 *  </function>
 *  <desc>
 *   Retrieves the value of the current working directory on the specified volume. 
 *   When the volume is omitted, the programs current working directory is returned 
 *   for the current volume.
 *  </desc>
 * </class_method>
 */
JSBool FileName::getCwd(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString vol = wxEmptyString;
    if ( argc > 0 )
        FromJS(cx, argv[0], vol);

    *vp = ToJS(cx, wxFileName::GetCwd(vol));
    return JS_TRUE;
}

/***
 * <class_method name="getFormat">
 *  <function returns=ZZZJS_TYPE_NUMBER>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Returns the canonical path format for this platform.
 *  </desc>
 * </class_method>
 */
JSBool FileName::getFormat(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    int format = wxPATH_NATIVE;
    if ( argc > 0 )
        FromJS(cx, argv[0], format);

    *vp = ToJS<int>(cx, wxFileName::GetFormat((wxPathFormat) format));
    return JS_TRUE;
}

/***
 * <class_method name="getPathSeparator">
 *  <function returns=ZZZJS_TYPE_STRING>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Returns the usually used path separator for this format. 
 *   For all formats but wxPathFormat.DOS there is only one path 
 *   separator anyhow, but for DOS there are two of them and the 
 *   native one, i.e. the backslash is returned by this method.
 *  </desc>
 * </class_method>
 */
JSBool FileName::getPathSeparator(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    int format = wxPATH_NATIVE;
    if (     argc > 0
        && ! FromJS(cx, argv[0], format) )
        return JS_FALSE;

    *vp = ToJS(cx, wxString(wxFileName::GetPathSeparator((wxPathFormat) format)));
    return JS_TRUE;
}

/***
 * <class_method name="getPathSeparators">
 *  <function returns=ZZZJS_TYPE_STRING>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Returns the string containing all the path separators for this format.
 *   For all formats but wxPathFormat.DOS this string contains only one character 
 *   but for DOS and Windows both '/' and '\' may be used as separators.
 *  </desc>
 * </class_method>
 */
JSBool FileName::getPathSeparators(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    int format = wxPATH_NATIVE;
    if (     argc > 0
        && ! FromJS(cx, argv[0], format) )
        return JS_FALSE;

    *vp = ToJS(cx, wxFileName::GetPathSeparators((wxPathFormat) format));
    return JS_TRUE;
}

/***
 * <class_method name="getVolumeSeparator">
 *  <function returns=ZZZJS_TYPE_STRING>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Returns the string separating the volume from the path for this format.
 *  </desc>
 * </class_method>
 */
JSBool FileName::getVolumeSeparator(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    int format = wxPATH_NATIVE;
    if (     argc > 0
        && ! FromJS(cx, argv[0], format) )
        return JS_FALSE;

    *vp = ToJS(cx, wxString(wxFileName::GetVolumeSeparator((wxPathFormat) format)));
    return JS_TRUE;
}

/***
 * <class_method name="isCaseSensitive">
 *  <function returns=ZZZJS_TYPE_STRING>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Returns true if filenames for the given format are case-sensitive.
 *  </desc>
 * </class_method>
 */
JSBool FileName::isCaseSensitive(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    int format = wxPATH_NATIVE;
    if (     argc > 0
        && ! FromJS(cx, argv[0], format) )
        return JS_FALSE;

    *vp = ToJS(cx, wxFileName::IsCaseSensitive((wxPathFormat) format));
    return JS_TRUE;
}

/***
 * <class_method name="isPathSeparator">
 *  <function returns="Boolean">
 *   <arg name="Sep" type=ZZZJS_TYPE_STRING>A path separator</arg>
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   Returns true if the given string (only the first character is checked!)
 *   is a separator on the format.
 *  </desc>
 * </class_method>
 */
JSBool FileName::isPathSeparator(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString sep;
    FromJS(cx, argv[0], sep);
    if ( sep.Length() == 0 )
        return JS_TRUE;

    int format = wxPATH_NATIVE;
    if (     argc > 1
        && ! FromJS(cx, argv[1], format) )
        return JS_FALSE;

    *vp = ToJS(cx, wxFileName::IsPathSeparator(sep[0], (wxPathFormat) format));
    return JS_TRUE;
}

/***
 * <class_method name="mkdir">
 *  <function returns="Boolean">
 *   <arg name="Dir" type=ZZZJS_TYPE_STRING>Name of the directory</arg>
 *   <arg name="Perm" type=ZZZJS_TYPE_NUMBER default="777">Permissions</arg>
 *   <arg name="Flags" type="@wxFileName#wxPathMkdir" default="0">
 *    Default is 0. If the flags contain wxPathMkdir.FULL flag,
 *    try to create each directory in the path and also don't return 
 *    an error if the target directory already exists.
 *   </arg>
 *  </function>
 *  <desc>
 *   Creates a directory. Returns true on success.
 *  </desc>
 * </class_method>
 */
JSBool FileName::smkdir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( argc > 3 )
        argc = 3;

    wxString dir;
    int perm = 777;
    int flag = 0;
    
    switch(argc)
    {
    case 3:
        if ( ! FromJS(cx, argv[2], flag) )
            return JS_FALSE;
        // Fall through
    case 2:
        if ( ! FromJS(cx, argv[1], perm) )
            return JS_FALSE;
    default:
        FromJS(cx, argv[0], dir);
        *vp = ToJS(cx, wxFileName::Mkdir(dir, perm, flag));
    }
    return JS_TRUE;
}

/***
 * <class_method name="rmdir">
 *  <function>
 *   <arg name="Dir" type=ZZZJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Deletes the directory from the file system.
 *  </desc>
 * </class_method>
 */
JSBool FileName::srmdir(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString dir;
    FromJS(cx, argv[0], dir);
    wxFileName::Rmdir(dir);

    return JS_TRUE;
}

/***
 * <class_method name="splitPath">
 *  <function returns="String Array">
 *   <arg name="FullPath" type=ZZZJS_TYPE_STRING />
 *   <arg name="Format" type="@wxFileName#wxPathFormat" default="wxPathFormat.NATIVE" />
 *  </function>
 *  <desc>
 *   This function splits a full file name into components: the volume, path,
 *   the base name and the extension. 
 *   <br /><br /><b>Remark:</b> In wxWindows the arguments are passed as
 *   pointers. Because this is not possible in JavaScript, wxJS returns an array containing
 *   the parts of the path.
 *   <br /><br />
 *   The following code illustrates how splitPath works in JavaScript. parts[0] contains "C", 
 *   parts[1] contains "\\", parts[2] contains "Temp" and parts[3] is empty.
 *   <pre><code class="whjs">
 *    var parts = wxFileName.splitPath("C:\\Temp");
 *    for(element in parts)
 *    {
 *      ...
 *    }
 *    </code></pre>
 *  </desc>
 * </class_method>
 */
JSBool FileName::splitPath(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString path;
    FromJS(cx, argv[0], path);

    int format = wxPATH_NATIVE;
    if (      argc > 1 
         && ! FromJS(cx, argv[1], format) )
        return JS_FALSE;

    wxString parts[4];
    wxFileName::SplitPath(path, &parts[0], &parts[1], &parts[2], &parts[3], (wxPathFormat) format);
    
    JSObject *objArray = JS_NewArrayObject(cx, 4, NULL);
    *vp = OBJECT_TO_JSVAL(objArray);
    for(int i = 0; i < 4; i++)
    {
        jsval element = ToJS(cx, parts[i]);
        JS_SetElement(cx, objArray, i, &element);
    }

    return JS_TRUE;
}

bool FileName::SetDate(JSContext *cx, jsval v, const wxDateTime &date)
{
	if ( v.isObject() )
    {
        JSObject *obj = JSVAL_TO_OBJECT(v);
        if ( js_DateIsValid(/*cx,*/ obj) )
        {
/*
    JS_FN("setYear",             date_setYear,            1,0),
    JS_FN("setFullYear",         date_setFullYear,        3,0),
    JS_FN("setUTCFullYear",      date_setUTCFullYear,     3,0),
    JS_FN("setMonth",            date_setMonth,           2,0),
    JS_FN("setUTCMonth",         date_setUTCMonth,        2,0),
    JS_FN("setDate",             date_setDate,            1,0),
    JS_FN("setUTCDate",          date_setUTCDate,         1,0),
    JS_FN("setHours",            date_setHours,           4,0),
    JS_FN("setUTCHours",         date_setUTCHours,        4,0),
    JS_FN("setMinutes",          date_setMinutes,         3,0),
    JS_FN("setUTCMinutes",       date_setUTCMinutes,      3,0),
    JS_FN("setSeconds",          date_setSeconds,         2,0),
    JS_FN("setUTCSeconds",       date_setUTCSeconds,      2,0),
    JS_FN("setMilliseconds",     date_setMilliseconds,    1,0),
    JS_FN("setUTCMilliseconds",  date_setUTCMilliseconds, 1,0),
    JS_FN("toUTCString",         date_toGMTString,        0,0),
    JS_FN("toLocaleFormat",      date_toLocaleFormat,     0,0),

*/
            //js_DateSetYear(cx, obj, date.GetYear());
            //js_DateSetMonth(cx, obj, date.GetMonth());
            //js_DateSetDate(cx, obj, date.GetDay());
            //js_DateSetHours(cx, obj, date.GetHour());
            //js_DateSetMinutes(cx, obj, date.GetMinute());
            //js_DateSetSeconds(cx, obj, date.GetSecond());

			jsval arg[1];
			JSAutoCompartment ac(cx, obj);
			JS::RootedValue r(cx);

			arg[0].setInt32(date.GetYear());
			JS_CallFunctionName(cx, obj, "setYear", 1, arg, r.address());
			
			arg[0].setInt32(date.GetMonth());
			JS_CallFunctionName(cx, obj, "setMonth", 1, arg, r.address());
			
			arg[0].setInt32(date.GetDay());
			JS_CallFunctionName(cx, obj, "setDate", 1, arg, r.address());
			
			arg[0].setInt32(date.GetHour());
			JS_CallFunctionName(cx, obj, "setHours", 1, arg, r.address());
			
			arg[0].setInt32(date.GetMinute());
			JS_CallFunctionName(cx, obj, "setMinutes", 1, arg, r.address());
			
			arg[0].setInt32(date.GetSecond());
			JS_CallFunctionName(cx, obj, "setSeconds", 1, arg, r.address());

            return true;
        }
    }
    return false;
}

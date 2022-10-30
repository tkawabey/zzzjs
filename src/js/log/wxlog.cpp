/*
 * wxJavaScript - dir.cpp
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
 * $Id: dir.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// wxJSDir.cpp
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/log/wxlog.h"
#include "js/gui/errors.h"
#include "js/common/jsutil.h"

#include "js/io/stream.h"
#include "js/io/ostream.h"
#include "js/io/istream.h"

using namespace zzzJs;
using namespace zzzJs::log;
using namespace zzzJs::io;

/***
 * <file>dir</file>
 * <module>io</module>
 * <class name="wxDir">
 *  wxDir is a portable equivalent of Unix open/read/closedir functions which allow 
 *  enumerating of the files in a directory. wxDir can enumerate files as well as directories.
 *  <br /><br />
 *  The following example checks if the temp-directory exists,
 *  and when it does, it retrieves all files with ".tmp" as extension.
 *  <pre><code class="whjs">
 *   if ( wxDir.exists("c:\\temp") )
 *   {
 *     files = wxDir.getAllFiles("c:\\temp", "*.tmp");
 *     for(e in files)
 *       wxMessageBox(files[e]);
 *   }
 *  </code></pre>
 *  See also @wxDirTraverser
 * </class>
 */
WXJS_INIT_CLASS(Log, "Log", 0)

/***
 * <constants>
 *  <type name="wxDirFlags">
 *   <constant name="FILES" />
 *   <constant name="DIRS" />
 *   <constant name="HIDDEN" />
 *   <constant name="DOTDOT" />
 *   <constant name="DEFAULT" />
 *   <desc>Constants used for filtering files. The default: FILES | DIRS | HIDDEN.</desc>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(Log)
 //   WXJS_CONSTANT(wxLOG_, FatalError)
	//WXJS_CONSTANT(wxLOG_, Error)
	//WXJS_CONSTANT(wxLOG_, Warning)
	//WXJS_CONSTANT(wxLOG_, Message)
	//WXJS_CONSTANT(wxLOG_, Status)
	//WXJS_CONSTANT(wxLOG_, Info)
	//WXJS_CONSTANT(wxLOG_, Debug)
	//WXJS_CONSTANT(wxLOG_, Trace)
	//WXJS_CONSTANT(wxLOG_, Progress)
	//WXJS_CONSTANT(wxLOG_, User)
WXJS_END_CONSTANT_MAP()

WXJS_BEGIN_STATIC_METHOD_MAP(Log)
    WXJS_METHOD("addTraceMask", addTraceMask, 1)
    WXJS_METHOD("clearTraceMasks", clearTraceMasks, 0)
    WXJS_METHOD("getTraceMasks", getTraceMasks, 0)
    WXJS_METHOD("isAllowedTraceMask", isAllowedTraceMask, 1)
    WXJS_METHOD("removeTraceMask", removeTraceMask, 1)
    WXJS_METHOD("dontCreateOnDemand", dontCreateOnDemand, 0)
    WXJS_METHOD("getActiveTarget", getActiveTarget, 0)
    WXJS_METHOD("setActiveTarget", setActiveTarget, 1)
    WXJS_METHOD("setThreadActiveTarget", setThreadActiveTarget, 1)
    WXJS_METHOD("flushActive", flushActive, 0)
	WXJS_METHOD("resume", resume, 0)
	WXJS_METHOD("suspend", suspend, 0)
	WXJS_METHOD("getLogLevel", getLogLevel, 0)
	WXJS_METHOD("isLevelEnabled", isLevelEnabled, 2)
	WXJS_METHOD("setComponentLevel", setComponentLevel, 2)
	WXJS_METHOD("setLogLevel", setLogLevel, 1)
	WXJS_METHOD("enableLogging", enableLogging, 1)
	WXJS_METHOD("isEnabled", isEnabled, 0)
	WXJS_METHOD("getRepetitionCounting", getRepetitionCounting, 0)
	WXJS_METHOD("setRepetitionCounting", setRepetitionCounting, 1)
	WXJS_METHOD("getTimestamp", getTimestamp, 0)
	WXJS_METHOD("setTimestamp", setTimestamp, 1)
	WXJS_METHOD("disableTimestamp", disableTimestamp, 0)
	WXJS_METHOD("getVerbose", getVerbose, 0)
	WXJS_METHOD("setVerbose", setVerbose, 1)
WXJS_END_METHOD_MAP()


JSBool Log::addTraceMask(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString mask;
    if( FromJS(cx, argv[0], mask) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;

	}
	wxLog::AddTraceMask( mask );
    return JS_TRUE;
}
JSBool Log::clearTraceMasks(JSContext *cx, unsigned argc, JS::Value *vp)
{
	//JSObject *obj = JS_THIS_OBJECT(cx, vp);
	//JS::CallArgs argv = CallArgsFromVp(argc, vp);

 //   wxString mask;
 //   if( FromJS(cx, argv[0], mask) == false ) {
	//	JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
	//	return JS_FALSE;

	//}
	wxLog::ClearTraceMasks();
    return JS_TRUE;
}
JSBool Log::getTraceMasks(JSContext *cx, unsigned argc, JS::Value *vp)
{
	//JSObject *obj = JS_THIS_OBJECT(cx, vp);
	//JS::CallArgs argv = CallArgsFromVp(argc, vp);

 //   wxString mask;
 //   if( FromJS(cx, argv[0], mask) == false ) {
	//	JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
	//	return JS_FALSE;

	//}
	wxArrayString arry = wxLog::GetTraceMasks();


    JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
    //JS_AddRoot(cx, &objArray);
	JS::RootedObject jsvaArray(cx, objArray);

	for(size_t i = 0; i < arry.GetCount(); i++ ) {	
        JS::Value element = ToJS(cx, arry[i]);
	    JS_SetElement(cx, objArray, i++, &element);
    }
	vp->setObjectOrNull(objArray);

    return JS_TRUE;
}
JSBool Log::isAllowedTraceMask(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString mask;
    if( FromJS(cx, argv[0], mask) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;

	}
	vp->setBoolean( wxLog::IsAllowedTraceMask( mask ) );
    return JS_TRUE;
}

JSBool Log::removeTraceMask(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString mask;
    if( FromJS(cx, argv[0], mask) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	wxLog::RemoveTraceMask( mask );
    return JS_TRUE;
}
JSBool Log::dontCreateOnDemand(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxLog::DontCreateOnDemand();
    return JS_TRUE;
}
JSBool Log::getActiveTarget(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxLog* pActiveTarget = wxLog::GetActiveTarget();
	if( pActiveTarget == NULL ) {
		vp->setNull();
	} else {
		*vp = Log::CreateObject( cx, pActiveTarget, NULL);
	}
    return JS_TRUE;
}
JSBool Log::setActiveTarget(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	wxLog* pTarget = NULL;
	if( argv[0].isNull() == false ) {
		pTarget =Log::GetPrivate(cx, argv[0], false);	
		if( pTarget == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Log");
			return JS_FALSE;
		}
	}
	wxLog* pOldTarget = wxLog::SetActiveTarget( pTarget );
	if( pOldTarget == NULL ) {
		vp->setNull();
	} else {
		*vp = Log::CreateObject( cx, pOldTarget, NULL);
	}
    return JS_TRUE;
}
JSBool Log::setThreadActiveTarget(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	wxLog* pTarget = NULL;
	if( argv[0].isNull() == false ) {
		pTarget =Log::GetPrivate(cx, argv[0], false);	
		if( pTarget == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Log");
			return JS_FALSE;
		}
	}
	wxLog* pOldTarget = wxLog::SetThreadActiveTarget( pTarget );
	if( pOldTarget == NULL ) {
		vp->setNull();
	} else {
		*vp = Log::CreateObject( cx, pOldTarget, NULL);
	}
    return JS_TRUE;
}
JSBool Log::flushActive(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxLog::FlushActive ();
    return JS_TRUE;
}
JSBool Log::resume(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxLog::Resume ();
    return JS_TRUE;
}
JSBool Log::suspend(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxLog::Suspend();
    return JS_TRUE;
}
JSBool Log::getLogLevel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	int logLevel = (int)wxLog::GetLogLevel();
	vp->setInt32(logLevel);
    return JS_TRUE;
}
JSBool Log::isLevelEnabled(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	int logLevel = 0;
    wxString component;
    if( FromJS(cx, argv[1], component) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
    if( FromJS(cx, argv[0], logLevel) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	vp->setBoolean( wxLog::IsLevelEnabled ( logLevel, component ) );
    return JS_TRUE;
}
JSBool Log::setComponentLevel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	int logLevel = 0;
    wxString component;
    if( FromJS(cx, argv[1], logLevel) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
    if( FromJS(cx, argv[0], component) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	wxLog::SetComponentLevel(component,  logLevel);
    return JS_TRUE;
}
JSBool Log::setLogLevel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	int logLevel = 0;
    if( FromJS(cx, argv[0], logLevel) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	wxLog::SetLogLevel(logLevel);
    return JS_TRUE;
}
JSBool Log::enableLogging(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	bool b = false;
    if( FromJS(cx, argv[0], b) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
		return JS_FALSE;
	}
	wxLog::EnableLogging(b);
    return JS_TRUE;
}
JSBool Log::isEnabled(JSContext *cx, unsigned argc, JS::Value *vp)
{
	vp->setBoolean( wxLog::IsEnabled() );
    return JS_TRUE;
}
JSBool Log::getRepetitionCounting(JSContext *cx, unsigned argc, JS::Value *vp)
{
	vp->setBoolean( wxLog::GetRepetitionCounting() );
    return JS_TRUE;
}
JSBool Log::setRepetitionCounting(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	bool b = false;
    if( FromJS(cx, argv[0], b) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
		return JS_FALSE;
	}
	wxLog::SetRepetitionCounting(b);
    return JS_TRUE;
}
JSBool Log::getTimestamp(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxString str = wxLog::GetTimestamp();
	*vp = ToJS(cx, str);
    return JS_TRUE;
}
JSBool Log::setTimestamp(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxString str(_T(""));
    if( FromJS(cx, argv[0], str) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	wxLog::SetTimestamp(str);
    return JS_TRUE;
}
JSBool Log::disableTimestamp(JSContext *cx, unsigned argc, JS::Value *vp)
{
	wxLog::DisableTimestamp();
    return JS_TRUE;
}
JSBool Log::getVerbose(JSContext *cx, unsigned argc, JS::Value *vp)
{
	vp->setBoolean( wxLog::GetVerbose() );
    return JS_TRUE;
}
JSBool Log::setVerbose(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	bool b = false;
    if( FromJS(cx, argv[0], b) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "Boolean");
		return JS_FALSE;
	}
	wxLog::SetVerbose(b);
    return JS_TRUE;
}








WXJS_BEGIN_CONSTRUCTOR(wxLog, Log)

    return NULL;

WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_DESTRUCTOR(wxLog, Log)

WXJS_END_DESTRUCTOR

/***
 * <properties>
 *  <property name="opened" type="Boolean" readonly="Y">
 *   Returns true when the directory was opened by calling @wxDir#open.
 *  </property>
 *  <property name="name" type=WXJS_TYPE_STRING readonly="Y">
 *   Returns the name of the directory itself. The returned string 
 *   does not have the trailing path separator (slash or backslash).
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Log)
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxLog, Log)

    return true;
WXJS_END_GET_PROP

WXJS_BEGIN_METHOD_MAP(Log)
    //WXJS_METHOD("addChild", addChild, 2)
    //WXJS_METHOD("insertChild", insertChild, 3)
    //WXJS_METHOD("insertChildAfter", insertChildAfter, 3)
    //WXJS_METHOD("removeChild", removeChild, 1)
    //WXJS_METHOD("addAttribute", addAttribute, 2)
    //WXJS_METHOD("deleteAttribute", deleteAttribute, 1)
    //WXJS_METHOD("getAttribute", getAttribute, 1)
WXJS_END_METHOD_MAP()




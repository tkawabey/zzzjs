/*
 * wxJavaScript - dirtrav.cpp
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
 * $Id: dirtrav.cpp 716 2007-05-20 17:57:22Z fbraem $
 */
// wxJSDirTraverser.cpp
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/archive.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/jsutil.h"
#include "js/common/clntdata.h"
#include "js/io/dirtrav.h"


using namespace zzzJs;
using namespace zzzJs::io;

DirTraverser::DirTraverser()
        : wxDirTraverser()
{
}

wxDirTraverseResult DirTraverser::OnFile(const wxString& filename)
{
  JavaScriptClientData *data
    = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	jsval fval;
	if ( GetFunctionProperty(cx, data->GetObject(), "onFile", &fval) == JS_TRUE )
	{
		jsval rval;
		jsval argv[] = { ToJS(cx, filename) };
		if ( JS_CallFunctionValue(cx, data->GetObject(), fval, 1, argv, &rval) == JS_TRUE )
		{
			int result;
			if ( FromJS(cx, rval, result ) )
			{
                return (wxDirTraverseResult) result;
			}
		}
        else
        {
            if ( JS_IsExceptionPending(cx) )
            {
                JS_ReportPendingException(cx);
            }
        }
		return wxDIR_STOP;
	}

    // No function set, we return continue
	return wxDIR_CONTINUE;
}

wxDirTraverseResult DirTraverser::OnDir(const wxString& filename)
{
  JavaScriptClientData *data
    = dynamic_cast<JavaScriptClientData*>(GetClientObject());

	JSContext *cx = data->GetContext();
	jsval fval;
	if ( GetFunctionProperty(cx, data->GetObject(), "onDir", &fval) == JS_TRUE )
	{
		jsval rval;
		jsval argv[] = { ToJS(cx, filename) };
		if ( JS_CallFunctionValue(cx, data->GetObject(), fval, 1, argv, &rval) == JS_TRUE )
		{
			int result;
			if ( FromJS(cx, rval, result) )
			{
                return (wxDirTraverseResult) result;
			}
		}
        else
        {
            if ( JS_IsExceptionPending(cx) )
            {
                JS_ReportPendingException(cx);
            }
        }
		return wxDIR_STOP;
	}

    // No function set, we return continue
	return wxDIR_CONTINUE;
}

/***
 * <file>dirtrav</file>
 * <module>io</module>
 * <class name="wxDirTraverser">
 *  wxDirTraverser can be used to traverse into directories to retrieve filenames and subdirectories.
 *  <br /><br />
 *  See also @wxDir
 *  <br /><br />
 *  The following example counts all subdirectories of the temporary directory.
 *  Counting the direct subdirectories of temp is possible by returning
 *  IGNORE in @wxDirTraverser#onDir.
 *  <pre><code class="whjs">
 *  var dir = new wxDir("c:\\temp");
 *  var trav = new wxDirTraverser();
 *  subdir = 0; // Don't use var, it doesn't seem to work with closures
 *  
 *  trav.onDir = function(filename)
 *  {
 *    subdir = subdir + 1;
 *    return wxDirTraverser.CONTINUE;
 *  }
 * 
 *  dir.traverse(trav);
 *
 *  wxMessageBox("Number of subdirectories: " + subdir);
 *  </code></pre>
 * </class>
 */
ZZZJS_INIT_CLASS(DirTraverser, "DirTraverser", 0)

/***
 * <constants>
 *  <type name="wxDirTraverseResult">
 *   <constant name="IGNORE" />
 *   <constant name="STOP" />
 *   <constant name="CONTINUE" />
 *  </type>
 * </constants>
 */
ZZZJS_BEGIN_CONSTANT_MAP(DirTraverser)
    ZZZJS_CONSTANT(wxDIR_, IGNORE)
    ZZZJS_CONSTANT(wxDIR_, STOP)
    ZZZJS_CONSTANT(wxDIR_, CONTINUE)
ZZZJS_END_CONSTANT_MAP()

/***
 * <properties>
 *  <property name="onFile" type="Function">
 *   Function which will be called for each file. The function
 *   gets a filename and should return a constant @wxDirTraverser#wxDirTraverseResult except 
 *   for IGNORE. When no function is set, it will return 
 *   CONTINUE. This makes it possible to enumerate the subdirectories.
 *  </property>
 *  <property name="onDir" type="Function">
 *   Function which will be called for each directory. The function
 *   gets a directoryname and should return a constant @wxDirTraverser#wxDirTraverseResult.
 *   It may return STOP to abort traversing completely, IGNORE to skip this directory but continue with 
 *   others or CONTINUE to enumerate all files and subdirectories
 *   in this directory. When no function is set, it will return CONTINUE.
 *   This makes it possible to enumerate all files.
 *  </property>
 * </properties>
 */

/***
 * <ctor>
 *  <function />
 *  <desc>
 *   Constructs a new wxDirTraverser object.
 *  </desc>
 * </ctor>
 */
//DirTraverser* DirTraverser::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(DirTraverser, DirTraverser)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    DirTraverser *p = new DirTraverser();
    p->SetClientObject(new JavaScriptClientData(cx, obj, false, true));
    return p;
ZZZJS_END_CONSTRUCTOR

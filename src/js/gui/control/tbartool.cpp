/*
 * wxJavaScript - toolbar.cpp
 *
 * Copyright (c) 2002-2007 Franky Braem and the wxJavaScript project
 *
 * Project Info: http://www.wxjavascript.net or http://zzzJs.sourceforge.net
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
 * $Id: toolbar.cpp 696 2007-05-07 21:16:23Z fbraem $
 */
#include "precompile.h"
#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/toolbar.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/ext/zzzjs_ext_init.h"




#include "js/gui/control/tbartool.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/tbartool</file>
 * <module>gui</module>
 * <class name="wxToolBarTool">
 *  A tool on a toolbar. See @wxToolBar.
 * </class>
 */
WXJS_INIT_CLASS(ToolBarToolBase, "ToolBarTool", 0)

/***
 * <properties>
 *  <property name="onTool" type="Function">
 *   The function to execute when the tool is clicked
 *  </property>
 * </properties>
 */

WXJS_BEGIN_METHOD_MAP(ToolBarToolBase)
  WXJS_METHOD("enable", enable, 1)
  WXJS_METHOD("toggle", toggle, 1)
WXJS_END_METHOD_MAP()

/***
 * <method name="enable">
 *  <function returns="Boolean">
 *   <arg name="Switch" type="Boolean" />
 *  </function>
 *  <desc>
 *   Enable/disable the tool
 *  </desc>
 * </method>
 */
JSBool ToolBarToolBase::enable(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxToolBarToolBase *p = GetPrivate(cx, obj);

  bool enable;
  if ( FromJS(cx, argv[0], enable) )
  {
    *vp = ToJS(cx, p->Enable(enable));
  }

  return JS_TRUE;
}

/***
 * <method name="toggle">
 *  <function returns="Boolean">
 *   <arg name="Switch" type="Boolean" />
 *  </function>
 *  <desc>
 *   Toggle the tool
 *  </desc>
 * </method>
 */
JSBool ToolBarToolBase::toggle(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxToolBarToolBase *p = GetPrivate(cx, obj);

  bool sw;
  if ( FromJS(cx, argv[0], sw) )
  {
    *vp = ToJS(cx, p->Toggle(sw));
  }

  return JS_TRUE;
}

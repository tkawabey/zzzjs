/*
 * wxJavaScript - acctable.cpp
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
 * $Id: acctable.cpp 782 2007-06-24 20:23:23Z fbraem $
 */
// acctable.cpp
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
#include "js/common/jsutil.h"
#include "js/gui/misc/acctable.h"
#include "js/gui/misc/accentry.h"
#include <memory>

using namespace zzzJs;
using namespace zzzJs::gui;


#define PROP_ENTRIES    "entries"



/***
 * <file>misc/acctable</file>
 * <module>gui</module>
 * <class name="wxAcceleratorTable">
 *  An accelerator table allows the application to specify a table 
 *  of keyboard shortcuts for menus or other commands. On Windows,
 *  menu or button commands are supported; on GTK,
 *  only menu commands are supported.
 *  The following example adds an accelerator to a frame. When CTRL-F1 is pressed
 *  the menu action associated with id 1 is executed.
 *  <pre><code class="whjs">
 *    wxTheApp.onInit = init;
 *
 *    function init()
 *    {
 *      var frame = new wxFrame(null, -1, "Accelerator Test");
 *      var menuBar = new wxMenuBar();
 *      var menu = new wxMenu();
 *      var idInfoAbout = 1;
 *
 *      menu = new wxMenu();
 *      menu.append(idInfoAbout, "About", infoAboutMenu);
 *      menuBar.append(menu, "Info");
 *
 *      frame.menuBar = menuBar;
 *
 *      var entries = new Array();
 *      entries[0] = new wxAcceleratorEntry(wxAcceleratorEntry.CTRL,
 *                                          wxKeyCode.F1,
 *                                          idInfoAbout);
 *      frame.acceleratorTable = new wxAcceleratorTable(entries);
 *
 *      menu.getItem(idInfoAbout).accel = entries[0];
 *
 *      topWindow = frame;
 *      frame.visible = true;
 *
 *      return true;
 *    }
 *
 *    function infoAboutMenu(event)
 *    {
 *      wxMessageBox("Accelerator Test Version 1.0");
 *    }
 *   </code></pre>
 * </class>
 */
ZZZJS_INIT_CLASS(AcceleratorTable, "AcceleratorTable", 1)

/***
 * <properties>
 *  <property name="ok" type="Boolean" readonly="Y">
 *   Returns true when the accelerator table is valid
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(AcceleratorTable)
  ZZZJS_READONLY_PROPERTY(P_OK, "ok")
ZZZJS_END_PROPERTY_MAP()


ZZZJS_BEGIN_GET_PROP(wxAcceleratorTable, AcceleratorTable)
{
	if ( id == P_OK )
	{
		ToJSVal(cx, vp, p->Ok());
    }
    return true;
}
ZZZJS_END_GET_PROP

/***
 * <ctor>
 *  <function>
 *   <arg name="Entries" type="Array">
 *    An array of @wxAcceleratorEntry objects
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxAcceleratorTable object.
 *  </desc>
 * </ctor>
 */

ZZZJS_BEGIN_CONSTRUCTOR(wxAcceleratorTable, AcceleratorTable)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	if ( argv[0].isObject() )
	{
		do {
			JSObject* pObj = argv[0].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}
			if ( JS_IsArrayObject(cx, pObj) )
			{
				uint32_t length = 0;
				JS_GetArrayLength(cx, pObj, &length);
				int n = length;
				std::auto_ptr<wxAcceleratorEntry*> apItem(new wxAcceleratorEntry*[n]);
				wxAcceleratorEntry **items = apItem.get();

				for(uint32_t i =0; i < (uint32_t)n; i++)
				{
					jsval element;
					JS_GetElement(cx, pObj, i, &element);
					items[i] = AcceleratorEntry::GetPrivate(cx, element);
				}

				wxAcceleratorTable *p = new wxAcceleratorTable(n, *items);
				return p;
			} 

			zzzJsPtr<wxAcceleratorTable> apRet;
			if( apRet.set( 
				AcceleratorTable::getObject2Instance(cx, pObj, apRet.bAllocation) ) == true 
			) {
				if( apRet.bAllocation == true ) {
					return apRet.release();
				} else {
					return new wxAcceleratorTable(*apRet.get());
				}
			}
		} while( 0 );
	}


	
	JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
	return NULL;
}
ZZZJS_END_CONSTRUCTOR
	
// Object 2 Instatance

ZZZJS_BEGIN_O2I(wxAcceleratorTable, AcceleratorTable)
{

	pRet = AcceleratorTable::GetPrivate(cx, obj);
	if( pRet != NULL ) {
		return pRet;
	}
	

	if( GetPropertyWhenPresent( cx, obj, PROP_ENTRIES, &v) == JS_TRUE )  
	{

		JSObject *objEntries = JSVAL_TO_OBJECT(v);
		if ( JS_IsArrayObject(cx, objEntries) )
		{
			uint32_t length = 0;
			JS_GetArrayLength(cx, objEntries, &length);
			int n = length;
			std::auto_ptr<wxAcceleratorEntry*> apItem(new wxAcceleratorEntry*[n]);
			wxAcceleratorEntry **items = apItem.get();

			for(uint32_t i =0; i < (uint32_t)n; i++)
			{
				jsval element;
				JS_GetElement(cx, objEntries, i, &element);
				items[i] = AcceleratorEntry::GetPrivate(cx, element);
			}
			
			bAllocation = true;
			return new wxAcceleratorTable(n, *items);
		} else {
			ReportError_PropTypeError(cx, PROP_ENTRIES, "Array");
			return JS_FALSE;	
		}
	}
	return NULL;
}
ZZZJS_END_O2I
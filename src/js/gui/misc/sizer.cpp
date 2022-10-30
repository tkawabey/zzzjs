/*
 * wxJavaScript - sizer.cpp
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
 * $Id: sizer.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// sizer.cpp
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/jsutil.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/ext/point.h"
#include "js/gui/misc/sizer.h"
#include "js/gui/misc/size.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/gui/control/window.h"

using namespace zzzJs;
using namespace zzzJs::gui;

// プロパティー名
#define PROP_NM_X				"x"
#define PROP_NM_Y				"y"
#define PROP_NM_HEIGHT			"height"
#define PROP_NM_WIDTH			"width"
/***
 * <file>misc/sizer</file>
 * <module>gui</module>
 * <class name="wxSizer">
 *	wxSizer is the prototype for all sizer objects :
 *	@wxBoxSizer, @wxFlexGridSizer, @wxGridSizer and @wxStaticBoxSizer.
 *	See also following wxWindow properties: @wxWindow#sizer, and @wxWindow#autoLayout.
 *  <br /><br />
 *  The example will show a dialog box that asks the user to enter a name and a password. 
 *  The labels, text controls and buttons are placed dynamically on the dialog using sizers.
 *  <pre><code class="whjs">
 *    // The wxSizer example
 *    wxTheApp.onInit = init;
 *   
 *    function init()
 *    {
 *      //Create a dialog box
 *
 *      var dlg = new wxDialog(null, -1, "wxSizer Example",
 *                             wxDefaultPosition, new wxSize(200, 150));
 *      // Create a wxBoxSizer for the dialog. 
 *      // The main direction of this sizer is vertical. 
 *      // This means that when an item is added to this sizer, it will be added below the previous item.
 *
 *      dlg.sizer = new wxBoxSizer(wxOrientation.VERTICAL);
 *  
 *      // Use a wxFlexGridSizer to layout the labels with their corresponding text controls.
 *      // The sizer is created with 2 rows and 2 columns. The first column is used for the label, 
 *      // while the second column is used for the text controls. The space between the rows and 
 *      // columns is set to 10.
 *
 *      var sizer1 = new wxFlexGridSizer(2, 2, 10, 10);
 *
 *      // Add the labels and text controls to sizer1. A label is centered vertically. 
 *      // A grid sizer is filled from left to right, top to bottom.
 *
 *      sizer1.add(new wxStaticText(dlg, -1, "Username"), 0, wxAlignment.CENTER_VERTICAL);
 *      sizer1.add(new wxTextCtrl(dlg, -1, "&lt;user&gt;"));
 *      sizer1.add(new wxStaticText(dlg, -1, "Password"), 0, wxAlignment.CENTER_VERTICAL);
 *      sizer1.add(new wxTextCtrl(dlg, -1, "&lt;pwd&gt;"));
 *
 *      // Add this sizer to the sizer of the dialog. The flag argument is 0 which means 
 *      // that this item is not allowed to grow in the main direction (which is vertically).
 *      // The item is centered. Above (wxDirection.TOP) and below (wxDirection.BOTTOM) the item, 
 *      // a border is created with a size of 10.
 *
 *      dlg.sizer.add(sizer1, 0, wxAlignment.CENTER | wxDirection.TOP | wxDirection.BOTTOM, 10);
 *
 *      // Create a new wxBoxSizer and assign it to sizer1. The main direction of this sizer 
 *      // is horizontally. This means that when an item is added it will be shown on the same row.
 *
 *      sizer1 = new wxBoxSizer(wxOrientation.HORIZONTAL);
 *
 *      // Add the Ok button to the sizer and make sure that it has a right border of size 10. 
 *      // This way there's a space between the ok button and the cancel button.
 *
 *      sizer1.add(new wxButton(dlg, wxId.OK, "Ok"), 0, wxDirection.RIGHT, 10);
 *
 *      // Add the Cancel button to the sizer.
 *
 *      sizer1.add(new wxButton(dlg, wxId.CANCEL, "Cancel"));
 *
 *      // Add the sizer to the sizer of the dialog. The item is centered.
 *
 *      dlg.sizer.add(sizer1, 0, wxAlignment.CENTER);
 *
 *      // Before showing the dialog, set the autoLayout property to true and call 
 *      // layout to layout the controls. When the dialog is resized, the controls
 *      // will be automaticcally resized.
 *
 *      dlg.autoLayout = true;
 *      dlg.layout();
 *      dlg.showModal();
 *      return false;
 *    }
 *  </code></pre>
 * </class>
 */
ZZZJS_INIT_CLASS(Sizer, "Sizer", 0)

/***
 * <properties>
 *	<property name="minSize" type="@wxSize">
 *	 Get/Set the minimal size of the sizer.
 *	 See @wxSizer#setMinSize
 *  </property>
 *  <property name="position" type="@wxPoint" readonly="Y">
 *	 Gets the position of the sizer.
 *  </property>
 *  <property name="size" type="@wxSize" readonly="Y">
 *	 Gets the current size of the sizer.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(Sizer)
  ZZZJS_PROPERTY(P_MIN_SIZE, "minSize")
  ZZZJS_READONLY_PROPERTY(P_POSITION, "position")
  ZZZJS_READONLY_PROPERTY(P_SIZE, "size")
ZZZJS_END_PROPERTY_MAP()

ZZZJS_BEGIN_METHOD_MAP(Sizer)
  ZZZJS_METHOD("add", add, 1)
  ZZZJS_METHOD("layout", layout, 0)
  ZZZJS_METHOD("prepend", prepend, 5)
  ZZZJS_METHOD("remove", remove, 1)
  ZZZJS_METHOD("setDimension", setDimension, 4)
  ZZZJS_METHOD("setMinSize", setMinSize, 2)
  ZZZJS_METHOD("setItemMinSize", setItemMinSize, 3)
ZZZJS_END_METHOD_MAP()

//bool Sizer::GetProperty(wxSizer *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxSizer, Sizer)
{
	switch(id)
	{
	case P_MIN_SIZE:
		vp.set( Size::CreateObject(cx, new wxSize(p->GetMinSize())) );
		break;
	case P_SIZE:
		vp.set( Size::CreateObject(cx, new wxSize(p->GetSize())) );
		break;
	case P_POSITION:
      vp.set( zzzJs::ext::CreatePoint(cx, p->GetPosition()) );
		break;
	}
	return true;
 }
ZZZJS_END_GET_PROP


ZZZJS_BEGIN_SET_PROP(wxSizer, Sizer)
{
	if ( id == P_MIN_SIZE )
	{
		zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
		if( ZZZJS_PROP_GET_AP(apSize, Size, vp) == false )
		{
			p->SetMinSize(*(apSize.get()));
		}
	}
	return true;
}
ZZZJS_END_SET_PROP

/***
 * <method name="add">
 *	<function>
 *   <arg name="Window" type="@wxWindow">
 *	  An object with a @wxWindow as its prototype.
 *   </arg>
 *	 <arg name="Option" type=WXJS_TYPE_NUMBER default="0">
 *	  Option is used together with @wxBoxSizer. 0 means that the size of the control
 *	  is not allowed to change in the main orientation of the sizer. 1 means that the 
 *	  size of the control may grow or shrink in the main orientation of the sizer
 *   </arg>
 *   <arg name="Flag" type=WXJS_TYPE_NUMBER default="0">
 *	  This parameter is used to set a number of flags. One main behaviour of a flag is to
 *	  set a border around the window. Another behaviour is to determine the child window's 
 *	  behaviour when the size of the sizer changes. You can use the constants of @wxDirection
 *	  and @wxStretch.
 *   </arg>
 *   <arg name="Border" type=WXJS_TYPE_NUMBER default="0">
 *	  The border width. Use this when you used a border(@wxDirection) flag.
 *   </arg>
 *  </function>
 *	<function>
 *   <arg name="Sizer" type="wxSizer">
 *	  An object with a @wxWindow as its prototype.
 *	  An object which prototype is wxSizer.
 *   </arg>
 *	 <arg name="Option" type=WXJS_TYPE_NUMBER default="0">
 *	  Option is used together with @wxBoxSizer. 0 means that the size of the control
 *	  is not allowed to change in the main orientation of the sizer. 1 means that the 
 *	  size of the control may grow or shrink in the main orientation of the sizer
 *   </arg>
 *   <arg name="Flag" type=WXJS_TYPE_NUMBER default="0">
 *	  This parameter is used to set a number of flags. One main behaviour of a flag is to
 *	  set a border around the window. Another behaviour is to determine the child window's 
 *	  behaviour when the size of the sizer changes. You can use the constants of @wxDirection
 *	  and @wxStretch.
 *   </arg>
 *   <arg name="Border" type=WXJS_TYPE_NUMBER default="0">
 *	  The border width. Use this when you used a border(@wxDirection) flag.
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *	  The width of the spacer.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *	  The height of the spacer.
 *   </arg>
 *	 <arg name="Option" type=WXJS_TYPE_NUMBER default="0">
 *	  Option is used together with @wxBoxSizer. 0 means that the size of the control
 *	  is not allowed to change in the main orientation of the sizer. 1 means that the 
 *	  size of the control may grow or shrink in the main orientation of the sizer
 *   </arg>
 *   <arg name="Flag" type=WXJS_TYPE_NUMBER default="0">
 *	  This parameter is used to set a number of flags. One main behaviour of a flag is to
 *	  set a border around the window. Another behaviour is to determine the child window's 
 *	  behaviour when the size of the sizer changes. You can use the constants of @wxDirection
 *	  and @wxStretch.
 *   </arg>
 *   <arg name="Border" type=WXJS_TYPE_NUMBER default="0">
 *	  The border width. Use this when you used a border(@wxDirection) flag.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Adds a window, another sizer or a spacer to the sizer.
 *  </desc>
 * </method>
 */
JSBool Sizer::add(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	/*
	wxSizerItem * 	Add (wxWindow *window, const wxSizerFlags &flags)
 		Appends a child to the sizer. More...
 
	wxSizerItem * 	Add (wxWindow *window, int proportion=0, int flag=0, int border=0, wxObject *userData=NULL)
 		Appends a child to the sizer. More...
 
	wxSizerItem * 	Add (wxSizer *sizer, const wxSizerFlags &flags)
 		Appends a child to the sizer. More...
 
	wxSizerItem * 	Add (wxSizer *sizer, int proportion=0, int flag=0, int border=0, wxObject *userData=NULL)
 		Appends a child to the sizer. More...
 
	wxSizerItem * 	Add (int width, int height, int proportion=0, int flag=0, int border=0, wxObject *userData=NULL)
 		Appends a spacer child to the sizer. More...
 
	wxSizerItem * 	Add (int width, int height, const wxSizerFlags &flags)
 		Appends a spacer child to the sizer. More...
 
	wxSizerItem * 	Add (wxSizerItem *item)
	*/

	wxSizer *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	
	int argIndex = 0;
	int option = 0;
	int flag = 0;
	int border = 0;

	if ( Window::HasPrototype(cx, argv[argIndex]) )
	{		
		ZZZJS_CHECK_ARG_COUNT(1, 4);
		argIndex = argc -1;
		wxWindow *win = Window::GetPrivate(cx, argv[0], false);
		switch(argc)
		{
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(border, WXJS_TYPE_NUMBER);
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(flag, WXJS_TYPE_NUMBER);
			argIndex--;
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(option, WXJS_TYPE_NUMBER);
			argIndex--;
		}
		p->Add(win, option, flag, border);
	}
	else if (HasPrototype(cx, argv[argIndex]) )
	{
		wxSizer *sizer = GetPrivate(cx, argv[argIndex], false);
		ZZZJS_CHECK_ARG_COUNT(1, 4);
		argIndex = argc -1;
		switch(argc)
		{
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(border, WXJS_TYPE_NUMBER);
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(flag, WXJS_TYPE_NUMBER);
			argIndex--;
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(option, WXJS_TYPE_NUMBER);
			argIndex--;
		}
		p->Add(sizer, option, flag, border);
        
		// Protect the sizer
		JavaScriptClientData *data 
			= dynamic_cast<JavaScriptClientData*>(sizer->GetClientObject());
		if ( data != NULL )
		{
			data->Protect(true);
			data->SetOwner(false);
		}
	}
	else
	{
		ZZZJS_CHECK_ARG_COUNT(2, 5);
		argIndex = argc -1;


		switch(argc)
		{
		case 5:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(border, WXJS_TYPE_NUMBER);
			argIndex--;
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(flag, WXJS_TYPE_NUMBER);
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(option, WXJS_TYPE_NUMBER);
			argIndex--;
		}

		int height = 0, width = 0;

		argIndex = 1;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
		argIndex--;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);

		p->Add(width, height, option, flag, border);
	}

	return JS_TRUE;
}

/***
 * <method name="layout">
 *  <function />
 *  <desc>
 *	 Call this to force layout of the children.
 *  </desc>
 * </method> 
 */
JSBool Sizer::layout(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSizer *p = (wxSizer *) GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	
	p->Layout();

	return JS_TRUE;
}

/***
 * <method name="add">
 *	<function>
 *   <arg name="Window" type="@wxWindow">
 *	  An object with a @wxWindow as its prototype.
 *   </arg>
 *	 <arg name="Option" type=WXJS_TYPE_NUMBER default="0">
 *	  Option is used together with @wxBoxSizer. 0 means that the size of the control
 *	  is not allowed to change in the main orientation of the sizer. 1 means that the 
 *	  size of the control may grow or shrink in the main orientation of the sizer
 *   </arg>
 *   <arg name="Flag" type=WXJS_TYPE_NUMBER default="0">
 *	  This parameter is used to set a number of flags. One main behaviour of a flag is to
 *	  set a border around the window. Another behaviour is to determine the child window's 
 *	  behaviour when the size of the sizer changes. You can use the constants of @wxDirection
 *	  and @wxStretch.
 *   </arg>
 *   <arg name="Border" type=WXJS_TYPE_NUMBER default="0">
 *	  The border width. Use this when you used a border(@wxDirection) flag.
 *   </arg>
 *  </function>
 *	<function>
 *   <arg name="Sizer" type="wxSizer">
 *	  An object with a @wxWindow as its prototype.
 *	  An object which prototype is wxSizer.
 *   </arg>
 *	 <arg name="Option" type=WXJS_TYPE_NUMBER default="0">
 *	  Option is used together with @wxBoxSizer. 0 means that the size of the control
 *	  is not allowed to change in the main orientation of the sizer. 1 means that the 
 *	  size of the control may grow or shrink in the main orientation of the sizer
 *   </arg>
 *   <arg name="Flag" type=WXJS_TYPE_NUMBER default="0">
 *	  This parameter is used to set a number of flags. One main behaviour of a flag is to
 *	  set a border around the window. Another behaviour is to determine the child window's 
 *	  behaviour when the size of the sizer changes. You can use the constants of @wxDirection
 *	  and @wxStretch.
 *   </arg>
 *   <arg name="Border" type=WXJS_TYPE_NUMBER default="0">
 *	  The border width. Use this when you used a border(@wxDirection) flag.
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *	  The width of the spacer.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *	  The height of the spacer.
 *   </arg>
 *	 <arg name="Option" type=WXJS_TYPE_NUMBER default="0">
 *	  Option is used together with @wxBoxSizer. 0 means that the size of the control
 *	  is not allowed to change in the main orientation of the sizer. 1 means that the 
 *	  size of the control may grow or shrink in the main orientation of the sizer
 *   </arg>
 *   <arg name="Flag" type=WXJS_TYPE_NUMBER default="0">
 *	  This parameter is used to set a number of flags. One main behaviour of a flag is to
 *	  set a border around the window. Another behaviour is to determine the child window's 
 *	  behaviour when the size of the sizer changes. You can use the constants of @wxDirection
 *	  and @wxStretch.
 *   </arg>
 *   <arg name="Border" type=WXJS_TYPE_NUMBER default="0">
 *	  The border width. Use this when you used a border(@wxDirection) flag.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Prepends a window, another sizer or a spacer to the beginning of the list of items 
 *	 owned by this sizer. See @wxSizer#add.
 *  </desc>
 * </method>
 */
JSBool Sizer::prepend(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSizer *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	/*
	wxSizerItem * 	Prepend (wxWindow *window, const wxSizerFlags &flags)
 		Same as Add(), but prepends the items to the beginning of the list of items (windows, subsizers or spaces) owned by this sizer. More...
 
	wxSizerItem * 	Prepend (wxWindow *window, int proportion=0, int flag=0, int border=0, wxObject *userData=NULL)
 		Same as Add(), but prepends the items to the beginning of the list of items (windows, subsizers or spaces) owned by this sizer. More...
 
	wxSizerItem * 	Prepend (wxSizer *sizer, const wxSizerFlags &flags)
 		Same as Add(), but prepends the items to the beginning of the list of items (windows, subsizers or spaces) owned by this sizer. More...
 
	wxSizerItem * 	Prepend (wxSizer *sizer, int proportion=0, int flag=0, int border=0, wxObject *userData=NULL)
 		Same as Add(), but prepends the items to the beginning of the list of items (windows, subsizers or spaces) owned by this sizer. More...
 
	wxSizerItem * 	Prepend (int width, int height, int proportion=0, int flag=0, int border=0, wxObject *userData=NULL)
 		Same as Add(), but prepends the items to the beginning of the list of items (windows, subsizers or spaces) owned by this sizer. More...
 
	wxSizerItem * 	Prepend (int width, int height, const wxSizerFlags &flags)
 		Same as Add(), but prepends the items to the beginning of the list of items (windows, subsizers or spaces) owned by this sizer. More...
 
	wxSizerItem * 	Prepend (wxSizerItem *item)
	*/
	int argIndex = 0;
	int option = 0;
	int flag = 0;
	int border = 0;

	if ( Window::HasPrototype(cx, argv[argIndex]) )
	{
		ZZZJS_CHECK_ARG_COUNT(1, 4);
		argIndex = argc -1;
		wxWindow *win = Window::GetPrivate(cx, argv[0], false);
		switch(argc)
		{
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(border, WXJS_TYPE_NUMBER);
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(flag, WXJS_TYPE_NUMBER);
			argIndex--;
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(option, WXJS_TYPE_NUMBER);
			argIndex--;
		}
		p->Prepend(win, option, flag, border);
	}
	else if (HasPrototype(cx, argv[argIndex]) )
	{
		wxSizer *sizer = GetPrivate(cx, argv[0], false);
		ZZZJS_CHECK_ARG_COUNT(1, 4);
		argIndex = argc -1;
		switch(argc)
		{
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(border, WXJS_TYPE_NUMBER);
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(flag, WXJS_TYPE_NUMBER);
			argIndex--;
		case 2:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(option, WXJS_TYPE_NUMBER);
			argIndex--;
		}
		p->Prepend(sizer, option, flag, border);
	}
	else
	{
		ZZZJS_CHECK_ARG_COUNT(2, 5);
		argIndex = argc -1;

		switch(argc)
		{
		case 5:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(border, WXJS_TYPE_NUMBER);
			argIndex--;
		case 4:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(flag, WXJS_TYPE_NUMBER);
			argIndex--;
		case 3:
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(option, WXJS_TYPE_NUMBER);
			argIndex--;
		}

		int height = 0, width = 0;

		argIndex = 1;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
		argIndex--;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);

		p->Prepend(width, height, option, flag, border);
	}

	return JS_TRUE;
}

/***
 * <method name="remove">
 *	<function>
 *   <arg name="Index" type=WXJS_TYPE_NUMBER>
 *	  The index of the item to remove from the sizer.
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="Window" type="@wxWindow">
 *	  Window to remove from the sizer.
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="Sizer" type="wxSizer">
 *	  Sizer to remove from this sizer.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Removes the item from the sizer. Call @wxSizer#layout to update the screen.
 *  </desc>
 * </method>
 */
JSBool Sizer::remove(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	
	int argIndex = 0;
	wxSizer *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	if ( Window::HasPrototype(cx, argv[argIndex]) )
	{
		wxWindow *win = Window::GetPrivate(cx, argv[argIndex], false);
		//p->Remove(win);
		p->Detach(win);
	}
	else if ( HasPrototype(cx, argv[argIndex]) )
	{
		wxSizer *sizer = GetPrivate(cx, argv[argIndex], false);
		p->Remove(sizer);
	}
	else
	{
		int idx = 0;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(idx, WXJS_TYPE_NUMBER);
		p->Remove(idx);
	}

	return JS_TRUE;
}

/***
 * <method name="setDimension">
 *	<function>
 *   <arg name="x" type=WXJS_TYPE_NUMBER />
 *   <arg name="y" type=WXJS_TYPE_NUMBER />
 *   <arg name="width" type=WXJS_TYPE_NUMBER />
 *   <arg name="height" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *	 Call this to force the sizer to take the given dimension and thus force the items 
 *	 owned by the sizer to resize themselves according to the rules defined by the parameters 
 *	 in the @wxSizer#add and @wxSizer#prepend methods.
 *  </desc>
 * </method>
 */
JSBool Sizer::setDimension(JSContext *cx, unsigned argc, JS::Value *vp)
{
	/*
	void 	SetDimension (int x, int y, int width, int height)
 		Call this to force the sizer to take the given dimension and thus force the items owned by the sizer to resize themselves according to the rules defined by the parameter in the Add() and Prepend() methods. More...
 
	void 	SetDimension (const wxPoint &pos, const wxSize &size)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts. More...
	*/
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSizer *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;
	
	int argIndex = 0;
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;	
	zzzJsPtr<wxPoint> apPoin;
	bool bOk = false;
	
	ZZZJS_CHECK_ARG_COUNT(1, 4);
	
	if( ZZZJS_PROP_GET_AP(apPoin, zzzJs::ext::Point, argv[argIndex]) == true)
	{
		ZZZJS_CHECK_ARG_COUNT(2, 4);
		zzzJsPtr<wxSize> apSize;

		argIndex++;
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);

		x = apPoin->x;
		y = apPoin->y;
		width = apSize->x;
		height = apSize->y;

		bOk = true;
	}
	else if( argv[argIndex].isNumber() == true ) 
	{
		ZZZJS_CHECK_ARG_COUNT(4, 4);


		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(x, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(y, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
		argIndex++;

		bOk = true;
	}
	else if( argv[argIndex].isObjectOrNull() == true ) 
	{

		do {
			// Objectの場合
			/*
			{
				  x:***
				, y:***
				, width:***
				, height:***
			}
			*/
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}


			// x
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(x, pObj, PROP_NM_X, WXJS_TYPE_NUMBER)
			// y
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(y, pObj, PROP_NM_Y, WXJS_TYPE_NUMBER)
			// height
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, pObj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)
			// width
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, pObj, PROP_NM_WIDTH, WXJS_TYPE_DOUBLE)

			bOk = true;
		} while( 0 );
	}

	if( bOk == false )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}
	
	p->SetDimension(x, y, width, height);

	return JS_TRUE;
}

/***
 * <method name="setMinSize">
 *	<function>
 *   <arg name="Width" type=WXJS_TYPE_NUMBER />
 *   <arg name="Height" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *	 Sets the minimal size of the sizer.
 *	 See @wxSizer#minSize.
 *  </desc>
 * </method>
 */
JSBool Sizer::setMinSize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSizer *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;

	/*
	void 	SetMinSize (const wxSize &size)
 		Call this to give the sizer a minimal size. More...
 
	void 	SetMinSize (int width, int height)
 		This is an overloaded member function, provided for convenience. It differs from the above function only in what argument(s) it accepts. More...
	*/
	int argIndex = 0;
    int width = 0;
    int height = 0;
	zzzJsPtr<wxSize> apSize;
	bool bOk = false;

	ZZZJS_CHECK_ARG_COUNT(1, 2);


	if( ZZZJS_PROP_GET_AP(apSize, Size, argv[argIndex]) == true)
	{

		width = apSize->x;
		height = apSize->y;

		bOk = true;
	}
	else if( argv[argIndex].isNumber() == true ) 
	{
		ZZZJS_CHECK_ARG_COUNT(2, 2);

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
		argIndex++;

		bOk = true;
	}
	else if( argv[argIndex].isObjectOrNull() == true ) 
	{

		do {
			// Objectの場合
			/*
			{
				  width:***
				, height:***
			}
			*/
			jsval v;
			JSObject* pObj = argv[argIndex].toObjectOrNull();
			if( pObj == NULL ) {
				break;
			}


			// height
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(width, pObj, PROP_NM_HEIGHT, WXJS_TYPE_NUMBER)
			// width
			ZZZJS_PROP_FROMJS_CHK_AND_ERROR(height, pObj, PROP_NM_WIDTH, WXJS_TYPE_DOUBLE)

			bOk = true;
		} while( 0 );
	}

	if( bOk == false )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}


	p->SetMinSize(width, height);
	return JS_TRUE;
}

/***
 * <method name="setItemMinSize">
 *	<function>
 *	 <arg name="Window" type="@wxWindow" />
 *   <arg name="Width" type=WXJS_TYPE_NUMBER />
 *   <arg name="Height" type=WXJS_TYPE_NUMBER />
 *  </function>
 *	<function>
 *	 <arg name="Sizer" type="wxSizer" />
 *   <arg name="Width" type=ZZZJS_TYPE_NUMBER />
 *   <arg name="Height" type=ZZZJS_TYPE_NUMBER />
 *  </function>
 *	<function>
 *	 <arg name="Item" type=ZZZJS_TYPE_NUMBER />
 *   <arg name="Width" type=ZZZJS_TYPE_NUMBER />
 *   <arg name="Height" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <desc>
 *	 Sets an item minimal size.
 *  </desc>
 * </method>
 */
JSBool Sizer::setItemMinSize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSizer *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;


	/*
	bool 	SetItemMinSize (wxWindow *window, int width, int height)
 		Set an item's minimum size by window, sizer, or position. More...
 
	bool 	SetItemMinSize (wxWindow *window, const wxSize &size)
 		Set an item's minimum size by window, sizer, or position. More...
 
	bool 	SetItemMinSize (wxSizer *sizer, int width, int height)
 		Set an item's minimum size by window, sizer, or position. More...
 
	bool 	SetItemMinSize (wxSizer *sizer, const wxSize &size)
 		Set an item's minimum size by window, sizer, or position. More...
 
	bool 	SetItemMinSize (size_t index, int width, int height)
 		Set an item's minimum size by window, sizer, or position. More...
 
	bool 	SetItemMinSize (size_t index, const wxSize &size)
 		Set an item's minimum size by window, sizer, or position
	*/
	int argIndex = 0;
	int width = 0;
	int height = 0;
	zzzJsPtr<wxSize> apSize;
	bool bOk = false;



	 if ( Window::HasPrototype(cx, argv[argIndex]) == true )
	 {
		/*
		bool 	SetItemMinSize (wxWindow *window, int width, int height)
 			Set an item's minimum size by window, sizer, or position. More...
 
		bool 	SetItemMinSize (wxWindow *window, const wxSize &size)
 			Set an item's minimum size by window, sizer, or position. More...
		*/

		ZZZJS_CHECK_ARG_COUNT(2, 3);
		
		wxWindow * pWnd = Window::GetPrivate(cx, argv[argIndex], false);
		argIndex++;

		if( ZZZJS_PROP_GET_AP(apSize, Size, argv[argIndex]) == true)
		{
			width = apSize->x;
			height = apSize->y;
			bOk = true;
		}
		else if( argv[argIndex].isNumber() == true ) 
		{
			ZZZJS_CHECK_ARG_COUNT(3, 3);

			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
			argIndex++;
			bOk = true;
		}

		if( bOk == false )
		{
			JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
			return JS_FALSE;
		}
		
		p->SetItemMinSize(pWnd, width, height);
	 }
	 else if ( Sizer::HasPrototype(cx, argv[argIndex]) == true )
	 {
		/*
		bool 	SetItemMinSize (wxSizer *sizer, int width, int height)
 			Set an item's minimum size by window, sizer, or position. More...
 
		bool 	SetItemMinSize (wxSizer *sizer, const wxSize &size)
 			Set an item's minimum size by window, sizer, or position. More...
		*/

		ZZZJS_CHECK_ARG_COUNT(2, 3);

		
		wxSizer * pSizer = Sizer::GetPrivate(cx, argv[argIndex], false);
		argIndex++;		
		

		if( ZZZJS_PROP_GET_AP(apSize, Size, argv[argIndex]) == true)
		{
			width = apSize->x;
			height = apSize->y;
			bOk = true;
		}
		else if( argv[argIndex].isNumber() == true ) 
		{
			ZZZJS_CHECK_ARG_COUNT(3, 3);

			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
			argIndex++;
			bOk = true;
		}

		if( bOk == false )
		{
			JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
			return JS_FALSE;
		}
		
		p->SetItemMinSize(pSizer, width, height);
	}
	else if( argv[argIndex].isNumber() == true ) 
	{
		/*
		bool 	SetItemMinSize (size_t index, int width, int height)
 			Set an item's minimum size by window, sizer, or position. More...
 
		bool 	SetItemMinSize (size_t index, const wxSize &size)
 			Set an item's minimum size by window, sizer, or position
		*/
		ZZZJS_CHECK_ARG_COUNT(2, 3);
		int index = 0;

		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(index, WXJS_TYPE_NUMBER);	
		argIndex++;			
		
		if( ZZZJS_PROP_GET_AP(apSize, Size, argv[argIndex]) == true)
		{
			width = apSize->x;
			height = apSize->y;
			bOk = true;
		}
		else if( argv[argIndex].isNumber() == true ) 
		{
			ZZZJS_CHECK_ARG_COUNT(3, 3);

			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(width, WXJS_TYPE_NUMBER);
			argIndex++;
			ZZZJS_ARG_FROMJS_CHK_AND_ERROR(height, WXJS_TYPE_NUMBER);
			argIndex++;
			bOk = true;
		}

		if( bOk == false )
		{
			JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
			return JS_FALSE;
		}
		
		p->SetItemMinSize(index, width, height);
	}

	if( bOk == false )
	{
		JS_ReportError(cx, WXJS_ARGUMETS_ERROR);
		return JS_FALSE;
	}



    return JS_TRUE;
}

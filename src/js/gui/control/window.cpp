/*
 * wxJavaScript - window.cpp
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
 * $Id: window.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// window.cpp
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
#include "js/common/clntdata.h"
#include "js/ext/point.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/gui/misc/size.h"
#include "js/gui/misc/rect.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/font.h"
#include "js/gui/misc/sizer.h"
#include "js/gui/misc/validate.h"
#include "js/gui/misc/acctable.h"
#include "js/gui/control/window.h"
#include "js/gui/gdi/dc.h"


using namespace zzzJs;
using namespace zzzJs::gui;


/***
 * <file>control/window</file>
 * <module>gui</module>
 * <class name="wxWindow">
 *	wxWindow is the prototype of all objects based on wxWindow. 
 *	This means that you can use all properties and methods in all those objects.
 * </class>
 */
WXJS_INIT_CLASS(Window, "Window", 0)

void Window::InitClass(JSContext* WXUNUSED(cx), JSObject* WXUNUSED(obj), JSObject* WXUNUSED(proto))
{
    WindowEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *	<property name="acceleratorTable" type="@wxAcceleratorTable" />
 *	<property name="acceptsFocus" type="Boolean" readonly="Y">
 * 	 Can this window have focus?
 *  </property>
 *	<property name="acceptsFocusFromKeyboard" type="Boolean" readonly="Y">
 *	can this window be given focus by keyboard navigation? if not, the
 *	only way to give it focus (provided it accepts it at all) is to
 *	click it
 *  </property>
 *	<property name="autoLayout"	type="Boolean">
 *	Indicates whether the layout method must be called automatically or not when a window is resized.
 *	See @wxSizer
 *  </property>
 *	<property name="backgroundColour" type="@wxColour">
 *  Get/Set the background colour of the window
 *  </property>
 *	<property name="bestSize" type="@wxSize" readonly="Y">
 *	Gets the size best suited for the window
 *  </property>
 *	<property name="children" type="Array" readonly="Y">
 *	Gets a list of children
 *  </property>
 *	<property name="clientAreaOrigin" type="@wxPoint" readonly="Y">
 *	Get the origin of the client area of the window relative to the
 *	window top left corner (the client area may be shifted because of
 *	the borders, scrollbars, other decorations...)
 *  </property>
 *	<property name="clientHeight" type=WXJS_TYPE_NUMBER>
 *	Get/Set the client height.
 *  </property>
 *	<property name="clientRect" type="@wxRect" readonly="Y">
 *	Gets the rectangle of the client area
 *  </property>
 *	<property name="clientSize" type="@wxSize">
 *	Get/Set the clientsize of the window. You can also use
 *  @wxRect (only when setting)
 *  </property>
 *	<property name="clientWidth" type=WXJS_TYPE_NUMBER>
 *	Get/Set the client width.
 *  </property>
 *	<property name="enable" type="Boolean">
 *	Enables/Disables the window
 *  </property>
 *	<property name="extraStyle" type=WXJS_TYPE_NUMBER>
 *	Get/Set the extra window styles.
 *	See @wxWindow#extraStyles
 *  </property>
 *	<property name="font" type="@wxFont">
 *  Get/Set the font.
 *  </property>
 *	<property name="foregroundColour" type="@wxColour">
 *  Get/Set the foreground colour of the window
 *  </property>
 *	<property name="hasCapture" type="Boolean">
 *	Returns true when this window has the capture.
 *	Set to true to capture this window, or false to release the capture.
 *	(not possible in wxWindows) 
 *  </property>
 *	<property name="height" type=WXJS_TYPE_NUMBER>
 *	Get/Set the height.
 *  </property>
 *	<property name="id" type=WXJS_TYPE_NUMBER readonly="Y">
 *	Gets the unique id of the window, or -1 when it is not set.
 *  </property>
 *	<property name="parent" type="@wxWindow">
 *	Get/Set the parent
 *  </property>
 *	<property name="position" type="@wxPoint">
 *	Get/Set the position.
 *  </property>
 *	<property name="rect" type="@wxRect" readonly="Y">
 *	Gets the window rectangle 
 *  </property>
 *	<property name="shown" type="Boolean" readonly="Y">
 *	Returns true when the window is visible
 *	See @wxWindow#visible property, @wxWindow#show method
 *  </property>
 *	<property name="size" type="@wxSize">
 *	 Get/Set the size of the window. You can also use
 *   @wxRect (only when setting)
 *  </property>
 *	<property name="sizer" type="@wxSizer">
 *	Get/Set the sizer of the window. Set @wxWindow#autoLayout to true when you
 *	want that the sizer is automatically used when the size of the window is changed.
 *  </property>
 *	<property name="topLevel" type="Boolean" readonly="Y">
 *	Returns true when the window is a top level window.
 *	Currently all frames and dialogs are considered to be 
 *	top-level windows (even if they have a parent window).
 *  </property>
 *	<property name="validator" type="@wxValidator">
 *	Get/Set the validator of the window
 *  </property>
 *	<property name="visible" type="Boolean">
 *	Show/Hide the window.
 *  </property>
 *	<property name="windowStyle" type=WXJS_TYPE_NUMBER>
 *	Get/Set the window flag styles.
 *	Please note that some styles cannot be changed after the window 
 *	creation and that @wxWindow#refresh might be called after changing 
 *	the others for the change to take place immediately.
 *	See @wxWindow#styles
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Window)
  WXJS_PROPERTY( P_AUTO_LAYOUT, "autoLayout")
  WXJS_PROPERTY( P_CLIENT_HEIGHT, "clientHeight")
  WXJS_PROPERTY( P_CLIENT_WIDTH, "clientWidth")
  WXJS_READONLY_PROPERTY( P_CLIENT_ORIGIN, "clientAreaOrigin")
  WXJS_READONLY_PROPERTY( P_ACCEPTS_FOCUS, "acceptsFocus")
  WXJS_READONLY_PROPERTY( P_ACCEPTS_FOCUS_KEYBOARD, "acceptsFocusFromKeyboard")
  WXJS_PROPERTY( P_ENABLE, "enable")
  WXJS_PROPERTY( P_HEIGHT, "height")
  WXJS_PROPERTY( P_VISIBLE, "visible")
  WXJS_PROPERTY( P_WIDTH, "width")
  WXJS_PROPERTY( P_SIZE, "size")
  WXJS_PROPERTY( P_SIZER, "sizer")
  WXJS_PROPERTY( P_CLIENT_SIZE, "clientSize")
  WXJS_PROPERTY( P_POSITION, "position")
  WXJS_READONLY_PROPERTY( P_ID, "id")
  WXJS_READONLY_PROPERTY( P_RECT, "rect")
  WXJS_READONLY_PROPERTY( P_CLIENT_RECT, "clientRect")
  WXJS_READONLY_PROPERTY( P_BEST_SIZE, "bestSize")
  WXJS_PROPERTY( P_WINDOW_STYLE, "windowStyle")
  WXJS_PROPERTY( P_EXTRA_STYLE, "extraStyle")
  WXJS_READONLY_PROPERTY( P_SHOWN, "shown")
  WXJS_READONLY_PROPERTY( P_TOP_LEVEL, "topLevel")
  WXJS_READONLY_PROPERTY( P_CHILDREN, "children")
  WXJS_PROPERTY( P_PARENT, "parent")
  WXJS_PROPERTY( P_VALIDATOR, "validator")
  WXJS_PROPERTY( P_ACCELERATOR_TABLE, "acceleratorTable")
  WXJS_PROPERTY( P_HAS_CAPTURE, "hasCapture")
  WXJS_PROPERTY( P_BACKGROUND_COLOUR, "backgroundColour")
  WXJS_PROPERTY( P_FOREGROUND_COLOUR, "foregroundColour")
  WXJS_PROPERTY( P_FONT, "font")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxWindow, Window)
	switch (id) 
	{
	case P_VISIBLE:
	case P_SHOWN:
		ToJSVal(cx, vp, p->IsShown());
		break;
	case P_ENABLE:
		ToJSVal(cx, vp, p->IsEnabled());
		break;
	case P_SIZE:
		vp.set( Size::CreateObject(cx, new wxSize(p->GetSize())) );
		break;
	case P_CLIENT_SIZE:
		vp.set( Size::CreateObject(cx, new wxSize(p->GetClientSize())) );
		break;
	case P_WIDTH:
		ToJSVal(cx, vp, p->GetSize().GetWidth());
		break;
	case P_HEIGHT:
		ToJSVal(cx, vp, p->GetSize().GetHeight());
		break;
	case P_CLIENT_HEIGHT:
		ToJSVal(cx, vp, p->GetClientSize().GetHeight());
		break;
	case P_CLIENT_WIDTH:
		ToJSVal(cx, vp, p->GetClientSize().GetHeight());
		break;
	case P_POSITION:
      vp.set( zzzJs::ext::CreatePoint(cx, p->GetPosition()) );
		break;
	case P_CLIENT_ORIGIN:
      vp.set( zzzJs::ext::CreatePoint(cx, p->GetClientAreaOrigin()) );
	    break;
	case P_SIZER:
		{
          wxSizer *sizer = p->GetSizer();
          if ( sizer != NULL )
          {
            JavaScriptClientData *data
              = dynamic_cast<JavaScriptClientData*>(sizer->GetClientObject());
            if ( data != NULL )
            {
			  vp.set(  OBJECT_TO_JSVAL(data->GetObject()) );
            }
          }
		  break;
		}
	case P_AUTO_LAYOUT:
		ToJSVal(cx, vp, p->GetAutoLayout());
		break;
	case P_ID:
		ToJSVal(cx, vp, p->GetId());
		break;
	case P_RECT:
        vp.set(  Rect::CreateObject(cx, new wxRect(p->GetRect())) );
		break;
	case P_CLIENT_RECT:
		vp.set(  Rect::CreateObject(cx, new wxRect(p->GetClientRect())) );
		break;
	case P_BEST_SIZE:
		vp.set( Size::CreateObject(cx, new wxSize(p->GetBestSize())) );
		break;
	case P_WINDOW_STYLE:
		ToJSVal(cx, vp, p->GetWindowStyle());
		break;
	case P_EXTRA_STYLE:
		ToJSVal(cx, vp, p->GetExtraStyle());
		break;
	case P_TOP_LEVEL:
		ToJSVal(cx, vp, p->IsTopLevel());
		break;
	case P_ACCEPTS_FOCUS:
		ToJSVal(cx, vp, p->AcceptsFocus());
		break;
	case P_ACCEPTS_FOCUS_KEYBOARD:
		ToJSVal(cx, vp, p->AcceptsFocusFromKeyboard());
		break;
	case P_CHILDREN:
		{
			wxWindowList &winList = p->GetChildren();
			uint32_t count = winList.GetCount();

			JSObject *objSelections = JS_NewArrayObject(cx, count, NULL);
			vp.set( OBJECT_TO_JSVAL(objSelections) );
			
			uint32_t i = 0;
			for (wxWindowList::Node *node = winList.GetFirst(); node; node = node->GetNext() )
			{
				wxWindow *win = dynamic_cast<wxWindow*>(node->GetData());
                if ( win )
                {
                  JavaScriptClientData *data
                    = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
                  if ( data != NULL )
                  {
				    jsval element = OBJECT_TO_JSVAL(data->GetObject());
				    JS_SetElement(cx, objSelections, i++, &element);
                  }
                }
			}
			break;
		}
	case P_PARENT:
		{
			wxWindow *win = p->GetParent();
            if ( win )
            {
              JavaScriptClientData *data
                = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
              if ( data != NULL )
              {
    			vp.set( OBJECT_TO_JSVAL(data->GetObject()) );
              }
            }
			break;
		}
	case P_VALIDATOR:
		{
			wxValidator *val = p->GetValidator();
            if ( val )
            {
              JavaScriptClientData *data
                = dynamic_cast<JavaScriptClientData*>(val->GetClientObject());
              if ( data != NULL )
              {
    			vp.set( OBJECT_TO_JSVAL(data->GetObject()) );
              }
            }
			break;
		}
	case P_HAS_CAPTURE:
		ToJSVal(cx, vp, p->HasCapture());
		break;
	case P_BACKGROUND_COLOUR:
		vp.set( Colour::CreateObject(cx, new wxColour(p->GetBackgroundColour())) );
		break;
	case P_FOREGROUND_COLOUR:
		vp.set( Colour::CreateObject(cx, new wxColour(p->GetForegroundColour())) );
		break;
	case P_FONT:
        vp.set( Font::CreateObject(cx, new wxFont(p->GetFont()), obj) );
		break;
	}
	return true;
WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxWindow, Window)
	switch(id)
	{
	case P_ACCELERATOR_TABLE:
		{
			wxAcceleratorTable *table = AcceleratorTable::GetPrivate(cx, vp);
			if ( table != NULL )
				p->SetAcceleratorTable(*table);
			break;
		}
	case P_VISIBLE:
		{
			bool visible;
			if ( FromJS(cx, vp, visible) )
				p->Show(visible);
			break;
		}
	case P_ENABLE:
		{
			bool enable;
			if ( FromJS(cx, vp, enable) )
				p->Enable(enable);
    		break;
		}
	case P_WIDTH:
		{
			int size;
			if ( FromJS(cx, vp, size) )
				p->SetSize(size, -1);
			break;
		}
	case P_HEIGHT:
		{
			int height;
			if ( FromJS(cx, vp, height) )
				p->SetSize(-1, height);
			break;
		}
	case P_SIZE:
		{
			zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
			if( ZZZJS_PROP_GET_AP(apSize, Size, vp) == true )
			{
				p->SetSize(*(apSize.get()));
			}
			else
			{
				// Try wxRect
                zzzJsPtr<wxRect> apRect;
				//if ( FromJS(cx, vp, rect) )
				if( (ZZZJS_PROP_GET_AP(apRect, Rect, vp)) == true )
					p->SetSize( *(apRect.get()) );
			}
    		break;
		}
	case P_SIZER:
    {
      wxSizer *sizer = Sizer::GetPrivate(cx, vp);
      if ( sizer != NULL )
      {
        p->SetSizer(sizer);
        JavaScriptClientData *data
          = dynamic_cast<JavaScriptClientData*>(sizer->GetClientObject());
        if ( data != NULL )
        {
          data->Protect(true);
          data->SetOwner(false);
        }
	  }
  	  break;
	}
	case P_CLIENT_HEIGHT:
		{
			int size;
			if ( FromJS(cx, vp, size) )
				p->SetClientSize(-1, size);
			break;
		}
	case P_CLIENT_WIDTH:
		{
			int size;
			if ( FromJS(cx, vp, size) )
				p->SetClientSize(size, -1);
			break;
		}
	case P_CLIENT_SIZE:
		{
			zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
			if( ZZZJS_PROP_GET_AP(apSize, Size, vp) == true )
			{
				p->SetClientSize(*(apSize.get()));
			}
			else
			{
				// Try wxRect
                zzzJsPtr<wxRect> apRect;
				//if ( FromJS(cx, vp, rect) )
				if( (ZZZJS_PROP_GET_AP(apRect, Rect, vp)) == true )
					p->SetClientSize( *(apRect.get()) );
			}
			break;
		}
	case P_POSITION:
		{
          zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
		  if ( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, vp) == true )
			  p->Move(*(apPoint.get()));
		}
		break;
	case P_AUTO_LAYOUT:
		{
			bool autoLayout;
			if ( FromJS(cx, vp, autoLayout) )
				p->SetAutoLayout(autoLayout);
			break;
		}
	case P_WINDOW_STYLE:
		{
			int style;
			if ( FromJS(cx, vp, style) )
				p->SetWindowStyle(style);
			break;
		}
	case P_EXTRA_STYLE:
		{
			int style;
			if ( FromJS(cx, vp, style) )
				p->SetExtraStyle(style);
			break;
		}
	case P_PARENT:
        {
            wxWindow *win = Window::GetPrivate(cx, vp);
		    if ( win != NULL )
            {
				p->Reparent(win);
			}
		}
	case P_VALIDATOR:
		{
			wxValidator *val = Validator::GetPrivate(cx, vp);
			if ( val != NULL )
			{
                val->SetClientObject(new JavaScriptClientData(cx, JSVAL_TO_OBJECT(vp), true, true));
				p->SetValidator(*val);
				val->SetWindow(p); // We do this, because otherwise we loose the knowledge
								   // of WindowObject
			}
			break;
		}
	case P_HAS_CAPTURE:
		{
			bool capture;
			if ( FromJS(cx, vp, capture) )
				capture ? p->CaptureMouse() : p->ReleaseMouse();
			break;
		}
	case P_BACKGROUND_COLOUR:
		{
			wxColour *colour = Colour::GetPrivate(cx, vp);
			if ( colour != NULL )
				p->SetBackgroundColour(*colour);
			break;
		}
	case P_FOREGROUND_COLOUR:
		{
			wxColour *colour = Colour::GetPrivate(cx, vp);
			if ( colour != NULL )
				p->SetForegroundColour(*colour);
			break;
		}
	case P_FONT:
		{
			zzzJsPtr<wxFont> apFont;
			if ( ZZZJS_PROP_GET_AP(apFont, Font, vp) == true )
				p->SetFont(*apFont.get());
			break;
		}
	}
	return true;
WXJS_END_SET_PROP


/***
 * <class_properties>
 *	<property name="capture" type="@wxWindow" readonly="Y">
 *	 Gets the window that has the capture.
 *	 See @wxWindow#hasCapture, @wxWindow#releaseMouse and @wxWindow#captureMouse
 *  </property>
 * </class_properties>
 */
WXJS_BEGIN_STATIC_PROPERTY_MAP(Window)
  WXJS_READONLY_STATIC_PROPERTY(P_CAPTURE, "capture")
WXJS_END_PROPERTY_MAP()

bool Window::GetStaticProperty(JSContext* cx,
                                    int id,
                                    JS::MutableHandle<JS::Value>& vp)
{
    if ( id == P_CAPTURE )
	{
		wxWindow *win = wxWindow::GetCapture();
        if ( win != NULL )
        {
          JavaScriptClientData *data
            = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
          if ( data != NULL )
          {
            vp.set( OBJECT_TO_JSVAL(data->GetObject()) );
          }
        }
	}
	return true;
}

/***
 * <constants>
 *	<type name="styles">
 *   <constant name="DOUBLE_BORDER" />
 *   <constant name="SUNKEN_BORDER" />
 *   <constant name="RAISED_BORDER" />
 *   <constant name="BORDER" />
 *   <constant name="SIMPLE_BORDER" />
 *   <constant name="STATIC_BORDER" />
 *   <constant name="NO_BORDER" />
 *   <constant name="NO_3D" />
 *   <constant name="CLIP_CHILDREN" />
 *   <constant name="TAB_TRAVERSAL" />
 *   <constant name="WANTS_CHARS" />
 *   <constant name="NO_FULL_REPAINT_ON_RESIZE" />
 *   <constant name="VSCROLL" />
 *   <constant name="HSCROLL" />
 *  </type>
 *  <type name="extraStyles">
 *   <constant name="WS_EX_VALIDATE_RECURSIVELY">
 *	  TransferDataTo/FromWindow() and Validate() methods will recursively descend 
 *	  into all children of the window if it has this style flag set.  
 *   </constant>
 *   <constant name="WS_EX_BLOCK_EVENTS">
 *	  Normally, the command events are propagared upwards to the window parent recursively 
 *	  until a handler for them is found. Using this style allows to prevent them from being 
 *	  propagated beyond this window. Notice that wxDialog has this style on by default for 
 *	  the reasons explained in the event processing overview.  
 *   </constant>
 *   <constant name="WS_EX_TRANSIENT">
 *	  This can be used to prevent a window from being used as an implicit parent for the 
 *	  dialogs which were created without a parent. It is useful for the windows which can
 *	  disappear at any moment as creating childs of such windows results in fatal problems.  
 *   </constant>
 *  </type>
 *  <type name="sizeFlags">
 *   <constant name="SIZE_AUTO_WIDTH">
 *	  Use internally-calculated width if -1
 *   </constant>
 *   <constant name="SIZE_AUTO_HEIGHT">
 *	  Use internally-calculated height if -1
 *   </constant>
 *   <constant name="SIZE_AUTO">
 *	  Use internally-calculated width and height if each is -1
 *   </constant>
 *   <constant name="SIZE_USE_EXISTING">
 *	  Ignore missing (-1) dimensions (use existing).
 *   </constant>
 *   <constant name="SIZE_ALLOW_MINUS_ONE">
 *	  Allow -1 as a valid position
 *   </constant>
 *   <constant name="SIZE_NO_ADJUSTMENTS">
 *	  Don't do parent client adjustments (for implementation only)
 *   </constant>
 *  </type>
 * </constants>
 */

WXJS_BEGIN_CONSTANT_MAP(Window)
  WXJS_CONSTANT(wx, DOUBLE_BORDER)
  WXJS_CONSTANT(wx, SUNKEN_BORDER)
  WXJS_CONSTANT(wx, RAISED_BORDER)
  WXJS_CONSTANT(wx, BORDER)
  WXJS_CONSTANT(wx, SIMPLE_BORDER)
  WXJS_CONSTANT(wx, STATIC_BORDER)
  WXJS_CONSTANT(wx, NO_BORDER)
//  WXJS_CONSTANT(wx, NO_3D)
  WXJS_CONSTANT(wx, CLIP_CHILDREN)
  WXJS_CONSTANT(wx, TAB_TRAVERSAL)
  WXJS_CONSTANT(wx, WANTS_CHARS)
  WXJS_CONSTANT(wx, NO_FULL_REPAINT_ON_RESIZE)
  WXJS_CONSTANT(wx, VSCROLL)
  WXJS_CONSTANT(wx, HSCROLL)
  WXJS_CONSTANT(wx, SIZE_AUTO_WIDTH)
  WXJS_CONSTANT(wx, SIZE_AUTO_HEIGHT)
  WXJS_CONSTANT(wx, SIZE_AUTO)
  WXJS_CONSTANT(wx, SIZE_USE_EXISTING)
  WXJS_CONSTANT(wx, SIZE_ALLOW_MINUS_ONE)
  WXJS_CONSTANT(wx, SIZE_NO_ADJUSTMENTS)
  WXJS_CONSTANT(wx, WS_EX_VALIDATE_RECURSIVELY)
  WXJS_CONSTANT(wx, WS_EX_BLOCK_EVENTS)
  WXJS_CONSTANT(wx, WS_EX_TRANSIENT)
WXJS_END_CONSTANT_MAP()

WXJS_BEGIN_METHOD_MAP(Window)
  WXJS_METHOD("captureMouse", captureMouse, 0)
  WXJS_METHOD("centre", centre, 1)
  WXJS_METHOD("center", centre, 1)
  WXJS_METHOD("clearBackground", clearBackground, 0)
  WXJS_METHOD("clientToScreen", clientToScreen, 1)
  WXJS_METHOD("close", close, 1)
  WXJS_METHOD("convertDialogToPixels", convertDialogToPixels, 1)
  WXJS_METHOD("convertPixelsToDialog", convertPixelsToDialog, 1)
  WXJS_METHOD("destroy", destroy, 0)
  WXJS_METHOD("destroyChildren", destroyChildren, 0)
  WXJS_METHOD("releaseMouse", releaseMouse, 0)
  WXJS_METHOD("layout", layout, 0)
  WXJS_METHOD("move", move, 2)
  WXJS_METHOD("lower", lower, 0)
  WXJS_METHOD("raise", raise, 0)
  WXJS_METHOD("centreOnParent", centreOnParent, 1)
  WXJS_METHOD("centerOnParent", centreOnParent, 1)
  WXJS_METHOD("show", show, 1)
  WXJS_METHOD("fit", fit, 0)
  WXJS_METHOD("setSizeHints", setSizeHints, 6)
  WXJS_METHOD("refresh", refresh, 2)
  WXJS_METHOD("setFocus", setFocus, 0)
  WXJS_METHOD("findWindow", findWindow, 1)
  WXJS_METHOD("initDialog", initDialog, 0)
  WXJS_METHOD("transferDataToWindow", transferDataToWindow, 0)
  WXJS_METHOD("transferDataFromWindow", transferDataFromWindow, 0)
  WXJS_METHOD("validate", validate, 0)
  WXJS_METHOD("makeModal", makeModal, 1)
  WXJS_METHOD("warpPointer", warpPointer, 1)
  WXJS_METHOD("update", update, 0)
  WXJS_METHOD("freeze", freeze, 0)
  WXJS_METHOD("thaw", thaw, 0)
  WXJS_METHOD("prepareDC", prepareDC, 1)
  
// setter	  
  WXJS_METHOD("setAutoLayout", setAutoLayout, 1)
  WXJS_METHOD("setClientHeight", setClientHeight, 1)
  WXJS_METHOD("setClientWidth", setClientWidth, 1)
  WXJS_METHOD("setEnable", setEnable, 1)
  WXJS_METHOD("setHeight", setHeight, 1)
  WXJS_METHOD("setVisible", setVisible, 1)
  WXJS_METHOD("setWidth", setWidth, 1)
  WXJS_METHOD("setSizer", setSizer, 1)
  WXJS_METHOD("setClientSize", setClientSize, 1)
  WXJS_METHOD("setPosition", setPosition, 1)
  WXJS_METHOD("setWindowStyle", setWindowStyle, 1)
  WXJS_METHOD("setExtraStyle", setExtraStyle, 1)
  WXJS_METHOD("setParent", setParent, 1)
  WXJS_METHOD("setValidator", setValidator, 1)
  WXJS_METHOD("setAcceleratorTable", setAcceleratorTable, 1)
  WXJS_METHOD("setHasCapture", setHasCapture, 1)
  WXJS_METHOD("setBackgroundColour", setBackgroundColour, 1)
  WXJS_METHOD("setForegroundColour", setForegroundColour, 1)
  WXJS_METHOD("setFont", setFont, 1)

WXJS_END_METHOD_MAP()

/***
 * <method name="captureMouse">
 *	<function />
 *	<desc>
 *   Directs all mouse input to this window. Call @wxWindow#releaseMouse to release the capture.
 *   See @wxWindow#hasCapture
 *  </desc>
 * </method>
 */
JSBool Window::captureMouse(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->CaptureMouse();

	return JS_TRUE;
}

/***
 * <method name="centre">
 *	<function>
 *   <arg name="Direction" type=WXJS_TYPE_NUMBER default="wxOrientation.BOTH"> 
 *	  You can use the constants from @wxOrientation
 *   </arg>
 *  </function>
 * </method>
 */
JSBool Window::centre(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	if ( argc == 0 )
	{
		p->Centre();
	}
	else if (argc == 1)
	{
		int direction;
		if ( FromJS(cx, argv[0], direction) )
		{
			p->Centre(direction);
		}
		else
		{
			return JS_FALSE;
		}
	}
    else
    {
        return JS_FALSE;
    }

	return JS_TRUE;
}

/***
 * <method name="clearBackground">
 *	<function />
 *  <desc>
 *   Clears the window by filling it with the current background color.
 *  </desc>
 * </method>
 */
JSBool Window::clearBackground(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->ClearBackground();

	return JS_TRUE;
}

/***
 * <method name="clientToScreen">
 *	<function returns="@wxPoint">
 *	 <arg name="Point" type="@wxPoint">
 *	  The client position
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns the screen coordinates from coordinates relative to this window.
 *  </desc>
 * </method>
 */
JSBool Window::clientToScreen(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	
	ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
	argIndex++;

     *vp = zzzJs::ext::CreatePoint(cx, p->ClientToScreen( *(apPoint.get()) ));


	return JS_TRUE;
}

/***
 * <method name="close">
 *	<function>
 *   <arg name="Force" type="Boolean" default="false">
 *	  When true the application can't veto the close. By default Force is false.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Closes the window. This applies only for @wxFrame and @wxDialog objects.	
 *  </desc>
 * </method>
 */
JSBool Window::close(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

    if ( argc == 1 )
    {
        bool force = false;
        if ( FromJS(cx, argv[0], force) )
        {
            p->Close(force);
            return JS_TRUE;
        }
        else
        {
            return JS_FALSE;
        }
    }
    else if ( argc == 0 )
    {
        p->Close();
        return JS_TRUE;
    }

	return JS_FALSE;
}

/***
 * <method name="convertDialogToPixels">
 *	<function returns="@wxPoint">
 *   <arg name="Point" type="@wxPoint">Converts a point</arg>
 *  </function>
 *  <function returns="@wxSize">
 *	 <arg name="Size" type="@wxSize">
 *	  Converts a size
 *   </arg>
 *  </function>
 *  <desc>
 *	 Converts a point or a size to from dialog units to pixels.
 *  </desc>
 * </method>
 */
JSBool Window::convertDialogToPixels(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	JSBool result = JS_FALSE;
	
	int argIndex = 0;
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	if( ZZZJS_PROP_GET_AP(apSize, Size, argv[0]) == true )
	{
		*vp = Size::CreateObject(cx, new wxSize(p->ConvertDialogToPixels(*(apSize.get()))));
		return JS_TRUE;
	}
	else
	{
		argIndex = 0;
        zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
        if ( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, argv[argIndex]) == true )
		{
          *vp = zzzJs::ext::CreatePoint(cx, p->ConvertDialogToPixels( *(apPoint.get()) ));
		  result = JS_TRUE;
		}
	}

	return result;
}

/***
 * <method name="convertPixelsToDialog">
 *	<function returns="@wxPoint">
 *   <arg name="Point" type="wxPoint">Converts a point</arg>
 *  </function>
 *  <function>
 *	 <arg name="Size" type="@wxSize">
 *	  Converts a size
 *   </arg>
 *  </function>
 *  <desc>
 *	 Converts a point or a size from pixels to dialog units.
 *  </desc>
 * </method>
 */
JSBool Window::convertPixelsToDialog(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	
	int argIndex = 0;
    JSBool result = JS_FALSE;

	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	if( ZZZJS_PROP_GET_AP(apSize, Size, argv[0]) == true )
	{
		*vp = Size::CreateObject(cx, new wxSize(p->ConvertPixelsToDialog(*(apSize.get()))));
		result = JS_TRUE;
	}
	else
	{
        zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
        if ( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, argv[argIndex]) == true )
		{
          *vp = zzzJs::ext::CreatePoint(cx, p->ConvertPixelsToDialog(*(apPoint.get())));
			result = JS_TRUE;
		}
	}

	return result;
}

/***
 * <method name="destroy">
 *	<function returns="Boolean" />
 *	<desc>
 *   Destroys the window. Returns true when the window is destroyed.
 *  </desc>
 * </method>
 */
JSBool Window::destroy(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	*vp = ToJS(cx, p->Destroy());

	return JS_TRUE;
}

/***
 * <method name="destroyChildren">
 *	<function />
 *	<desc>
 *   Destroys all children of the window.
 *  </desc>
 * </method>
 */
JSBool Window::destroyChildren(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->DestroyChildren();

	return JS_TRUE;
}

/***
 * <method name="releaseMouse">
 *	<function />
 *	<desc>
 *   Releases mouse input captured by @wxWindow#captureMouse.
 *   See @wxWindow#hasCapture and @wxWindow#captureMouse
 *  </desc>
 * </method>
 */
JSBool Window::releaseMouse(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->ReleaseMouse();

	return JS_TRUE;
}

/***
 * <method name="warpPointer">
 *	<function>
 *   <arg name="X" type=WXJS_TYPE_NUMBER />
 *   <arg name="Y" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <function>
 *	 <arg name="Point" type="@wxPoint" />
 *	</function>
 *  <desc>
 *	 Moves the mouse to the given position
 *	</desc>
 * </method>
 */
JSBool Window::warpPointer(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	
	int argIndex = 0;

	if ( argc == 1 )
	{

        zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
        if ( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, argv[argIndex]) == true )
		{
			p->WarpPointer(apPoint->x, apPoint->y);
            return JS_TRUE;
		}
	}
	else if ( argc == 2 )
	{
        int x = 0;
        int y = 0;
		if (    FromJS(cx, argv[0], x)
			 || FromJS(cx, argv[1], y) )
		{
			p->WarpPointer(x, y);
            return JS_TRUE;
		}
	}
	
    return JS_FALSE;
}

/***
 * <method name="layout">
 *	<function />
 *  <desc>
 * 	 Layout the window using the sizer.
 *  </desc>
 * </method>
 */
JSBool Window::layout(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->Layout();

	return JS_TRUE;
}

/***
 * <method name="move">
 *	<function>
 *   <arg name="X" type=WXJS_TYPE_NUMBER />
 *   <arg name="Y" type=WXJS_TYPE_NUMBER />
 *  </function>
 *  <function>
 *   <arg name="Point" type="@wxPoint" />
 *  </function>
 *  <desc>
 * 	 Moves the window.
 *  </desc>
 * </method>
 */
JSBool Window::move(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

    if ( argc > 2 )
        argc = 2;
	
	int argIndex = 0;
    JSBool result = JS_FALSE;
    
    switch(argc)
    {
    case 2:
        {
            int x;
            int y;
            if (    FromJS(cx, argv[0], x)
                 && FromJS(cx, argv[1], y) )
            {
                p->Move(x, y);
                result = JS_TRUE;
            }
            break;
        }
    case 1:
	    {
			argIndex = 0;
			zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
			if ( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, argv[argIndex]) == true )
			{
			    p->Move(*(apPoint.get()));
                result = JS_TRUE;
            }
            break;
	    }
    }

	return result;
}

/***
 * <method name="setSize">
 *	<function>
 *   <arg name="X" type=WXJS_TYPE_NUMBER>
 *	  X position in pixels, or -1 to indicate that the existing value should be used.
 *   </arg>
 *   <arg name="Y" type=WXJS_TYPE_NUMBER>
 *	  Y position in pixels, or -1 to indicate that the existing value should be used.
 *   </arg>
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *	  Width in pixels, or -1 to indicate that the existing value should be used.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *	  Height in pixels, or -1 to indicate that the existing value should be used.
 *   </arg>
 *   <arg name="Flag" type=WXJS_TYPE_NUMBER>
 *	  Indicates the interpretation of the parameters.
 *   </arg>
 *  </function>
 *  <function>
 *   <arg name="Width" type=WXJS_TYPE_NUMBER>
 *	  Width in pixels, or -1 to indicate that the existing value should be used.
 *   </arg>
 *   <arg name="Height" type=WXJS_TYPE_NUMBER>
 *	  Height in pixels, or -1 to indicate that the existing value should be used.
 *   </arg>
 *  </function>
 *	<desc>
 *   Sets a new window size.
 *	 See @wxWindow#size property, @wxWindow#sizeFlags
 *  </desc>
 * </method>
 */
JSBool Window::setSize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

    JSBool result = JS_FALSE;

	int x;
	int y;
	int width;
	int height;
	int flag = wxSIZE_AUTO;

	if ( argc == 2 )
	{
		if (    FromJS(cx, argv[0], width)
			 && FromJS(cx, argv[1], height) )
		{
			p->SetSize(width, height);
			result = JS_TRUE;
		}
	}
	else if ( argc > 3 )
	{
		if (    FromJS(cx, argv[0], x)
			 && FromJS(cx, argv[1], y)
			 && FromJS(cx, argv[2], width)
			 && FromJS(cx, argv[3], height) )
		{
			if (    argc > 4 
				 && ! FromJS(cx, argv[4], flag) )
			{
				return JS_FALSE;
			}
			p->SetSize(x, y, width, height, flag);
			result = JS_TRUE;
		}
	}

    return result;
}

/***
 * <method name="raise">
 *	<function />
 *	<desc>
 *   Raises the window to the top of the window hierarchy if it is a managed window (dialog or frame).
 *  </desc>
 * </method>
 */
JSBool Window::raise(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->Raise();

	return JS_TRUE;
}

/***
 * <method name="lower">
 *	<function />
 *	<desc>
 *   Lowers the window to the bottom of the window hierarchy if it is a managed window (dialog or frame).
 *  </desc>
 * </method>
 */
JSBool Window::lower(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->Lower();

	return JS_TRUE;
}

/***
 * <method name="centerOnParent">
 *	<function>
 *	 <arg name="Direction" type=WXJS_TYPE_NUMBER default="wxOrientation.BOTH" />
 *	</function>
 *  <desc>
 *   Centres the window based on the parent. centreOnParent is an alias for this method.
 *  </desc>
 * </method>
 */
JSBool Window::centreOnParent(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	if ( argc == 0 )
	{
		p->CentreOnParent();
	}
	else
	{
		int direction;
		if ( FromJS(cx, argv[0], direction) )
		{
			p->CentreOnParent(direction);
		}
		else
		{
			return JS_FALSE;
		}
	}
	return JS_TRUE;
}

/***
 * <method name="fit">
 *	<function />
 *	<desc>
 *	 Set window size to wrap around its children
 *  </desc>
 * </method>
 */
JSBool Window::fit(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->Fit();

	return JS_TRUE;
}

/***
 * <method name="setSizeHints">
 *	<function>
 *   <arg name="MinWidth" type=WXJS_TYPE_NUMBER default="-1">
 *	  The minimum width of the window.
 *   </arg>
 *   <arg name="MinHeight" type=WXJS_TYPE_NUMBER default="-1">
 *    The minimum height of the window.
 *   </arg>
 *   <arg name="MaxWidth" type=WXJS_TYPE_NUMBER default="-1">
 *	  The maximum width of the window.
 *   </arg>
 *   <arg name="MaxHeight" type=WXJS_TYPE_NUMBER default="-1">
 *	  The maximum height of the window.
 *   </arg>
 *   <arg name="IncWidth" type=WXJS_TYPE_NUMBER default="-1">
 *	  The increment for resizing the width (Motif/Xt only).
 *   </arg>
 *   <arg name="IncHeight" type=WXJS_TYPE_NUMBER default="-1">
 *	  The increment for resizing the height (Motif/Xt only).
 *   </arg>
 *  </function>
 *  <desc>
 * 	 Allows specification of minimum and maximum window sizes, and window size increments.
 * 	 If a pair of values is not set (or set to -1), the default values will be used.
 *	 If this function is called, the user will not be able to size the window 
 *	 outside the given bounds.
 *   <br /><br />
 *	 The resizing increments are only significant under Motif or Xt.
 *  </desc>
 * </method>
 */
JSBool Window::setSizeHints(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	int minWidth = -1;
	int minHeight = -1;
	int maxWidth = -1;
	int maxHeight = -1;
	int incWidth = -1;
	int incHeight = -1;

	if ( JS_ConvertArguments(cx, argc, vp, "/iiiiii", 
							 &minWidth, &minHeight, &maxWidth,
							 &maxHeight, &incWidth, &incHeight) == JS_TRUE )
	{
		p->SetSizeHints(minWidth, minHeight, maxWidth, maxHeight, incWidth, incHeight);
	}
	else
		return JS_FALSE;

	return JS_TRUE;
}

/***
 * <method name="show">
 *	<function>
 *	 <arg name="Visible" type="Boolean" default="true" />
 *	</function>
 *  <desc>
 *	 Shows (true) or hides (false) the window.
 *   See @wxWindow#visible property, @wxWindow#shown property
 *	</desc>
 * </method>
 */
JSBool Window::show(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	if ( argc == 0 )
		p->Show();
	else
	{
		bool visible;
		if ( FromJS(cx, argv[0], visible) )
			p->Show(visible);
		else
			return JS_FALSE;
	}

	return JS_TRUE;
}

/***
 * <method name="refresh">
 *	<function>
 *   <arg name="EraseBackGround" type="Boolean" default="true">
 *	  When true the background is erased.
 *   </arg>
 *   <arg name="Rect" type="@wxRect" default="null">
 *	  When set, the given rectangle will be treated as damaged.
 *   </arg>
 *  </function>
 *  <desc>
 *	 Generates an event for repainting the window
 *  </desc>
 * </method>
 */
JSBool Window::refresh(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

    bool erase = true;
    zzzJsPtr<wxRect> apRect;
	wxRect *pRect = NULL;

    if ( argc > 2 )
        argc = 2;

    switch(argc)
    {
    case 2:
//        if ( FromJS(cx, argv[1], rect) == false )
		if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[1])) == true )
            break;
		pRect = apRect.get();
        // Fall Through
    case 1:
        if ( ! FromJS(cx, argv[0], erase) )
            break;
        // Fall Through
    default:
        p->Refresh(erase, pRect);
        return JS_TRUE;
    }

    return JS_FALSE;
}

/***
 * <method name="setFocus">
 *  <function />
 *  <desc>
 * 	 This sets the window to receive keyboard input.
 *  </desc>
 * </method>
 */
JSBool Window::setFocus(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->SetFocus();

	return JS_TRUE;
}

/***
 * <method name="findWindow">
 *	<function returns="@wxWindow">
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>The id of a window</arg>
 *  </function>
 *  <function returns="@wxWindow">
 *   <arg name="Name" type=WXJS_TYPE_STRING>The name of a window</arg>
 *  </function>
 *  <desc>
 *	 Find a child of this window, by identifier or by name
 *  </desc>
 * </method>
 */
JSBool Window::findWindow(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	wxWindow *win;
	int id;
	if ( FromJS(cx, argv[0], id) )
	{
		win = p->FindWindow(id);
	}
	else
	{
		wxString name;
		FromJS(cx, argv[0], name);
		win = p->FindWindow(name);
	}
	if ( win == (wxWindow*) NULL )
    {
		*vp = JSVAL_VOID;
    }
	else
	{
		JavaScriptClientData *data 
          = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
        if ( data == NULL )
        {
          *vp = JSVAL_VOID;
        }
        else
        {
		  *vp = OBJECT_TO_JSVAL(data->GetObject()); 
        }
	}

	return JS_TRUE;

}

/***
 * <method name="initDialog">
 *	<function />
 *  <desc>
 *	 Sends an onInitDialog event, which in turn transfers data to the dialog via validators
 *  </desc>
 * </method>
 */
JSBool Window::initDialog(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->InitDialog();

	return JS_TRUE;
}

/***
 * <method name="transferDataToWindow">
 *  <function returns="Boolean" />
 *  <desc>
 *	 Transfers values to child controls from data areas specified by their validators
 *	 Returns FALSE if a transfer failed.
 *  </desc>
 * </method>
 */
JSBool Window::transferDataToWindow(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	*vp = ToJS(cx, p->TransferDataToWindow());

	return JS_TRUE;
}

/***
 * <method name="transferDataFromWindow">
 *	<function returns="Boolean" />
 *	<desc>
 *   Transfers values from child controls to data areas specified by their validators.
 *	 Returns false if a transfer failed.
 *  </desc>
 * </method>
 */
JSBool Window::transferDataFromWindow(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	*vp = ToJS(cx, p->TransferDataToWindow());

	return JS_TRUE;
}

/***
 * <method name="validate">
 *	<function returns="Boolean" />
 *	<desc>
 *   Validates the current values of the child controls using their validators.
 *  </desc>
 * </method>
 */
JSBool Window::validate(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	*vp = ToJS(cx, p->Validate());

	return JS_TRUE;
}

/***
 * <method name="makeModal">
 *	<function>
 *	 <arg name="Flag" type="Boolean" default="true" />
 *  </function>
 *  <desc>
 *	 Make modal or not.
 *   When flag is true, all other windows are disabled.
 *	</desc>
 * </method>
 */
JSBool Window::makeModal(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	if ( argc == 1 )
	{
		bool flag;
		if ( FromJS(cx, argv[0], flag) )
		{
			//p->MakeModal(flag);
			p->Enable( flag );
		}
		else
		{
			return JS_FALSE;
		}
	}
	else
		//p->MakeModal();
		p->Enable();

	return JS_TRUE;
}

/***
 * <method name="update">
 *	<function />
 *	<desc>
 *	 Repaint all invalid areas of the window immediately
 *	</desc>
 * </method>
 */
JSBool Window::update(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->Update();

	return JS_TRUE;
}

/***
 * <method name="freeze">
 *	<function />
 *	<desc>
 *   Freeze the window: don't redraw it until it is thawed
 *	 See @wxWindow#thaw
 *	</desc>
 * </method>
 */
JSBool Window::freeze(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->Freeze();

	return JS_TRUE;
}

/***
 * <method name="thaw">
 *	<function />
 *  <desc>
 *	 Thaw the window: redraw it after it had been frozen.
 *	 See @wxWindow#freeze
 *	</desc>
 * </method>
 */
JSBool Window::thaw(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	p->Thaw();

	return JS_TRUE;
}

/***
 * <method name="prepareDC">
 *	<function />
 *  <desc>
 *	 Thaw the window: redraw it after it had been frozen.
 *	 See @wxWindow#freeze
 *	</desc>
 * </method>
 */
JSBool Window::prepareDC(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;

	wxDC *pDC =  zzzJs::gui::gdi::DC::GetPrivate(cx, argv[0], false);
	if( pDC == NULL ) {
		return JS_FALSE;
	}


	p->PrepareDC( *pDC );


	return JS_TRUE;
}



/***
 * <method name="setAutoLayout">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setAutoLayout(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}

	bool autoLayout;
	if ( FromJS(cx, argv[0], autoLayout) )
		p->SetAutoLayout(autoLayout);

	return JS_TRUE;
}


/***
 * <method name="setClientHeight">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setClientHeight(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}

	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	if( ZZZJS_PROP_GET_AP(apSize, Size, argv[0]) == false )
	{
		p->SetClientSize(*(apSize.get()));
	}
	else
	{
		// Try wxRect
		zzzJsPtr<wxRect> apRect;
//		if ( FromJS(cx, argv[0], rect) )
		if( (ZZZJS_PROP_GET_AP(apRect, Rect, argv[0])) == true )
			p->SetClientSize( *(apRect.get()) );
	}

	return JS_TRUE;
}


/***
 * <method name="setClientWidth">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setClientWidth(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	int size;
	if ( FromJS(cx, argv[0], size) )
		p->SetClientSize(size, -1);

	return JS_TRUE;
}


/***
 * <method name="setEnable">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setEnable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	

	bool enable;
	if ( FromJS(cx, argv[0], enable) )
		p->Enable(enable);

	return JS_TRUE;
}


/***
 * <method name="setHeight">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setHeight(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}

	int height;
	if ( FromJS(cx, argv[0], height) )
		p->SetSize(-1, height);

	return JS_TRUE;
}


/***
 * <method name="setVisible">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setVisible(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	bool visible;
	if ( FromJS(cx, argv[0], visible) )
		p->Show(visible);

	return JS_TRUE;
}


/***
 * <method name="setWidth">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setWidth(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	int size;
	if ( FromJS(cx, argv[0], size) )
		p->SetSize(size, -1);

	return JS_TRUE;
}




/***
 * <method name="setSizer">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setSizer(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
      wxSizer *sizer = Sizer::GetPrivate(cx, argv[0]);
      if ( sizer != NULL )
      {
        p->SetSizer(sizer);
        JavaScriptClientData *data
          = dynamic_cast<JavaScriptClientData*>(sizer->GetClientObject());
        if ( data != NULL )
        {
          data->Protect(true);
          data->SetOwner(false);
        }
	  }

	return JS_TRUE;
}


/***
 * <method name="setClientSize">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setClientSize(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	int size;
	if ( FromJS(cx, argv[0], size) )
		p->SetClientSize(-1, size);

	return JS_TRUE;
}


/***
 * <method name="setPosition">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setPosition(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	int argIndex = 0;
	
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	if ( ZZZJS_PROP_GET_AP(apPoint, zzzJs::ext::Point, argv[argIndex]) == true )
	{
		p->Move(*(apPoint.get()));
	}

	return JS_TRUE;
}


/***
 * <method name="setWindowStyle">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setWindowStyle(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	int style;
	if ( FromJS(cx, argv[0], style) )
		p->SetWindowStyle(style);

	return JS_TRUE;
}


/***
 * <method name="setExtraStyle">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setExtraStyle(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	int style;
	if ( FromJS(cx, argv[0], style) )
		p->SetExtraStyle(style);

	return JS_TRUE;
}


/***
 * <method name="setParent">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setParent(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
    wxWindow *win = Window::GetPrivate(cx, argv[0]);
	if ( win != NULL )
    {
		p->Reparent(win);
	}

	return JS_TRUE;
}


/***
 * <method name="setValidator">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setValidator(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	wxValidator *val = Validator::GetPrivate(cx, argv[0]);
	if ( val != NULL )
	{
        val->SetClientObject(new JavaScriptClientData(cx, JSVAL_TO_OBJECT(argv[0]), true, true));
		p->SetValidator(*val);
		val->SetWindow(p); // We do this, because otherwise we loose the knowledge
							// of WindowObject
	}

	return JS_TRUE;
}


/***
 * <method name="setAcceleratorTable">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setAcceleratorTable(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	wxAcceleratorTable *table = AcceleratorTable::GetPrivate(cx, argv[0]);
	if ( table != NULL )
		p->SetAcceleratorTable(*table);

	return JS_TRUE;
}


/***
 * <method name="setHasCapture">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setHasCapture(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	bool capture;
	if ( FromJS(cx, argv[0], capture) )
		capture ? p->CaptureMouse() : p->ReleaseMouse();

	return JS_TRUE;
}


/***
 * <method name="setHasCapture">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setBackgroundColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	wxColour *colour = Colour::GetPrivate(cx, argv[0]);
	if ( colour != NULL )
		p->SetBackgroundColour(*colour);

	return JS_TRUE;
}


/***
 * <method name="setHasCapture">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setForegroundColour(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	wxColour *colour = Colour::GetPrivate(cx, argv[0]);
	if ( colour != NULL )
		p->SetForegroundColour(*colour);

	return JS_TRUE;
}



/***
 * <method name="setHasCapture">
 *	<function />
 *  <desc>
 *	 
 *	</desc>
 * </method>
 */
JSBool Window::setFont(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxWindow *p = GetPrivate(cx, obj);
    if ( p == NULL )
		return JS_FALSE;
	if ( argc == 0 ) {
		return JS_FALSE;
	}
	
	int argIndex = 0;
	zzzJsPtr<wxFont> apFont;


	ZZZJS_ARG_AP_CHK_AND_ERROR(apFont, Font);

	p->SetFont(*(apFont.get()));

	return JS_TRUE;
}




WXJS_BEGIN_STATIC_METHOD_MAP(Window)
  WXJS_METHOD("findFocus", findFocus, 0)
  WXJS_METHOD("findWindowById", findWindowById, 1)
  WXJS_METHOD("findWindowByLabel", findWindowByLabel, 1)
WXJS_END_METHOD_MAP()

/***
 * <class_method name="findFocus">
 *	<function returns="@wxWindow" />
 *  <desc>
 *	 Finds the window or control which currently has the keyboard focus
 *	</desc>
 * </class_method>
 */
JSBool Window::findFocus(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxWindow *win = wxWindow::FindFocus();
	if ( win == NULL )
    {
      *vp = JSVAL_VOID;
    }
    else
    {
      JavaScriptClientData *data
        = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
      if ( data == NULL )
      {
        *vp = JSVAL_VOID;
      }
      else
      {
        *vp = OBJECT_TO_JSVAL(data->GetObject());
      }
    }
	return JS_TRUE;
}

/***
 * <class_method name="findWindowById">
 *	<function returns="@wxWindow">
 *	 <arg name="Id" type=WXJS_TYPE_NUMBER>The id of a window</arg>
 *  </function>
 *  <desc>
 *	 Find a window by identifier
 *  </desc>
 * </class_method>
 */
JSBool Window::findWindowById(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  int id;
  if ( FromJS(cx, argv[0], id) )
  {
    wxWindow *win = wxWindow::FindWindowById(id);
    if ( win == (wxWindow*) NULL )
    {
    *vp = JSVAL_VOID;
    }
    else
    {
      JavaScriptClientData *data 
        = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
      if ( data == NULL )
      {
        *vp = JSVAL_VOID;
      }
      else
      {
        *vp = OBJECT_TO_JSVAL(data->GetObject()); 
      }
    }
  }
  return JS_TRUE;
}

/***
 * <class_method name="findWindowByLabel">
 *	<function returns="@wxWindow">
 *	 <arg name="Label" type=WXJS_TYPE_STRING>The label of a window</arg>
 *  </function>
 *  <desc>
 *	 Find a window by label
 *  </desc>
 * </class_method>
 */
JSBool Window::findWindowByLabel(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

  wxString label;
  if ( FromJS(cx, argv[0], label) )
  {
    wxWindow *win = wxWindow::FindWindowByLabel(label);
    if ( win == (wxWindow*) NULL )
    {
      *vp = JSVAL_VOID;
    }
    else
    {
      JavaScriptClientData *data 
        = dynamic_cast<JavaScriptClientData*>(win->GetClientObject());
      if ( data == NULL )
      {
        *vp = JSVAL_VOID;
      }
      else
      {
        *vp = OBJECT_TO_JSVAL(data->GetObject()); 
      }
    }
  }
  
  return JS_TRUE;
}

/***
 * <events>
 *  <event name="onActivate">
 *   Called when the window is activated/disactivated. The function
 *   gets a @wxActivateEvent as argument.
 *  </event>
 *  <event name="onChar">
 *   Called when the user enters a character. The function
 *   gets a @wxKeyEvent object as argument.
 *  </event>
 *  <event name="onCharHook">
 *   This event is triggered to allow the window to intercept keyboard events before they are
 *   processed by child windows. The function gets a @wxKeyEvent as argument.
 *  </event>
 *  <event name="onKeyDown">
 *   Called when the user has pressed a key, before it is translated into an 
 *   ASCII value using other modifier keys that might be pressed at the same time. 
 *   The function gets a @wxKeyEvent object as argument.
 *  </event>
 *  <event name="onKeyUp">
 *   Called when the user has released the key.
 *   The function gets a @wxKeyEvent object as argument.
 *  </event>
 *  <event name="onSetFocus">
 *   Called when the window gets the focus.
 *   The function gets a @wxFocusEvent object as argument.
 *  </event>
 *  <event name="onKillFocus">
 *   Called when the window looses the focus.
 *   The function gets a @wxFocusEvent object as argument.
 *  </event>
 *  <event name="onMouseEvents">
 *   Used for handling all the mouse events. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onEnterWindow">
 *   Event triggered when the mouse enters the window. The function
 *   gets a @wxMouseEvent as argument.
 *   Under Windows mouse enter and leave events are not natively supported by the
 *   system but are generated by wxWindows itself. This has several drawbacks: 
 *   the @wxWindow#onLeaveWindow event might be received some time after the mouse left
 *   the window and the state variables for it may have changed during this time.
 *   See @wxWindow#onLeaveWindow
 *  </event>
 *  <event name="onLeaveWindow">
 *   Event triggered when the mouse leaves the window. The function
 *   gets a @wxMouseEvent as argument.
 *   Under Windows mouse enter and leave events are not natively supported by the
 *   system but are generated by wxWindows itself. This has several drawbacks: 
 *   the onLeaveWindow event might be received some time after the mouse left
 *   the window and the state variables for it may have changed during this time.
 *   See @wxWindow#onEnterWindow
 *  </event>
 *  <event name="onLeftDown">
 *   Event triggered when the left button is pressed. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onLeftUp">
 *   Event triggered when the left button is released. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onLeftDClick">
 *   Event triggered when the left button is double clicked. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onMiddleDown">
 *   Event triggered when the middle button is pressed. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onMiddleUp">
 *   Event triggered when the middle button is released. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onMiddleDClick">
 *   Event triggered when the middle button is double clicked. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onRightDown">
 *   Event triggered when the right button is pressed. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onRightUp">
 *   Event triggered when the right button is released. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onRightDClick">
 *   Event triggered when the right button is double clicked. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onMotion">
 *   Event triggered when the mouse is moved. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onMouseWheel">
 *   Event triggered when the mousewheel is used. The function
 *   gets a @wxMouseEvent as argument.
 *  </event>
 *  <event name="onMove">
 *   Called when the window is moved. The function gets a @wxMoveEvent as argument.
 *  </event>
 *  <event name="onSize">
 *   Called when the window is resized. The function gets a @wxSizeEvent as argument.
 *  </event>
 *  <event name="onScroll">
 *  Catch all scroll commands. The argument of the function is a @wxScrollWinEvent.
 *  </event>
 *  <event name="onScrollTop">
 *   Catch a command to put the scroll thumb at the maximum position. 
 *   The argument of the function is a @wxScrollWinEvent.
 *  </event>
 *  <event name="onScrollBottom">
 *   Catch a command to put the scroll thumb at the maximum position.
 *   The argument of the function is a @wxScrollWinEvent.
 *  </event>
 *  <event name="onScrollLineUp">
 *   Catch a line up command.
 *   The argument of the function is a @wxScrollWinEvent.
 *  </event>
 *  <event name="onScrollLineDown">
 *   Catch a line down command.
 *   The argument of the function is a @wxScrollWinEvent.
 *  </event>
 *  <event name="onScrollPageUp">
 *   Catch a page up command.
 *   The argument of the function is a @wxScrollWinEvent.
 *  </event>
 *  <event name="onScrollPageDown">
 *   Catch a page down command. 
 *   The argument of the function is a @wxScrollWinEvent.
 *  </event>
 *  <event name="onScrollThumbTrack">
 *   Catch a thumbtrack command (continuous movement of the scroll thumb). 
 *   The argument of the function is a @wxScrollWinEvent.
 *  </event>
 *  <event name="onScrollThumbRelease">
 *   Catch a thumbtrack release command.
 *   The argument of the function is a @wxScrollWinEvent.
 *  </event>
 *  <event name="onHelp">
 *   Triggered when the user pressed F1 (on Windows) or 
 *   when the user requested context-sensitive help.
 *   The argument of the function is a @wxHelpEvent.
 *   See @wxContextHelp, @wxHelpEvent and @wxContextHelpButton
 *  </event>
 * </events>
*/

#include "js/gui/event/jsevent.h"
#include "js/gui/event/key.h"
#include "js/gui/event/activate.h"
#include "js/gui/event/mouse.h"
#include "js/gui/event/move.h"
#include "js/gui/event/sizeevt.h"
#include "js/gui/event/help.h"
#include "js/gui/event/scrollwin.h"
#include "js/gui/event/evt_paint.h"

WXJS_INIT_EVENT_MAP(wxWindow)
const wxString WXJS_SETFOCUS_EVENT(wxT("onSetFocus"));
const wxString WXJS_CHAR_EVENT(wxT("onChar"));
const wxString WXJS_CHAR_HOOK_EVENT(wxT("onCharHook"));
const wxString WXJS_KEY_DOWN_EVENT(wxT("onKeyDown"));
const wxString WXJS_KEY_UP_EVENT(wxT("onKeyUp"));
const wxString WXJS_ACTIVATE_EVENT(wxT("onActivate"));
const wxString WXJS_SET_FOCUS_EVENT(wxT("onSetFocus"));
const wxString WXJS_KILL_FOCUS_EVENT(wxT("onKillFocus"));
const wxString WXJS_LEFT_DOWN_EVENT(wxT("onLeftDown"));
const wxString WXJS_LEFT_UP_EVENT(wxT("onLeftUp"));
const wxString WXJS_LEFT_DCLICK_EVENT(wxT("onLeftDClick"));
const wxString WXJS_MIDDLE_DOWN_EVENT(wxT("onMiddleDown"));
const wxString WXJS_MIDDLE_UP_EVENT(wxT("onMiddleUp"));
const wxString WXJS_MIDDLE_DCLICK_EVENT(wxT("onMiddleDClick"));
const wxString WXJS_RIGHT_DOWN_EVENT(wxT("onRightDown"));
const wxString WXJS_RIGHT_UP_EVENT(wxT("onRightUp"));
const wxString WXJS_RIGHT_DCLICK_EVENT(wxT("onRightDClick"));
const wxString WXJS_MOTION_EVENT(wxT("onMotion"));
const wxString WXJS_ENTER_WINDOW_EVENT(wxT("onEnterWindow"));
const wxString WXJS_LEAVE_WINDOW_EVENT(wxT("onLeaveWindow"));
const wxString WXJS_MOUSE_WHEEL_EVENT(wxT("onMouseWheel"));
const wxString WXJS_MOVE_EVENT(wxT("onMove"));
const wxString WXJS_SIZE_EVENT(wxT("onSize"));
const wxString WXJS_SCROLL_EVENT(wxT("onScroll"));
const wxString WXJS_SCROLL_TOP_EVENT(wxT("onScrollTop"));
const wxString WXJS_SCROLL_BOTTOM_EVENT(wxT("onScrollBottom"));
const wxString WXJS_SCROLL_LINEUP_EVENT(wxT("onScrollLineUp"));
const wxString WXJS_SCROLL_LINEDOWN_EVENT(wxT("onScrollLineDown"));
const wxString WXJS_SCROLL_PAGEUP_EVENT(wxT("onScrollPageUp"));
const wxString WXJS_SCROLL_PAGEDOWN_EVENT(wxT("onScrollPageDown"));
const wxString WXJS_SCROLL_THUMBTRACK_EVENT(wxT("onScrollThumbtrack"));
const wxString WXJS_SCROLL_THUMBRELEASE(wxT("onScrollThumbRelease"));
const wxString WXJS_HELP_EVENT(wxT("onHelp"));
const wxString WNDEVT_ON_PAINT(wxT("onPaint"));

void WindowEventHandler::OnChar(wxKeyEvent &event)
{
    PrivKeyEvent::Fire<KeyEvent>(event, WXJS_CHAR_EVENT);
}
void WindowEventHandler::OnCharHook(wxKeyEvent &event)
{
    PrivKeyEvent::Fire<KeyEvent>(event, WXJS_CHAR_HOOK_EVENT);
}
void WindowEventHandler::OnKeyDown(wxKeyEvent &event)
{
    PrivKeyEvent::Fire<KeyEvent>(event, WXJS_KEY_DOWN_EVENT);
}
void WindowEventHandler::OnKeyUp(wxKeyEvent &event)
{
    PrivKeyEvent::Fire<KeyEvent>(event, WXJS_KEY_UP_EVENT);
}
void WindowEventHandler::OnActivate(wxActivateEvent &event)
{
    PrivActivateEvent::Fire<ActivateEvent>(event, WXJS_ACTIVATE_EVENT);
}

void WindowEventHandler::OnSetFocus(wxFocusEvent &event)
{
    PrivFocusEvent::Fire<FocusEvent>(event, WXJS_SET_FOCUS_EVENT);
}

void WindowEventHandler::OnKillFocus(wxFocusEvent &event)
{
    PrivFocusEvent::Fire<FocusEvent>(event, WXJS_KILL_FOCUS_EVENT);
}

void WindowEventHandler::OnLeftDown(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_LEFT_DOWN_EVENT);
}

void WindowEventHandler::OnLeftUp(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_LEFT_UP_EVENT);
}

void WindowEventHandler::OnLeftDClick(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_LEFT_DCLICK_EVENT);
}

void WindowEventHandler::OnMiddleDown(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_MIDDLE_DOWN_EVENT);
}

void WindowEventHandler::OnMiddleUp(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_MIDDLE_UP_EVENT);
}

void WindowEventHandler::OnMiddleDClick(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_MIDDLE_DCLICK_EVENT);
}

void WindowEventHandler::OnRightDown(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_RIGHT_DOWN_EVENT);
}

void WindowEventHandler::OnRightUp(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_RIGHT_UP_EVENT);
}

void WindowEventHandler::OnRightDClick(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_RIGHT_DCLICK_EVENT);
}

void WindowEventHandler::OnMotion(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_MOTION_EVENT);
}

void WindowEventHandler::OnEnterWindow(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_ENTER_WINDOW_EVENT);
}

void WindowEventHandler::OnLeaveWindow(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_LEAVE_WINDOW_EVENT);
}

void WindowEventHandler::OnMouseWheel(wxMouseEvent &event)
{
    PrivMouseEvent::Fire<MouseEvent>(event, WXJS_MOUSE_WHEEL_EVENT);
}

void WindowEventHandler::OnMove(wxMoveEvent &event)
{
    PrivMoveEvent::Fire<MoveEvent>(event, WXJS_MOVE_EVENT);
}
void WindowEventHandler::OnSize(wxSizeEvent &event)
{
    PrivSizeEvent::Fire<SizeEvent>(event, WXJS_SIZE_EVENT);
}
void WindowEventHandler::OnScrollTop(wxScrollWinEvent& event)
{
    PrivScrollWinEvent::Fire<ScrollWinEvent>(event, WXJS_SCROLL_TOP_EVENT);
}
void WindowEventHandler::OnScrollBottom(wxScrollWinEvent& event)
{
    PrivScrollWinEvent::Fire<ScrollWinEvent>(event, WXJS_SCROLL_BOTTOM_EVENT);
}
void WindowEventHandler::OnScrollLineUp(wxScrollWinEvent& event)
{
    PrivScrollWinEvent::Fire<ScrollWinEvent>(event, WXJS_SCROLL_LINEUP_EVENT);
}
void WindowEventHandler::OnScrollLineDown(wxScrollWinEvent& event)
{
    PrivScrollWinEvent::Fire<ScrollWinEvent>(event, WXJS_SCROLL_LINEDOWN_EVENT);
}
void WindowEventHandler::OnScrollPageUp(wxScrollWinEvent& event)
{
    PrivScrollWinEvent::Fire<ScrollWinEvent>(event, WXJS_SCROLL_PAGEUP_EVENT);
}
void WindowEventHandler::OnScrollPageDown(wxScrollWinEvent& event)
{
    PrivScrollWinEvent::Fire<ScrollWinEvent>(event, WXJS_SCROLL_PAGEDOWN_EVENT);
}
void WindowEventHandler::OnScrollThumbTrack(wxScrollWinEvent& event)
{
    PrivScrollWinEvent::Fire<ScrollWinEvent>(event, WXJS_SCROLL_THUMBTRACK_EVENT);
}
void WindowEventHandler::OnScrollThumbRelease(wxScrollWinEvent& event)
{
    PrivScrollWinEvent::Fire<ScrollWinEvent>(event, WXJS_SCROLL_THUMBRELEASE);
}
void WindowEventHandler::OnHelp(wxHelpEvent &event)
{
    PrivHelpEvent::Fire<HelpEvent>(event, WXJS_HELP_EVENT);
}
void WindowEventHandler::OnPaint(wxPaintEvent &event)
{
    PrivPaintEvent::Fire<PaintEvent>(event, WNDEVT_ON_PAINT);
}
void WindowEventHandler::InitConnectEventMap(void)
{
    AddConnector(WXJS_CHAR_EVENT, ConnectChar);
    AddConnector(WXJS_KEY_DOWN_EVENT, ConnectKeyDown);
    AddConnector(WXJS_KEY_UP_EVENT, ConnectKeyUp);
    AddConnector(WXJS_CHAR_HOOK_EVENT, ConnectCharHook);
    AddConnector(WXJS_ACTIVATE_EVENT, ConnectActivate);
    AddConnector(WXJS_SET_FOCUS_EVENT, ConnectSetFocus);
    AddConnector(WXJS_KILL_FOCUS_EVENT, ConnectKillFocus);
    AddConnector(WXJS_MOVE_EVENT, ConnectMove);
    AddConnector(WXJS_SIZE_EVENT, ConnectSize);
    AddConnector(WXJS_SCROLL_TOP_EVENT, ConnectScrollTop);
    AddConnector(WXJS_SCROLL_BOTTOM_EVENT, ConnectScrollBottom);
    AddConnector(WXJS_SCROLL_LINEUP_EVENT, ConnectScrollLineUp);
    AddConnector(WXJS_SCROLL_LINEDOWN_EVENT, ConnectScrollLineDown);
    AddConnector(WXJS_SCROLL_PAGEUP_EVENT, ConnectScrollPageUp);
    AddConnector(WXJS_SCROLL_PAGEDOWN_EVENT, ConnectScrollPageDown);
    AddConnector(WXJS_SCROLL_THUMBTRACK_EVENT, ConnectScrollThumbTrack);
    AddConnector(WXJS_SCROLL_THUMBRELEASE, ConnectScrollThumbRelease);
    AddConnector(WXJS_HELP_EVENT, ConnectHelp);
    AddConnector(WXJS_LEFT_DOWN_EVENT, ConnectLeftDown);
    AddConnector(WXJS_LEFT_UP_EVENT, ConnectLeftUp);
    AddConnector(WXJS_LEFT_DCLICK_EVENT, ConnectLeftDClick);
    AddConnector(WXJS_MIDDLE_DOWN_EVENT, ConnectMiddleDown);
    AddConnector(WXJS_MIDDLE_UP_EVENT, ConnectMiddleUp);
    AddConnector(WXJS_MIDDLE_DCLICK_EVENT, ConnectMiddleDClick);
    AddConnector(WXJS_RIGHT_DOWN_EVENT, ConnectRightDown);
    AddConnector(WXJS_RIGHT_UP_EVENT, ConnectRightUp);
    AddConnector(WXJS_RIGHT_DCLICK_EVENT, ConnectRightDClick);
    AddConnector(WXJS_MOTION_EVENT, ConnectMotion);
    AddConnector(WXJS_ENTER_WINDOW_EVENT, ConnectEnterWindow);
    AddConnector(WXJS_LEAVE_WINDOW_EVENT, ConnectLeaveWindow);
    AddConnector(WXJS_MOUSE_WHEEL_EVENT, ConnectMouseWheel);
	AddConnector(WNDEVT_ON_PAINT, ConnectPaint);
}

void WindowEventHandler::ConnectChar(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_CHAR, wxCharEventHandler(WindowEventHandler::OnChar));
  }
  else
  {
    p->Disconnect(wxEVT_CHAR, wxCharEventHandler(WindowEventHandler::OnChar));
  }
}
void WindowEventHandler::ConnectKeyDown(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(WindowEventHandler::OnKeyDown));
  }
  else
  {
    p->Disconnect(wxEVT_KEY_DOWN, wxKeyEventHandler(WindowEventHandler::OnKeyDown));
  }
}
void WindowEventHandler::ConnectKeyUp(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_KEY_UP, wxKeyEventHandler(WindowEventHandler::OnKeyUp));
  }
  else
  {
    p->Disconnect(wxEVT_KEY_UP, wxKeyEventHandler(WindowEventHandler::OnKeyUp));
  }
}
void WindowEventHandler::ConnectCharHook(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_CHAR_HOOK, wxCharEventHandler(WindowEventHandler::OnCharHook));
  }
  else
  {
    p->Disconnect(wxEVT_CHAR_HOOK, wxCharEventHandler(WindowEventHandler::OnCharHook));
  }
}
void WindowEventHandler::ConnectActivate(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_ACTIVATE, wxActivateEventHandler(WindowEventHandler::OnActivate));
  }
  else
  {
    p->Disconnect(wxEVT_ACTIVATE, wxActivateEventHandler(WindowEventHandler::OnActivate));
  }
}

void WindowEventHandler::ConnectSetFocus(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SET_FOCUS, wxFocusEventHandler(WindowEventHandler::OnSetFocus));
  }
  else
  {
    p->Disconnect(wxEVT_SET_FOCUS, wxFocusEventHandler(WindowEventHandler::OnSetFocus));
  }
}

void WindowEventHandler::ConnectKillFocus(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_KILL_FOCUS, wxFocusEventHandler(WindowEventHandler::OnKillFocus));
  }
  else
  {
    p->Disconnect(wxEVT_KILL_FOCUS, wxFocusEventHandler(WindowEventHandler::OnKillFocus));
  }
}
void WindowEventHandler::ConnectMove(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_MOVE, wxMoveEventHandler(WindowEventHandler::OnMove));
  }
  else
  {
    p->Disconnect(wxEVT_MOVE, wxMoveEventHandler(WindowEventHandler::OnMove));
  }
}
void WindowEventHandler::ConnectSize(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SIZE, wxSizeEventHandler(WindowEventHandler::OnSize));
  }
  else
  {
    p->Disconnect(wxEVT_SIZE, wxSizeEventHandler(WindowEventHandler::OnSize));
  }
}
void WindowEventHandler::ConnectScrollTop(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_TOP, wxScrollWinEventHandler(WindowEventHandler::OnScrollTop));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_TOP, wxScrollWinEventHandler(WindowEventHandler::OnScrollTop));
  }
}
void WindowEventHandler::ConnectScrollBottom(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_BOTTOM, wxScrollWinEventHandler(WindowEventHandler::OnScrollBottom));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_BOTTOM, wxScrollWinEventHandler(WindowEventHandler::OnScrollBottom));
  }
}
void WindowEventHandler::ConnectScrollLineUp(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_LINEUP, wxScrollWinEventHandler(WindowEventHandler::OnScrollLineUp));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_LINEUP, wxScrollWinEventHandler(WindowEventHandler::OnScrollLineUp));
  }
}
void WindowEventHandler::ConnectScrollLineDown(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_LINEDOWN, wxScrollWinEventHandler(WindowEventHandler::OnScrollLineDown));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_LINEDOWN, wxScrollWinEventHandler(WindowEventHandler::OnScrollLineDown));
  }
}
void WindowEventHandler::ConnectScrollPageUp(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_PAGEUP, wxScrollWinEventHandler(WindowEventHandler::OnScrollPageUp));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_PAGEUP, wxScrollWinEventHandler(WindowEventHandler::OnScrollPageUp));
  }
}
void WindowEventHandler::ConnectScrollPageDown(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_PAGEDOWN, wxScrollWinEventHandler(WindowEventHandler::OnScrollPageDown));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_PAGEDOWN, wxScrollWinEventHandler(WindowEventHandler::OnScrollPageDown));
  }
}
void WindowEventHandler::ConnectScrollThumbTrack(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_THUMBTRACK, wxScrollWinEventHandler(WindowEventHandler::OnScrollThumbTrack));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_THUMBTRACK, wxScrollWinEventHandler(WindowEventHandler::OnScrollThumbTrack));
  }
}
void WindowEventHandler::ConnectScrollThumbRelease(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_THUMBRELEASE, wxScrollWinEventHandler(WindowEventHandler::OnScrollThumbRelease));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_THUMBRELEASE, wxScrollWinEventHandler(WindowEventHandler::OnScrollThumbRelease));
  }
}
void WindowEventHandler::ConnectHelp(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_HELP, wxHelpEventHandler(WindowEventHandler::OnHelp));
  }
  else
  {
    p->Disconnect(wxEVT_HELP, wxHelpEventHandler(WindowEventHandler::OnHelp));
  }
}

void WindowEventHandler::ConnectLeftDown(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(WindowEventHandler::OnLeftDown));
  }
  else
  {
    p->Disconnect(wxEVT_LEFT_DOWN, wxMouseEventHandler(WindowEventHandler::OnLeftDown));
  }
}
void WindowEventHandler::ConnectLeftUp(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_LEFT_UP, wxMouseEventHandler(WindowEventHandler::OnLeftUp));
  }
  else
  {
    p->Disconnect(wxEVT_LEFT_UP, wxMouseEventHandler(WindowEventHandler::OnLeftUp));
  }
}
void WindowEventHandler::ConnectLeftDClick(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(WindowEventHandler::OnLeftDClick));
  }
  else
  {
    p->Disconnect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(WindowEventHandler::OnLeftDClick));
  }
}

void WindowEventHandler::ConnectMiddleDown(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_MIDDLE_DOWN, wxMouseEventHandler(WindowEventHandler::OnMiddleDown));
  }
  else
  {
    p->Disconnect(wxEVT_MIDDLE_DOWN, wxMouseEventHandler(WindowEventHandler::OnMiddleDown));
  }
}

void WindowEventHandler::ConnectMiddleUp(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_MIDDLE_UP, wxMouseEventHandler(WindowEventHandler::OnMiddleUp));
  }
  else
  {
    p->Disconnect(wxEVT_MIDDLE_UP, wxMouseEventHandler(WindowEventHandler::OnMiddleUp));
  }
}

void WindowEventHandler::ConnectMiddleDClick(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_MIDDLE_DCLICK, wxMouseEventHandler(WindowEventHandler::OnMiddleDClick));
  }
  else
  {
    p->Disconnect(wxEVT_MIDDLE_DCLICK, wxMouseEventHandler(WindowEventHandler::OnMiddleDClick));
  }
}

void WindowEventHandler::ConnectRightDown(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(WindowEventHandler::OnRightDown));
  }
  else
  {
    p->Disconnect(wxEVT_RIGHT_DOWN, wxMouseEventHandler(WindowEventHandler::OnRightDown));
  }
}

void WindowEventHandler::ConnectRightUp(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_RIGHT_UP, wxMouseEventHandler(WindowEventHandler::OnRightUp));
  }
  else
  {
    p->Disconnect(wxEVT_RIGHT_UP, wxMouseEventHandler(WindowEventHandler::OnRightUp));
  }
}

void WindowEventHandler::ConnectRightDClick(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_RIGHT_DCLICK, wxMouseEventHandler(WindowEventHandler::OnRightDClick));
  }
  else
  {
    p->Disconnect(wxEVT_RIGHT_DCLICK, wxMouseEventHandler(WindowEventHandler::OnRightDClick));
  }
}

void WindowEventHandler::ConnectMotion(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_MOTION, wxMouseEventHandler(WindowEventHandler::OnMotion));
  }
  else
  {
    p->Disconnect(wxEVT_MOTION, wxMouseEventHandler(WindowEventHandler::OnMotion));
  }
}

void WindowEventHandler::ConnectEnterWindow(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(WindowEventHandler::OnEnterWindow));
  }
  else
  {
    p->Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler(WindowEventHandler::OnEnterWindow));
  }
}

void WindowEventHandler::ConnectLeaveWindow(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(WindowEventHandler::OnLeaveWindow));
  }
  else
  {
    p->Disconnect(wxEVT_LEAVE_WINDOW, wxMouseEventHandler(WindowEventHandler::OnLeaveWindow));
  }
}

void WindowEventHandler::ConnectMouseWheel(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(WindowEventHandler::OnMouseWheel));
  }
  else
  {
    p->Disconnect(wxEVT_MOUSEWHEEL, wxMouseEventHandler(WindowEventHandler::OnMouseWheel));
  }
}

void WindowEventHandler::ConnectPaint(wxWindow *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_PAINT, wxPaintEventHandler(WindowEventHandler::OnPaint));
  }
  else
  {
    p->Disconnect(wxEVT_PAINT, wxPaintEventHandler(WindowEventHandler::OnPaint));
  }
}

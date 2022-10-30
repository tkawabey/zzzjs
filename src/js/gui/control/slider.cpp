/*
 * wxJavaScript - slider.cpp
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
 * $Id: slider.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// slider.cpp
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
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/point.h"


#include "js/gui/event/jsevent.h"
#include "js/gui/event/command.h"
#include "js/gui/event/scroll.h"

#include "js/gui/misc/size.h"
#include "js/gui/misc/validate.h"

#include "js/gui/control/slider.h"
#include "js/gui/control/window.h"
#include "js/gui/control/control.h"
#include "js/gui/errors.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>control/slider</file>
 * <module>gui</module>
 * <class name="wxSlider" prototype="@wxControl">
 *  A slider is a control with a handle which can be pulled back and forth
 *  to change the value.
 *  In Windows versions below Windows 95, a scrollbar is used to simulate the
 *  slider. In Windows 95, the track bar control is used.
 *  See also @wxScrollEvent.
 * </class>
 */
WXJS_INIT_CLASS(Slider, "Slider", 5)

void Slider::InitClass(JSContext* WXUNUSED(cx),
                       JSObject* WXUNUSED(obj), 
                       JSObject* WXUNUSED(proto))
{
  SliderEventHandler::InitConnectEventMap();
}

/***
 * <properties>
 *  <property name="lineSize" type=WXJS_TYPE_NUMBER>
 *   Get/Set the line size
 *  </property>
 *  <property name="max" type=WXJS_TYPE_NUMBER>
 *   Get/Set the maximum value
 *  </property>
 *  <property name="min" type=WXJS_TYPE_NUMBER>
 *   Get/Set the minimum value
 *  </property>
 *  <property name="pageSize" type=WXJS_TYPE_NUMBER>
 *   Get/Set the pagesize
 *  </property>
 *  <property name="selEnd" type=WXJS_TYPE_NUMBER>
 *   Get/Set the end selection point
 *  </property>
 *  <property name="selStart" type=WXJS_TYPE_NUMBER>
 *   Get/Set the start selection point
 *  </property>
 *  <property name="value" type=WXJS_TYPE_NUMBER>
 *   Get/Set the current value
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(Slider)
	WXJS_PROPERTY(P_LINESIZE, "lineSize")
	WXJS_PROPERTY(P_MAX, "max")
	WXJS_PROPERTY(P_MIN, "min")
	WXJS_PROPERTY(P_PAGESIZE, "pageSize")
	WXJS_PROPERTY(P_SEL_END, "selEnd")
	WXJS_PROPERTY(P_SEL_START, "selStart")
	WXJS_PROPERTY(P_THUMB_LENGTH, "thumbLength")
	WXJS_PROPERTY(P_VALUE, "value")
WXJS_END_PROPERTY_MAP()

/***
 * <constants>
 *  <type name="Styles">
 *   <constant name="HORIZONTAL">
 *    Displays the slider horizontally.  
 *   </constant>
 *   <constant name="VERTICAL">
 *    Displays the slider vertically.  
 *   </constant>
 *   <constant name="AUTOTICKS">
 *    Displays tick marks.  
 *   </constant>
 *   <constant name="LABELS">
 *    Displays minimum, maximum and value labels. 
 *    (NB: only displays the current value label under wxGTK)  
 *   </constant>
 *   <constant name="LEFT">
 *    Displays ticks on the left, if a vertical slider.  
 *   </constant>
 *   <constant name="RIGHT">
 *    Displays ticks on the right, if a vertical slider.  
 *   </constant>
 *   <constant name="TOP">
 *    Displays ticks on the top, if a horizontal slider.  
 *   </constant>
 *   <constant name="SELRANGE">
 *    Allows the user to select a range on the slider. Windows 95 only.  
 *   </constant>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(Slider)
	WXJS_CONSTANT(wxSL_, HORIZONTAL)
	WXJS_CONSTANT(wxSL_, VERTICAL)
	WXJS_CONSTANT(wxSL_, TICKS)
	WXJS_CONSTANT(wxSL_, AUTOTICKS)
	WXJS_CONSTANT(wxSL_, LABELS)
	WXJS_CONSTANT(wxSL_, LEFT)
	WXJS_CONSTANT(wxSL_, TOP)
	WXJS_CONSTANT(wxSL_, RIGHT)
	WXJS_CONSTANT(wxSL_, BOTTOM)
	WXJS_CONSTANT(wxSL_, BOTH)
	WXJS_CONSTANT(wxSL_, SELRANGE)
WXJS_END_CONSTANT_MAP()


WXJS_BEGIN_GET_PROP(wxSlider, Slider)
    switch (id) 
	{
	case P_LINESIZE:
		ToJSVal(cx, vp, p->GetLineSize());
		break;
	case P_MAX:
		ToJSVal(cx, vp, p->GetMax());
		break;
	case P_MIN:
		ToJSVal(cx, vp, p->GetMin());
		break;
	case P_PAGESIZE:
		ToJSVal(cx, vp, p->GetPageSize());
		break;
	case P_SEL_END:
		ToJSVal(cx, vp, p->GetSelEnd());
		break;
	case P_SEL_START:
		ToJSVal(cx, vp, p->GetSelStart());
		break;
	case P_THUMB_LENGTH:
		vp.set( ToJS(cx ,p->GetThumbLength()) );
		break;
	case P_VALUE:
		ToJSVal(cx, vp, p->GetValue());
		break;
    }
    return true;

WXJS_END_GET_PROP


WXJS_BEGIN_SET_PROP(wxSlider, Slider)
    switch (id) 
	{
	case P_LINESIZE:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetLineSize(value);
			break;
		}
	case P_MAX:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetRange(p->GetMin(), value);
			break;
		}
	case P_MIN:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetRange(value, p->GetMax());
			break;
		}
	case P_PAGESIZE:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetPageSize(value);
			break;
		}
	case P_SEL_END:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetSelection(p->GetSelStart(), value);
			break;
		}
	case P_SEL_START:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetSelection(value, p->GetSelEnd());
			break;
		}
	case P_THUMB_LENGTH:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetThumbLength(value);
			break;
		}
	case P_TICK:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetTick(value);
			break;
		}
	case P_VALUE:
		{
			int value;
			if ( FromJS(cx, vp, value) )
				p->SetValue(value);
			break;
		}
    }
    return true;
WXJS_END_SET_PROP
	
	
WXJS_BEGIN_GET_SET_STR_PROP(wxSlider, Slider)
	Control::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_ADD_PROP(wxSlider, Slider)
    if ( WindowEventHandler::ConnectEvent(p, prop, true) )
        return true;
    
    SliderEventHandler::ConnectEvent(p, prop, true);

    return true;
WXJS_END_ADD_PROP



WXJS_BEGIN_DEL_PROP(wxSlider, Slider)
  if ( WindowEventHandler::ConnectEvent(p, prop, false) )
    return true;
  
  SliderEventHandler::ConnectEvent(p, prop, false);
  return true;
WXJS_END_DEL_PROP

/***
 * <ctor>
 *  <function />
 *  <function>
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of wxSlider.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    An window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Value" type=WXJS_TYPE_NUMBER>
 *    Initial position of the slider
 *   </arg>
 *   <arg name="Min" type=WXJS_TYPE_NUMBER>
 *    Minimum slider position.
 *   </arg>
 *   <arg name="Max" type=WXJS_TYPE_NUMBER>
 *    Maximum slider position.
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the Slider control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the Slider control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxSlider.HORIZONTAL">
 *    The wxSlider style.
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null" />
 *  </function>
 *  <desc>
 *   Constructs a new wxSlider object.
 *  </desc>
 * </ctor>
 */

WXJS_BEGIN_CONSTRUCTOR(wxSlider, Slider)

	wxSlider *p = new wxSlider();



    SetPrivate(cx, obj, p);

    if ( argc > 0 )
    {
        jsval rval;
        if ( ! _innerCreate(cx, obj, argc, vp, &rval) )
        {
          return NULL;
        }
    }

	return p;
WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_DESTRUCTOR(wxSlider, Slider)
WXJS_END_DESTRUCTOR


WXJS_BEGIN_METHOD_MAP(Slider)
  WXJS_METHOD("create", create, 5)
  WXJS_METHOD("clearSel", clearSel, 0)
  WXJS_METHOD("setRange", setRange, 2)
  WXJS_METHOD("setSelection", setSelection, 2)
  WXJS_METHOD("setTickFreq", setTickFreq, 2)
WXJS_END_METHOD_MAP()

/***
 * <method name="create">
 *  <function>
 *   <arg name="Parent" type="@wxWindow">
 *    The parent of wxSlider.
 *   </arg>
 *   <arg name="Id" type=WXJS_TYPE_NUMBER>
 *    An window identifier. Use -1 when you don't need it.
 *   </arg>
 *   <arg name="Value" type=WXJS_TYPE_NUMBER>
 *    Initial position of the slider
 *   </arg>
 *   <arg name="Min" type=WXJS_TYPE_NUMBER>
 *    Minimum slider position.
 *   </arg>
 *   <arg name="Max" type=WXJS_TYPE_NUMBER>
 *    Maximum slider position.
 *   </arg>
 *   <arg name="Position" type="@wxPoint" default="wxDefaultPosition">
 *    The position of the Slider control on the given parent.
 *   </arg>
 *   <arg name="Size" type="@wxSize" default="wxDefaultSize">
 *    The size of the Slider control.
 *   </arg>
 *   <arg name="Style" type=WXJS_TYPE_NUMBER default="wxSlider.HORIZONTAL">
 *    The wxSlider style.
 *   </arg>
 *   <arg name="Validator" type="@wxValidator" default="null" />
 *  </function>
 *  <desc>
 *   Constructs a new wxSlider object.
 *  </desc>
 * </method>
 */
JSBool Slider::create(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);

	jsval rval;
	if( _innerCreate(cx, obj, argc, vp, &rval) == JS_FALSE ) {
		return JS_FALSE;
	}
	JS_SET_RVAL(cx, vp, rval);

	return JS_TRUE;
}
JSBool Slider::_innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxSlider* p = GetPrivate(cx, obj);
	*rval = JSVAL_FALSE;

	
	int argIndex = 0;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);
	int style = 0;
	const wxValidator *val = &wxDefaultValidator;
	
	ZZZJS_CHECK_ARG_COUNT(4, 9);
	argIndex = argc -1;
	switch(argc)
	{
	case 9:
		val = Validator::GetPrivate(cx, argv[8]);
		if ( val == NULL )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 9, "Validator");
			return JS_FALSE;
		}
		argIndex--;
	case 8:
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(style, WXJS_TYPE_NUMBER);
		argIndex--;
	case 7:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
		argIndex--;
	case 6:
		ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
		argIndex--;
	default:
		wxWindow *parent = NULL;
		int id;
		int value;
		int min;
		int max;

		
		argIndex = 0;
		ZZZJS_ARG_GET_PRIVATE(parent, Window);
		if ( parent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(id, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(value, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(min, WXJS_TYPE_NUMBER);
		argIndex++;
		ZZZJS_ARG_FROMJS_CHK_AND_ERROR(max, WXJS_TYPE_NUMBER);
		argIndex++;



		JavaScriptClientData *clntParent =
				dynamic_cast<JavaScriptClientData *>(parent->GetClientObject());
		if ( clntParent == NULL )
		{
			JS_ReportError(cx, WXJS_NO_PARENT_ERROR, GetClass()->name);
			return JS_FALSE;
		}
		JS_SetParent(cx, obj, clntParent->GetObject());

		if ( p->Create(parent, id, value, min, max, *(apPoint.get()), *(apSize.get()), style, *val) )
		{
			*rval = JSVAL_TRUE;
			p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));
		}
	}
	return JS_TRUE;
}

/***
 * <method name="clearSel">
 *  <function />
 *  <desc>
 *   Clears the selection, for a slider with the SELRANGE style.
 *  </desc>
 * </method>
 */
JSBool Slider::clearSel(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSlider *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	p->ClearSel();

	return JS_TRUE;
}

/***
 * <method name="clearTicks">
 *  <function />
 *  <desc>
 *   Clears the ticks.
 *  </desc>
 * </method>
 */
JSBool Slider::clearTicks(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSlider *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	p->ClearTicks();

	return JS_TRUE;
}

/***
 * <method name="setRange">
 *  <function>
 *   <arg name="Min" type=WXJS_TYPE_NUMBER>
 *    The minimum value
 *   </arg>
 *   <arg name="Max" type=WXJS_TYPE_NUMBER>
 *    The maximum value
 *   </arg>
 *  </function>
 *  <desc>
 *   Sets the minimum and maximum slider values.
 *  </desc>
 * </method>
 */
JSBool Slider::setRange(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSlider *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int mini;
	int maxi;
	
	if (    FromJS(cx, argv[0], mini) 
		 && FromJS(cx, argv[1], maxi) )
	{
		p->SetRange(mini, maxi);
	}
	else
	{
		return JS_FALSE;
	}

	return JS_TRUE;
}

/***
 * <method name="setSelection">
 *  <function>
 *   <arg name="Start" type=WXJS_TYPE_NUMBER>
 *    The selection start position
 *   </arg>
 *   <arg name="End" type=WXJS_TYPE_NUMBER>
 *    The selection end position
 *   </arg>
 *  </function>
 *  <desc>
 *   Sets the selection
 *  </desc>
 * </method>
 */
JSBool Slider::setSelection(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSlider *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int start;
	int end;
		
	if (    FromJS(cx, argv[0], start)
		 && FromJS(cx, argv[1], end)   )
	{
		p->SetSelection(start, end);
	}
	else
	{
		return JS_FALSE;
	}

	return JS_TRUE;
}

/***
 * <method name="setTickFreq">
 *  <function>
 *   <arg name="Freq" type=WXJS_TYPE_NUMBER>
 *    Frequency
 *   </arg>
 *   <arg name="Pos" type=WXJS_TYPE_NUMBER>
 *    Position
 *   </arg>
 *  </function>
 *  <desc>
 *   Sets the tick mark frequency and position.
 *  </desc>
 * </method>
 */
JSBool Slider::setTickFreq(JSContext *cx, unsigned argc, JS::Value *vp)
{
  	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxSlider *p = GetPrivate(cx, obj);
	if ( p == NULL )
		return JS_FALSE;

	int n;
	int pos;

	if (    FromJS(cx, argv[0], n)
		 && FromJS(cx, argv[1], pos) )
	{
		p->SetTickFreq(n/*, pos*/);
	}
	else
	{
		return JS_FALSE;
	}

	return JS_TRUE;
}

/***
 * <events>
 *  <event name="onScrollChanged">
 *   Event is triggered when scrolling/ moving has finished independently of the
 *   way it had started. The argument of the function is a @wxScrollEvent.
 *  </event>
 *  <event name="onScrollTop">
 *   Catch a command to put the scroll thumb at the maximum position. 
 *   The argument of the function is a @wxScrollEvent.
 *  </event>
 *  <event name="onScrollBottom">
 *   Catch a command to put the scroll thumb at the maximum position.
 *   The argument of the function is a @wxScrollEvent.
 *  </event>
 *  <event name="onScrollLineUp">
 *   Catch a line up command.
 *   The argument of the function is a @wxScrollEvent.
 *  </event>
 *  <event name="onScrollLineDown">
 *   Catch a line down command.
 *   The argument of the function is a @wxScrollEvent.
 *  </event>
 *  <event name="onScrollPageUp">
 *   Catch a page up command.
 *   The argument of the function is a @wxScrollEvent.
 *  </event>
 *  <event name="onScrollPageDown">
 *   Catch a page down command. 
 *   The argument of the function is a @wxScrollEvent.
 *  </event>
 *  <event name="onScrollThumbTrack">
 *   Catch a thumbtrack command (continuous movement of the scroll thumb). 
 *   The argument of the function is a @wxScrollEvent.
 *  </event>
 *  <event name="onScrollThumbRelease">
 *   Catch a thumbtrack release command.
 *   The argument of the function is a @wxScrollEvent.
 *  </event>
 * </events>
 */
WXJS_INIT_EVENT_MAP(wxSlider)
const wxString WXJS_SCROLL_CHANGED_EVENT = wxT("onScrollChanged");
const wxString WXJS_SCROLL_TOP_EVENT = wxT("onScrollTop");
const wxString WXJS_SCROLL_BOTTOM_EVENT = wxT("onScrollBottom");
const wxString WXJS_SCROLL_LINEUP_EVENT = wxT("onScrollLineUp");
const wxString WXJS_SCROLL_LINEDOWN_EVENT = wxT("onScrollLineDown");
const wxString WXJS_SCROLL_PAGEUP_EVENT = wxT("onScrollPageUp");
const wxString WXJS_SCROLL_PAGEDOWN_EVENT = wxT("onScrollPageDown");
const wxString WXJS_SCROLL_THUMBTRACK_EVENT = wxT("onScrollThumbTrack");
const wxString WXJS_SCROLL_THUMBRELEASE_EVENT = wxT("onScrollThumbRelease");

void SliderEventHandler::OnScrollChanged(wxScrollEvent& event)
{
  PrivScrollEvent::Fire<ScrollEvent>(event, WXJS_SCROLL_CHANGED_EVENT);
}

void SliderEventHandler::OnScrollTop(wxScrollEvent& event)
{
  PrivScrollEvent::Fire<ScrollEvent>(event, WXJS_SCROLL_TOP_EVENT);
}

void SliderEventHandler::OnScrollBottom(wxScrollEvent& event)
{
  PrivScrollEvent::Fire<ScrollEvent>(event, WXJS_SCROLL_BOTTOM_EVENT);
}

void SliderEventHandler::OnScrollLineUp(wxScrollEvent& event)
{
  PrivScrollEvent::Fire<ScrollEvent>(event, WXJS_SCROLL_LINEUP_EVENT);
}

void SliderEventHandler::OnScrollLineDown(wxScrollEvent& event)
{
  PrivScrollEvent::Fire<ScrollEvent>(event, WXJS_SCROLL_LINEDOWN_EVENT);
}

void SliderEventHandler::OnScrollPageUp(wxScrollEvent& event)
{
  PrivScrollEvent::Fire<ScrollEvent>(event, WXJS_SCROLL_PAGEUP_EVENT);
}

void SliderEventHandler::OnScrollPageDown(wxScrollEvent& event)
{
  PrivScrollEvent::Fire<ScrollEvent>(event, WXJS_SCROLL_PAGEDOWN_EVENT);
}

void SliderEventHandler::OnScrollThumbTrack(wxScrollEvent& event)
{
  PrivScrollEvent::Fire<ScrollEvent>(event, WXJS_SCROLL_THUMBTRACK_EVENT);
}

void SliderEventHandler::OnScrollThumbRelease(wxScrollEvent& event)
{
  PrivScrollEvent::Fire<ScrollEvent>(event, WXJS_SCROLL_THUMBRELEASE_EVENT);
}

void SliderEventHandler::ConnectScrollChanged(wxSlider *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_CHANGED, 
               wxScrollEventHandler(SliderEventHandler::OnScrollChanged));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_CHANGED, 
                  wxScrollEventHandler(SliderEventHandler::OnScrollChanged));
  }
}

void SliderEventHandler::ConnectScrollTop(wxSlider *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_TOP, 
               wxScrollEventHandler(SliderEventHandler::OnScrollTop));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_TOP, 
                  wxScrollEventHandler(SliderEventHandler::OnScrollTop));
  }
}

void SliderEventHandler::ConnectScrollBottom(wxSlider *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_BOTTOM, 
               wxScrollEventHandler(SliderEventHandler::OnScrollBottom));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_BOTTOM, 
                  wxScrollEventHandler(SliderEventHandler::OnScrollBottom));
  }
}

void SliderEventHandler::ConnectScrollLineUp(wxSlider *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_LINEUP, 
               wxScrollEventHandler(SliderEventHandler::OnScrollTop));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_LINEUP, 
                  wxScrollEventHandler(SliderEventHandler::OnScrollTop));
  }
}

void SliderEventHandler::ConnectScrollLineDown(wxSlider *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_LINEDOWN, 
               wxScrollEventHandler(SliderEventHandler::OnScrollLineDown));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_LINEDOWN, 
                  wxScrollEventHandler(SliderEventHandler::OnScrollLineDown));
  }
}

void SliderEventHandler::ConnectScrollPageUp(wxSlider *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_PAGEUP, 
               wxScrollEventHandler(SliderEventHandler::OnScrollPageUp));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_PAGEUP, 
               wxScrollEventHandler(SliderEventHandler::OnScrollPageUp));
  }
}

void SliderEventHandler::ConnectScrollPageDown(wxSlider *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_PAGEDOWN, 
               wxScrollEventHandler(SliderEventHandler::OnScrollPageDown));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_PAGEDOWN, 
               wxScrollEventHandler(SliderEventHandler::OnScrollPageDown));
  }
}

void SliderEventHandler::ConnectScrollThumbTrack(wxSlider *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_THUMBTRACK, 
               wxScrollEventHandler(SliderEventHandler::OnScrollThumbTrack));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_THUMBTRACK, 
                  wxScrollEventHandler(SliderEventHandler::OnScrollThumbTrack));
  }
}

void SliderEventHandler::ConnectScrollThumbRelease(wxSlider *p, bool connect)
{
  if ( connect )
  {
    p->Connect(wxEVT_SCROLL_THUMBRELEASE, 
               wxScrollEventHandler(SliderEventHandler::OnScrollThumbRelease));
  }
  else
  {
    p->Disconnect(wxEVT_SCROLL_THUMBRELEASE, 
                  wxScrollEventHandler(SliderEventHandler::OnScrollThumbRelease));
  }
}

void SliderEventHandler::InitConnectEventMap()
{
  AddConnector(WXJS_SCROLL_CHANGED_EVENT, ConnectScrollChanged);
  AddConnector(WXJS_SCROLL_TOP_EVENT, ConnectScrollTop);
  AddConnector(WXJS_SCROLL_BOTTOM_EVENT, ConnectScrollBottom);
  AddConnector(WXJS_SCROLL_LINEUP_EVENT, ConnectScrollLineUp);
  AddConnector(WXJS_SCROLL_LINEDOWN_EVENT, ConnectScrollLineDown);
  AddConnector(WXJS_SCROLL_PAGEUP_EVENT, ConnectScrollPageUp);
  AddConnector(WXJS_SCROLL_PAGEDOWN_EVENT, ConnectScrollPageDown);
  AddConnector(WXJS_SCROLL_THUMBTRACK_EVENT, ConnectScrollThumbTrack);
  AddConnector(WXJS_SCROLL_THUMBRELEASE_EVENT, ConnectScrollThumbRelease);
}

/*
 * wxJavaScript - mouse.cpp
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
 * $Id: mouse.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// mouse.cpp
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
#include "js/gui/event/jsevent.h"
#include "js/gui/event/mouse.h"
#include "js/gui/event/event.h"

#include "js/ext/zzzjs_ext_init.h"


using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>event/mouse</file>
 * <module>gui</module>
 * <class name="wxMouseEvent" prototype="@wxEvent">
 *	This event class contains information about mouse events.
 *  <br /><br />
 *  Note the difference between methods like @wxMouseEvent#leftDown
 *  and @wxMouseEvent#leftIsDown: the formet returns true when the event corresponds
 *  to the left mouse button click while the latter returns true if the left mouse button
 *  is currently being pressed. For example, when the user is dragging the mouse you can use 
 *  @wxMouseEvent#leftIsDown to test whether the left mouse button is (still) depressed.
 *  Also, by convention, if @wxMouseEvent#leftDown returns true, @wxMouseEvent#leftIsDown 
 *  will also return true in wxWindows whatever the underlying GUI 
 *  behaviour is (which is platform-dependent).
 *  The same applies, of course, to other mouse buttons as well.
 *  <br /><br />
 *  See @wxWindow#onMouseEvents, @wxWindow#onEnterWindow, @wxWindow#onLeaveWindow,
 *  @wxWindow#onLeftUp, @wxWindow#onLeftDown, @wxWindow#onLeftDClick,
 *  @wxWindow#onMiddleUp, @wxWindow#onMiddleDown, @wxWindow#onMiddleDClick,
 *  @wxWindow#onRightUp, @wxWindow#onRightDown, @wxWindow#onRightDClick.
 * </class>
 */
WXJS_INIT_CLASS(MouseEvent, "MouseEvent", 0)

/***
 * <properties>
 *	<property name="altDown" type="Boolean" readonly="Y">
 *	 Returns true when the alt key is down at the time of the key event.
 *  </property>
 *	<property name="button" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Get the button which is changing state
 *  </property>
 *	<property name="controlDown" type="Boolean" readonly="Y">
 *	 Returns true when the control key is down at the time of the event.
 *  </property>
 *	<property name="dragging" type="Boolean" readonly="Y">
 *	 Returns true when this is a dragging event.
 *  </property>
 *	<property name="entering" type="Boolean" readonly="Y">
 *	 Returns true when the mouse was entering the window.
 *	 See @wxMouseEvent#leaving
 *  </property>
 *	<property name="leaving" type="Boolean" readonly="Y">
 *	 Returns true when the mouse was leaving the window.
 *	 See @wxMouseEvent#entering.
 *  </property>
 *	<property name="leftDClick" type="Boolean" readonly="Y">
 *	 Returns true when the event is a left double click event (wxEVT_LEFT_DCLICK).
 *  </property>
 *	<property name="leftDown" type="Boolean" readonly="Y">
 *	 Returns true when the event is a left down event (wxEVT_LEFT_DOWN).
 *  </property>
 *	<property name="leftIsDown" type="Boolean" readonly="Y">
 *	 Returns true if the left mouse button is currently down, independent of the current event type.
 *	 Please notice that it is not the same as @wxMouseEvent#leftDown which returns true
 *	 if the left mouse button was just pressed. Rather, it describes the state of the mouse button 
 *	 before the event happened.
 *  </property>
 *	<property name="linesPerAction" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Returns the configured number of lines (or whatever)
 *	 to be scrolled per wheel action. Defaults to 1.
 *  </property>
 *	<property name="metaDown" type="Boolean" readonly="Y">
 *	 Returns true when the meta key was down at the time of the event.
 *  </property>
 *	<property name="middleDClick" type="Boolean" readonly="Y">
 *	 Returns true when the event is a middle double click event (wxEVT_MIDDLE_DCLICK).
 *  </property>
 *	<property name="middleDown" type="Boolean" readonly="Y">
 *	 Returns true when the event is a middle down event (wxEVT_MIDDLE_DOWN).
 *  </property>
 *	<property name="middleIsDown" type="Boolean" readonly="Y">
 *	 Returns true if the middle mouse button is currently down, independent of the current event type.
 *  </property>
 *	<property name="moving" type="Boolean" readonly="Y">
 *	 Returns true when this was a moving event (wxEVT_MOTION)
 *  </property>
 *	<property name="position" type="@wxPoint" readonly="Y">
 *	 Returns the physical mouse position in pixels.
 *  </property>
 *	<property name="rightDClick" type="Boolean" readonly="Y">
 *	 Returns true when the event is a right double click event (wxEVT_RIGHT_DCLICK).
 *  </property>
 *	<property name="rightDown" type="Boolean" readonly="Y">
 *	 Returns true when the event is a right down event (wxEVT_RIGHT_DOWN).
 *  </property>
 *	<property name="rightIsDown" type="Boolean" readonly="Y">
 *	 Returns true if the right mouse button is currently down, independent of the current event type.
 *  </property>
 *	<property name="shiftDown" type="Boolean" readonly="Y">
 *	 Returns true when the shift key was down at the time of the event.
 *  </property>
 *	<property name="wheelDelta" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Get wheel delta, normally 120.  This is the threshold for action to be
 *	 taken, and one such action (for example, scrolling one increment)
 *	 should occur for each delta.
 *  </property>
 *	<property name="wheelRotation" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Get wheel rotation, positive or negative indicates direction of
 *	 rotation.	Current devices all send an event when rotation is equal to
 *	 +/-WheelDelta, but this allows for finer resolution devices to be
 *	 created in the future.  Because of this you shouldn't assume that one
 *	 event is equal to 1 line or whatever, but you should be able to either
 *	 do partial line scrolling or wait until +/-WheelDelta rotation values
 *	 have been accumulated before scrolling.
 *  </property>
 *	<property name="x" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Returns the x-coordinate of the physical mouse position.
 *	 See @wxMouseEvent#position and @wxMouseEvent#y
 *  </property>
 *	<property name="y" type=WXJS_TYPE_NUMBER readonly="Y">
 *	 Returns the y-coordinate of the physical mouse position.
 *	 See @wxMouseEvent#position and @wxMouseEvent#x
 *  </property>
 * </properties>
 */

WXJS_BEGIN_PROPERTY_MAP(MouseEvent)
  WXJS_READONLY_PROPERTY(P_ALTDOWN, "altDown")
  WXJS_READONLY_PROPERTY(P_CONTROLDOWN, "controlDown")
  WXJS_READONLY_PROPERTY(P_DRAGGING, "dragging")
  WXJS_READONLY_PROPERTY(P_ENTERING, "entering")
  WXJS_READONLY_PROPERTY(P_POSITION, "position")
  WXJS_READONLY_PROPERTY(P_LINES_PER_ACTION, "linesPerAction")
  WXJS_READONLY_PROPERTY(P_BUTTON, "button")
  WXJS_READONLY_PROPERTY(P_METADOWN, "metaDown")
  WXJS_READONLY_PROPERTY(P_SHIFTDOWN, "shiftDown")
  WXJS_READONLY_PROPERTY(P_LEFT_DOWN, "leftDown")
  WXJS_READONLY_PROPERTY(P_MIDDLE_DOWN, "middleDown")
  WXJS_READONLY_PROPERTY(P_RIGHT_DOWN, "rightDown")
  WXJS_READONLY_PROPERTY(P_LEFT_UP, "leftUp")
  WXJS_READONLY_PROPERTY(P_MIDDLE_UP, "middleUp")
  WXJS_READONLY_PROPERTY(P_RIGHT_UP, "rightUp")
  WXJS_READONLY_PROPERTY(P_LEFT_DCLICK, "leftDClick")
  WXJS_READONLY_PROPERTY(P_MIDDLE_DCLICK, "middleDClick")
  WXJS_READONLY_PROPERTY(P_RIGHT_DCLICK, "rightDClick")
  WXJS_READONLY_PROPERTY(P_LEFT_IS_DOWN, "leftIsDown")
  WXJS_READONLY_PROPERTY(P_MIDDLE_IS_DOWN, "middleIsDown")
  WXJS_READONLY_PROPERTY(P_RIGHT_IS_DOWN, "rightIsDown")
  WXJS_READONLY_PROPERTY(P_MOVING, "moving")
  WXJS_READONLY_PROPERTY(P_LEAVING, "leaving")
  WXJS_READONLY_PROPERTY(P_X, "x")
  WXJS_READONLY_PROPERTY(P_Y, "y")
  WXJS_READONLY_PROPERTY(P_WHEELROTATION, "wheelRotation")
  WXJS_READONLY_PROPERTY(P_WHEELDELTA, "wheelDelta")
WXJS_END_PROPERTY_MAP()

bool MouseEvent::GetProperty(PrivMouseEvent *p,  
									JSContext *cx, 
									JSObject *obj, 
									int id, 
									JS::MutableHandle<JS::Value>& vp)
{
    wxMouseEvent *event = (wxMouseEvent*) p->GetEvent();
    switch (id) 
	{
		case P_ALTDOWN:
			ToJSVal(cx, vp, event->AltDown());
			break;
		case P_CONTROLDOWN:
			ToJSVal(cx, vp, event->ControlDown());
			break;
		case P_DRAGGING:
			ToJSVal(cx, vp, event->Dragging());
			break;
		case P_ENTERING:
			ToJSVal(cx, vp, event->Entering());
			break;
		case P_POSITION:
            vp.set( zzzJs::ext::CreatePoint(cx, event->GetPosition()) );
			break;
		case P_LINES_PER_ACTION:
			ToJSVal(cx, vp, event->GetLinesPerAction());
			break;
		case P_BUTTON:
			ToJSVal(cx, vp, event->GetButton());
			break;
		case P_METADOWN:
			ToJSVal(cx, vp, event->MetaDown());
			break;
		case P_SHIFTDOWN:
			ToJSVal(cx, vp, event->ShiftDown());
			break;
		case P_LEFT_DOWN:
			ToJSVal(cx, vp, event->LeftDown());
			break;
		case P_MIDDLE_DOWN:
			ToJSVal(cx, vp, event->MiddleDown());
			break;
		case P_RIGHT_DOWN:
			ToJSVal(cx, vp, event->RightDown());
			break;
		case P_LEFT_UP:
			ToJSVal(cx, vp, event->LeftUp());
			break;
		case P_MIDDLE_UP:
			ToJSVal(cx, vp, event->MiddleUp());
			break;
		case P_RIGHT_UP:
			ToJSVal(cx, vp, event->RightUp());
			break;
		case P_LEFT_DCLICK:
			ToJSVal(cx, vp, event->LeftDClick());
			break;
		case P_MIDDLE_DCLICK:
			ToJSVal(cx, vp, event->MiddleDClick());
			break;
		case P_RIGHT_DCLICK:
			ToJSVal(cx, vp, event->RightDClick());
			break;
		case P_LEFT_IS_DOWN:
			ToJSVal(cx, vp, event->LeftIsDown());
			break;
		case P_MIDDLE_IS_DOWN:
			ToJSVal(cx, vp, event->MiddleIsDown());
			break;
		case P_RIGHT_IS_DOWN:
			ToJSVal(cx, vp, event->RightIsDown());
			break;
		case P_MOVING:
			ToJSVal(cx, vp, event->Moving());
			break;
		case P_LEAVING:
			ToJSVal(cx, vp, event->Leaving());
			break;
		case P_X:
			ToJSVal(cx, vp, event->GetX());
			break;
		case P_Y:
			ToJSVal(cx, vp, event->GetY());
			break;
		case P_WHEELROTATION:
			ToJSVal(cx, vp, event->GetWheelRotation());
			break;
		case P_WHEELDELTA:
			ToJSVal(cx, vp, event->GetWheelDelta());
			break;
	}
	return true;
}
	
WXJS_BEGIN_GET_SET_STR_PROP(PrivMouseEvent, MouseEvent)
	Event::SetStringProperty((PrivEvent*)p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

WXJS_BEGIN_METHOD_MAP(MouseEvent)
  WXJS_METHOD("button", button, 1)
  WXJS_METHOD("buttonDClick", buttonDClick, 1)
  WXJS_METHOD("buttonDown", buttonDown, 1)
  WXJS_METHOD("buttonUp", buttonUp, 1)
//	Waiting for wxDC
//	WXJS_METHOD("getLogicalPosition", getLogicalPosition, 1)
WXJS_END_METHOD_MAP()

/***
 * <method name="button">
 *	<function returns="Boolean">
 *	 <arg name=WXJS_TYPE_NUMBER type=WXJS_TYPE_NUMBER>
 *	  The mouse button.  
 *   </arg>
 *  </function>
 *  <desc>
 *	 Returns true if the identified mouse button is changing state.
 *	 Valid values of button are 1, 2 or 3 for left, middle and right buttons respectively.
 *  </desc>
 * </method>
 */ 
JSBool MouseEvent::button(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	PrivMouseEvent *p = (PrivMouseEvent*) JS_GetPrivate(obj);//JS_GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxMouseEvent"));

	int button;
	if ( FromJS(cx, argv[0], button) )
	{
		*vp = ToJS(cx, p->GetEvent()->Button(button));
		return JS_TRUE;
	}
	else
	{
		return JS_FALSE;
	}
}

/***
 * <method name="buttonDClick">
 *	<function returns="Boolean">
 *	 <arg name=WXJS_TYPE_NUMBER type=WXJS_TYPE_NUMBER>
 *	  The mouse button.  
 *   </arg>
 *  </function>
 *  <desc>
 *	 If the argument is omitted, this returns true if the event was a mouse double click event. 
 *	 Otherwise the argument specifies which double click event was generated (1, 2 or 3 for left, middle and right buttons respectively).
 *  </desc>
 * </method>
 */
JSBool MouseEvent::buttonDClick(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	PrivMouseEvent *p = (PrivMouseEvent*) JS_GetPrivate(obj);//JS_GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxMouseEvent"));

	int button = -1;
	FromJS(cx, argv[0], button);
	*vp = ToJS(cx, p->GetEvent()->ButtonDClick(button));

	return JS_TRUE;
}

/***
 * <method name="buttonDown">
 *	<function returns="Boolean">
 *	 <arg name=WXJS_TYPE_NUMBER type=WXJS_TYPE_NUMBER>
 *	  The mouse button.  
 *   </arg>
 *  </function>
 *  <desc>
 *	 If the argument is omitted, this returns true if the event was a mouse button down event. 
 *	 Otherwise the argument specifies which button-down event was generated (1, 2 or 3 for left, middle and right buttons respectively).
 *  </desc>
 * </method>
 */
JSBool MouseEvent::buttonDown(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	PrivMouseEvent *p = (PrivMouseEvent*) JS_GetPrivate(obj);//JS_GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxMouseEvent"));

	int button = -1;
	FromJS(cx, argv[0], button);
	*vp = ToJS(cx, p->GetEvent()->ButtonDown(button));

	return JS_TRUE;
}

/***
 * <method name="buttonUp">
 *	<function returns="Boolean">
 *	 <arg name=WXJS_TYPE_NUMBER type=WXJS_TYPE_NUMBER>
 *	  The mouse button.  
 *   </arg>
 *  </function>
 *  <desc>
 *	 If the argument is omitted, this returns true if the event was a mouse button up event.
 *	 Otherwise the argument specifies which button-up event was generated (1, 2 or 3 for left, middle and right buttons respectively).
 *  </desc>
 * </method>
 */
JSBool MouseEvent::buttonUp(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	PrivMouseEvent *p = (PrivMouseEvent*) JS_GetPrivate(obj);//JS_GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxMouseEvent"));

	int button = -1;
	FromJS(cx, argv[0], button);
	*vp = ToJS(cx, p->GetEvent()->ButtonUp(button));

	return JS_TRUE;
}

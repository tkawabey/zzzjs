/*
 * wxJavaScript - bmpbtn.cpp
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
 * $Id: bmpbtn.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
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
#include "js/common/jsutil.h"
#include "js/gui/misc/rect.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/gui/errors.h"
#include "js/ext/point.h"
#include "js/gui/misc/bitmap.h"
#include "js/gui/misc/colour.h"
#include "js/gui/misc/font.h"
#include "js/gui/misc/size.h"
#include "js/gui/control/window.h"
#include "js/gui/pg/pg_editor.h"
#include "js/gui/pg/pg_grid.h"
#include "js/gui/pg/pg_prop.h"
#include "js/gui/pg/pg_wndlist.h"
#include "js/gui/pg/pg_cell.h"
#include "js/gui/pg/pg_wndlist.h"
#include "js/gui/event/jsevent.h"
#include "js/gui/event/event.h"
#include "js/gui/gdi/dc.h"



#include <wx/propgrid/advprops.h>

using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;
using namespace zzzJs::gui::gdi;


wxString Editor::GetName() const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onGetName", &fval) == JS_FALSE ) 
	{
		return wxPGEditor::GetName();
	}
	
	jsval rval;
//	jsval argv[] = { ToJS(cx, (long)0)/*, ToJS(cx, column)*/ };

	if ( JS_CallFunctionValue(cx, obj, fval, 0, NULL, &rval) == JS_TRUE )
	{
		wxString text;
		FromJS(cx, rval, text);
		return text;
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return wxPGEditor::GetName();
}
wxPGWindowList Editor::CreateControls(wxPropertyGrid* propgrid,
                                          wxPGProperty* property,
                                          const wxPoint& pos,
                                          const wxSize& size) const 
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onCreateControls", &fval) == JS_FALSE ) 
	{
		return wxPGWindowList(NULL, NULL);
	}
	jsval rval;
	jsval argv[] = { Grid::CreateObject(cx, propgrid, NULL)
			,		Property::CreateObject(cx, property, NULL)
			,		zzzJs::ext::Point::CreateObject(cx, new wxPoint(pos), NULL)
			,		Size::CreateObject(cx, new wxSize(size), NULL)
	};
	if ( JS_CallFunctionValue(cx, obj, fval, 0, NULL, &rval) == JS_TRUE )
	{
		wxPGWindowList* pWndList = WindowList::GetPrivate(cx, rval, false);
		if( pWndList == NULL ) {
			return wxPGWindowList(NULL, NULL);
		}
		return wxPGWindowList(pWndList->m_primary, pWndList->m_secondary);
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return wxPGWindowList(NULL, NULL);
}
void Editor::UpdateControl( wxPGProperty* property, wxWindow* ctrl ) const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onUpdateControl", &fval) == JS_FALSE ) 
	{
		return ;
	}
	jsval rval;
	jsval argv[] = { Property::CreateObject(cx, property, NULL)
			,		Window::CreateObject(cx, ctrl, NULL)
	};
	if ( JS_CallFunctionValue(cx, obj, fval, 2, argv, &rval) == JS_TRUE )
	{

	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
}
void Editor::DrawValue( wxDC& dc,
						const wxRect& rect,
						wxPGProperty* property,
						const wxString& text ) const
{
	// TODO... 
	wxPGEditor::DrawValue(dc, rect, property, text);
}
bool Editor::OnEvent( wxPropertyGrid* propgrid, wxPGProperty* property,
					wxWindow* wnd_primary, wxEvent& event ) const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onOnEvent", &fval) == JS_FALSE ) 
	{
		return false;
	}
	jsval rval;
	PrivEvent	privEvent(event);
	jsval argv[] = { Grid::CreateObject(cx, propgrid, NULL)
			,		Property::CreateObject(cx, property, NULL)
			,		Window::CreateObject(cx, wnd_primary, NULL)
			,		Event::CreateObject(cx, &privEvent, NULL)
	};
	if ( JS_CallFunctionValue(cx, obj, fval, 2, argv, &rval) == JS_TRUE )
	{

		bool bVal = false;
		FromJS(cx, rval, bVal);
		return bVal;
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return false;
}
bool Editor::GetValueFromControl( wxVariant& variant,
												wxPGProperty* property,
												wxWindow* ctrl ) const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onGetValueFromControl", &fval) == JS_FALSE ) 
	{
		return wxPGEditor::GetValueFromControl(variant, property, ctrl);
	}
	jsval rval;
	jsval argv[] = { Property::CreateObject(cx, property, NULL)
			,		Window::CreateObject(cx, ctrl, NULL)
	};
	if ( JS_CallFunctionValue(cx, obj, fval, 2, argv, &rval) == JS_TRUE )
	{
		FromJS(cx, rval, variant);
		return true;
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return false;
}
void Editor::SetControlAppearance( wxPropertyGrid* pg,
													wxPGProperty* property,
													wxWindow* ctrl,
													const wxPGCell& appearance,
													const wxPGCell& oldAppearance,
													bool unspecified ) const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onSetControlAppearance", &fval) == JS_FALSE ) 
	{
		wxPGEditor::SetControlAppearance(pg, property, ctrl, appearance, oldAppearance, unspecified);
		return ;
	}
	jsval rval;
	jsval argv[] = { Grid::CreateObject(cx, pg, NULL)
			,		Property::CreateObject(cx, property, NULL)
			,		Window::CreateObject(cx, ctrl, NULL)
			,		Cell::CreateObject(cx, (wxPGCell*)&appearance, NULL)
			,		Cell::CreateObject(cx, (wxPGCell*)&oldAppearance, NULL)
			,		ToJS(cx, unspecified)
	};
	if ( JS_CallFunctionValue(cx, obj, fval, 6, argv, &rval) == JS_TRUE )
	{
		return ;
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	wxPGEditor::SetControlAppearance(pg, property, ctrl, appearance, oldAppearance, unspecified);
}
void Editor::SetValueToUnspecified( wxPGProperty* property,
													wxWindow* ctrl ) const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onSetValueToUnspecified", &fval) == JS_FALSE ) 
	{
		wxPGEditor::SetValueToUnspecified(property, ctrl);
		return ;
	}
	jsval rval;
	jsval argv[] = { Property::CreateObject(cx, property, NULL)
			,		Window::CreateObject(cx, ctrl, NULL)
	};
	if ( JS_CallFunctionValue(cx, obj, fval, 2, argv, &rval) == JS_TRUE )
	{
		return ;
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	wxPGEditor::SetValueToUnspecified(property, ctrl);
}
void Editor::SetControlStringValue( wxPGProperty* property,
													wxWindow* ctrl,
													const wxString& txt ) const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onSetControlStringValue", &fval) == JS_FALSE ) 
	{
		wxPGEditor::SetControlStringValue(property, ctrl, txt);
		return ;
	}
	jsval rval;
	jsval argv[] = { Property::CreateObject(cx, property, NULL)
			,		Window::CreateObject(cx, ctrl, NULL)
			,		ToJS(cx, txt)
	};
	if ( JS_CallFunctionValue(cx, obj, fval, 3, argv, &rval) == JS_TRUE )
	{
		return ;
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	wxPGEditor::SetControlStringValue(property, ctrl, txt);
}
void Editor::SetControlIntValue( wxPGProperty* property,
													wxWindow* ctrl,
													int value ) const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onSetControlIntValue", &fval) == JS_FALSE ) 
	{
		wxPGEditor::SetControlIntValue(property, ctrl, value);
		return ;
	}
	jsval rval;
	jsval argv[] = { Property::CreateObject(cx, property, NULL)
			,		Window::CreateObject(cx, ctrl, NULL)
			,		ToJS(cx, value)
	};
	if ( JS_CallFunctionValue(cx, obj, fval, 3, argv, &rval) == JS_TRUE )
	{
		return ;
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	wxPGEditor::SetControlIntValue(property, ctrl, value);
}
int Editor::InsertItem( wxWindow* ctrl,
										const wxString& label,
										int index ) const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onInsertItem", &fval) == JS_FALSE ) 
	{
		return wxPGEditor::InsertItem(ctrl, label, index);
	}
	jsval rval;
	jsval argv[] = { Window::CreateObject(cx, ctrl, NULL)
			,		ToJS(cx, label)
			,		ToJS(cx, index)
	};
	if ( JS_CallFunctionValue(cx, obj, fval, 3, argv, &rval) == JS_TRUE )
	{
		int ret = 0;
		FromJS(cx, rval, ret);
		return ret;
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return wxPGEditor::InsertItem(ctrl, label, index);
}
void Editor::DeleteItem( wxWindow* ctrl, int index ) const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onDeleteItem", &fval) == JS_FALSE ) 
	{
		wxPGEditor::DeleteItem(ctrl, index);
		return;
	}
	jsval rval;
	jsval argv[] = { Window::CreateObject(cx, ctrl, NULL)
			,		ToJS(cx, index)
	};
	if ( JS_CallFunctionValue(cx, obj, fval, 2, argv, &rval) == JS_TRUE )
	{

		return ;
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	wxPGEditor::DeleteItem(ctrl, index);
}
void Editor::OnFocus( wxPGProperty* property, wxWindow* wnd ) const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onOnFocus", &fval) == JS_FALSE ) 
	{
		wxPGEditor::OnFocus(property, wnd);
		return;
	}
	jsval rval;
	jsval argv[] = { Property::CreateObject(cx, property, NULL)
			,		 Window::CreateObject(cx, wnd, NULL)
	};
	if ( JS_CallFunctionValue(cx, obj, fval, 2, argv, &rval) == JS_TRUE )
	{

		return ;
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	wxPGEditor::OnFocus(property, wnd);
}
bool Editor::CanContainCustomImage() const
{
	JavaScriptClientData *data  = dynamic_cast<JavaScriptClientData*>(GetClientObject());
	JSContext *cx = data->GetContext();
	JSObject *obj = data->GetObject();

	
	jsval fval;
	if ( GetFunctionProperty(cx, obj, "onCanContainCustomImage", &fval) == JS_FALSE ) 
	{
		return wxPGEditor::CanContainCustomImage();
	}
	jsval rval;
	if ( JS_CallFunctionValue(cx, obj, fval, 0, NULL, &rval) == JS_TRUE )
	{		
		bool ret = false;;
		FromJS(cx, rval, ret);
		return ret;
	}
	else
	{
		if ( JS_IsExceptionPending(cx) )
		{
			JS_ReportPendingException(cx);
		}
	}
	return wxPGEditor::CanContainCustomImage();
}







//--------------------------------------------------------
//	Editor
//--------------------------------------------------------
WXJS_INIT_CLASS(Editor, "Editor", 0)
	
// コンストラクタ
WXJS_BEGIN_CONSTRUCTOR(wxPGEditor, Editor)
{
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
	Editor *p = NULL;


	p = new Editor();
	p->SetClientObject(new JavaScriptClientData(cx, obj, true, false));


	return p;
}
WXJS_END_CONSTRUCTOR

// デストラクタ
WXJS_BEGIN_DESTRUCTOR(wxPGEditor, Editor)
{
	//if( p->IsKindOf( CLASSINFO(Editor) ) ) {
	//	delete p;
	//}
}
WXJS_END_DESTRUCTOR
	
	
WXJS_BEGIN_STATIC_PROPERTY_MAP(Editor)
  WXJS_READONLY_STATIC_PROPERTY(P_STOCK_SPINCTRL, "stockSpinCtrl")
  WXJS_READONLY_STATIC_PROPERTY(P_STOCK_DATETIMECTRL, "stockDatetimeCtrl")
WXJS_END_PROPERTY_MAP()

WXJS_BEGIN_GET_STATIC_PROP(Editor)
{	

	if ( id == P_STOCK_SPINCTRL )
	{
		vp.set( Editor::CreateObject(cx, wxPGEditor_SpinCtrl) );
	} else
	if ( id == P_STOCK_DATETIMECTRL )
	{
		vp.set( Editor::CreateObject(cx, wxPGEditor_DatePickerCtrl) );
	}
	return true;
}
WXJS_END_GET_STATIC_PROP


	
WXJS_BEGIN_PROPERTY_MAP(Editor)
  WXJS_READONLY_PROPERTY(P_NAME, "name")
  WXJS_READONLY_PROPERTY(P_CanContainCustomImage, "canContainCustomImage")
WXJS_END_PROPERTY_MAP()



// プロパティー get の実装
WXJS_BEGIN_GET_PROP(wxPGEditor, Editor)
{
	switch (id) 
	{
	case P_NAME:
		vp.set( ToJS(cx, p->GetName()) );
		break;
	case P_CanContainCustomImage:
		vp.set( ToJS(cx, p->CanContainCustomImage()) );
		break;
	}
	return true;
}
WXJS_END_GET_PROP

	
// メソッドの定義
WXJS_BEGIN_METHOD_MAP(Editor)
	WXJS_METHOD("createControls", createControls, 4)
	WXJS_METHOD("updateControl", updateControl, 2)
	WXJS_METHOD("drawValue", drawValue, 4)
	WXJS_METHOD("getValueFromControl", getValueFromControl, 3)
	WXJS_METHOD("setValueToUnspecified", setValueToUnspecified,  2)
	WXJS_METHOD("setControlAppearance", setControlAppearance,  6)
	WXJS_METHOD("setControlStringValue", setControlStringValue,  3)
	WXJS_METHOD("setControlIntValue", setControlIntValue,  3)
	WXJS_METHOD("insertItem", insertItem,  3)
	WXJS_METHOD("deleteItem", deleteItem,  2)
WXJS_END_METHOD_MAP()


JSBool Editor::createControls(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGEditor *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	virtual wxPGWindowList 	CreateControls (
			wxPropertyGrid *propgrid, 
			wxPGProperty *property, 
			const wxPoint &pos, 
			const wxSize &size
	) const =0

 		Instantiates editor controls.
	*/
	// 引数の取得
	int argIndex = 0;

	wxPropertyGrid *propgrid = NULL;
	wxPGProperty *property = NULL;
	zzzJsPtr<wxPoint> apPoint(NULL, &wxDefaultPosition);
	zzzJsPtr<wxSize> apSize(NULL, &wxDefaultSize);

	// 0
	propgrid = Grid::GetPrivate(cx, argv[argIndex], false);
	if( propgrid == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Grid");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	property = Property::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return JS_FALSE;
	}
	argIndex++;
	// 2
	ZZZJS_ARG_AP_CHK_AND_ERROR(apPoint, zzzJs::ext::Point);
	argIndex++;
	// 2
	ZZZJS_ARG_AP_CHK_AND_ERROR(apSize, Size);
	argIndex++;

	
	// APIの実行と戻り値の設定
	wxPGWindowList wndList = p->CreateControls(propgrid, property, *(apPoint.get()), *(apSize.get()));
	*vp = WindowList::CreateObject(
		cx, 
		new wxPGWindowList(wndList.m_primary, wndList.m_secondary), 
		NULL);
	return JS_TRUE;
}

JSBool Editor::updateControl(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGEditor *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	virtual void 	UpdateControl (
			wxPGProperty *property, 
			wxWindow *ctrl
	) const =0

 		Loads value from property to the control. 
	*/
	// 引数の取得
	int argIndex = 0;

	wxPGProperty *property = NULL;
	wxWindow *ctrl = NULL;

	// 0
	property = Property::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	ctrl = Window::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
		return JS_FALSE;
	}
	argIndex++;
	
	// APIの実行と戻り値の設定
	p->UpdateControl(property, ctrl);
	return JS_TRUE;
}

JSBool Editor::drawValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGEditor *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	virtual void 	DrawValue (
			wxDC &dc, 
			const wxRect &rect, 
			wxPGProperty *property, 
			const wxString &text
	) const
 		Draws value for given property.
	*/
	// 引数の取得
	int argIndex = 0;
	
	wxDC *pDc = NULL;
	zzzJsPtr<wxRect> apRect;
	wxPGProperty *property = NULL;
	wxString text;

	// 0
	pDc = DC::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "DC");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	ZZZJS_ARG_AP_CHK_AND_ERROR(apRect, Rect);
	//if( FromJS(cx, argv[argIndex], rect) == false ) {
	//	JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Rect");
	//	return JS_FALSE;
	//}
	argIndex++;
	// 1
	property = Property::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	if( FromJS(cx, argv[argIndex], text) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	argIndex++;
	
	// APIの実行と戻り値の設定
	p->DrawValue(*pDc, *(apRect.get()), property, text );
	return JS_TRUE;
}

JSBool Editor::getValueFromControl(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGEditor *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	virtual bool 	GetValueFromControl (
			wxVariant &variant, 
			wxPGProperty *property, 
			wxWindow *ctrl) const
 		Returns value from control, via parameter 'variant'.
	*/
	// 引数の取得
	int argIndex = 0;
	
	wxVariant variant;
	wxPGProperty *property;
	wxWindow *ctrl;
	
	// 0
	if( FromJS(cx, argv[argIndex], variant) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Rect");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	property = Property::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	ctrl = Window::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
		return JS_FALSE;
	}
	argIndex++;
	
	// APIの実行と戻り値の設定
	vp->setBoolean( 
		p->GetValueFromControl(variant, property, ctrl )
	);
	return JS_TRUE;
}

JSBool Editor::setValueToUnspecified(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGEditor *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	virtual void 	SetValueToUnspecified (
			wxPGProperty *property, 
			wxWindow *ctrl) const =0
 		Sets value in control to unspecified.
	*/
	// 引数の取得
	int argIndex = 0;
	
	wxPGProperty *property;
	wxWindow *ctrl;
	

	// 0
	property = Property::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	ctrl = Window::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
		return JS_FALSE;
	}
	argIndex++;
	
	// APIの実行と戻り値の設定
	p->SetValueToUnspecified( property, ctrl );
	return JS_TRUE;
}

JSBool Editor::setControlAppearance(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGEditor *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	virtual void 	SetControlAppearance (
			wxPropertyGrid *pg, 
			wxPGProperty *property, 
			wxWindow *ctrl, 
			const wxPGCell &appearance, 
			const wxPGCell &oldAppearance, 
			bool unspecified
	) const
 		Called by property grid to set new appearance for the control.
	*/
	// 引数の取得
	int argIndex = 0;
	
	wxPropertyGrid *pg = NULL;
	wxPGProperty *property = NULL;
	wxWindow *ctrl = NULL;
	wxPGCell* appearance = NULL;
	wxPGCell* oldAppearance = NULL;
	bool unspecified = false;
	

	// 0
	pg = Grid::GetPrivate(cx, argv[argIndex], false);
	if( pg == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Grid");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	property = Property::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return JS_FALSE;
	}
	argIndex++;
	// 2
	ctrl = Window::GetPrivate(cx, argv[argIndex], false);
	if( ctrl == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
		return JS_FALSE;
	}
	argIndex++;
	// 3
	appearance = Cell::GetPrivate(cx, argv[argIndex], false);
	if( appearance == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Cell");
		return JS_FALSE;
	}
	argIndex++;
	// 4
	oldAppearance = Cell::GetPrivate(cx, argv[argIndex], false);
	if( oldAppearance == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Cell");
		return JS_FALSE;
	}
	argIndex++;
	// 5
	if( FromJS(cx, argv[argIndex], unspecified) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Boolean");
		return JS_FALSE;
	}
	
	// APIの実行と戻り値の設定
	p->SetControlAppearance( pg, property, ctrl, *appearance, *oldAppearance, unspecified  );
	return JS_TRUE;
}

JSBool Editor::setControlStringValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGEditor *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	virtual void 	SetControlStringValue (
			wxPGProperty *property, 
			wxWindow *ctrl, 
			const wxString &txt) const
 		Sets control's value specifically from string. 
	*/
	// 引数の取得
	int argIndex = 0;
	
	wxPGProperty *property = NULL;
	wxWindow *ctrl = NULL;
	wxString txt;
	

	// 0
	property = Property::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	ctrl = Window::GetPrivate(cx, argv[argIndex], false);
	if( ctrl == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
		return JS_FALSE;
	}
	argIndex++;
	// 5
	if( FromJS(cx, argv[argIndex], txt) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	
	// APIの実行と戻り値の設定
	p->SetControlStringValue( property, ctrl, txt  );
	return JS_TRUE;
}

JSBool Editor::setControlIntValue(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGEditor *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	virtual void 	SetControlIntValue (
			wxPGProperty *property, 
			wxWindow *ctrl, 
			int value
	) const
 		Sets control's value specifically from int (applies to choice etc.).
	*/
	// 引数の取得
	int argIndex = 0;
	
	wxPGProperty *property = NULL;
	wxWindow *ctrl = NULL;
	int value;
	

	// 0
	property = Property::GetPrivate(cx, argv[argIndex], false);
	if( property == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "pg.Property");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	ctrl = Window::GetPrivate(cx, argv[argIndex], false);
	if( ctrl == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
		return JS_FALSE;
	}
	argIndex++;
	// 5
	if( FromJS(cx, argv[argIndex], value) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	
	// APIの実行と戻り値の設定
	p->SetControlIntValue( property, ctrl, value  );
	return JS_TRUE;
}

JSBool Editor::insertItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGEditor *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	virtual int 	InsertItem (
			wxWindow *ctrl, 
			const wxString &label, 
			int index
	) const
 		Inserts item to existing control.
	*/
	// 引数の取得
	int argIndex = 0;
	
	wxWindow *	ctrl = NULL;
	wxString	label;
	int			index;
	

	// 0
	ctrl = Window::GetPrivate(cx, argv[argIndex], false);
	if( ctrl == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	if( FromJS(cx, argv[argIndex], label) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	argIndex++;
	// 1
	if( FromJS(cx, argv[argIndex], index) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	
	// APIの実行と戻り値の設定
	vp->setInt32( 
		p->InsertItem( ctrl, label,  index )
	);
	return JS_TRUE;
}

JSBool Editor::deleteItem(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    wxPGEditor *p = GetPrivate(cx, obj);
    if ( p == NULL )
        return JS_FALSE;
	/*
	virtual void 	DeleteItem (
			wxWindow *ctrl, 
			int index
	) const
 		Deletes item from existing control.
	*/
	// 引数の取得
	int argIndex = 0;
	
	wxWindow *	ctrl = NULL;
	int			index;
	

	// 0
	ctrl = Window::GetPrivate(cx, argv[argIndex], false);
	if( ctrl == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, "Window");
		return JS_FALSE;
	}
	argIndex++;
	// 1
	if( FromJS(cx, argv[argIndex], index) == false ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, argIndex+1, WXJS_TYPE_NUMBER);
		return JS_FALSE;
	}
	
	// APIの実行と戻り値の設定
	p->DeleteItem( ctrl, index );
	return JS_TRUE;
}




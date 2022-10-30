/*
 * wxJavaScript - init.cpp
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
 * $Id: init.cpp 644 2007-03-27 20:31:33Z fbraem $
 */
#include "precompile.h"

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"

#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/property.h>
#include <wx/propgrid/manager.h>
#include <jsapi.h>

#include "js/gui/pg/pg_init.h"
#include "js/gui/pg/pg_grid_manager.h"
#include "js/gui/pg/pg_grid_page.h"
#include "js/gui/pg/pg_grid.h"
#include "js/gui/pg/pg_prop.h"
#include "js/gui/pg/pg_cell.h"
#include "js/gui/pg/pg_choice_entry.h"
#include "js/gui/pg/pg_choices.h"
#include "js/gui/pg/pg_colour_property_value.h"
#include "js/gui/pg/pg_prop_array_string.h"
#include "js/gui/pg/pg_prop_bool.h"
#include "js/gui/pg/pg_prop_category.h"
#include "js/gui/pg/pg_prop_colour.h"
#include "js/gui/pg/pg_prop_date.h"
#include "js/gui/pg/pg_prop_dir.h"
#include "js/gui/pg/pg_prop_edit_enum.h"
#include "js/gui/pg/pg_prop_enum.h"
#include "js/gui/pg/pg_prop_file.h"
#include "js/gui/pg/pg_prop_flags.h"
#include "js/gui/pg/pg_prop_float.h"
#include "js/gui/pg/pg_prop_font.h"
#include "js/gui/pg/pg_prop_image_file.h"
#include "js/gui/pg/pg_prop_int.h"
#include "js/gui/pg/pg_prop_long_string.h"
#include "js/gui/pg/pg_prop_multi_choice.h"
#include "js/gui/pg/pg_prop_string.h"
#include "js/gui/pg/pg_prop_system_colour.h"
#include "js/gui/pg/pg_prop_uint.h"
#include "js/gui/pg/pg_validation_info.h"
#include "js/gui/pg/pg_evt_grid.h"

#include "js/gui/pg/pg_editor.h"
#include "js/gui/pg/pg_wndlist.h"

#include "js/gui/control/control.h"
#include "js/gui/control/panel.h"

using namespace zzzJs;
using namespace zzzJs::gui;
using namespace zzzJs::gui::pg;


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif



JSConstDoubleSpec wxPGWindowStlesMap[] = 
{
	WXJS_CONSTANT(wxPG_, AUTO_SORT)
	WXJS_CONSTANT(wxPG_, HIDE_CATEGORIES)
	WXJS_CONSTANT(wxPG_, ALPHABETIC_MODE)
	WXJS_CONSTANT(wxPG_, BOLD_MODIFIED)
	WXJS_CONSTANT(wxPG_, SPLITTER_AUTO_CENTER)
	WXJS_CONSTANT(wxPG_, TOOLTIPS)
	WXJS_CONSTANT(wxPG_, HIDE_MARGIN)
	WXJS_CONSTANT(wxPG_, STATIC_SPLITTER)
	WXJS_CONSTANT(wxPG_, STATIC_LAYOUT)
	WXJS_CONSTANT(wxPG_, LIMITED_EDITING)
	WXJS_CONSTANT(wxPG_, TOOLBAR)
	WXJS_CONSTANT(wxPG_, DESCRIPTION)
	WXJS_CONSTANT(wxPG_, NO_INTERNAL_BORDER)
	WXJS_CONSTANT(wxPG_, WINDOW_STYLE_MASK)
	{ 0 }
};
JSConstDoubleSpec wxPGExWindowStlesMap[] = 
{
	WXJS_CONSTANT(wxPG_EX_, INIT_NOCAT)
	WXJS_CONSTANT(wxPG_EX_, NO_FLAT_TOOLBAR)
	WXJS_CONSTANT(wxPG_EX_, MODE_BUTTONS)
	WXJS_CONSTANT(wxPG_EX_, HELP_AS_TOOLTIPS)
	WXJS_CONSTANT(wxPG_EX_, NATIVE_DOUBLE_BUFFERING)
	WXJS_CONSTANT(wxPG_EX_, AUTO_UNSPECIFIED_VALUES)
	WXJS_CONSTANT(wxPG_EX_, WRITEONLY_BUILTIN_ATTRIBUTES)
	WXJS_CONSTANT(wxPG_EX_, HIDE_PAGE_BUTTONS)
	WXJS_CONSTANT(wxPG_EX_, MULTIPLE_SELECTION)
	WXJS_CONSTANT(wxPG_EX_, ENABLE_TLP_TRACKING)
	WXJS_CONSTANT(wxPG_EX_, NO_TOOLBAR_DIVIDER)
	WXJS_CONSTANT(wxPG_EX_, TOOLBAR_SEPARATOR)
	WXJS_CONSTANT(wxPG_EX_, ALWAYS_ALLOW_FOCUS)
	WXJS_CONSTANT(wxPG_EX_, WINDOW_STYLE_MASK)
	{ 0 }
};
JSConstDoubleSpec wxPGVFBMap[] = 
{
	WXJS_CONSTANT(wxPG_VFB_, STAY_IN_PROPERTY)
	WXJS_CONSTANT(wxPG_VFB_, BEEP)
	WXJS_CONSTANT(wxPG_VFB_, MARK_CELL)
	WXJS_CONSTANT(wxPG_VFB_, SHOW_MESSAGE)
	WXJS_CONSTANT(wxPG_VFB_, SHOW_MESSAGEBOX)
	WXJS_CONSTANT(wxPG_VFB_, SHOW_MESSAGE_ON_STATUSBAR)
	WXJS_CONSTANT(wxPG_VFB_, DEFAULT)
	WXJS_CONSTANT(wxPG_VFB_, UNDEFINED)
	{ 0 }
};
JSConstDoubleSpec wxPGKeybordActionMap[] = 
{
	WXJS_CONSTANT(wxPG_ACTION_, INVALID)
	WXJS_CONSTANT(wxPG_ACTION_, NEXT_PROPERTY)
	WXJS_CONSTANT(wxPG_ACTION_, PREV_PROPERTY)
	WXJS_CONSTANT(wxPG_ACTION_, EXPAND_PROPERTY)
	WXJS_CONSTANT(wxPG_ACTION_, COLLAPSE_PROPERTY)
	WXJS_CONSTANT(wxPG_ACTION_, CANCEL_EDIT)
	WXJS_CONSTANT(wxPG_ACTION_, EDIT)
	WXJS_CONSTANT(wxPG_ACTION_, PRESS_BUTTON)
	WXJS_CONSTANT(wxPG_ACTION_, MAX)
	{ 0 }
};
JSConstDoubleSpec wxPGSelectPropMap[] = 
{
	WXJS_CONSTANT(wxPG_SEL_, FOCUS)
	WXJS_CONSTANT(wxPG_SEL_, FORCE)
	WXJS_CONSTANT(wxPG_SEL_, NONVISIBLE)
	WXJS_CONSTANT(wxPG_SEL_, NOVALIDATE)
	WXJS_CONSTANT(wxPG_SEL_, DELETING)
	WXJS_CONSTANT(wxPG_SEL_, SETUNSPEC)
	WXJS_CONSTANT(wxPG_SEL_, DIALOGVAL)
	WXJS_CONSTANT(wxPG_SEL_, DONT_SEND_EVENT)
	WXJS_CONSTANT(wxPG_SEL_, NO_REFRESH)
	{ 0 }
};
JSConstDoubleSpec wxPGSpitterMap[] = 
{
	WXJS_CONSTANT(wxPG_SPLITTER_, REFRESH)
	WXJS_CONSTANT(wxPG_SPLITTER_, ALL_PAGES)
	WXJS_CONSTANT(wxPG_SPLITTER_, FROM_EVENT)
	WXJS_CONSTANT(wxPG_SPLITTER_, FROM_AUTO_CENTER)
	{ 0 }
};



bool zzzJs::gui::pg::InitClass(JSContext *cx, JSObject *global)
{
    JSObject *obj = NULL;
    JSObject *namespaceObj = JS_DefineObject(cx, global, "pg", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);


	// Constant‚Ì’è‹`
	{
		JSObject *emObj = JS_DefineObject(cx, namespaceObj, "WindowStyle", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxPGWindowStlesMap);

		emObj = JS_DefineObject(cx, namespaceObj, "WindowStyleEx", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxPGExWindowStlesMap);

		emObj = JS_DefineObject(cx, namespaceObj, "VFB", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxPGVFBMap);

		emObj = JS_DefineObject(cx, namespaceObj, "ACTION", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxPGKeybordActionMap);

		emObj = JS_DefineObject(cx, namespaceObj, "SEL", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxPGSelectPropMap);

		emObj = JS_DefineObject(cx, namespaceObj, "SPLITTER", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxPGSpitterMap);
	}


	obj = GridManager::define_Class(cx, namespaceObj, Panel::GetClassPrototype() );
	obj = GridPage::define_Class(cx, namespaceObj );
	obj = Grid::define_Class(cx, namespaceObj, Control::GetClassPrototype() );
	obj = Cell::define_Class(cx, namespaceObj );
	obj = ChoiceEntry::define_Class(cx, namespaceObj, Cell::GetClassPrototype() );
	obj = Choices::define_Class(cx, namespaceObj );
	obj = ColourPropertyValue::define_Class(cx, namespaceObj );


	obj = Property::define_Class(cx, namespaceObj );
	obj = ArrayStringProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	obj = BoolProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	obj = PropertyCategory::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	
	obj = EnumProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	obj = SystemColourProperty::define_Class(cx, namespaceObj, EnumProperty::GetClassPrototype() );
	obj = ColourProperty::define_Class(cx, namespaceObj, SystemColourProperty::GetClassPrototype() );
	obj = DateProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );


	obj = LongStringProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	obj = DirProperty::define_Class(cx, namespaceObj, LongStringProperty::GetClassPrototype() );
	obj = FileProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	obj = FlagsProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	obj = FloatProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	obj = FontProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	obj = ImageFileProperty::define_Class(cx, namespaceObj, FileProperty::GetClassPrototype() );
	obj = MultiChoiceProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	obj = StringProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	obj = IntProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	obj = UIntProperty::define_Class(cx, namespaceObj, Property::GetClassPrototype() );
	
	
	obj = ValidationInfo::define_Class(cx, namespaceObj );
	obj = GridEvent::define_Class(cx, namespaceObj );

	
	obj = Editor::define_Class(cx, namespaceObj );
	obj = WindowList::define_Class(cx, namespaceObj );



	

	// •¶Žš—ñ‚ÌConstant‚ð’è‹`
	{		
        jsval attrValue = ToJS(cx, wxPG_LABEL);
		wxString attr((const char *)"LABEL");
		JS_SetUCProperty(cx, namespaceObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
	}
	{
		 JSObject *attrObj = JS_DefineObject(cx, namespaceObj, "ATTR", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		 {
			jsval attrValue = ToJS(cx, wxPG_ATTR_DEFAULT_VALUE);
			wxString attr((const char *)"DEFAULT_VALUE");
			JS_SetUCProperty(cx, attrObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
		 }
		 {
			jsval attrValue = ToJS(cx, wxPG_ATTR_MIN);
			wxString attr((const char *)"MIN");
			JS_SetUCProperty(cx, attrObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
		 }
		 {
			jsval attrValue = ToJS(cx, wxPG_ATTR_MAX);
			wxString attr((const char *)"MAX");
			JS_SetUCProperty(cx, attrObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
		 }
		 {
			jsval attrValue = ToJS(cx, wxPG_ATTR_UNITS);
			wxString attr((const char *)"UNITS");
			JS_SetUCProperty(cx, attrObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
		 }
		 {
			jsval attrValue = ToJS(cx, wxPG_ATTR_HINT);
			wxString attr((const char *)"HINT");
			JS_SetUCProperty(cx, attrObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
		 }
	}

    return true;
}

bool zzzJs::gui::pg::InitObject(JSContext *cx, JSObject *global)
{
//	XmlDocument::define_Class(cx, global);
//    XmlNode::define_Class(cx, global);
    return true;
}

void zzzJs::gui::pg::Destroy()
{
}

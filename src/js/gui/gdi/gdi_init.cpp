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

#include "js/gui/gdi/gdi_init.h"
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

#include "js/gui/gdi/gdi_init.h"
#include "js/gui/gdi/auto_buffered_paint_dc.h"
#include "js/gui/gdi/buffered_dc.h"
#include "js/gui/gdi/buffered_paint_dc.h"
#include "js/gui/gdi/client_dc.h"
#include "js/gui/gdi/dc.h"
#include "js/gui/gdi/gcdc.h"
#include "js/gui/gdi/memory_dc.h"
#include "js/gui/gdi/metafile.h"
#include "js/gui/gdi/metafile_dc.h"
#include "js/gui/gdi/mirror_dc.h"
#include "js/gui/gdi/paint_dc.h"
#include "js/gui/gdi/screen_dc.h"
#include "js/gui/gdi/window_dc.h"





JSConstDoubleSpec wxDeprecatedGUIConstantsMap[] = 
{
	WXJS_CONSTANT(wx, DEFAULT)
	WXJS_CONSTANT(wx, DECORATIVE)
	WXJS_CONSTANT(wx, ROMAN)
	WXJS_CONSTANT(wx, SCRIPT)
	WXJS_CONSTANT(wx, SWISS)
	WXJS_CONSTANT(wx, MODERN)
	WXJS_CONSTANT(wx, TELETYPE)
	WXJS_CONSTANT(wx, VARIABLE )
	WXJS_CONSTANT(wx, FIXED)
	WXJS_CONSTANT(wx, NORMAL)
	WXJS_CONSTANT(wx, LIGHT)
	WXJS_CONSTANT(wx, BOLD)
	WXJS_CONSTANT(wx, ITALIC)
	WXJS_CONSTANT(wx, SLANT)
	WXJS_CONSTANT(wx, SOLID)
	WXJS_CONSTANT(wx, DOT)
	WXJS_CONSTANT(wx, LONG_DASH)
	WXJS_CONSTANT(wx, SHORT_DASH)
	WXJS_CONSTANT(wx, DOT_DASH)
	WXJS_CONSTANT(wx, USER_DASH)
	WXJS_CONSTANT(wx, TRANSPARENT)
	WXJS_CONSTANT(wx, STIPPLE_MASK_OPAQUE)
	WXJS_CONSTANT(wx, STIPPLE_MASK)
	WXJS_CONSTANT(wx, STIPPLE)
	WXJS_CONSTANT(wx, BDIAGONAL_HATCH)
	WXJS_CONSTANT(wx, CROSSDIAG_HATCH)
	WXJS_CONSTANT(wx, FDIAGONAL_HATCH)
	WXJS_CONSTANT(wx, CROSS_HATCH)
	WXJS_CONSTANT(wx, HORIZONTAL_HATCH)
	WXJS_CONSTANT(wx, VERTICAL_HATCH)
	WXJS_CONSTANT(wx, FIRST_HATCH)
	WXJS_CONSTANT(wx, LAST_HATCH)
	{ 0 }
};

JSConstDoubleSpec wxMappingModeMap[] = 
{
	WXJS_CONSTANT(wxMM_, TEXT)
	WXJS_CONSTANT(wxMM_, METRIC)
	WXJS_CONSTANT(wxMM_, LOMETRIC)
	WXJS_CONSTANT(wxMM_, TWIPS)
	WXJS_CONSTANT(wxMM_, POINTS)
	{ 0 }
};

JSConstDoubleSpec wxPenStyleMap[] = 
{
    WXJS_CONSTANT(wxPENSTYLE_, INVALID)
    WXJS_CONSTANT(wxPENSTYLE_, SOLID)
    WXJS_CONSTANT(wxPENSTYLE_, DOT)
    WXJS_CONSTANT(wxPENSTYLE_, LONG_DASH)
    WXJS_CONSTANT(wxPENSTYLE_, SHORT_DASH)
    WXJS_CONSTANT(wxPENSTYLE_,  DOT_DASH)
    WXJS_CONSTANT(wxPENSTYLE_,  USER_DASH)
    WXJS_CONSTANT(wxPENSTYLE_,  TRANSPARENT)
    WXJS_CONSTANT(wxPENSTYLE_,  STIPPLE_MASK_OPAQUE)
    WXJS_CONSTANT(wxPENSTYLE_,  STIPPLE_MASK)
    WXJS_CONSTANT(wxPENSTYLE_,  STIPPLE)
    WXJS_CONSTANT(wxPENSTYLE_,  BDIAGONAL_HATCH)
    WXJS_CONSTANT(wxPENSTYLE_,  CROSSDIAG_HATCH)
    WXJS_CONSTANT(wxPENSTYLE_,  FDIAGONAL_HATCH)
    WXJS_CONSTANT(wxPENSTYLE_,  CROSS_HATCH)
    WXJS_CONSTANT(wxPENSTYLE_,  HORIZONTAL_HATCH)
    WXJS_CONSTANT(wxPENSTYLE_,  VERTICAL_HATCH)
    WXJS_CONSTANT(wxPENSTYLE_,  FIRST_HATCH)
    WXJS_CONSTANT(wxPENSTYLE_,  LAST_HATCH)
	{ 0 }
};



JSConstDoubleSpec wxBrushStyleMap[] = 
{
    WXJS_CONSTANT(wxBRUSHSTYLE_, INVALID)
	WXJS_CONSTANT(wxBRUSHSTYLE_, SOLID)
	WXJS_CONSTANT(wxBRUSHSTYLE_, TRANSPARENT)
	WXJS_CONSTANT(wxBRUSHSTYLE_, STIPPLE_MASK_OPAQUE)
	WXJS_CONSTANT(wxBRUSHSTYLE_, STIPPLE_MASK)
	WXJS_CONSTANT(wxBRUSHSTYLE_, STIPPLE)
	WXJS_CONSTANT(wxBRUSHSTYLE_, BDIAGONAL_HATCH)
	WXJS_CONSTANT(wxBRUSHSTYLE_, CROSSDIAG_HATCH)
	WXJS_CONSTANT(wxBRUSHSTYLE_, FDIAGONAL_HATCH)
	WXJS_CONSTANT(wxBRUSHSTYLE_, CROSS_HATCH)
	WXJS_CONSTANT(wxBRUSHSTYLE_, HORIZONTAL_HATCH)
	WXJS_CONSTANT(wxBRUSHSTYLE_, VERTICAL_HATCH)
	WXJS_CONSTANT(wxBRUSHSTYLE_, FIRST_HATCH)
	WXJS_CONSTANT(wxBRUSHSTYLE_, LAST_HATCH)
	{ 0 }
};

JSConstDoubleSpec wxPenJoinMap[] = 
{
	WXJS_CONSTANT(wxJOIN_, INVALID)
	WXJS_CONSTANT(wxJOIN_, BEVEL)
	WXJS_CONSTANT(wxJOIN_, MITER)
	WXJS_CONSTANT(wxJOIN_, ROUND)
	{ 0 }
};


JSConstDoubleSpec wxPenCapMap[] = 
{
	WXJS_CONSTANT(wxCAP_, INVALID)
	WXJS_CONSTANT(wxCAP_, ROUND)
	WXJS_CONSTANT(wxCAP_, PROJECTING)
	WXJS_CONSTANT(wxCAP_, BUTT)
	{ 0 }
};
JSConstDoubleSpec wxPolygonFillModeMap[] = 
{
	WXJS_CONSTANT(wx, ODDEVEN_RULE)
	WXJS_CONSTANT(wx, WINDING_RULE)
	{ 0 }
};

bool zzzJs::gui::gdi::InitClass(JSContext *cx, JSObject *global)
{
    JSObject *obj = NULL;
    JSObject *namespaceObj = global;


	// Constant‚Ì’è‹`
	{
		JSObject *emObj = NULL;
	//	emObj = JS_DefineObject(cx, namespaceObj, "WindowStyle", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	//	JS_DefineConstDoubles(cx, emObj, wxPGWindowStlesMap);

	//	emObj = JS_DefineObject(cx, namespaceObj, "WindowStyleEx", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	//	JS_DefineConstDoubles(cx, emObj, wxPGExWindowStlesMap);

	//	emObj = JS_DefineObject(cx, namespaceObj, "VFB", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	//	JS_DefineConstDoubles(cx, emObj, wxPGVFBMap);

	//	emObj = JS_DefineObject(cx, namespaceObj, "ACTION", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	//	JS_DefineConstDoubles(cx, emObj, wxPGKeybordActionMap);

	//	emObj = JS_DefineObject(cx, namespaceObj, "SEL", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	//	JS_DefineConstDoubles(cx, emObj, wxPGSelectPropMap);

	//	emObj = JS_DefineObject(cx, namespaceObj, "SPLITTER", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, namespaceObj, wxDeprecatedGUIConstantsMap);

		emObj = JS_DefineObject(cx, namespaceObj, "MappingMode", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxMappingModeMap);

		emObj = JS_DefineObject(cx, namespaceObj, "PENSTYLE", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxPenStyleMap);

		// 
		emObj = JS_DefineObject(cx, namespaceObj, "BRUSHSTYLE", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxBrushStyleMap);

		emObj = JS_DefineObject(cx, namespaceObj, "PENJOIN", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxPenJoinMap);

		emObj = JS_DefineObject(cx, namespaceObj, "PENJOIN", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxPenJoinMap);

		emObj = JS_DefineObject(cx, namespaceObj, "PENCAP", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxPenCapMap);

		emObj = JS_DefineObject(cx, namespaceObj, "PolygonFillMode", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
		JS_DefineConstDoubles(cx, emObj, wxPolygonFillModeMap);
	}



	obj = DC::define_Class(cx, namespaceObj );
	obj = GCDC::define_Class(cx, namespaceObj, DC::GetClassPrototype() );
	obj = MemoryDC::define_Class(cx, namespaceObj, DC::GetClassPrototype() );
	obj = BufferedDC::define_Class(cx, namespaceObj, MemoryDC::GetClassPrototype() );
	obj = BufferedPaintDC::define_Class(cx, namespaceObj, BufferedDC::GetClassPrototype() );
	obj = AutoBufferedPaintDC::define_Class(cx, namespaceObj, BufferedPaintDC::GetClassPrototype() );
	obj = MetafileDC::define_Class(cx, namespaceObj, DC::GetClassPrototype() );
	obj = MirrorDC::define_Class(cx, namespaceObj, DC::GetClassPrototype() );
	obj = ScreenDC::define_Class(cx, namespaceObj, DC::GetClassPrototype() );
	obj = WindowDC::define_Class(cx, namespaceObj, DC::GetClassPrototype() );
	obj = ClientDC::define_Class(cx, namespaceObj, WindowDC::GetClassPrototype() );
	obj = PaintDC::define_Class(cx, namespaceObj, ClientDC::GetClassPrototype() );

	obj = Metafile::define_Class(cx, namespaceObj );


	//// •¶Žš—ñ‚ÌConstant‚ð’è‹`
	//{		
 //       jsval attrValue = ToJS(cx, wxPG_LABEL);
	//	wxString attr((const char *)"LABEL");
	//	JS_SetUCProperty(cx, namespaceObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
	//}
	//{
	//	 JSObject *attrObj = JS_DefineObject(cx, namespaceObj, "ATTR", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	//	 {
	//		jsval attrValue = ToJS(cx, wxPG_ATTR_DEFAULT_VALUE);
	//		wxString attr((const char *)"DEFAULT_VALUE");
	//		JS_SetUCProperty(cx, attrObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
	//	 }
	//	 {
	//		jsval attrValue = ToJS(cx, wxPG_ATTR_MIN);
	//		wxString attr((const char *)"MIN");
	//		JS_SetUCProperty(cx, attrObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
	//	 }
	//	 {
	//		jsval attrValue = ToJS(cx, wxPG_ATTR_MAX);
	//		wxString attr((const char *)"MAX");
	//		JS_SetUCProperty(cx, attrObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
	//	 }
	//	 {
	//		jsval attrValue = ToJS(cx, wxPG_ATTR_UNITS);
	//		wxString attr((const char *)"UNITS");
	//		JS_SetUCProperty(cx, attrObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
	//	 }
	//	 {
	//		jsval attrValue = ToJS(cx, wxPG_ATTR_HINT);
	//		wxString attr((const char *)"HINT");
	//		JS_SetUCProperty(cx, attrObj, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
	//	 }
	//}

    return true;
}

bool zzzJs::gui::gdi::InitObject(JSContext *cx, JSObject *global)
{
//	XmlDocument::define_Class(cx, global);
//    XmlNode::define_Class(cx, global);
    return true;
}

void zzzJs::gui::gdi::Destroy()
{
}

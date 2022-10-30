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

#include <jsapi.h>

#include "js/xml/zzzjs_xml_init.h"
#include "js/xml/xml_doc.h"
#include "js/xml/xml_node.h"

using namespace zzzJs::wxxml;
using namespace zzzJs::xml;




JSConstDoubleSpec wxXmlNodeTypeMap[] = 
{
	WXJS_CONSTANT(wxXML_, ELEMENT_NODE)
	WXJS_CONSTANT(wxXML_, ATTRIBUTE_NODE)
	WXJS_CONSTANT(wxXML_, TEXT_NODE)
	WXJS_CONSTANT(wxXML_, CDATA_SECTION_NODE)
	WXJS_CONSTANT(wxXML_, ENTITY_REF_NODE)
	WXJS_CONSTANT(wxXML_, ENTITY_NODE)
	WXJS_CONSTANT(wxXML_, PI_NODE)
	WXJS_CONSTANT(wxXML_, COMMENT_NODE)
	WXJS_CONSTANT(wxXML_, DOCUMENT_NODE)
	WXJS_CONSTANT(wxXML_, DOCUMENT_TYPE_NODE)
	WXJS_CONSTANT(wxXML_, DOCUMENT_FRAG_NODE)
	WXJS_CONSTANT(wxXML_, NOTATION_NODE)
	WXJS_CONSTANT(wxXML_, HTML_DOCUMENT_NODE)
	{ 0 }
};

bool zzzJs::wxxml::InitClass(JSContext *cx, JSObject *global)
{
    JSObject *namespaceObj = JS_DefineObject(cx, global, "xml", NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	
	// Constant‚Ì’è‹`
	JS_DefineConstDoubles(cx, namespaceObj, wxXmlNodeTypeMap);


	XmlDocument::define_Class(cx, namespaceObj);
    XmlNode::define_Class(cx, namespaceObj);
    return true;
}

bool zzzJs::wxxml::InitObject(JSContext *cx, JSObject *global)
{
	XmlDocument::define_Class(cx, global);
    XmlNode::define_Class(cx, global);
    return true;
}

void zzzJs::wxxml::Destroy()
{
}

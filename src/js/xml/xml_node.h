/*
 * wxJavaScript - dir.h
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
 * $Id: dir.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WX_XML_NODE_H
#define _WX_XML_NODE_H

#include "js/common/apiwrap.h"
/////////////////////////////////////////////////////////////////////////////
// Name:        dir.h
// Purpose:     wxJSDir ports wxDir to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     27.09.2002
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

#include <wx/xml/xml.h>

namespace zzzJs
{
    namespace xml
    {

        class XmlNode : public ApiWrapper<XmlNode, wxXmlNode>
        {
        public:
            /**
             * Callback for retrieving properties of wxDir
             */
			WXJS_DECLARE_GET_PROP(wxXmlNode)
            //static bool GetProperty(wxDir *p, 
            //                      JSContext *cx, 
            //                      JSObject *obj, 
            //                      int id, 
            //                      JS::MutableHandle<JS::Value>& vp);

            /**
             * Callback for when a wxDir object is created
             */
			WXJS_DECLARE_CONSTRUCTOR(wxXmlNode)
			WXJS_DECLARE_DESTRUCTOR(wxXmlNode)
			//  static wxDir* Construct(JSContext *cx, 
									//unsigned int argc, 
									//JS::Value *vp, 
									//bool constructing);

			WXJS_DECLARE_METHOD(addChild)
			WXJS_DECLARE_METHOD(insertChild)
			WXJS_DECLARE_METHOD(insertChildAfter)
			WXJS_DECLARE_METHOD(removeChild)
			WXJS_DECLARE_METHOD(addAttribute)
			WXJS_DECLARE_METHOD(deleteAttribute)
			WXJS_DECLARE_METHOD(getAttribute)
	

			WXJS_DECLARE_PROPERTY_MAP()
//			WXJS_DECLARE_CONSTANT_MAP()
			WXJS_DECLARE_METHOD_MAP()
//			WXJS_DECLARE_STATIC_METHOD_MAP()

            /**
             * Property Ids.
             */
            enum
            {
				  P_TYPE
				, p_NAME
				, P_CONTENT
				, P_NODE_CONTENT
				, P_PARENT
				, P_NEXT
				, P_CHILDREN
				, P_ATTRIBUTES
				, P_LINE_NO
				, P_ELEMENTS
            };
        };
    }; // namespace io
}; // namespace wxjs
#endif //_WX_XML_NODE_H


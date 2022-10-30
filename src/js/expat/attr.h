/*
 * wxJavaScript - attr.h
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
 * $Id: attr.h 607 2007-03-12 21:41:14Z fbraem $
 */
#ifndef _wxjs_xml_attr_h
#define _wxjs_xml_attr_h

/////////////////////////////////////////////////////////////////////////////
// Name:        attr.h
// Module:      wxJS_xml
// Purpose:		Implements the XMLAttr object
// Author:      Franky Braem
// Modified by:
// Created:     17.04.02
// Copyright:   (c) 2003- Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace xml
    {

        class Attr : public ApiWrapper<Attr, Attr>
        {
        public:
            Attr();
			
			WXJS_DECLARE_CONSTRUCTOR(Attr)
			WXJS_DECLARE_DESTRUCTOR(Attr)
            //static Attr* Construct(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, bool constructing);
            //static void Destruct(JSContext *cx, Attr *p);
			//static void Destruct(Attr *p);
        };
    }; // namespace xml
}; // namespace wxjs
#endif //_wxjs_xml_attr_h

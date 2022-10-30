/*
 * wxJavaScript - attr.cpp
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
 * $Id: attr.cpp 644 2007-03-27 20:31:33Z fbraem $
 */
// attr.cpp
#include "precompile.h"


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/expat/attr.h"

using namespace zzzJs;
using namespace zzzJs::xml;

/***
 * <file>xmlattr</file>
 * <module>expat</module>
 * <class name="expat.Attr">
 *  expat.Attr is used together with @expat.Parser#onStartElement.
 *  expat.Attr gets his properties at run-time.
 *  For example:
 *  <pre>
 *   &lt;tag1 attr="1" attr2="2" /&gt;</pre>
 *  Will result in a expat.Attr object that has <strong>attr</strong> 
 *  and <strong>attr2</strong> as properties.
 *  An easy way of processing all the attributes of a tag is done as follows:
 *  <pre><code class="whjs">
 *   var p = new expat.Parser();
 *
 *   p.onStartElement = function(element, attrs)
 *   {
 *      for(attr in attrs)
 *      {
 *         // attr contains the name of the attribute
 *         var attrValue = attrs[attr];
 *      }
 *   }
 *  </code></pre>
 * </class>
 */
Attr::Attr()
{
}

WXJS_INIT_CLASS(Attr, "XMLAttr", 0)

//Attr* Attr::Construct(JSContext* WXUNUSED(cx), JSObject* WXUNUSED(obj), uintN WXUNUSED(argc), jsval* WXUNUSED(argv), bool WXUNUSED(constructing))
WXJS_BEGIN_CONSTRUCTOR(Attr, Attr)
    return new Attr();
WXJS_END_CONSTRUCTOR

//void Attr::Destruct(JSContext* WXUNUSED(cx), Attr *p)
WXJS_BEGIN_DESTRUCTOR(Attr, Attr)
    delete p;
    p = NULL;
WXJS_END_DESTRUCTOR


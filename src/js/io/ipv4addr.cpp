/*
 * wxJavaScript - ipv4addr.cpp
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
 * $Id: ipv4addr.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/protocol/http.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/jsutil.h"
#include "js/io/ipv4addr.h"
#include "js/io/ipaddr.h"




using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>ipv4addr</file>
 * <module>io</module>
 * <class name="wxIPV4address" prototype="@wxIPaddress" version="0.8.4">
 *  Implements the IPV4 of the internet protocal.
 * </class>
 */
ZZZJS_INIT_CLASS(IPV4address, "IPV4address", 0)
	
ZZZJS_BEGIN_GET_SET_STR_PROP(wxIPV4address, IPV4address)
	IPaddress::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP

//wxIPV4address* IPV4address::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
ZZZJS_BEGIN_CONSTRUCTOR(wxIPV4address, IPV4address)
	return new wxIPV4address();
ZZZJS_END_CONSTRUCTOR

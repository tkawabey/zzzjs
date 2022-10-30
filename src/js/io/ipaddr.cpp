/*
 * wxJavaScript - ipaddr.cpp
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
 * $Id: ipaddr.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/io/ipaddr.h"
#include "js/io/sockaddr.h"


using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>ipaddr</file>
 * <module>io</module>
 * <class name="wxIPaddress" prototype="@wxSockAddress" version="0.8.4">
 *  wxIPaddress is an prototype class for all internet protocol address objects. 
 *  Currently, only @wxIPV4address is implemented.
 * </class>
 */
ZZZJS_INIT_CLASS(IPaddress, "IPaddress", 0)

/***
 * <properties>
 *  <property name="hostname" type=ZZZJS_TYPE_STRING>
 *   Get/Set the hostname.
 *  </property>
 *  <property name="IPAddress" type=ZZZJS_TYPE_STRING readonly="Y">
 *   Returns a string containing the IP address.
 *  </property>
 *  <property name="localhost" type="Boolean" readonly="Y">
 *   Returns true when the hostname is localhost.
 *  </property>
 *  <property name="service" type=ZZZJS_TYPE_NUMBER>
 *   Get/Set the current service.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(IPaddress)
	ZZZJS_PROPERTY(P_HOSTNAME, "hostname")
	ZZZJS_READONLY_PROPERTY(P_IPADDRESS, "IPAddress")
	ZZZJS_READONLY_PROPERTY(P_LOCALHOST, "localhost")
	ZZZJS_PROPERTY(P_SERVICE, "service")
ZZZJS_END_PROPERTY_MAP()

bool IPaddress::GetProperty(wxIPaddress *p,
                                  JSContext *cx, 
                                  JSObject *obj, 
                                  int id, 
                                  JS::MutableHandle<JS::Value>& vp)
{
	switch(id)
	{
	case P_HOSTNAME:
		ToJSVal(cx, vp, p->Hostname());
		break;
	case P_IPADDRESS:
		ToJSVal(cx, vp, p->IPAddress());
		break;
	case P_LOCALHOST:
		ToJSVal(cx, vp, p->IsLocalHost());
		break;
	case P_SERVICE:
		ToJSVal<int>(cx, vp, p->Service());
		break;
	default:
		vp.setNull();
//		*vp = JSVAL_VOID;
	}
    return true;
}

bool IPaddress::SetProperty(wxIPaddress *p, 
                                  JSContext *cx, 
                                  JSObject *obj, 
                                  int id, 
                                  JS::MutableHandle<JS::Value>& vp)
{
	switch(id)
	{
	case P_HOSTNAME:
		{
			wxString hostname;
			FromJS(cx, vp, hostname);
			p->Hostname(hostname);
			break;
		}
	case P_SERVICE:
		{
			int service;
			if ( FromJS(cx, vp, service) )
				p->Service(service);
			break;
		}
	}
    return true;
}

ZZZJS_BEGIN_GET_SET_STR_PROP(wxIPaddress, IPaddress)
	SockAddress::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP



ZZZJS_BEGIN_METHOD_MAP(IPaddress)
	ZZZJS_METHOD("anyAddress", anyAddress, 0)
	ZZZJS_METHOD("localhost", localhost, 0)
ZZZJS_END_METHOD_MAP()

/***
 * <method name="anyAddress">
 *  <function returns="Boolean" />
 *  <desc>
 *   Internally, this is the same as setting the IP address to INADDR_ANY.
 *   Returns true on success, false if something went wrong.
 *  </desc>
 * </method>
 */
JSBool IPaddress::anyAddress(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxIPaddress *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxIPaddress"));

	*vp = ToJS(cx, p->AnyAddress());

	return JS_TRUE;
}

/***
 * <method name="localhost">
 *  <function returns="Boolean" />
 *  <desc>
 *   Set the address to localhost.
 *   Returns true on success, false if something went wrong.
 *  </desc>
 * </method>
 */
JSBool IPaddress::localhost(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	wxIPaddress *p = GetPrivate(cx, obj);
	wxASSERT_MSG(p != NULL, wxT("No private data associated with wxIPaddress"));

	*vp = ToJS(cx, p->LocalHost());

	return JS_TRUE;
}

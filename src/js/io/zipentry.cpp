/*
 * wxJavaScript - zipentry.cpp
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
 * $Id: zipentry.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
#include "precompile.h"
#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif
#include <wx/archive.h>

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/common/index.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/ext/jsmembuf.h"
#include "js/io/zipentry.h"
#include "js/io/archentry.h"


using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>zipentry</file>
 * <module>io</module>
 * <class name="wxZipEntry" prototype="@wxArchiveEntry" version="0.8.3">
 *  Holds the meta-data for an entry in a zip.
 * </class>
 */

ZZZJS_INIT_CLASS(ZipEntry, "ZipEntry", 0)

/***
 * <constants>
 *  <type name="wxZipMethod">
 *   <constant name="STORE" />
 *   <constant name="SHRINK" />
 *   <constant name="REDUCE1" />
 *   <constant name="REDUCE2" />
 *   <constant name="REDUCE3" />
 *   <constant name="REDUCE4" />
 *   <constant name="IMPLODE" />
 *   <constant name="TOKENIZE" />
 *   <constant name="DEFLATE" />
 *   <constant name="DEFLATE64" />
 *   <constant name="BZIP2" />
 *   <constant name="DEFAULT" />
 *   <desc>
 *    Compression Mode. wxZipMethod is ported as a separate JavaScript class.
 *   </desc>
 *  </type>
 *  <type name="wxZipSystem">
 *   <constant name="MSDOS" />
 *   <constant name="AMIGA" />
 *   <constant name="OPENVMS" />
 *   <constant name="UNIX" />
 *   <constant name="VM_CMS" />
 *   <constant name="ATARI_ST" />
 *   <constant name="OS2_HPFS" />
 *   <constant name="MACINTOSH" />
 *   <constant name="Z_SYSTEM" />
 *   <constant name="CPM" />
 *   <constant name="WINDOWS_NTFS" />
 *   <constant name="MVS" />
 *   <constant name="VSE" />
 *   <constant name="ACORN_RISC" />
 *   <constant name="VFAT" />
 *   <constant name="ALTERNATE_MVS" />
 *   <constant name="BEOS" />
 *   <constant name="TANDEM" />
 *   <constant name="OS_400" />
 *   <desc>
 *    Originating File-System. wxZipSystem is ported as a separate JavaScript object.
 *   </desc>
 *  </type>
 *  <type name="wxZipAttributes">
 *   <constant name="RDONLY" />
 *   <constant name="HIDDEN" />
 *   <constant name="SYSTEM" />
 *   <constant name="SUBDIR" />
 *   <constant name="ARCH" />
 *   <constant name="MASK" />
 *   <desc>
 *    wxZipAttributes is ported as a separate JavaScript object
 *   </desc>
 *  </type>
 *  <type name="wxZipFlags">
 *   <constant name="ENCRYPTED" />
 *   <constant name="DEFLATE_NORMAL" />
 *   <constant name="DEFLATE_EXTRA" />
 *   <constant name="DEFLATE_FAST" />
 *   <constant name="DEFLATE_SUPERFAST" />
 *   <constant name="DEFLATE_MASK" />
 *   <constant name="SUMS_FOLLOW" />
 *   <constant name="ENHANCED" />
 *   <constant name="PATCH" />
 *   <constant name="STRONG_ENC" />
 *   <constant name="UNUSED" />
 *   <constant name="RESERVED" />
 *   <desc>
 *    wxZipFlags is ported as a separate JavaScript object.
 *   </desc>
 *  </type>
 *
 * </constants>
 */
void ZipEntry::InitClass(JSContext *cx, JSObject *obj, JSObject *proto)
{
    JSConstDoubleSpec wxZipMethodMap[] = 
    {
		ZZZJS_CONSTANT(wxZIP_METHOD_, STORE)
		ZZZJS_CONSTANT(wxZIP_METHOD_, SHRINK)
		ZZZJS_CONSTANT(wxZIP_METHOD_, REDUCE1)
		ZZZJS_CONSTANT(wxZIP_METHOD_, REDUCE2)
		ZZZJS_CONSTANT(wxZIP_METHOD_, REDUCE3)
		ZZZJS_CONSTANT(wxZIP_METHOD_, REDUCE4)
		ZZZJS_CONSTANT(wxZIP_METHOD_, IMPLODE)
		ZZZJS_CONSTANT(wxZIP_METHOD_, TOKENIZE)
		ZZZJS_CONSTANT(wxZIP_METHOD_, DEFLATE)
		ZZZJS_CONSTANT(wxZIP_METHOD_, DEFLATE64)
		ZZZJS_CONSTANT(wxZIP_METHOD_, BZIP2)
		ZZZJS_CONSTANT(wxZIP_METHOD_, DEFAULT)
	    { 0 }
    };

    JSObject *constObj = JS_DefineObject(cx, obj, "wxZipMethod", 
									 	 NULL, NULL,
							             JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineConstDoubles(cx, constObj, wxZipMethodMap);

    JSConstDoubleSpec wxZipSystemMap[] = 
    {
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, MSDOS)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, AMIGA)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, OPENVMS)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, UNIX)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, VM_CMS)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, ATARI_ST)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, OS2_HPFS)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, MACINTOSH)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, Z_SYSTEM)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, CPM)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, WINDOWS_NTFS)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, MVS)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, VSE)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, ACORN_RISC)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, VFAT)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, ALTERNATE_MVS)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, BEOS)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, TANDEM)
		ZZZJS_CONSTANT(wxZIP_SYSTEM_, OS_400)
	    { 0 }
    };

    constObj = JS_DefineObject(cx, obj, "wxZipSystem", 
						 	   NULL, NULL,
							   JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineConstDoubles(cx, constObj, wxZipSystemMap);

	JSConstDoubleSpec wxZipAttributes[] = 
    {
		ZZZJS_CONSTANT(wxZIP_A_, RDONLY)
		ZZZJS_CONSTANT(wxZIP_A_, HIDDEN)
		ZZZJS_CONSTANT(wxZIP_A_, SYSTEM)
		ZZZJS_CONSTANT(wxZIP_A_, SUBDIR)
		ZZZJS_CONSTANT(wxZIP_A_, ARCH)
		ZZZJS_CONSTANT(wxZIP_A_, MASK)
		{ 0 }
	};
    constObj = JS_DefineObject(cx, obj, "wxZipAttributes", 
						 	   NULL, NULL,
							   JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineConstDoubles(cx, constObj, wxZipAttributes);

	JSConstDoubleSpec wxZipFlags[] = 
    {
		ZZZJS_CONSTANT(wxZIP_, ENCRYPTED)
		ZZZJS_CONSTANT(wxZIP_, DEFLATE_NORMAL)
		ZZZJS_CONSTANT(wxZIP_, DEFLATE_EXTRA)
		ZZZJS_CONSTANT(wxZIP_, DEFLATE_FAST)
		ZZZJS_CONSTANT(wxZIP_, DEFLATE_SUPERFAST)
		ZZZJS_CONSTANT(wxZIP_, DEFLATE_MASK)
		ZZZJS_CONSTANT(wxZIP_, SUMS_FOLLOW)
		ZZZJS_CONSTANT(wxZIP_, ENHANCED)
		ZZZJS_CONSTANT(wxZIP_, PATCH)
		ZZZJS_CONSTANT(wxZIP_, STRONG_ENC)
		ZZZJS_CONSTANT(wxZIP_, UNUSED)
		ZZZJS_CONSTANT(wxZIP_, RESERVED)
		{ 0 }
	};
    constObj = JS_DefineObject(cx, obj, "wxZipFlags", 
						 	   NULL, NULL,
							   JSPROP_READONLY | JSPROP_PERMANENT);
    JS_DefineConstDoubles(cx, constObj, wxZipFlags);
}
 
ZZZJS_BEGIN_GET_SET_STR_PROP(wxZipEntry, ZipEntry)
	ArchiveEntry::SetStringProperty(p, cx,  obj, propertyName, vp);
	return true;
ZZZJS_END_GET_SET_STR_PROP
/***
 * <ctor>
 *  <function>
 *   <arg name="Name" type=ZZZJS_TYPE_STRING default="" />
 *   <arg name="Date" type="Date" default="Now()" />
 *   <arg name="Offset" type=ZZZJS_TYPE_NUMBER default="-1" />
 *  </function>
 *  <desc>
 *   Creates a new wxZipEntry
 *  </desc>
 * </ctor>
 */
//wxZipEntry* ZipEntry::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
ZZZJS_BEGIN_CONSTRUCTOR(wxZipEntry, ZipEntry)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

	off_t size = wxInvalidOffset;
	wxDateTime dt = wxDateTime::Now();
	wxString name = wxEmptyString;

	switch(argc)
	{
	case 3:
		if ( ! FromJS(cx, argv[2], size) )
			return NULL;
		// Fall through
	case 2:
		if ( ! FromJS(cx, argv[1], dt) )
			return NULL;
		// Fall through
	case 1:
		FromJS(cx, argv[0], name);
		break;
	}

	wxZipEntry* entry = new wxZipEntry(name, dt, size);
	entry->SetMethod(wxZIP_METHOD_DEFAULT);
	return entry;
ZZZJS_END_CONSTRUCTOR


/***
 * <properties>
 *  <property name="comment" type=ZZZJS_TYPE_STRING>
 *   Get/Set a short comment for this entry.
 *  </property>
 *  <property name="compressedSize" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   The compressed size of this entry in bytes.
 *  </property>
 *  <property name="crc" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   CRC32 for this entry's data.
 *  </property>
 *  <property name="externalAttributes" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   Attributes of the entry. See @wxZipEntry#wxZipAttributes.
 *  </property>
 *  <property name="extra" type=ZZZJS_TYPE_STRING>
 *   The extra field is used to store platform or application specific data. 
 *   See Pkware's document 'appnote.txt' for information on its format.
 *  </property>
 *  <property name="flags" type=ZZZJS_TYPE_NUMBER readonly="Y">
 *   see @wxZipEntry#wxZipFlags
 *  </property>
 *  <property name="localExtra" type=ZZZJS_TYPE_STRING>
 *   The extra field is used to store platform or application specific data. 
 *   See Pkware's document 'appnote.txt' for information on its format. 
 *  </property>
 *  <property name="method" type=ZZZJS_TYPE_NUMBER>
 *   The compression method. See @wxZipEntry#wxZipMethod.
 *  </property>
 *  <property name="mode" type=ZZZJS_TYPE_NUMBER />
 *  <property name="systemMadeBy" type=ZZZJS_TYPE_NUMBER>
 *   The originating file-system. The default constructor sets this to 
 *   wxZipSystem.MSDOS. Set it to wxZipSystem.UNIX in order to be able
 *   to store unix permissions using @wxZipEntry#mode.
 *  </property>
 *  <property name="madeByUnix" type="Boolean" readonly="Y">
 *   Returns true if @wxZipEntry#systemMadeBy is a flavour of unix.
 *  </property>
 *  <property name="text" type="Boolean">
 *   Indicates that this entry's data is text in an 8-bit encoding.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(ZipEntry)
	ZZZJS_PROPERTY(P_COMMENT, "comment")
	ZZZJS_READONLY_PROPERTY(P_COMPRESSED_SIZE, "compressedSize")
	ZZZJS_READONLY_PROPERTY(P_CRC, "crc")
	ZZZJS_READONLY_PROPERTY(P_EXTERNAL_ATTR, "externalAttributes")
	ZZZJS_PROPERTY(P_EXTRA, "extra")
	ZZZJS_READONLY_PROPERTY(P_FLAGS, "flags")
	ZZZJS_PROPERTY(P_LOCAL_EXTRA, "localExtra")
	ZZZJS_PROPERTY(P_MODE, "mode")
	ZZZJS_PROPERTY(P_METHOD, "method")
	ZZZJS_PROPERTY(P_SYSTEM_MADE_BY, "systemMadeBy")
	ZZZJS_READONLY_PROPERTY(P_MADE_BY_UNIX, "madeByUnix")
	ZZZJS_PROPERTY(P_TEXT, "text")
ZZZJS_END_PROPERTY_MAP()

//bool ZipEntry::GetProperty(wxZipEntry *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxZipEntry, ZipEntry)
    switch (id)
    {
	case P_COMMENT:
		ToJSVal(cx, vp, p->GetComment());
		break;
	case P_COMPRESSED_SIZE:
		ToJSVal<long>(cx, vp, p->GetCompressedSize());
		break;
	case P_CRC:
		ToJSVal(cx, vp, p->GetCrc());
		break;
	case P_EXTERNAL_ATTR:
		ToJSVal(cx, vp, p->GetExternalAttributes());
		break;
	case P_EXTRA:
		ToJSVal(cx, vp, wxString::FromAscii(p->GetExtra()));
		break;
	case P_FLAGS:
		ToJSVal(cx, vp, p->GetFlags());
		break;
	case P_LOCAL_EXTRA:
		ToJSVal(cx, vp, wxString::FromAscii(p->GetLocalExtra()));
		break;
	case P_METHOD:
		ToJSVal(cx, vp, p->GetMethod());
		break;
	case P_MODE:
		ToJSVal(cx, vp, p->GetMode());
		break;
	case P_SYSTEM_MADE_BY:
		ToJSVal(cx, vp, p->GetSystemMadeBy());
		break;
	case P_MADE_BY_UNIX:
		ToJSVal(cx, vp, p->IsMadeByUnix());
		break;
	case P_TEXT:
		ToJSVal(cx, vp, p->IsText());
		break;
    }
    return true;
ZZZJS_END_GET_PROP

//bool ZipEntry::SetProperty(wxZipEntry *p,  
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_SET_PROP(wxZipEntry, ZipEntry)
    switch (id)
    {
	case P_EXTRA:
		{
			wxString extra;
			FromJS(cx, vp, extra);
			p->SetExtra(extra.ToAscii(), extra.Length());
		}
		break;
	case P_LOCAL_EXTRA:
		{
			wxString extra;
			FromJS(cx, vp, extra);
			p->SetLocalExtra(extra.ToAscii(), extra.Length());
		}
		break;
	case P_MODE:
		{
			int mode;
			if ( FromJS(cx, vp, mode) )
			{
				p->SetMode(mode);
			}
			break;
		}
	case P_METHOD:
		{
			int method;
			if ( FromJS(cx, vp, method) )
			{
				p->SetMethod(method);
			}
		}
	case P_SYSTEM_MADE_BY:
		{
			int madeBy;
			if ( FromJS(cx, vp, madeBy) )
			{
				p->SetSystemMadeBy(madeBy);
			}
			break;
		}
	case P_TEXT:
		{
			bool text;
			if ( FromJS(cx, vp, text) )
			{
				p->SetIsText(text);
			}
			break;
		}
    }
	return true;
ZZZJS_END_SET_PROP

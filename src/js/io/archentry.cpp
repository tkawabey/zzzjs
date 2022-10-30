/*
 * wxJavaScript - archentry.cpp
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
 * $Id: archentry.cpp 598 2007-03-07 20:13:28Z fbraem $
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
#include "js/io/archentry.h"

using namespace zzzJs;
using namespace zzzJs::io;

/***
 * <file>archentry</file>
 * <module>io</module>
 * <class name="wxArchiveEntry" version="0.8.3">
 *  A prototype class used for entries in an archive.
 * </class>
 */

ZZZJS_INIT_CLASS(ArchiveEntry, "ArchiveEntry", 0)

/***
 * <properties>
 *  <property name="dateTime" type="Date">
 *   Get/Set the timestamp of the entryset
 *  </property>
 *  <property name="internalFormat" type="@wxFileName#wxPathFormat" readonly="Y">
 *   Returns the path format used internally within the archive to store filenames.
 *  </property>
 *  <property name="internalName" type=WXJS_TYPE_STRING readonly="Y">
 *   Returns the entry's filename in the internal format used within the archive. 
 *   The name can include directory components, i.e. it can be a full path.
 *   <br /><br />
 *   The names of directory entries are returned without any trailing path separator. 
 *   This gives a canonical name that can be used in comparisons.
 *  </property>
 *  <property name="dir" type="Boolean">
 *   True if this is a directory entry.
 *   <br /><br />
 *   Directory entries are entries with no data, which are used to store the
 *   meta-data of directories. They also make it possible for completely empty 
 *   directories to be stored.
 *   <br /><br />
 *   The names of entries within an archive can be complete paths, and unarchivers 
 *   typically create whatever directories are necessary as they restore files, 
 *   even if the archive contains no explicit directory entries.
 *  </property>
 *  <property name="readOnly" type="Boolean">
 *   True if the entry is a read-only file.
 *  </property>
 *  <property name="offset" type=WXJS_TYPE_NUMBER readonly="Y">
 *   Returns a numeric value unique to the entry within the archive.
 *  </property>
 *  <property name="size" type=WXJS_TYPE_NUMBER>
 *   Get/Set the size of the entry's data in bytes.
 *  </property>
 * </properties>
 */
ZZZJS_BEGIN_PROPERTY_MAP(ArchiveEntry)
	ZZZJS_PROPERTY(P_DATE_TIME, "dateTime")
	ZZZJS_READONLY_PROPERTY(P_INTERNAL_FMT, "internalFormat")
	ZZZJS_READONLY_PROPERTY(P_INTERNAL_NAME, "internalName")
	ZZZJS_PROPERTY(P_DIR, "dir")
	ZZZJS_PROPERTY(P_READ_ONLY, "readOnly")
	ZZZJS_PROPERTY(P_NAME, "name")
	ZZZJS_READONLY_PROPERTY(P_OFFSET, "offset")
	ZZZJS_PROPERTY(P_SIZE, "size")
ZZZJS_END_PROPERTY_MAP()

//bool ArchiveEntry::GetProperty(wxArchiveEntry *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_GET_PROP(wxArchiveEntry, ArchiveEntry)
    switch (id)
    {
    case P_DATE_TIME:
		ToJSVal(cx, vp, p->GetDateTime());
        break;
	case P_INTERNAL_FMT:
		ToJSVal<int>(cx, vp, p->GetInternalFormat());
        break;
	case P_INTERNAL_NAME:
		ToJSVal(cx, vp,  p->GetInternalName());
        break;
	case P_DIR:
		ToJSVal(cx, vp,  p->IsDir());
        break;
	case P_READ_ONLY:
		ToJSVal(cx, vp,  p->IsReadOnly());
		break;
	case P_NAME:
		ToJSVal(cx, vp,  p->GetName());
		break;
	case P_OFFSET:
		ToJSVal<long>(cx, vp, p->GetOffset());
		break;
	case P_SIZE:
		ToJSVal<long>(cx, vp, p->GetSize());
		break;
    }
    return true;
ZZZJS_END_GET_PROP

//bool ArchiveEntry::SetProperty(wxArchiveEntry *p, 
//                                  JSContext *cx, 
//                                  JSObject *obj, 
//                                  int id, 
//                                  JS::MutableHandle<JS::Value>& vp)
//{
ZZZJS_BEGIN_SET_PROP(wxArchiveEntry, ArchiveEntry)
    switch (id)
    {
    case P_DATE_TIME:
		{
			wxDateTime date;
			if ( FromJS(cx, vp, date) )
				p->SetDateTime(date);
		}
		break;
	case P_DIR:
		{
			bool dir;
			if ( FromJS(cx, vp, dir) )
				p->SetIsDir(dir);
		}
		break;
	case P_READ_ONLY:
		{
			bool readonly;
			if ( FromJS(cx, vp, readonly) )
				p->SetIsReadOnly(readonly);
		}
		break;
	case P_NAME:
		{
			wxString name;
			FromJS(cx, vp, name);
			p->SetName(name);
		}
		break;
	case P_SIZE:
		{
			long size;
			if ( FromJS(cx, vp, size) )
			{
				p->SetSize(size);
			}
		}
		break;
    }
	return true;
ZZZJS_END_SET_PROP

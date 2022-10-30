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
 * $Id: init.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// main.cpp
#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 
#include <wx/setup.h>


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

#include "js/common/index.h"
#include "js/common/jsutil.h"


#include "js/io/init.h"
#include "js/io/constant.h"
#include "js/io/file.h"
#include "js/io/ffile.h"
#include "js/io/dir.h"
#include "js/io/dirtrav.h"
#include "js/io/stream.h"
#include "js/io/istream.h"
#include "js/io/ostream.h"
#include "js/io/fistream.h"
#include "js/io/fostream.h"
#include "js/io/ffistream.h"
#include "js/io/ffostream.h"
#include "js/io/costream.h"
#include "js/io/mistream.h"
#include "js/io/mostream.h"
#include "js/io/bostream.h"
#include "js/io/bistream.h"
#include "js/io/tistream.h"
#include "js/io/tostream.h"
#include "js/io/filename.h"
#include "js/io/aistream.h"
#include "js/io/archentry.h"
#include "js/io/zipentry.h"
#include "js/io/zistream.h"
#include "js/io/aostream.h"
#include "js/io/zostream.h"
#include "js/io/tempfile.h"
#include "js/io/textfile.h"
#include "js/io/textline.h"
#include "js/io/distream.h"
#include "js/io/dostream.h"
#include "js/io/sockaddr.h"
#include "js/io/sockbase.h"
#include "js/io/sockclient.h"
#include "js/io/socksrv.h"
#include "js/io/sostream.h"
#include "js/io/sistream.h"
#include "js/io/ipaddr.h"
#include "js/io/ipv4addr.h"
#include "js/io/protocol.h"
#include "js/io/uri.h"
#include "js/io/url.h"
#include "js/io/http.h"
#include "js/io/httphdr.h"
#include "js/io/sound.h"
#include "js/io/fn.h"
#include "js/io/process.h"

using namespace zzzJs;

bool io::InitClass(JSContext *cx, JSObject *global)
{
    InitConstants(cx, global);

	JSObject *obj = File::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("wxFile prototype creation failed"));
	if (! obj )
		return false;

	obj = FFile::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("wxFFile prototype creation failed"));
	if (! obj )
		return false;

    obj = TempFile::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("wxTempFile prototype creation failed"));
	if (! obj )
		return false;

	obj = Dir::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("wxDir prototype creation failed"));
	if (! obj )
		return false;

	obj = DirTraverser::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("wxDirTraverser prototype creation failed"));
	if (! obj )
		return false;

	obj = StreamBase::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("wxStreamBase prototype creation failed"));
	if (! obj )
		return false;

	obj = InputStream::define_Class(cx, global, StreamBase::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxInputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = BufferedInputStream::define_Class(cx, global, InputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxBufferedInputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = OutputStream::define_Class(cx, global, StreamBase::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxOutputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = BufferedOutputStream::define_Class(cx, global, OutputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxBufferedOutputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = CountingOutputStream::define_Class(cx, global, OutputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxCountingOutputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = FileInputStream::define_Class(cx, global, InputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxFileInputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = FileOutputStream::define_Class(cx, global, OutputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxFileOutputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = MemoryInputStream::define_Class(cx, global, InputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxMemoryInputStream prototype creation failed"));
	if (! obj )
		return false;

    obj = MemoryOutputStream::define_Class(cx, global, OutputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxMemoryOutputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = TextInputStream::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxTextInputStream prototype creation failed"));
	if (! obj )
		return false;

    obj = TextOutputStream::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxTextOutputStream prototype creation failed"));
	if (! obj )
		return false;

    obj = FileName::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxFileName prototype creation failed"));
	if (! obj )
		return false;

	obj = ArchiveInputStream::define_Class(cx, global, InputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxArchiveInputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = ArchiveOutputStream::define_Class(cx, global, OutputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxArchiveOutputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = ArchiveEntry::define_Class(cx, global, NULL);
	wxASSERT_MSG(obj != NULL, wxT("wxArchiveEntry prototype creation failed"));
	if (! obj )
		return false;

	obj = ZipEntry::define_Class(cx, global, ArchiveEntry::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxZipEntry prototype creation failed"));
	if (! obj )
		return false;

	obj = ZipInputStream::define_Class(cx, global, ArchiveInputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxZipInputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = ZipOutputStream::define_Class(cx, global, ArchiveOutputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxZipOutputStream"));
	if (! obj )
		return false;

	obj = TextFile::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxTextFile"));
	if (! obj )
		return false;

	obj = TextLine::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxTextLine"));
	if (! obj )
		return false;

	obj = DataInputStream::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxDataInputStream prototype creation failed"));
	if (! obj )
		return false;

    obj = DataOutputStream::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxDataOutputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = SocketBase::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxSocketBase prototype creation failed"));
	if (! obj )
		return false;

	obj = SockAddress::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxSocketAddr prototype creation failed"));
	if (! obj )
		return false;

	obj = SocketClient::define_Class(cx, global, SocketBase::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSocketClient prototype creation failed"));
	if (! obj )
		return false;

	obj = SocketServer::define_Class(cx, global, SocketBase::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSocketServer prototype creation failed"));
	if (! obj )
		return false;

	obj = SocketInputStream::define_Class(cx, global, InputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSocketInputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = SocketOutputStream::define_Class(cx, global, OutputStream::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxSocketOutputStream prototype creation failed"));
	if (! obj )
		return false;

	obj = IPaddress::define_Class(cx, global, SockAddress::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxIPaddress prototype creation failed"));
	if (! obj )
		return false;

	obj = IPV4address::define_Class(cx, global, IPaddress::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxIPV4address prototype creation failed"));
	if (! obj )
		return false;

	obj = Protocol::define_Class(cx, global, SocketClient::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxProtocol prototype creation failed"));
	if (! obj )
		return false;

	obj = URI::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxURI prototype creation failed"));
	if (! obj )
		return false;

	obj = HTTP::define_Class(cx, global, Protocol::GetClassPrototype());
	wxASSERT_MSG(obj != NULL, wxT("wxHTTP prototype creation failed"));
	if (! obj )
		return false;

	obj = HTTPHeader::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxHTTPHeader prototype creation failed"));
	if (! obj )
		return false;

	obj = URL::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxURL prototype creation failed"));
	if (! obj )
		return false;

	obj = Sound::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxSound prototype creation failed"));
	if (! obj )
		return false;

    obj = Process::define_Class(cx, global);
	wxASSERT_MSG(obj != NULL, wxT("wxProcess prototype creation failed"));
	if (! obj )
		return false;

	JS_DefineFunction(cx, global, "wxConcatFiles", concatFiles, 3, 0);
	JS_DefineFunction(cx, global, "wxCopyFile", copyFile, 2, 0);
	JS_DefineFunction(cx, global, "wxFileExists", fileExists, 1, 0);
	JS_DefineFunction(cx, global, "wxRenameFile", renameFile, 2, 0);
	JS_DefineFunction(cx, global, "wxGetCwd", getCwd, 0, 0);
	JS_DefineFunction(cx, global, "wxGetFreeDiskSpace", getFreeDiskSpace, 1, 0);
	JS_DefineFunction(cx, global, "wxGetTotalDiskSpace", getTotalDiskSpace, 1, 0);
	JS_DefineFunction(cx, global, "wxGetOSDirectory", getOSDirectory, 0, 0);
	JS_DefineFunction(cx, global, "wxIsAbsolutePath", isAbsolutePath, 1, 0);
	JS_DefineFunction(cx, global, "wxIsWild", isWild, 1, 0);
	JS_DefineFunction(cx, global, "wxDirExists", dirExists, 1, 0);
	JS_DefineFunction(cx, global, "wxMatchWild", matchWild, 3, 0);
	JS_DefineFunction(cx, global, "wxMkDir", mkDir, 2, 0);
	JS_DefineFunction(cx, global, "wxRemoveFile", removeFile, 1, 0);
	JS_DefineFunction(cx, global, "wxRmDir", rmDir, 1, 0);
	JS_DefineFunction(cx, global, "wxSetWorkingDirectory", setWorkingDirectory, 1, 0);
    JS_DefineFunction(cx, global, "wxExecute", execute, 1, 0);
    JS_DefineFunction(cx, global, "wxShell", shell, 1, 0);

	return true;
}

bool io::InitObject(JSContext *cx, JSObject *obj)
{
    return true;
}

void io::Destroy()
{
}

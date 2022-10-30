/*
 * wxJavaScript - dir.cpp
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
 * $Id: dir.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
// wxJSDir.cpp
#include "precompile.h"

#ifdef _MSC_VER
	#pragma warning(disable:4800)
#endif 


#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/xml/xml_doc.h"
#include "js/xml/xml_node.h"
#include "js/gui/errors.h"
#include "js/common/jsutil.h"

#include "js/io/stream.h"
#include "js/io/ostream.h"
#include "js/io/istream.h"

using namespace zzzJs;
using namespace zzzJs::xml;
using namespace zzzJs::io;

/***
 * <file>dir</file>
 * <module>io</module>
 * <class name="wxDir">
 *  wxDir is a portable equivalent of Unix open/read/closedir functions which allow 
 *  enumerating of the files in a directory. wxDir can enumerate files as well as directories.
 *  <br /><br />
 *  The following example checks if the temp-directory exists,
 *  and when it does, it retrieves all files with ".tmp" as extension.
 *  <pre><code class="whjs">
 *   if ( wxDir.exists("c:\\temp") )
 *   {
 *     files = wxDir.getAllFiles("c:\\temp", "*.tmp");
 *     for(e in files)
 *       wxMessageBox(files[e]);
 *   }
 *  </code></pre>
 *  See also @wxDirTraverser
 * </class>
 */
WXJS_INIT_CLASS(XmlDocument, "XmlDocument", 0)

/***
 * <constants>
 *  <type name="wxDirFlags">
 *   <constant name="FILES" />
 *   <constant name="DIRS" />
 *   <constant name="HIDDEN" />
 *   <constant name="DOTDOT" />
 *   <constant name="DEFAULT" />
 *   <desc>Constants used for filtering files. The default: FILES | DIRS | HIDDEN.</desc>
 *  </type>
 * </constants>
 */
/*
WXJS_BEGIN_CONSTANT_MAP(XmlDocument)
    WXJS_CONSTANT(wxDIR_, FILES)
    WXJS_CONSTANT(wxDIR_, DIRS)
    WXJS_CONSTANT(wxDIR_, HIDDEN)
    WXJS_CONSTANT(wxDIR_, DOTDOT)
    WXJS_CONSTANT(wxDIR_, DEFAULT)
WXJS_END_CONSTANT_MAP()
*/
/*
WXJS_BEGIN_STATIC_METHOD_MAP(XmlDocument)
    WXJS_METHOD("getAllFiles", getAllFiles, 1)
    WXJS_METHOD("exists", exists, 1)
WXJS_END_METHOD_MAP()
*/
/***
 * <class_method name="exists">
 *  <function returns="Boolean">
 *   <arg name="DirName" type=WXJS_TYPE_STRING />
 *  </function>
 *  <desc>
 *   Returns true when the directory exists.
 *  </desc>
 * </class_method>
 */
 /*
JSBool Dir::exists(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxString dir;
    FromJS(cx, argv[0], dir);

    *vp = ToJS(cx, wxDir::Exists(dir));
    return JS_TRUE;
}
*/


/***
 * <class_method name="getAllFiles">
 *  <function returns="String Array">
 *   <arg name="DirName" type=WXJS_TYPE_STRING />
 *   <arg name="FileSpec" type=WXJS_TYPE_STRING default="" />
 *   <arg name="Flags" type=WXJS_TYPE_NUMBER default="wxDir.FILES | wxDir.DIRS | wxDir.HIDDEN" />
 *  </function>
 *  <desc>
 *   This function returns an array of all filenames under directory <strong>DirName</strong>
 *   Only files matching <strong>FileSpec</strong> are taken. When an empty spec is given,
 *   all files are given.
 *   <br /><br />
 *   Remark: when wxDir.DIRS is specified in <strong>Flags</strong> then
 *   getAllFiles recurses into subdirectories. So be carefull when using this method
 *   on a root directory.
 *  </desc>
 * </class_method>
 */
 /*
JSBool Dir::getAllFiles(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    if ( argc > 3 )
        argc = 3;

    wxString filespec = wxEmptyString;
    int flags = wxDIR_DEFAULT;
    wxArrayString files;

    switch(argc)
    {
    case 3:
        if ( ! FromJS(cx, argv[2], flags) )
            return JS_FALSE;
        // Fall through
    case 2:
        FromJS(cx, argv[1], filespec);
        // Fall through
    default:
        wxString dir;
        FromJS(cx, argv[0], dir);

        wxArrayString files;
        wxDir::GetAllFiles(dir, &files, filespec, flags);

        *vp = ToJS(cx, files);
    }

    return JS_TRUE;
}
*/
/***
 * <ctor>
 *  <function>
 *   <arg name="Directory" type=WXJS_TYPE_STRING default="null">The name of the directory.</arg>
 *  </function>
 *  <desc>
 *   Constructs a new wxDir object. When no argument is specified, use @wxDir#open
 *   afterwards. When a directory is passed, use @wxDir#isOpened to test for errors.
 *  </desc>
 * </ctor>
 */
//wxDir* Dir::Construct(JSContext *cx, 
//					unsigned int argc, 
//					JS::Value *vp, 
//					bool constructing)
//{
//	JSObject *obj = JS_THIS_OBJECT(cx, vp);
WXJS_BEGIN_CONSTRUCTOR(wxXmlDocument, XmlDocument)
	JS::CallArgs argv = CallArgsFromVp(argc, vp);


	wxString	filename;
	wxInputStream *pStream = NULL;
	wxString	encoding = wxT("UTF-8");

    if ( argc == 0 )
        return new wxXmlDocument();

	if( argc > 2 ) {
		argc = 2;
	}
	if( argc == 2 ) {
		if ( ! FromJS(cx, argv[1], encoding) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
			return NULL;
		}
	}

	if( argv[0].isString() ) {
		if ( ! FromJS(cx, argv[0], filename) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
			return NULL;
		}
	} else 
	if ( zzzJs::HasPrototype(cx, argv[0], "InputStream") ) {

		io::Stream *stream = (io::Stream *) JS_GetPrivate(/*cx,*/ JSVAL_TO_OBJECT(argv[0]));
		if ( stream == NULL ) {
			return NULL;
		}
		pStream = dynamic_cast<wxInputStream *>(stream->GetStream());
		if ( pStream == NULL )
		{
			// TODO: error reporting
			return NULL;
		}
	}

	if( pStream != NULL ) {
		return new wxXmlDocument(*pStream, encoding);
	} else {
		return new wxXmlDocument(filename, encoding);
	}

    return NULL;
WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_DESTRUCTOR(wxXmlDocument, XmlDocument)
	if( p != NULL ) {
		delete p;
	}
WXJS_END_DESTRUCTOR



/***
 * <properties>
 *  <property name="opened" type="Boolean" readonly="Y">
 *   Returns true when the directory was opened by calling @wxDir#open.
 *  </property>
 *  <property name="name" type=WXJS_TYPE_STRING readonly="Y">
 *   Returns the name of the directory itself. The returned string 
 *   does not have the trailing path separator (slash or backslash).
 *  </property>
 * </properties>
 */
WXJS_BEGIN_PROPERTY_MAP(XmlDocument)
    WXJS_READONLY_PROPERTY(P_IS_OK, "isOk")
    WXJS_READONLY_PROPERTY(P_ROOT, "root")
    WXJS_PROPERTY(P_VERSION, "version")
    WXJS_PROPERTY(P_FILEENCODING, "fileEncoding")
    WXJS_PROPERTY(P_DOCTYPE, "docType")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxXmlDocument, XmlDocument)
	switch( id ) {
	case P_IS_OK:
		ToJSVal(cx, vp, p->IsOk());
		break;
	case P_ROOT:
		{
			wxXmlNode* pRoot = p->GetRoot();
			if( pRoot == NULL ) {
				pRoot = new wxXmlNode(NULL, wxXML_ELEMENT_NODE, _T("Root"));
				p->SetRoot(pRoot);
			}
			vp.set( 
				XmlNode::CreateObject(cx, pRoot)
			);
		}
		break;
	case P_VERSION:
		ToJSVal(cx, vp, p->GetVersion());
		break;
	case P_FILEENCODING:
		ToJSVal(cx, vp, p->GetFileEncoding());
		break;
	case P_DOCTYPE:
		{
			wxXmlDoctype docType = p->GetDoctype();
			JSObject *objAttr = JS_NewObject(cx, NULL/*Attr::GetClass()*/, NULL, NULL);
			JS::RootedObject jsvaAttr(cx, objAttr);
			{
				wxString strName(_T("fullString"));
				jsval attrValue = ToJS(cx, docType.GetFullString() );
				JS_SetUCProperty(cx, 
					objAttr, 
					(const jschar *) strName.c_str(), 
					strName.Length(), &attrValue);
			}
			{
				wxString strName(_T("publicId"));
				jsval attrValue = ToJS(cx, docType.GetPublicId() );
				JS_SetUCProperty(cx, 
					objAttr, 
					(const jschar *) strName.c_str(), 
					strName.Length(), &attrValue);
			}
			{
				wxString strName(_T("rootName"));
				jsval attrValue = ToJS(cx, docType.GetRootName() );
				JS_SetUCProperty(cx, 
					objAttr, 
					(const jschar *) strName.c_str(), 
					strName.Length(), &attrValue);
			}
			{
				wxString strName(_T("systemId"));
				jsval attrValue = ToJS(cx, docType.GetSystemId() );
				JS_SetUCProperty(cx, 
					objAttr, 
					(const jschar *) strName.c_str(), 
					strName.Length(), &attrValue);
			}
			vp.setObjectOrNull(objAttr);
		}
		break;

	}
    return true;
WXJS_END_GET_PROP
	

WXJS_BEGIN_SET_PROP(wxXmlDocument, XmlDocument)
	switch( id ) {
	case P_VERSION:
		{
			wxString str;
			if( FromJS(cx, vp, str) ) {
				p->SetVersion( str );
			}
		}
		break;
	case P_FILEENCODING:
		{
			wxString str;
			if( FromJS(cx, vp, str) ) {
				p->SetFileEncoding( str );
			}
		}
		break;
	case P_DOCTYPE:
		{
			if( vp.isObjectOrNull() ) {
				jsval v;
				wxString rootName;
				wxString systemId;
				wxString publicId;


				if( JS_GetUCProperty(cx, vp.toObjectOrNull(), L"rootName", ::wcslen(L"rootName"), &v) == JS_FALSE) {
					return false;
				}
				if( v.isString() ) {
					if( FromJS(cx, v, rootName) ) {
						return false;
					}
				}
				if( JS_GetUCProperty(cx, vp.toObjectOrNull(), L"systemId", ::wcslen(L"systemId"), &v) == JS_FALSE) {
					return false;
				}
				if( v.isString() ) {
					if( FromJS(cx, v, systemId) ) {
						return false;
					}
				}
				if( JS_GetUCProperty(cx, vp.toObjectOrNull(), L"publicId", ::wcslen(L"publicId"), &v) == JS_FALSE) {
					return false;
				}
				if( v.isString() ) {
					if( FromJS(cx, v, publicId) ) {
						return false;
					}
				}
				wxXmlDoctype docType(rootName, systemId, publicId);
				p->SetDoctype(docType);
			}
		}
		break;

	}
    return true;
WXJS_END_SET_PROP



WXJS_BEGIN_METHOD_MAP(XmlDocument)
    WXJS_METHOD("load", load, 1)
    WXJS_METHOD("save", save, 1)
WXJS_END_METHOD_MAP()



JSBool XmlDocument::load(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxXmlDocument *p = GetPrivate(cx, obj);
	
	wxString	filename;
	wxInputStream *pStream = NULL;
	wxString	encoding = wxT("UTF-8");
	int flags = wxXMLDOC_NONE;


	if( argc > 3 ) {
		argc = 3;
	}



	switch( argc ) {
	case 3:
		if ( ! FromJS(cx, argv[2], flags) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 2:
		if ( ! FromJS(cx, argv[1], encoding) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
	case 1:
		if( argv[0].isString() ) {
			if ( ! FromJS(cx, argv[0], filename) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}
		} else 
		if ( zzzJs::HasPrototype(cx, argv[0], "InputStream") ) {

			io::Stream *stream = (io::Stream *) JS_GetPrivate(/*cx,*/ JSVAL_TO_OBJECT(argv[0]));
			if ( stream == NULL ) {
				return JS_FALSE;
			}
			pStream = dynamic_cast<wxInputStream *>(stream->GetStream());
			if ( pStream == NULL )
			{
				// TODO: error reporting
				return JS_FALSE;
			}
		}
	}


	bool bRet = false;

	if( pStream != NULL ) {
		bRet = p->Load(*pStream, encoding, flags);
	} else {
		bRet = p->Load(filename, encoding, flags);
	}
	vp->setBoolean( bRet );

    return JS_TRUE;
}

JSBool XmlDocument::save(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxXmlDocument *p = GetPrivate(cx, obj);
	
	wxString	filename;
	wxOutputStream *pStream = NULL;
	int indentstep = 2;


	if( argc > 2 ) {
		argc = 2;
	}



	switch( argc ) {
	case 2:
		if ( ! FromJS(cx, argv[1], indentstep) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 1:
		if( argv[0].isString() ) {
			if ( ! FromJS(cx, argv[0], filename) )
			{
				JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
				return JS_FALSE;
			}
		} else 
		if ( zzzJs::HasPrototype(cx, argv[0], "OutputStream") ) {

			io::Stream *stream = (io::Stream *) JS_GetPrivate(/*cx,*/ JSVAL_TO_OBJECT(argv[0]));
			if ( stream == NULL ) {
				return JS_FALSE;
			}
			pStream = dynamic_cast<wxOutputStream *>(stream->GetStream());
			if ( pStream == NULL )
			{
				// TODO: error reporting
				return JS_FALSE;
			}
		}
	}


	bool bRet = false;

	if( pStream != NULL ) {
		bRet = p->Save(*pStream, indentstep);
	} else {
		bRet = p->Save(filename, indentstep);
	}
	vp->setBoolean( bRet );

    return JS_TRUE;
}







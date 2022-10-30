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
WXJS_INIT_CLASS(XmlNode, "XmlNode", 0)

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
WXJS_BEGIN_CONSTANT_MAP(XmlNode)
    WXJS_CONSTANT(wxDIR_, FILES)
    WXJS_CONSTANT(wxDIR_, DIRS)
    WXJS_CONSTANT(wxDIR_, HIDDEN)
    WXJS_CONSTANT(wxDIR_, DOTDOT)
    WXJS_CONSTANT(wxDIR_, DEFAULT)
WXJS_END_CONSTANT_MAP()
*/
/*
WXJS_BEGIN_STATIC_METHOD_MAP(XmlNode)
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
WXJS_BEGIN_CONSTRUCTOR(wxXmlNode, XmlNode)

    return NULL;

WXJS_END_CONSTRUCTOR
	
WXJS_BEGIN_DESTRUCTOR(wxXmlNode, XmlNode)

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
WXJS_BEGIN_PROPERTY_MAP(XmlNode)
    WXJS_READONLY_PROPERTY(P_TYPE, "type")
    WXJS_READONLY_PROPERTY(p_NAME, "name")
    WXJS_READONLY_PROPERTY(P_NODE_CONTENT, "nodeContent")
    WXJS_READONLY_PROPERTY(P_PARENT, "parent")
    WXJS_READONLY_PROPERTY(P_NEXT, "next")
    WXJS_READONLY_PROPERTY(P_CHILDREN, "children")
    WXJS_READONLY_PROPERTY(P_ATTRIBUTES, "attrs")
    WXJS_READONLY_PROPERTY(P_LINE_NO, "lineNo")
    WXJS_READONLY_PROPERTY(P_ELEMENTS, "elements")
WXJS_END_PROPERTY_MAP()


WXJS_BEGIN_GET_PROP(wxXmlNode, XmlNode)

	switch( id ) {
	case P_TYPE:
		ToJSVal(cx, vp, (int)p->GetType());
		break;
	case p_NAME:
		ToJSVal(cx, vp, p->GetName());
		break;
	case P_CONTENT:
		ToJSVal(cx, vp, p->GetContent());
		break;
	case P_NODE_CONTENT:
		ToJSVal(cx, vp, p->GetNodeContent());
		break;
	case P_PARENT:
		{
			wxXmlNode* pParent = p->GetParent();
			if( pParent != NULL ) {
				vp.set( XmlNode::CreateObject(cx, pParent) );
			} else {
				vp.setNull();
			}
		}		
		break;
	case P_NEXT:
		{
			wxXmlNode* pParent = p->GetNext();
			if( pParent != NULL ) {
				vp.set( XmlNode::CreateObject(cx, pParent) );
			} else {
				vp.setNull();
			}
		}		
		break;
	case P_CHILDREN:
		{
			wxXmlNode* pParent = p->GetChildren();
			if( pParent != NULL ) {
				vp.set( XmlNode::CreateObject(cx, pParent) );
			} else {
				vp.setNull();
			}
		}		
		break;
	case P_ATTRIBUTES:
		{
			JSObject *objAttr = JS_NewObject(cx, NULL/*Attr::GetClass()*/, NULL, NULL);
			JS::RootedObject jsvaAttr(cx, objAttr);
			wxXmlAttribute* pAttr = p->GetAttributes();
			while( pAttr != NULL ) {


				jsval attrValue = ToJS(cx, pAttr->GetValue() );
				JS_SetUCProperty(cx, 
					objAttr, 
					(const jschar *) pAttr->GetName().c_str(), 
					pAttr->GetName().Length(), &attrValue);

				pAttr = pAttr->GetNext();
			}
			vp.setObjectOrNull( objAttr );
		}		
		break;
	case P_LINE_NO:
		ToJSVal(cx, vp, (int)p->GetLineNumber());
		break;
	case P_ELEMENTS:
		{
			size_t i = 0;
			wxXmlNode* pNode = p->GetChildren();
			JSObject *objArray = JS_NewArrayObject(cx, 0, NULL);
			JS::RootedObject jsvaArray(cx, objArray);
			while( pNode != NULL ) {
				if( pNode->GetType() != wxXML_ELEMENT_NODE ) {
					pNode = pNode->GetNext();
					continue;
				}
				jsval v = XmlNode::CreateObject(cx, pNode);

				JS_SetElement(cx, objArray, i, &v);
				i++;
				pNode = pNode->GetNext();
			}			
			vp.setObjectOrNull( objArray );
		}
		break;
	}

    return true;
WXJS_END_GET_PROP

WXJS_BEGIN_METHOD_MAP(XmlNode)
    WXJS_METHOD("addChild", addChild, 2)
    WXJS_METHOD("insertChild", insertChild, 3)
    WXJS_METHOD("insertChildAfter", insertChildAfter, 3)
    WXJS_METHOD("removeChild", removeChild, 1)
    WXJS_METHOD("addAttribute", addAttribute, 2)
    WXJS_METHOD("deleteAttribute", deleteAttribute, 1)
    WXJS_METHOD("getAttribute", getAttribute, 1)
WXJS_END_METHOD_MAP()



JSBool XmlNode::addChild(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxXmlNode *p = GetPrivate(cx, obj);
	
	
	
	int			type;
	wxString	name;
	wxString	content = wxEmptyString;
	int			contentType = wxXML_TEXT_NODE;


	if( argc > 4 ) {
		argc = 4;
	}
	

	switch( argc ) {
	case 4:
		if ( ! FromJS(cx, argv[3], contentType) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 3:
		if ( ! FromJS(cx, argv[2], content) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
	default:
		if ( ! FromJS(cx, argv[1], name) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		if ( ! FromJS(cx, argv[0], type) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	}

	wxXmlNode* pNewNode = new wxXmlNode(p, (wxXmlNodeType)type, name);
	if( content.Length() != 0 ) {
		pNewNode->AddChild(new wxXmlNode((wxXmlNodeType)contentType, _T(""), content));
	}

	*vp = XmlNode::CreateObject(cx, pNewNode);


    return JS_TRUE;
}

JSBool XmlNode::insertChild(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxXmlNode *p = GetPrivate(cx, obj);
	
	
	
	int			type;
	wxString	name;
	wxString	content = wxEmptyString;
	int			contentType = wxXML_TEXT_NODE;
	wxXmlNode*	pPrev = NULL;

	if( argc > 5 ) {
		argc = 5;
	}
	

	switch( argc ) {
	case 5:
		if ( ! FromJS(cx, argv[4], contentType) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 5, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 4:
		if ( ! FromJS(cx, argv[3], content) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
	default:
		if ( ! FromJS(cx, argv[2], name) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		if ( ! FromJS(cx, argv[1], type) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		pPrev = XmlNode::GetPrivate(cx, argv[0]);
		if( pPrev == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "XmlNode");
			return JS_FALSE;
		}

	}

	wxXmlNode* pNewNode = new wxXmlNode(NULL, (wxXmlNodeType)type, name);
	if( content.Length() != 0 ) {
		pNewNode->AddChild(new wxXmlNode((wxXmlNodeType)contentType, _T(""), content));
	}
	p->InsertChild(pNewNode, pPrev);

	*vp = XmlNode::CreateObject(cx, pNewNode);


    return JS_TRUE;
}

JSBool XmlNode::insertChildAfter(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxXmlNode *p = GetPrivate(cx, obj);
	
	
	
	int			type;
	wxString	name;
	wxString	content = wxEmptyString;
	int			contentType = wxXML_TEXT_NODE;
	wxXmlNode*	pPrev = NULL;

	if( argc > 5 ) {
		argc = 5;
	}
	

	switch( argc ) {
	case 5:
		if ( ! FromJS(cx, argv[4], contentType) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 5, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
	case 4:
		if ( ! FromJS(cx, argv[3], content) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 4, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
	default:
		if ( ! FromJS(cx, argv[2], name) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 3, WXJS_TYPE_STRING);
			return JS_FALSE;
		}
		if ( ! FromJS(cx, argv[1], type) )
		{
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_NUMBER);
			return JS_FALSE;
		}
		pPrev = XmlNode::GetPrivate(cx, argv[0]);
		if( pPrev == NULL ) {
			JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "XmlNode");
			return JS_FALSE;
		}

	}

	wxXmlNode* pNewNode = new wxXmlNode(NULL, (wxXmlNodeType)type, name);
	if( content.Length() != 0 ) {
		pNewNode->AddChild(new wxXmlNode((wxXmlNodeType)contentType, _T(""), content));
	}
	p->InsertChildAfter(pNewNode, pPrev);

	*vp = XmlNode::CreateObject(cx, pNewNode);


    return JS_TRUE;
}


JSBool XmlNode::removeChild(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxXmlNode *p = GetPrivate(cx, obj);
	
	
	wxXmlNode*	pPrev = NULL;
	pPrev = XmlNode::GetPrivate(cx, argv[0]);
	if( pPrev == NULL ) {
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, "XmlNode");
		return JS_FALSE;
	}

	vp->setBoolean( p->RemoveChild( pPrev ) );


    return JS_TRUE;
}


JSBool XmlNode::addAttribute(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxXmlNode *p = GetPrivate(cx, obj);
	
	wxString	name;
	wxString	value;
	
	if ( ! FromJS(cx, argv[1], value) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 2, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	if ( ! FromJS(cx, argv[0], name) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}

	p->AddAttribute( name, value );


    return JS_TRUE;
}


JSBool XmlNode::deleteAttribute(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxXmlNode *p = GetPrivate(cx, obj);
	
	wxString	name;
	
	if ( ! FromJS(cx, argv[0], name) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}

	p->DeleteAttribute( name );


    return JS_TRUE;
}


JSBool XmlNode::getAttribute(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);

    wxXmlNode *p = GetPrivate(cx, obj);
	
	wxString	name;
	
	if ( ! FromJS(cx, argv[0], name) )
	{
		JS_ReportError(cx, WXJS_INVALID_ARG_TYPE, 1, WXJS_TYPE_STRING);
		return JS_FALSE;
	}
	if( p->HasAttribute(name) == false ) {
		vp->setNull();
	} else {
		wxString strValue = p->GetAttribute( name );
		*vp = ToJS(cx, strValue);
	}


    return JS_TRUE;
}
















/*
 * wxJavaScript - parser.cpp
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
 * $Id: parser.cpp 810 2007-07-13 20:07:05Z fbraem $
 */
// parser.cpp
#include "precompile.h"

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "js/engine/mng_inst.h"
#include "js/common/conf.h"
#include "js/common/clntdata.h"
#include "js/common/jsutil.h"
#include "js/ext/zzzjs_ext_init.h"
#include "js/expat/attr.h"
#include "js/expat/parser.h"


using namespace zzzJs;
using namespace zzzJs::xml;

Parser::Parser() : m_cx(NULL), m_obj(NULL)
{
}

void Parser::StartElementHandler(void *userData,
                                 const XML_Char *name,
                                 const XML_Char **atts)
{
//	wxMBConvUTF16 conv;
    Parser *parser = (Parser*) userData;

    wxString element((const char *) name/*, conv*/);
	
//	JSObject*  pO = zzzJs::MngInst::instance()->getGlobalJSObject(parser->m_cx);
//	JSAutoCompartment autCmp(parser->m_cx, pO);
//    JSObject *objAttr = JS_GetConstructor(parser->m_cx, Attr::GetClassPrototype());//JS_ConstructObject(parser->m_cx, Attr::GetClass(), NULL, NULL);
	JSObject *objAttr = JS_NewObject(parser->m_cx, NULL/*Attr::GetClass()*/, NULL, NULL);
//  	JS_AddRoot(parser->m_cx, &objAttr);
 
    for (int i = 0; atts[i]; i += 2)
    {
        jsval attrValue = ToJS(parser->m_cx, wxString((const char*) atts[i+1]/*, conv*/));
		wxString attr((const char *) atts[i]/*, conv*/);
		JS_SetUCProperty(parser->m_cx, objAttr, (const jschar *) attr.c_str(), attr.Length(), &attrValue);
    }

    jsval rval;
    jsval argv[] = 
    {
        ToJS(parser->m_cx, element),
        OBJECT_TO_JSVAL(objAttr)
    };

	CallFunctionProperty(parser->m_cx, parser->m_obj, "onStartElement",
                              2, argv, &rval);
//    JS_RemoveRoot(parser->m_cx, &objAttr);

    parser->m_characters.SetDataLen(0);
}

void Parser::EndElementHandler(void *userData,
                               const XML_Char *name)
{
    wxMBConvUTF16 conv;
    Parser *parser = (Parser*) userData;

    jsval rval;

    wxString element((const char*) name, conv);
    jsval argv[] = 
    {
        ToJS(parser->m_cx, element)
    };
	CallFunctionProperty(parser->m_cx, parser->m_obj, "onEndElement",
                              1, argv, &rval);

    parser->m_characters.SetDataLen(0);
}

void Parser::CharacterDataHandler(void *userData,
                                  const XML_Char *s,
                                  int len)
{
    Parser *parser = (Parser*) userData;
    jsval callback;
    if ( GetFunctionProperty(parser->m_cx, parser->m_obj, "onCharacter", &callback) == JS_TRUE )
    {
	    jsval rval;

        jsval argv[] = 
        {
            zzzJs::ext::CreateMemoryBuffer(parser->m_cx, (void *) s, len * sizeof(XML_Char))
        };

        if ( JS_CallFunctionValue(parser->m_cx, parser->m_obj, callback, 1, argv, &rval) == JS_FALSE )
        {
            if ( JS_IsExceptionPending(parser->m_cx) )
            {
                JS_ReportPendingException(parser->m_cx);
            }
        }
    }
    else
    {
        parser->m_characters.AppendData(s, len * sizeof(XML_Char));
    }
}

void Parser::ProcessingInstructionHandler(void *userData,
                                          const XML_Char *target,
                                          const XML_Char *data)
{
    wxMBConvUTF16 conv;
    Parser *parser = (Parser*) userData;

	jsval rval;

    jsval argv[] = 
    {
        ToJS(parser->m_cx, wxString((const char *) target, conv)),
        ToJS(parser->m_cx, wxString((const char *) data, conv))
    };

	CallFunctionProperty(parser->m_cx, parser->m_obj, "onProcessing",
                              2, argv, &rval);
}

void Parser::CommentHandler(void *userData,
                            const XML_Char *data)
{
    wxMBConvUTF16 conv;
    Parser *parser = (Parser*) userData;

    jsval rval;
    wxString comment((const char *) data, conv);
    jsval argv[] = 
    {
        ToJS(parser->m_cx, comment)
    };
	CallFunctionProperty(parser->m_cx, parser->m_obj, "onComment",
                              1, argv, &rval);
}

void Parser::StartCDataSectionHandler(void *userData)
{
    Parser *parser = (Parser*) userData;

    jsval rval;
	CallFunctionProperty(parser->m_cx, parser->m_obj, "onStartCData",
                              0, NULL, &rval);
}

void Parser::EndCDataSectionHandler(void *userData)
{
    Parser *parser = (Parser*) userData;

    jsval rval;
	CallFunctionProperty(parser->m_cx, parser->m_obj, "onEndCData",
                              0, NULL, &rval);
}

void Parser::DefaultHandler(void *userData,
                            const XML_Char *s,
                            int len)
{
    wxMBConvUTF16 conv;
    wxString data((const char*) s, conv, len * sizeof(XML_Char));

    Parser *parser = (Parser*) userData;

	jsval rval;

    jsval argv[] = 
    {
        ToJS(parser->m_cx, data)
    };

	CallFunctionProperty(parser->m_cx, parser->m_obj, "onDefault",
                         1, argv, &rval);
}

void Parser::DefaultHandlerExpand(void *userData,
                                  const XML_Char *s,
                                  int len)
{
    wxMBConvUTF16 conv;
    wxString data((const char*) s, conv, len * sizeof(XML_Char));

    Parser *parser = (Parser*) userData;

	jsval rval;

    jsval argv[] = 
    {
        ToJS(parser->m_cx, data)
    };

	CallFunctionProperty(parser->m_cx, parser->m_obj, "onDefaultExpand",
                              1, argv, &rval);
}

int Parser::ExternalEntityRefHandler(XML_Parser p,
                                     const XML_Char *context,
                                     const XML_Char *base,
                                     const XML_Char *systemId,
                                     const XML_Char *publicId)
{
    wxMBConvUTF16 conv;
    Parser *parser = (Parser*) XML_GetUserData(p);

	jsval rval;

    jsval argv[] = 
    {
        OBJECT_TO_JSVAL(parser->m_obj),
        ToJS(parser->m_cx, wxString((const char *) context, conv)),
        base == NULL ? JSVAL_VOID : ToJS(parser->m_cx, wxString((const char *) base, conv)),
        ToJS(parser->m_cx, wxString((const char *) systemId, conv)),
        ToJS(parser->m_cx, wxString((const char *) publicId, conv)),
    };

	CallFunctionProperty(parser->m_cx, parser->m_obj, "onExternalEntityRef",
                              5, argv, &rval);
    
    return JSVAL_TO_INT(rval);
}

void Parser::SkippedEntityHandler(void *userData, const XML_Char *entity, int is_param)
{
    wxMBConvUTF16 conv;
    Parser *parser = (Parser*) userData;

	jsval rval;

    jsval argv[] = 
    {
        ToJS(parser->m_cx, wxString((const char *) entity, conv)),
        ToJS(parser->m_cx, is_param > 0)
    };

	CallFunctionProperty(parser->m_cx, parser->m_obj, "onSkippedEntity",
                              2, argv, &rval);
}

void Parser::StartNamespaceDeclHandler(void *userData, const XML_Char *prefix, const XML_Char *uri)
{
    wxMBConvUTF16 conv;
    Parser *parser = (Parser*) userData;

	jsval rval;

    jsval argv[] = 
    {
        ToJS(parser->m_cx, wxString((const char *) prefix, conv)),
        ToJS(parser->m_cx, wxString((const char *) uri, conv))
    };

	CallFunctionProperty(parser->m_cx, parser->m_obj, "onStartNamespaceDecl",
                              2, argv, &rval);
}

void Parser::EndNamespaceDeclHandler(void *userData, const XML_Char *prefix)
{
    wxMBConvUTF16 conv;
    Parser *parser = (Parser*) userData;

	jsval rval;

    jsval argv[] = 
    {
        ToJS(parser->m_cx, wxString((const char*) prefix, conv)),
    };

	CallFunctionProperty(parser->m_cx, parser->m_obj, "onEndNamespaceDecl",
                              1, argv, &rval);
}

/***
 * <file>XMLParser</file>
 * <module>expat</module>
 * <class name="expat.Parser">
 *  Parser implements the <strong>expat</strong> XML parser. 
 *  More info on expat can be found at <a href="http://expat.sourceforge.net">expat.sourceforge.net</a>.
 * </class>
 */
WXJS_INIT_CLASS(Parser, "Parser", 0)

/***
 * <constants>
 *  <type name="XML_STATUS">
 *   <constant name="XML_STATUS_ERROR" />
 *   <constant name="XML_STATUS_OK" />
 *   <desc>Indicates the status of a document</desc>
 *  </type>
 * </constants>
 */
WXJS_BEGIN_CONSTANT_MAP(Parser)
    WXJS_SIMPLE_CONSTANT(XML_STATUS_ERROR)
    WXJS_SIMPLE_CONSTANT(XML_STATUS_OK)
WXJS_END_CONSTANT_MAP()

/*** 
 * <ctor>
 *  <function>
 *   <arg name="Encoding" type=WXJS_TYPE_STRING default="null">
 *    Specifies a character encoding to use for the document. This overrides the document encoding 
 *    declaration. There are four built-in encodings: US-ASCII, UTF-8, UTF-16, ISO-8859-1.
 *   </arg>
 *  </function>
 *  <desc>
 *   Constructs a new parser.
 *  </desc>
 * </ctor>
 */
//Parser* Parser::Construct(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, bool WXUNUSED(constructing))
WXJS_BEGIN_CONSTRUCTOR(Parser, Parser)

	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    Parser *parser = new Parser();

    if ( argc == 1 )
    {
        FromJS(cx, argv[0], parser->m_encoding);
        parser->m_parser = XML_ParserCreate((const XML_Char *) parser->m_encoding.c_str());
    }
    else
    {
        parser->m_parser = XML_ParserCreate(NULL);
    }

    XML_SetCharacterDataHandler(parser->m_parser, Parser::CharacterDataHandler);

    parser->m_obj = obj;
	parser->m_cx = cx;
    XML_SetUserData(parser->m_parser, parser);

    return parser;
WXJS_END_CONSTRUCTOR


//void Parser::Destruct(JSContext* WXUNUSED(cx), Parser *p)
WXJS_BEGIN_DESTRUCTOR(Parser, Parser)
    XML_ParserFree(p->m_parser);
	delete p;
WXJS_END_DESTRUCTOR

/***
 * <properties>
 *  <property name="characters" type=WXJS_TYPE_STRING readonly="Y">
 *   When the onCharacter callback is not used, XMLParser will
 *   collect the characters in this property. It will be cleared
 *   when a start tag is read and it will be complete when an end
 *   tag is read. The string is always encoded in UTF-16 (JavaScript
 *   internal encoding).
 *  </property>
 *  <property name="onCharacter" type="Function">
 *   This function is called when contiguous text free of tags is found. Note that
 *   this function can be called more then ounce for the same tag. The function
 *   gets one argument: the received data.
 *  </property>
 *  <property name="onComment" type="Function">
 *   Set a handler for comments. This function gets one argument: all text inside
 *   the comment delimiters.
 *  </property>
 *  <property name="onDefault" type="Function">
 *   The function hase one argument: any characters in the document which wouldn't otherwise be handled.
 *   This includes both data for which no handlers can be set (like some kinds of DTD declarations) 
 *   and data which could be reported but which currently has no handler set. The characters are passed 
 *   exactly as they were present in the XML document except that they will be encoded in UTF-8
 *   or UTF-16. Line boundaries are not normalized. Note that a byte order mark character is not 
 *   passed to the default handler. There are no guarantees about how characters are divided between 
 *   calls to the default handler: for example, a comment might be split between multiple calls. 
 *   Setting this handler has the side effect of turning off expansion of references to internally 
 *   defined general entities. Instead these references are passed to the default handler.
 *  </property>
 *  <property name="onDefaultExpand" type="Function">
 *   This sets a default handler, but doesn't inhibit the expansion of internal entity references. 
 *   The entity reference will not be passed to the default handler. The function has one argument:
 *   any characters in the document which wouldn't otherwise handled.
 *  </property>
 *  <property name="onEndCData" type="Function">
 *   This function is called at the end of a CDATA section.
 *  </property>
 *  <property name="onEndElement" type="Function">
 *   This function will be called everytime when a tag is ended (also for empty tags). The
 *   functions gets one argument: the name of the element.
 *  </property>
 *  <property name="onEndNamespaceDecl" type="Function" />
 *  <property name="onExternalEntityRef" type="Function">
 *   Set an external entity reference handler. This handler is also called for processing 
 *   an external DTD subset if parameter entity parsing is in effect. This function
 *   gets 5 arguments: XMLParser, context, base, systemId and publicId. The function must
 *   return an integer value: non-zero for success, zero for failure.
 *  </property>
 *  <property name="onProcessing" type="Function">
 *   This function will be called for processing instructions. It gets two arguments: target and
 *   data. A target is the first word in the processing instruction. The data is the rest of the 
 *   characters in it after skipping all whitespace after the initial word.
 *  </property>
 *  <property name="onSkippedEntity" type="Function">
 *   The function has two arguments: the entity name and a boolean which will be true
 *   the entity is a parameter entity and false for general entity.
 *   This function is called in two situations:
 *   <ul>
 *    <li>An entity reference is encountered for which no declaration has been read
 *        and this is not an error.</li>
 *    <li>An internal entity reference is read, but not expanded, 
 *        because the onDefault handler has been called.</li>
 *   </ul>
 *  </property>
 *  <property name="onStartCData" type="Function">
 *   This function is called at the beginning of a CDATA section.
 *  </property>
 *  <property name="onStartElement" type="Function">
 *   This function will be called everytime when a tag is started (also for empty tags). The
 *   functions get two arguments: the name of the element and a @expat.Attr object.
 *  </property>
 * </properties>
 */

WXJS_BEGIN_PROPERTY_MAP(Parser)
    WXJS_READONLY_PROPERTY(P_CHARACTERS, "characters")
WXJS_END_PROPERTY_MAP()

//bool Parser::GetProperty(Parser *p, JSContext *cx, JSObject* WXUNUSED(obj), int id, jsval *vp)
WXJS_BEGIN_GET_PROP(Parser, Parser)
    switch(id)
    {
    case P_CHARACTERS:
        {
            wxMBConvUTF16 conv;
            wxString content((const char*) p->m_characters.GetData(), conv, p->m_characters.GetDataLen());
            ToJSVal(cx, vp, content);
            break;
        }
    }

    return true;
WXJS_END_GET_PROP

//bool Parser::SetProperty(Parser* WXUNUSED(p), JSContext* WXUNUSED(cx), JSObject* WXUNUSED(obj), int WXUNUSED(id), jsval* WXUNUSED(vp))
WXJS_BEGIN_SET_PROP(Parser, Parser)
    return true;
WXJS_END_SET_PROP

//bool Parser::AddProperty(Parser *p, JSContext* WXUNUSED(cx), JSObject *WXUNUSED(obj), 
//                         const wxString &prop, jsval* WXUNUSED(vp))
//{
WXJS_BEGIN_ADD_PROP(Parser, Parser)
    if ( prop.IsSameAs(wxT("onDefault")) )
        XML_SetDefaultHandler(p->m_parser, Parser::DefaultHandler);
    else if ( prop.IsSameAs(wxT("onDefaultExpand")) )
        XML_SetDefaultHandlerExpand(p->m_parser, Parser::DefaultHandlerExpand);
    else if ( prop.IsSameAs(wxT("onStartElement")) )
        XML_SetStartElementHandler(p->m_parser, Parser::StartElementHandler);
    else if ( prop.IsSameAs(wxT("onEndElement")) )
        XML_SetEndElementHandler(p->m_parser, Parser::EndElementHandler);
    else if ( prop.IsSameAs(wxT("onProcessing")) )
        XML_SetProcessingInstructionHandler(p->m_parser, Parser::ProcessingInstructionHandler);
    else if ( prop.IsSameAs(wxT("onComment")) )
        XML_SetCommentHandler(p->m_parser, Parser::CommentHandler);
    else if ( prop.IsSameAs(wxT("onStartCData")) )
        XML_SetStartCdataSectionHandler(p->m_parser, Parser::StartCDataSectionHandler);
    else if ( prop.IsSameAs(wxT("onEndCData")) )
        XML_SetEndCdataSectionHandler(p->m_parser, Parser::EndCDataSectionHandler);
    else if ( prop.IsSameAs(wxT("onExternalEntityRef")) )
        XML_SetExternalEntityRefHandler(p->m_parser, Parser::ExternalEntityRefHandler);
    else if ( prop.IsSameAs(wxT("onSkippedEntity")) )
        XML_SetSkippedEntityHandler(p->m_parser, Parser::SkippedEntityHandler);
    else if ( prop.IsSameAs(wxT("onStartNamespaceDecl")) )
        XML_SetStartNamespaceDeclHandler(p->m_parser, Parser::StartNamespaceDeclHandler);
    else if ( prop.IsSameAs(wxT("onEndNamespaceDecl")) )
        XML_SetEndNamespaceDeclHandler(p->m_parser, Parser::EndNamespaceDeclHandler);
    return true;
WXJS_END_ADD_PROP

WXJS_BEGIN_METHOD_MAP(Parser)
    WXJS_METHOD("reset", reset, 0)
    WXJS_METHOD("parse", parse, 2)
WXJS_END_METHOD_MAP()

/***
 * <method name="reset">
 *  <function returns="Boolean" />
 *  <desc>
 *   Clean up the memory structures maintained by the parser so that it may be used again.
 *   After this has been called, parser is ready to start parsing a new document
 *  </desc>
 * </method>
 */
JSBool Parser::reset(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    Parser *p = Parser::GetPrivate(cx, obj);
    if ( p != NULL )
    {
        p->m_characters.SetBufSize(0);
        *vp = XML_ParserReset(p->m_parser, (const XML_Char*) p->m_encoding.c_str()) == XML_TRUE ? JSVAL_TRUE : JSVAL_FALSE;
        return JS_TRUE;
    }
    return JS_FALSE;
}

/***
 * <method name="parse">
 *  <function returns=WXJS_TYPE_NUMBER>
 *   <arg name="Content" type=WXJS_TYPE_STRING>Containing part (or perhaps all) of the document</arg>
 *   <arg name="Final" type="Boolean">
 *    The final parameter informs the parser that this
 *    is the last piece of the document.
 *   </arg>
 *  </function>
 *  <desc>
 *   Parse some more of the document. Returns XML_STATUS_ERROR or XML_STATUS_OK.
 *   (see @expat.Parser#XML_STATUS)
 *   <br /><br />
 *   The following example shows how easy it is to create a simple DOM structure in JavaScript:
 *   <pre>
 *        // Constructor for a XMLElement object
 *        function XMLElement(parent, name, attrs)
 *        {
 *          this.parent = parent;
 *          if ( parent != null )
 *            parent.elements[parent.elements.length + 1] = this;
 *          this.name = name;
 *          this.attrs = attrs;
 *          this.elements = new Array();
 *        }
 *
 *        var p = new expat.Parser();
 *        p.currentElement = null;
 *
 *        p.onStartElement = function(element, attrs)
 *        {
 *          this.currentElement = new XMLElement(this.currentElement, element, attrs);
 *        }
 *
 *        p.onEndElement = function(element)
 *        {
 *          this.currentElement.data = this.characters;
 *
 *          if ( this.currentElement.parent != null )
 *             this.currentElement = this.currentElement.parent;
 *        }
 *
 *        p.parse('&lt;tag1 attr="1" attr2="2"&gt;&lt;child1&gt;child&lt;/child1&gt;&lt;/tag1&gt;', true);
 *        // p.currentElement points to the root tag now(tag1)</pre>
 *  </desc>
 * </method>
 */
JSBool Parser::parse(JSContext *cx, unsigned argc, JS::Value *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	JS::CallArgs argv = CallArgsFromVp(argc, vp);
    Parser *p = GetPrivate(cx, obj);
    if ( p != NULL )
    {
        bool final;
        if ( argc > 1 )
        {
            if ( ! FromJS(cx, argv[1], final) )
            {
                return JS_FALSE;
            }
        }
        else
        {
            final = true;
        }

        if ( JSVAL_IS_STRING(argv[0]) )
        {
		    JSString *str = JS_ValueToString(cx, argv[0]);
		    //char *data = JS_GetStringBytes(str);
			char* data = JS_EncodeString(cx, str);
            if ( FromJS(cx, argv[1], final) )
            {
			    XML_Status status = XML_Parse(p->m_parser, data, 
										      JS_GetStringLength(str), final ? 1 : 0);
                *vp = INT_TO_JSVAL(status);
                return JS_TRUE;
            }
        }
		else if ( argv[0].isObject() /*JSVAL_IS_OBJECT(argv[0])*/ )
    	{
            wxMemoryBuffer* buffer = zzzJs::ext::GetMemoryBuffer(cx, JSVAL_TO_OBJECT(argv[0]));
		    if ( buffer != NULL )
		    {
                XML_Status status = XML_Parse(p->m_parser, (const char *) buffer->GetData(), 
                                              buffer->GetDataLen(), final ? 1 : 0);
                *vp = INT_TO_JSVAL(status);
                return JS_TRUE;
		    }
        }
    }
    return JS_FALSE;
}

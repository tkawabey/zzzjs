/*
 * wxJavaScript - parser.h
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
 * $Id: parser.h 642 2007-03-27 20:11:28Z fbraem $
 */
#ifndef _wxjs_xml_parser_h
#define _wxjs_xml_parser_h

/////////////////////////////////////////////////////////////////////////////
// Name:        parser.h
// Module:      wxJS_xml
// Purpose:		Implements the XMLParser object
// Author:      Franky Braem
// Modified by:
// Created:     15.04.02
// Copyright:   (c) 2003- Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////


#include <wx/string.h>
#include "js/expat/expat_src/expat.h"

#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace xml
    {
        class Parser : public ApiWrapper<Parser, Parser>
        {
        public:

            Parser();
            virtual ~Parser() {}

	        //static bool GetProperty(Parser *p, JSContext *cx, JSObject *obj, int id, jsval *vp);
	        //static bool SetProperty(Parser *p, JSContext *cx, JSObject *obj, int id, jsval *vp);
            //static bool AddProperty(Parser *p, JSContext *cx, JSObject *obj, const wxString &prop, jsval *vp);
			WXJS_DECLARE_ADD_PROP(Parser)
			WXJS_DECLARE_GET_PROP(Parser)
			WXJS_DECLARE_SET_PROP(Parser)
			WXJS_DECLARE_CONSTRUCTOR(Parser)
	        /**
	         * Callback for when a XMLParser object is created
	         */
	        //static Parser* Construct(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, bool constructing);

            /**
	         * Callback for when a Parser object is destroyed
	         */
            //static void Destruct(JSContext *cx, Parser *p);
			//static void Destruct(Parser *p);
			WXJS_DECLARE_DESTRUCTOR(Parser)
			
   	        //static JSBool reset(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
   	        //static JSBool parse(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
            WXJS_DECLARE_METHOD(reset)
            WXJS_DECLARE_METHOD(parse)

            // XML Handlers
            static void StartElementHandler(void *userData,
                                            const XML_Char *name,
                                            const XML_Char **atts);
            static void EndElementHandler(void *userData,
                                          const XML_Char *name);
            static void CharacterDataHandler(void *userData,
                                             const XML_Char *s,
                                             int len);
            static void ProcessingInstructionHandler(void *userData,
                                                     const XML_Char *target,
                                                     const XML_Char *data);
            static void CommentHandler(void *userData,
                                       const XML_Char *s);
            
            static void StartCDataSectionHandler(void *userData);
            static void EndCDataSectionHandler(void *userData);
            static void DefaultHandler(void *userData, const XML_Char *s, int len);
            static void DefaultHandlerExpand(void *userData, const XML_Char *s, int len);
            static int  ExternalEntityRefHandler(XML_Parser p,
                                                 const XML_Char *context,
                                                 const XML_Char *base,
                                                 const XML_Char *systemId,
                                                 const XML_Char *publicId);
            static void SkippedEntityHandler(void *userData, const XML_Char *entity, int is_param);
            static void StartNamespaceDeclHandler(void *userData, const XML_Char *prefix, const XML_Char *uri);
            static void EndNamespaceDeclHandler(void *userData, const XML_Char *prefix);

            WXJS_DECLARE_PROPERTY_MAP()
	        WXJS_DECLARE_METHOD_MAP()
	        WXJS_DECLARE_CONSTANT_MAP()

	        /**
	         * Property Ids.
	         */
	        enum
	        {
                P_CHARACTERS = WXJS_START_PROPERTY_ID
	        };

        private:

            XML_Parser m_parser;
            wxString m_encoding;
            wxMemoryBuffer m_characters;

	        JSContext *m_cx;
            JSObject *m_obj;
        };
    }; // namespace xml
}; // namespace wxjs

#endif //_wxjs_xml_parser_h

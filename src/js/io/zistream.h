/*
 * wxJavaScript - zistream.h
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
 * $Id: zistream.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef wxjs_io_zistream_h
#define wxjs_io_zistream_h

#include <wx/zipstrm.h>
#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
        class ZipInputStream : public wxZipInputStream,
						           public JsWrapper<ZipInputStream, Stream>
        {
        public:

	        ZipInputStream(wxInputStream &str);

	        //static Stream* Construct(JSContext *cx,  
									//	unsigned int argc, 
									//	JS::Value *vp, 
									//	bool constructing);
			ZZZJS_DECLARE_SET_STR_PROP(Stream)
			ZZZJS_DECLARE_CONSTRUCTOR(Stream)
			ZZZJS_DECLARE_DESTRUCTOR(Stream)
            /**
             * Callback for retrieving properties of wxInputStream
             */
            //static bool GetProperty(Stream *p,  
            //                      JSContext *cx, 
            //                      JSObject *obj, 
            //                      int id, 
            //                      JS::MutableHandle<JS::Value>& vp);
			ZZZJS_DECLARE_GET_PROP(Stream)

            ZZZJS_DECLARE_PROPERTY_MAP()

            /**
             * Property Ids.
             */
            enum
            {
                P_COMMENT
		        , P_TOTAL_ENTRIES
		        , P_NEXT_ENTRY
            };

	        // Keep a reference to the stream to avoid deletion.
            Stream m_refStream;
        };
    }; // namespace io
}; // namespace wxjs
#endif // wxjs_io_zistream_h

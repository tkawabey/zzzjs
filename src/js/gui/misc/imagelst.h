/*
 * wxJavaScript - imagelst.h
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
 * $Id: imagelst.h 715 2007-05-18 20:38:04Z fbraem $
 */
#ifndef _WXJSImageList_H
#define _WXJSImageList_H

#include <wx/imaglist.h>
#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace gui
    {
      class ImageList : public JsWrapper<ImageList, ImageList>
                      , public wxImageList
                      , public wxClientDataContainer
        {
        public:

			ImageList();
			virtual ~ImageList() {}
		  
			ZZZJS_DECLARE_GET_PROP(ImageList)
			ZZZJS_DECLARE_CONSTRUCTOR(ImageList)
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(ImageList)
/*
			static bool GetProperty(wxImageList *p, 
									JSContext *cx, 
									JSObject *obj, 
									int id, 
									JS::MutableHandle<JS::Value>& vp);
			static ImageList* Construct(JSContext *cx,
										unsigned int argc, 
										JS::Value *vp, 
										bool constructing);
*/
			ZZZJS_DECLARE_PROPERTY_MAP()

			/**
			* Property Ids.
			*/
			enum
			{
				P_IMAGE_COUNT
			};

			ZZZJS_DECLARE_METHOD_MAP()
			ZZZJS_DECLARE_METHOD(add)
			ZZZJS_DECLARE_METHOD(create)
			ZZZJS_DECLARE_METHOD(draw)
			ZZZJS_DECLARE_METHOD(getSize)
			ZZZJS_DECLARE_METHOD(remove)
			ZZZJS_DECLARE_METHOD(replace)
			ZZZJS_DECLARE_METHOD(removeAll)
		  
			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);

        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSImageList_H


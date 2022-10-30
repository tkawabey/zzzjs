/*
 * wxJavaScript - image.h
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
 * $Id: image.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _WXJSImage_H
#define _WXJSImage_H

/////////////////////////////////////////////////////////////////////////////
// Name:        image.h
// Purpose:     Image ports wxImage to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     07-10-2002
// Copyright:   (c) 2001-2002 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

#include <wx/image.h>
#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace gui
    {
        class Image : public JsWrapper<Image, wxImage>
        {
        public:
			ZZZJS_DECLARE_GET_PROP(wxImage)
			ZZZJS_DECLARE_SET_PROP(wxImage)
			ZZZJS_DECLARE_CONSTRUCTOR(wxImage)
			
			// Object 2 Instatance
			ZZZJS_DECLARE_O2I(wxImage)

            /**
             * Property Ids.
             */
            enum
            {
                P_OK
                , P_MASK_RED
                , P_MASK_GREEN
                , P_MASK_BLUE
                , P_WIDTH
                , P_HEIGHT
                , P_MASK
                , P_HAS_PALETTE
                , P_HAS_MASK
                , P_PALETTE
                , P_SIZE
                , P_HANDLERS
            };
            ZZZJS_DECLARE_PROPERTY_MAP()

            ZZZJS_DECLARE_STATIC_PROPERTY_MAP()
            bool GetStaticProperty(JSContext *cx, int id, jsval *vp);

            ZZZJS_DECLARE_METHOD_MAP()
			ZZZJS_DECLARE_METHOD(create);
			ZZZJS_DECLARE_METHOD(destroy);
			ZZZJS_DECLARE_METHOD(copy);
			ZZZJS_DECLARE_METHOD(getSubImage);
			ZZZJS_DECLARE_METHOD(paste);
			// Image manipulation functions
			ZZZJS_DECLARE_METHOD(blur);
			ZZZJS_DECLARE_METHOD(blurHorizontal);
			ZZZJS_DECLARE_METHOD(blurVertical);
			ZZZJS_DECLARE_METHOD(scale);
			ZZZJS_DECLARE_METHOD(rescale);
			ZZZJS_DECLARE_METHOD(rotate);
			ZZZJS_DECLARE_METHOD(rotate90);
			ZZZJS_DECLARE_METHOD(rotate180);
			ZZZJS_DECLARE_METHOD(rotateHue);
			ZZZJS_DECLARE_METHOD(mirror);
			ZZZJS_DECLARE_METHOD(replace);
			ZZZJS_DECLARE_METHOD(_size);
			// Conversion functions
			ZZZJS_DECLARE_METHOD(convertToMono);
			ZZZJS_DECLARE_METHOD(convertAlphaToMask);
			ZZZJS_DECLARE_METHOD(convertToGreyscale);
			ZZZJS_DECLARE_METHOD(convertToDisabled);
			//
			ZZZJS_DECLARE_METHOD(setRGB);
			ZZZJS_DECLARE_METHOD(getRed);
			ZZZJS_DECLARE_METHOD(getGreen);
			ZZZJS_DECLARE_METHOD(getBlue);
			ZZZJS_DECLARE_METHOD(getColour);
			ZZZJS_DECLARE_METHOD(findFirstUnusedColour);
			ZZZJS_DECLARE_METHOD(setMaskFromImage);
			ZZZJS_DECLARE_METHOD(setMaskColour);
			ZZZJS_DECLARE_METHOD(saveFile);
			ZZZJS_DECLARE_METHOD(loadFile);
			ZZZJS_DECLARE_METHOD(setOption);
			ZZZJS_DECLARE_METHOD(getOption);
			ZZZJS_DECLARE_METHOD(getOptionInt);
			ZZZJS_DECLARE_METHOD(hasOption);

			// inner functions
			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);
 

			// Static Methods
            ZZZJS_DECLARE_STATIC_METHOD_MAP()
			ZZZJS_DECLARE_METHOD(canRead);
			ZZZJS_DECLARE_METHOD(addHandler);
			ZZZJS_DECLARE_METHOD(cleanUpHandlers);
			ZZZJS_DECLARE_METHOD(findHandler);
			ZZZJS_DECLARE_METHOD(removeHandler);
			ZZZJS_DECLARE_METHOD(findHandlerMime);
			ZZZJS_DECLARE_METHOD(insertHandler);
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSImage_H

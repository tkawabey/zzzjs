/*
 * wxJavaScript - bmpbtn.h
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
 * $Id: bmpbtn.h 678 2007-04-19 20:12:31Z fbraem $
 */
#ifndef _ZZZJS_GUI_DC_DC_H_
#define _ZZZJS_GUI_DC_DC_H_

#include "js/common/apiwrap.h"
#include <wx/dc.h>

namespace zzzJs
{
    namespace gui
    {
		namespace gdi 
		{
			class DC : public ApiWrapper<DC, wxDC>
			{
			public:

				WXJS_DECLARE_GET_PROP(wxDC)
				WXJS_DECLARE_SET_PROP(wxDC)
				WXJS_DECLARE_CONSTRUCTOR(wxDC)
				WXJS_DECLARE_DESTRUCTOR(wxDC)

				WXJS_DECLARE_PROPERTY_MAP()

				/**
				 * Property Ids.
				 */
				enum
				{
						P_DEPTH // GetDepth 
					,	P_DeviceOrigin // GetDeviceOrigin/SetDeviceOrigin  method SetDeviceOrigin”Å‚à—pˆÓ‚·‚é
					,	P_LogicalFunction // // GetLogicalFunction/SetLogicalFunction
					,	P_MapMode // GetMapMode/SetMapMode
					,	P_PPI // GEtPPI
					,	P_SIZE // GetSize
					,	P_SIZEMM // GetSizeMM 
					,	P_UserScale // GetUserScale/SetUserScale   obj.x, obj.y‚ÌŽó‚¯“n‚µ
					,	P_LogicalScale // GetLogicalScale/SetLogicalScale   obj.x, obj.y‚ÌŽó‚¯“n‚µ
					,	P_ISOK // IsOk 
					//,	P_Palette // SetPalette ... TODO
					,	P_ClippingBox  // GetClippingBox     obj.x, obj.y, obj.width, obj.height‚ÌŽó‚¯“n‚µ
					,	P_CharHeight // GetCharHeight
					,	P_CharWidth  // GetCharWidth 
					//,	P_FontMetrics   // GetFontMetrics  ... TODO
					// Text properties functions
					,	P_BackgroundMode   // GetBackgroundMode/SetBackgroundMode 
					,	P_Font    // GetFont /SetFont 
					,	P_LayoutDirection    // GetLayoutDirection /SetLayoutDirection 
					,	P_TextBackground    // GetTextBackground /SetTextBackground
					,	P_TextForeground    // GetTextForeground /SetTextForeground
					,	P_MaxX    // MaxX
					,	P_MaxY    // MaxY
					,	P_MinX    // MinX
					,	P_MinY    // MinY
					//	Background/foreground brush and pen
					,	P_Background    // Get/ Set Background 
					,	P_Brush    // Get/ Set Brush 
					,	P_Pen    // Get/ Set Pen 
					//	Transformation matrix
					//,	P_TransformMatrix    // Get/ Set TransformMatrix  ...TODO

				};

				WXJS_DECLARE_METHOD_MAP()
				WXJS_DECLARE_METHOD(release)
				WXJS_DECLARE_METHOD(copyAttributes)
				WXJS_DECLARE_METHOD(getPixel)
				WXJS_DECLARE_METHOD(setAxisOrientation)
				WXJS_DECLARE_METHOD(getAsBitmap)
				// Coordinate conversion functions
				WXJS_DECLARE_METHOD(deviceToLogicalX)
				WXJS_DECLARE_METHOD(deviceToLogicalY)
				WXJS_DECLARE_METHOD(deviceToLogicalXRel)
				WXJS_DECLARE_METHOD(deviceToLogicalYRel)
				WXJS_DECLARE_METHOD(logicalToDeviceX)
				WXJS_DECLARE_METHOD(logicalToDeviceY)
				WXJS_DECLARE_METHOD(logicalToDeviceXRel)
				WXJS_DECLARE_METHOD(logicalToDeviceYRel)
				// Drawing functions
				WXJS_DECLARE_METHOD(clear)
				WXJS_DECLARE_METHOD(drawArc)
				WXJS_DECLARE_METHOD(drawBitmap)
				WXJS_DECLARE_METHOD(drawCheckMark)
				WXJS_DECLARE_METHOD(drawCircle)
				WXJS_DECLARE_METHOD(drawEllipse)
				WXJS_DECLARE_METHOD(drawEllipticArc)
				WXJS_DECLARE_METHOD(drawIcon)
				WXJS_DECLARE_METHOD(drawLabel)
				WXJS_DECLARE_METHOD(drawLine)
				WXJS_DECLARE_METHOD(drawLines)
				WXJS_DECLARE_METHOD(drawPoint)
				WXJS_DECLARE_METHOD(drawPolygon)
				WXJS_DECLARE_METHOD(drawPolyPolygon)
				WXJS_DECLARE_METHOD(drawRectangle)
				WXJS_DECLARE_METHOD(drawRotatedText)
				WXJS_DECLARE_METHOD(drawRoundedRectangle)
				WXJS_DECLARE_METHOD(drawSpline)
				WXJS_DECLARE_METHOD(drawText)
				WXJS_DECLARE_METHOD(gradientFillConcentric)
				WXJS_DECLARE_METHOD(gradientFillLinear)
				WXJS_DECLARE_METHOD(floodFill)
				WXJS_DECLARE_METHOD(crossHair)
				// Clipping region functions
				WXJS_DECLARE_METHOD(destroyClippingRegion)
				WXJS_DECLARE_METHOD(setClippingRegion)
				WXJS_DECLARE_METHOD(setDeviceClippingRegion)
				// Text/character extent functions
				WXJS_DECLARE_METHOD(getMultiLineTextExtent)
				WXJS_DECLARE_METHOD(getPartialTextExtents)
				WXJS_DECLARE_METHOD(getTextExtent)
				// Text properties functions
				// Bounding box functions
				WXJS_DECLARE_METHOD(calcBoundingBox)
				WXJS_DECLARE_METHOD(resetBoundingBox)
				// Page and document start/end functions 
				WXJS_DECLARE_METHOD(startDoc)
				WXJS_DECLARE_METHOD(startPage)
				WXJS_DECLARE_METHOD(endDoc)
				WXJS_DECLARE_METHOD(endPage)
				// Bit-Block Transfer operations (blit)
				WXJS_DECLARE_METHOD(blit)
				WXJS_DECLARE_METHOD(stretchBlit)
				// Background/foreground brush and pen
				WXJS_DECLARE_METHOD(getPen)
				WXJS_DECLARE_METHOD(setPen)
				WXJS_DECLARE_METHOD(getBrush)
				WXJS_DECLARE_METHOD(setBrush)
				WXJS_DECLARE_METHOD(canUseTransformMatrix)
				WXJS_DECLARE_METHOD(resetTransformMatrix)
				// query capabilities
				WXJS_DECLARE_METHOD(canDrawBitmap)
				WXJS_DECLARE_METHOD(canGetTextExtent)

			};
		};	// namespace dc
    }; // namespace gui
}; //namespace wxjs
#endif //_ZZZJS_GUI_DC_DC_H_

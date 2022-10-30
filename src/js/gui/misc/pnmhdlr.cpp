/*
 * wxJavaScript - pnmhdlr.cpp
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
 * $Id: pnmhdlr.cpp 598 2007-03-07 20:13:28Z fbraem $
 */
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
#include "js/gui/misc/imghand.h"

using namespace zzzJs;
using namespace zzzJs::gui;

/***
 * <file>misc/pnmhdlr</file>
 * <module>gui</module>
 * <class name="wxPNMHandler" prototype="@wxImageHandler">
 *  Image handler for PNM images.
 *  Loading PNMs only works for ASCII or raw RGB images. When saving in PNM format, 
 *  wxPNMHandler will always save as raw RGB.
 * </class>
 */
ZZZJS_INIT_CLASS(PNMHandler, "PNMHandler", 0)

//ImageHandlerPrivate* PNMHandler::Construct(JSContext *cx, 
//										unsigned int argc, 
//										JS::Value *vp, 
//										bool constructing)
//{
ZZZJS_BEGIN_CONSTRUCTOR(ImageHandlerPrivate, PNMHandler)
{
    return new ImageHandlerPrivate(new wxPNMHandler(), true);
}
ZZZJS_END_CONSTRUCTOR

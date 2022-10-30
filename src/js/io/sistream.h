/*
 * wxJavaScript - sistream.h
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
 * $Id: sistream.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _wxjs_io_sistream_h
#define _wxjs_io_sistream_h

#include <wx/sckstrm.h>

#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
        class SocketInputStream : public wxSocketInputStream,
							          public JsWrapper<SocketInputStream, Stream>
        {
        public:
        #ifdef __MINGW32__
         // MingW needs a default constructor
	        SocketInputStream() {}
        #endif

			ZZZJS_DECLARE_CONSTRUCTOR(Stream)
			ZZZJS_DECLARE_DESTRUCTOR(Stream)

        };
    }; // namespace io
}; // namespace wxjs
#endif // _wxjs_io_sistream_h

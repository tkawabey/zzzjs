/*
 * wxJavaScript - wxlogtext.h
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
 * $Id: aistream.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef __ZZZJS_LOG_WXLOGTEXT_H__
#define __ZZZJS_LOG_WXLOGTEXT_H__

#include "js/common/apiwrap.h"
#include <wx/log.h>

namespace zzzJs
{
    namespace log
    {
        class LogText : public ApiWrapper<LogText, wxLogTextCtrl>
        {
        public:
			WXJS_DECLARE_ADD_PROP(wxLogTextCtrl)
			WXJS_DECLARE_DEL_PROP(wxLogTextCtrl)
			WXJS_DECLARE_GET_PROP(wxLogTextCtrl)
			WXJS_DECLARE_SET_PROP(wxLogTextCtrl)
			WXJS_DECLARE_SET_STR_PROP(wxLogTextCtrl)
			WXJS_DECLARE_CONSTRUCTOR(wxLogTextCtrl)
			WXJS_DECLARE_DESTRUCTOR(wxLogTextCtrl)

			// method...
	

			WXJS_DECLARE_PROPERTY_MAP()
//			WXJS_DECLARE_CONSTANT_MAP()
			WXJS_DECLARE_METHOD_MAP()
//			WXJS_DECLARE_STATIC_METHOD_MAP()
        };
    }; // namespace io
}; // namespace wxjs
#endif // __ZZZJS_LOG_WXLOGTEXT_H__

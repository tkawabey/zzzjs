/*
 * wxJavaScript - wxlogchain.h
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
#ifndef __ZZZJS_LOG_WXLOGFORMMATER_H__
#define __ZZZJS_LOG_WXLOGFORMMATER_H__

#include "js/common/apiwrap.h"
#include <wx/log.h>

namespace zzzJs
{
    namespace log
    {
        class LogFormatter : public ApiWrapper<LogFormatter, wxLogChain>
        {
        public:
			ZZZJS_DECLARE_ADD_PROP(wxLogChain)
			ZZZJS_DECLARE_DEL_PROP(wxLogChain)
			ZZZJS_DECLARE_GET_PROP(wxLogChain)
			ZZZJS_DECLARE_SET_PROP(wxLogChain)
			ZZZJS_DECLARE_SET_STR_PROP(wxLogChain)
			ZZZJS_DECLARE_CONSTRUCTOR(wxLogChain)
			ZZZJS_DECLARE_DESTRUCTOR(wxLogChain)

			// method...
			WXJS_DECLARE_METHOD(detachOldLog)
			WXJS_DECLARE_METHOD(passMessages)
			WXJS_DECLARE_METHOD(setLog)
	

			WXJS_DECLARE_PROPERTY_MAP()
//			WXJS_DECLARE_CONSTANT_MAP()
			WXJS_DECLARE_METHOD_MAP()
//			WXJS_DECLARE_STATIC_METHOD_MAP()

            /**
             * Property Ids.
             */
            enum
            {
				  P_OLD_LOG
				, p_IS_PASSING_MSG
            };
        };
    }; // namespace io
}; // namespace wxjs
#endif // __ZZZJS_LOG_WXLOGFORMMATER_H__

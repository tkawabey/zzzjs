/*
 * wxJavaScript - wxlog.h
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
#ifndef __ZZZJS_LOG_WXLOG_H__
#define __ZZZJS_LOG_WXLOG_H__

#include "js/common/apiwrap.h"
#include <wx/log.h>

namespace zzzJs
{
    namespace log
    {
        class Log : public ApiWrapper<Log, wxLog>
        {
        public:
            /**
             * Callback for retrieving properties of wxDir
             */
			WXJS_DECLARE_GET_PROP(wxLog)
            /**
             * Callback for when a wxDir object is created
             */
			WXJS_DECLARE_CONSTRUCTOR(wxLog)
			WXJS_DECLARE_DESTRUCTOR(wxLog)

			// method...
	
			// static method...
			WXJS_DECLARE_METHOD(addTraceMask)
			WXJS_DECLARE_METHOD(clearTraceMasks)
			WXJS_DECLARE_METHOD(getTraceMasks)
			WXJS_DECLARE_METHOD(isAllowedTraceMask)
			WXJS_DECLARE_METHOD(removeTraceMask)
			WXJS_DECLARE_METHOD(dontCreateOnDemand)
			WXJS_DECLARE_METHOD(getActiveTarget)
			WXJS_DECLARE_METHOD(setActiveTarget)
			WXJS_DECLARE_METHOD(setThreadActiveTarget)
			WXJS_DECLARE_METHOD(flushActive)
			WXJS_DECLARE_METHOD(resume)
			WXJS_DECLARE_METHOD(suspend)
			WXJS_DECLARE_METHOD(getLogLevel)
			WXJS_DECLARE_METHOD(isLevelEnabled)
			WXJS_DECLARE_METHOD(setComponentLevel )
			WXJS_DECLARE_METHOD(setLogLevel)
			WXJS_DECLARE_METHOD(enableLogging)
			WXJS_DECLARE_METHOD(isEnabled)
			WXJS_DECLARE_METHOD(getRepetitionCounting )
			WXJS_DECLARE_METHOD(setRepetitionCounting )
			WXJS_DECLARE_METHOD(getTimestamp)
			WXJS_DECLARE_METHOD(setTimestamp)
			WXJS_DECLARE_METHOD(disableTimestamp)
			WXJS_DECLARE_METHOD(getVerbose)
			WXJS_DECLARE_METHOD(setVerbose)

			WXJS_DECLARE_PROPERTY_MAP()
			WXJS_DECLARE_CONSTANT_MAP()
			WXJS_DECLARE_METHOD_MAP()
			WXJS_DECLARE_STATIC_METHOD_MAP()

        };
    }; // namespace io
}; // namespace wxjs
#endif // __ZZZJS_LOG_WXLOG_H__

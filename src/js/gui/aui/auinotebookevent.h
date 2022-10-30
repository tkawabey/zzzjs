/*
 * wxJavaScript - command.h
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
 * $Id: command.h 744 2007-06-11 19:57:09Z fbraem $
 */
#ifndef _WXJS_AuiNotebookEvent_H
#define _WXJS_AuiNotebookEvent_H


#include <wx/aui/auibook.h>
#include "js/gui/event/jsevent.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
		namespace aui 
		{
			typedef JSEvent<wxAuiNotebookEvent> PrivAuiNotebookEvent;
			class AuiNotebookEvent : public ApiWrapper<AuiNotebookEvent, PrivAuiNotebookEvent>
			{
			public:
				WXJS_DECLARE_GET_PROP(PrivAuiNotebookEvent)
				WXJS_DECLARE_SET_PROP(PrivAuiNotebookEvent)

				virtual ~AuiNotebookEvent()
				{
				}

				enum
				{ 
				  P_Button 
				};

				WXJS_DECLARE_PROPERTY_MAP()
			};
		};
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJS_AuiNotebookEvent_H

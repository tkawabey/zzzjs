/*
 * wxJavaScript - frame.h
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
 * $Id: frame.h 704 2007-05-11 19:46:45Z fbraem $
 */
#ifndef _WXJSFRAME_H
#define _WXJSFRAME_H

#include <wx/frame.h>
#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
	namespace gui
	{
/*
		class MyFrame : public wxFrame
		{
		public:	
			MyFrame(){}
			virtual ~MyFrame();

		};
*/
		class Frame : public ApiWrapper<Frame, wxFrame>
					, public wxFrame
		{
		public:

			Frame() : wxFrame() 
			{
			}

			virtual ~Frame()
			{
			}

			virtual wxToolBar* OnCreateToolBar(long style, 
												wxWindowID id,
												const wxString& name);

			static void InitClass(JSContext* cx, 
									JSObject* obj, 
									JSObject* proto);
			static bool Resolve(JSContext *cx, JS::Handle<JSObject*> obj, JS::Handle<jsid> id);


			WXJS_DECLARE_ADD_PROP(wxFrame)
			WXJS_DECLARE_DEL_PROP(wxFrame)
			WXJS_DECLARE_GET_PROP(wxFrame)
			WXJS_DECLARE_SET_PROP(wxFrame)
			WXJS_DECLARE_SET_STR_PROP(wxFrame)
			WXJS_DECLARE_CONSTRUCTOR(wxFrame)
            WXJS_DECLARE_DESTRUCTOR(wxFrame)
        	
			WXJS_DECLARE_METHOD_MAP()
			WXJS_DECLARE_METHOD(create)
			WXJS_DECLARE_METHOD(setStatusText)
			WXJS_DECLARE_METHOD(setStatusWidths)
			WXJS_DECLARE_METHOD(createStatusBar)
			WXJS_DECLARE_METHOD(processCommand)
			WXJS_DECLARE_METHOD(createToolBar)
		  
			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);


			WXJS_DECLARE_CONSTANT_MAP()

			WXJS_DECLARE_PROPERTY_MAP()

			enum
			{
				  P_MENUBAR
				, P_STATUSBAR_FIELDS
				, P_STATUS_WIDTHS
				, P_TOOLBAR
				, P_STATUSBAR
				, P_STATUSBAR_PANE
			};
		};

		class FrameEventHandler : public EventConnector<wxFrame>
								, public wxEvtHandler
		{
		public:
			// Events
			void OnClose(wxCloseEvent &event);
			void OnMenu(wxCommandEvent &event);
			void OnIconize(wxIconizeEvent &event);
			void OnMaximize(wxMaximizeEvent &event);
			static void InitConnectEventMap();
		private:
			static void ConnectClose(wxFrame *p, bool connect);
			static void ConnectMenu(wxFrame *p, bool connect);
			static void ConnectIconize(wxFrame *p, bool connect);
			static void ConnectMaximize(wxFrame *p, bool connect);
		};

	}; // namespace gui
}; // namespace wxjs

#endif // _WXJSFRAME_H

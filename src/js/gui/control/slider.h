/*
 * wxJavaScript - slider.h
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
 * $Id: slider.h 692 2007-05-02 21:30:16Z fbraem $
 */
#ifndef _WXJSSlider_H
#define _WXJSSlider_H

#include "js/common/evtconn.h"
#include "js/common/apiwrap.h"
namespace zzzJs
{
    namespace gui
    {
        class Slider : public ApiWrapper<Slider, wxSlider>
        {
        public:

            static void InitClass(JSContext* cx, 
                                  JSObject* obj, 
                                  JSObject* proto);
			WXJS_DECLARE_ADD_PROP(wxSlider)
			WXJS_DECLARE_DEL_PROP(wxSlider)
			WXJS_DECLARE_GET_PROP(wxSlider)
			WXJS_DECLARE_SET_PROP(wxSlider)
			WXJS_DECLARE_SET_STR_PROP(wxSlider)
			WXJS_DECLARE_CONSTRUCTOR(wxSlider)
            WXJS_DECLARE_DESTRUCTOR(wxSlider)
        	
	        WXJS_DECLARE_PROPERTY_MAP()
	        enum
	        {
		        P_LINESIZE
		        , P_MAX
		        , P_MIN
		        , P_PAGESIZE
		        , P_SEL_END
		        , P_SEL_START
		        , P_THUMB_LENGTH
		        , P_TICK
		        , P_VALUE
	        };

            WXJS_DECLARE_CONSTANT_MAP()

            WXJS_DECLARE_METHOD_MAP()
	        WXJS_DECLARE_METHOD(create)
	        WXJS_DECLARE_METHOD(clearSel)
	        WXJS_DECLARE_METHOD(clearTicks)
	        WXJS_DECLARE_METHOD(setRange)
	        WXJS_DECLARE_METHOD(setSelection)
	        WXJS_DECLARE_METHOD(setTickFreq)
			static JSBool _innerCreate(JSContext *cx, JSObject *obj, unsigned argc, JS::Value *vp,jsval *rval);

        };

        class SliderEventHandler : public EventConnector<wxSlider>
                                 , public wxEvtHandler
        {
        public:
          // Events
	        void OnScrollChanged(wxScrollEvent& event);
	        void OnScrollTop(wxScrollEvent& event);
	        void OnScrollBottom(wxScrollEvent& event);
	        void OnScrollLineUp(wxScrollEvent& event);
	        void OnScrollLineDown(wxScrollEvent& event);
	        void OnScrollPageUp(wxScrollEvent& event);
	        void OnScrollPageDown(wxScrollEvent& event);
	        void OnScrollThumbTrack(wxScrollEvent& event);
	        void OnScrollThumbRelease(wxScrollEvent& event);
            static void InitConnectEventMap();
        private:
	        static void ConnectScrollChanged(wxSlider *p, bool connect);
	        static void ConnectScrollTop(wxSlider *p, bool connect);
	        static void ConnectScrollBottom(wxSlider *p, bool connect);
	        static void ConnectScrollLineUp(wxSlider *p, bool connect);
	        static void ConnectScrollLineDown(wxSlider *p, bool connect);
	        static void ConnectScrollPageUp(wxSlider *p, bool connect);
	        static void ConnectScrollPageDown(wxSlider *p, bool connect);
	        static void ConnectScrollThumbTrack(wxSlider *p, bool connect);
	        static void ConnectScrollThumbRelease(wxSlider *p, bool connect);
        };
    }; // namespace gui
}; // namespace wxjs

#endif //_WXJSSlider_H

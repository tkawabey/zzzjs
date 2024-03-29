/*
 * wxJavaScript - process.h
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
 * $Id: process.h 598 2007-03-07 20:13:28Z fbraem $
 */
#ifndef _wxJS_io_process_h
#define _wxJS_io_process_h

#include <wx/process.h>
#include "js/common/jswrap.h"

namespace zzzJs
{
    namespace io
    {
        class Process : public JsWrapper<Process, Process>
                      , public wxProcess
        {
        public:
	        Process(JSContext *cx, JSObject *obj, int flags);
	        virtual ~Process();

	        //static Process *Construct(JSContext *cx, 
									//	unsigned int argc, 
									//	JS::Value *vp, 
									//	bool constructing);
			ZZZJS_DECLARE_CONSTRUCTOR(Process)
			ZZZJS_DECLARE_DESTRUCTOR(Process)
            static void InitClass(JSContext *cx, JSObject *obj, JSObject *proto);

            //static bool GetProperty(Process *p, 
            //                      JSContext *cx, 
            //                      JSObject *obj, 
            //                      int id, 
            //                      JS::MutableHandle<JS::Value>& vp);
			ZZZJS_DECLARE_GET_PROP(Process)
	        //static bool SetProperty(Process *p, JSContext *cx, JSObject *obj, int id, jsval *vp);

            ZZZJS_DECLARE_PROPERTY_MAP()
            ZZZJS_DECLARE_CONSTANT_MAP()
	        ZZZJS_DECLARE_METHOD_MAP()

            enum
            {
                  P_ERROR_STREAM = WXJS_START_PROPERTY_ID
                , P_INPUT_STREAM
                , P_OUTPUT_STREAM
                , P_ERROR_AVAILABLE
                , P_INPUT_AVAILABLE
                , P_INPUT_OPENED
                , P_PID
	        };

	        static JSBool closeOutput(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool detach(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool redirect(JSContext *cx, unsigned argc, JS::Value *vp);

            ZZZJS_DECLARE_STATIC_METHOD_MAP()
	        static JSBool kill(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool exists(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool open(JSContext *cx, unsigned argc, JS::Value *vp);

        };

    }; // namespace io
}; // namespace wxjs

#endif //_wxJS_io_process_h

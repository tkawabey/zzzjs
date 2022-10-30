#ifndef _WXJS_MEMBUF_H
#define _WXJS_MEMBUF_H

/////////////////////////////////////////////////////////////////////////////
// Name:        jsmembuf.h
// Purpose:		Ports wxMemoryBuffer to JavaScript
// Author:      Franky Braem
// Modified by:
// Created:     02.12.2005
// Copyright:   (c) 2001-2005 Franky Braem
// Licence:     LGPL
/////////////////////////////////////////////////////////////////////////////

#include <wx/buffer.h>
#include <jsapi.h>
#include <tchar.h>
#include <wx/string.h>
#include "js/common/apiwrap.h"
#include "js/common/conf.h"


namespace zzzJs
{
    namespace ext
    {
        class MemoryBuffer : public ApiWrapper<MemoryBuffer, wxMemoryBuffer>
        {
        public:
			WXJS_DECLARE_GET_PROP(wxMemoryBuffer)
			WXJS_DECLARE_SET_PROP(wxMemoryBuffer)
			WXJS_DECLARE_CONSTRUCTOR(wxMemoryBuffer)
/*        	
	        static bool GetProperty(wxMemoryBuffer *p, JSContext *cx, JSObject *obj, int id, JS::MutableHandle<JS::Value> vp);
	        static bool SetProperty(wxMemoryBuffer *p, JSContext *cx, JSObject *obj, int id, JS::MutableHandle<JS::Value> vp);
*/
	        enum
	        { 
		        P_DATA_LENGTH = WXJS_START_PROPERTY_ID,
		        P_LENGTH,
		        P_IS_NULL
	        };

	        WXJS_DECLARE_PROPERTY_MAP()
	        WXJS_DECLARE_METHOD_MAP()
/*
	        static wxMemoryBuffer *Construct(JSContext *cx, 
										JSObject* obj,
										unsigned int argc, 
										JS::Value *vp, 
										bool constructing);
*/
	        static JSBool append(JSContext *cx, unsigned argc, JS::Value *vp);
	        static JSBool toString(JSContext *cx, unsigned argc, JS::Value *vp);
        };
    }; // namespace ext
}; // namespace wxjs
#endif

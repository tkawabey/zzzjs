/*
 * wxJavaScript - stmt.h
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
 * $Id: stmt.h 713 2007-05-14 21:15:48Z fbraem $
 */
#ifndef wxjs_sqlite_stmt_h
#define wxjs_sqlite_stmt_h

#include <sqlite3.h>


#include "js/common/apiwrap.h"
#include "js/common/clntdata.h"
namespace zzzJs
{
    
    namespace sqlite
    {
        class Statement : public ApiWrapper<Statement, Statement>
        {
        public:
            Statement(Database &database,
                      sqlite3_stmt *stmt = NULL) : m_pStmt(stmt)
            {
                m_database.Ref(database);
            }
        
            virtual ~Statement()
            {
	            if ( m_pStmt != NULL )
	            {
		            sqlite3_finalize(m_pStmt);
	            }
                m_database.UnRef();
            }

            WXJS_DECLARE_PROPERTY_MAP()
            //static bool GetProperty(Statement *p,
            //                        JSContext *cx,
            //                        JSObject *obj,
            //                        int id,
            //                        jsval *vp);
			WXJS_DECLARE_GET_PROP(Statement)

            enum
            {
                P_COLUMNCOUNT
            };
        
            WXJS_DECLARE_METHOD_MAP()
            WXJS_DECLARE_METHOD(bind)
            WXJS_DECLARE_METHOD(columnOriginalName)
            WXJS_DECLARE_METHOD(columnDeclType)
            WXJS_DECLARE_METHOD(columnName)
            WXJS_DECLARE_METHOD(columnTableName)
            WXJS_DECLARE_METHOD(fetchArray)
            WXJS_DECLARE_METHOD(fetchObject)
            WXJS_DECLARE_METHOD(step)
            WXJS_DECLARE_METHOD(reset)


            //static JSBool bind(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
            ////static JSBool clearbindings(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
            //static JSBool columnOriginalName(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
            //static JSBool columnDeclType(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
            //static JSBool columnName(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
            //static JSBool columnTableName(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
            //static JSBool fetchArray(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
            //static JSBool fetchObject(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
            //static JSBool step(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);
            //static JSBool reset(JSContext *cx, JSObject *obj, uintN argc, jsval *argv, jsval *rval);

        private:
            
            sqlite3_stmt *m_pStmt;
            wxObject m_database;
        };
        
    }; // namespace sqlite
    
}; // namespace wxjs

#endif //  wxjs_sqlite_stmt_h

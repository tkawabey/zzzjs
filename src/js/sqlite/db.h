/*
 * wxJavaScript - db.h
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
 * $Id: db.h 713 2007-05-14 21:15:48Z fbraem $
 */
#ifndef wxjs_sqlite_db_h
#define wxjs_sqlite_db_h

#include <map>

#include <sqlite3.h>


#include "js/common/apiwrap.h"
#include "js/common/clntdata.h"
namespace zzzJs
{
  namespace sqlite
  {
    // Use reference counting to make sure that Database
    // is never closed before all depended objects
    // are destroyed
    class DatabaseRefData : public wxObjectRefData
    {
    public:
      DatabaseRefData() : wxObjectRefData()
                        , m_pDatabase(NULL)
      {
      }

      virtual ~DatabaseRefData()
      {
        if ( m_pDatabase != NULL )
    		sqlite3_close(m_pDatabase);
      }
      
      void SetHandle(sqlite3* db) { m_pDatabase = db; }
      sqlite3* GetHandle() { return m_pDatabase; }
      
    private:
      sqlite3* m_pDatabase;
    };

    class Statement;
    class Database : public ApiWrapper<Database, Database>
                   , public JavaScriptClientData
                   , public wxObject
    {
      public:
      
        Database(JSContext *cx, JSObject *obj);
        virtual ~Database() {}
      
        //static Database* Construct(JSContext *cx,
        //                           JSObject *obj,
        //                           uintN argc,
        //                           jsval *argv,
        //                           bool constructing);
			WXJS_DECLARE_CONSTRUCTOR(Database)
        
        WXJS_DECLARE_CONSTANT_MAP()

        WXJS_DECLARE_PROPERTY_MAP()
		//static bool GetProperty(Database *p,
  //                              JSContext *cx,
  //                              JSObject *obj,
  //                              int id,
  //                              jsval *vp);
  //      static bool AddProperty(Database *p,
  //                              JSContext *cx,
  //                              JSObject *obj,
  //                              const wxString &prop,
  //                              jsval *vp);
			WXJS_DECLARE_ADD_PROP(Database)
			WXJS_DECLARE_GET_PROP(Database)
				
		enum
		{
		    P_ERRMSG
		  , P_ERRNO
          , P_CHANGES
          , P_TOTAL_CHANGES
          , P_AUTO_COMMIT
          , P_LAST_ROWID
          , P_OPENED
		};
				
		WXJS_DECLARE_METHOD_MAP()
		WXJS_DECLARE_METHOD(prepare)
        WXJS_DECLARE_METHOD(exec)

        WXJS_DECLARE_STATIC_METHOD_MAP()
        WXJS_DECLARE_METHOD(complete)

        static int CommitHook(void *arg);
        static void RollbackHook(void *arg);
        static void Trace(void *arg, const char *SQL);
        static void Update(void *arg ,
                           int type,
                           char const *dbname,
                           char const *tbname,sqlite_int64 rowid);
    }; // class Database
        
  }; // namespace sqlite
  
}; // namespace wxjs

#endif // wxjs_sqlite_db_h

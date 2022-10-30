package.name = "io"
package.kind = "dll"
package.language = "c++"
package.target = "wxJS_io"
package.buildflags = { "unicode", "no-64bit-checks", "no-edit-and-continue" }
package.defines = { project.defines, "WXJSDLL_BUILD" }

-- Set the include paths
if ( windows ) then
  tinsert(package.config["Debug"].includepaths, wx_debug_include)
  tinsert(package.config["Release"].includepaths, wx_release_include)
end
tinsert(package.includepaths, js_include)

-- Set the library paths
if ( windows ) then
  tinsert(package.libpaths, wx_lib)
  tinsert(package.libpaths, js_lib)
end
if ( windows ) then
  tinsert(package.config["Debug"].libpaths, "../ext/Debug")
  tinsert(package.config["Release"].libpaths, "../ext/Release")
  package.config["Debug"].links = { "wxbase28ud", "wxzlibd", "wxbase28ud_net", "wxmsw28ud_adv", "js32mtd" }
  package.config["Release"].links = { "wxbase28u", "wxzlib", "wxbase28u_net", "wxmsw28u_adv", "js32mt" }
  package.links = { "shell32", "ole32", "advapi32", "user32", "wsock32", "Winmm" }
elseif ( linux ) then
  tinsert(package.buildoptions, "`" .. wx_lib .. "/wx-config --cxxflags` -W -Wall")
  tinsert(package.linkoptions,  "`" .. wx_lib .. "/wx-config --libs`")
end

tinsert(package.links, "wxJS_ext")

package.files = { matchfiles("*.cpp", "*.h"), 
                  "../common/index.h",
                  "../common/type.cpp", "../common/type.h", 
                  "../common/jsutil.cpp", "../common/jsutil.h",
                  "../common/wxjs.h" }

/*
函数列表：
base::runScript(script)         运行JS代码
dom::alert(str)                 提示弹窗
dom::confirm(str)               确认弹窗，点击确认返回true，否则返回false
http::get(url)                  HTTP GET方式获取数据（注意跨域问题）
http::post(url, body)           HTTP POST方式提交数据（注意跨域问题）
save::saveItem(key, value)      将value存储到key位置
save::readItem(key)             读取key位置的数据
base2::runHtml(html)            运行HTML代码
output::title1(String)          以1级标题显示String
output::title2(String)          以2级标题显示String
output::title3(String)          以3级标题显示String
output::title4(String)          以4级标题显示String
output::title5(String)          以5级标题显示String
output::title6(String)          以6级标题显示String
output::body(num, String[])     以正文文字显示String，共num行，第i行的文字为String[i]
URL::slt(url, String)           设置一个超链接，链接地址为url，链接显示文字为String
URL::ol(url)                    打开url地址的网址
table::form(line, row, value[]) 显示line行row列的表格，第i行第j列表格里的值是value[(i-1)*row+j]
table::listing(num, value[])    显示1个列表，共num行，第i行的列表文字为value[i]
*/

#include "codingtang.h"
#include <string>

using namespace std;

namespace base {
inline string escapeString(string str) { // 转义字符串
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '\\' || str[i] == '\'') {
            str.insert(i, "\\");
        }
    }
    return str;
}
template <typename Type = void> inline Type runScript(const string &script); // 运行JS代码
template <> inline void runScript<void>(const string &script) {
    emscripten_run_script(script.c_str());
}
template <> inline int runScript<int>(const string &script) {
    return emscripten_run_script_int(script.c_str());
}
template <> inline string runScript<string>(const string &script) {
    return emscripten_run_script_string(script.c_str());
}
} // namespace base

namespace dom {
using namespace base;
inline void alert(const string &str) { // 提示弹窗
    runScript("alert('" + escapeString(str) + "');");
}
inline bool confirm(const string &str) { // 确认弹窗，点击确认返回true，否则返回false
    string script = "(function() {";
    script += "let r = confirm('" + escapeString(str) + "');";
    script += "if (r==true) return 1;";
    script += "else return 0;";
    script += "})();";
    return runScript<int>(script);
}
/*
在一般网页中可用，但是在酷町平台的网页中出错，原因未知
inline string prompt(const string &str, const string &def = "") {
    return runScript<string>("prompt('" + escapeString(str) + "', '" + escapeString(def) + "');");
}
*/
} // namespace dom

namespace http {
using namespace base;
inline string get(const string &url) { // HTTP GET方式获取数据（注意跨域问题）
    string script = "(function() {";
    script += "let request = new XMLHttpRequest();";
    script += "request.open('GET', '" + escapeString(url) + "', false);";
    script += "request.send(null);";
    script += "return request.responseText;";
    script += "})();";
    return runScript<string>(script);
}
inline string post(const string &url, const string &body) { // HTTP POST方式提交数据（注意跨域问题）
    string script = "(function() {";
    script += "let request = new XMLHttpRequest();";
    script += "request.open('POST', '" + escapeString(url) + "', false);";
    script += "request.send('" + escapeString(body) + "');";
    script += "return request.responseText;";
    script += "})();";
    return runScript<string>(script);
}
} // namespace http

namespace save {
using namespace base;
inline void saveItem(const string &key, const string &value) { // 将value存储到key位置
    runScript("localStorage.setItem('" + escapeString(key) + "', '" + escapeString(value) + "');");
}
inline string readItem(const string &key) { // 读取key位置的数据
    return runScript<string>("localStorage.getItem('" + escapeString(key) + "');");
}
} // namespace save
 
namespace base2 {
using namespace base;
template <typename Type = void> inline Type runHtml(const string &html); // 运行HTML代码
template <> inline void runHtml<void>(const string &html) {
    runScript("document.write('" + escapeString(html) + "');");
}
template <> inline int runHtml<int>(const string &html) {
    return runScript<int>("document.write('" + escapeString(html) + "');");
}
template <> inline string runHtml<string>(const string &html) {
    return runScript<string>("document.write('" + escapeString(html) + "');");
}
} // namespace base2

namespace output {
using namespace base2;
inline void title1(const string &String) { // 1级标题
    runHtml("<h1>" + escapeString(String) + "</h1>");
}
inline void title2(const string &String) { // 2级标题
    runHtml("<h2>" + escapeString(String) + "</h2>");
}
inline void title3(const string &String) { // 3级标题
    runHtml("<h3>" + escapeString(String) + "</h3>");
}
inline void title4(const string &String) { // 4级标题
    runHtml("<h4>" + escapeString(String) + "</h4>");
}
inline void title5(const string &String) { // 5级标题
    runHtml("<h5>" + escapeString(String) + "</h5>");
}
inline void title6(const string &String) { // 6级标题
    runHtml("<h6>" + escapeString(String) + "</h6>");
}
inline void body(const int &num, const string String[]) { // 正文
    string html = "<p>";
    for(int i=1;i<num;i++){
        html += escapeString(String[i]) + "<br>";
    }
    html += escapeString(String[num]);
    html += "</p>";
    runHtml(html);
}
} // namespace output

namespace URL {
using namespace base2;
inline void slt(const string &url, const string &String) { // 显示链接文字
    runHtml("<a href=\"" + escapeString(url) + "\">" + escapeString(String) +"</a>");
}
inline void ol(const string &url) { // 打开网址
    runHtml("<iframe src=\"" + escapeString(url) + "" "\" scrolling=\"true\" border=\"0\" frameborder=\"true\" framespacing=\"0\" allowfullscreen=\"true\" width=\"97%\" height=\"97%\"> </iframe>");
}
} // namespace URL

namespace table {
using namespace base2;
inline void form(const int &line, const int &row, const string value[]) { // 表格
    string html = "<table border=\"";
    html += "1";
    html += "\">";
    for(int i=1;i<=line;i++){
        html += "<tr>";
        for(int j=1;j<=row;j++){
            html += "<td>" + escapeString(value[(i-1)*row+j]) + "</td>";
        }
        html += "</tr>";
    }
    html += "</table>";
    runHtml(html);
}
inline void listing(const int &num, const string value[]) { // 列表
    string html = "<ul>";
    for(int i=1;i<=num;i++){
        html += "<li>" + escapeString(value[i]) + "</li>";
    }
    html += "</ul>";
    runHtml(html);
}
} // namespace table

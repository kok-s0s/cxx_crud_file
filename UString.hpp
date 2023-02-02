#ifndef USTRING_H_
#define USTRING_H_

#include <regex>
#include <string>

using std::regex;
using std::smatch;
using std::string;
using std::to_string;

class String {
 private:
  string _content;

 public:
  String(string content) { _content = content; }
  ~String() {}

  String args(string substitution) {
    string upToDateContent = "";
    string suffix = "";

    regex percentSign("%([1-9]{1})");

    auto content_begin =
        std::sregex_iterator(_content.begin(), _content.end(), percentSign);
    auto content_end = std::sregex_iterator();

    for (std::sregex_iterator i = content_begin; i != content_end; ++i) {
      smatch match = *i;
      string match_str = match.str();

      int index = match_str[1] - '1';

      if (index == 0)
        upToDateContent += match.prefix().str() + substitution;
      else
        upToDateContent += match.prefix().str() + "%" + std::to_string(index);

      suffix = match.suffix();
    }

    upToDateContent += suffix;

    return String(upToDateContent);
  }

  String args(const char *substitution) {
    string upToDateContent = "";
    string suffix = "";

    regex percentSign("%([1-9]{1})");

    auto content_begin =
        std::sregex_iterator(_content.begin(), _content.end(), percentSign);
    auto content_end = std::sregex_iterator();

    for (std::sregex_iterator i = content_begin; i != content_end; ++i) {
      smatch match = *i;
      string match_str = match.str();

      int index = match_str[1] - '1';

      if (index == 0)
        upToDateContent += match.prefix().str() + substitution;
      else
        upToDateContent += match.prefix().str() + "%" + std::to_string(index);

      suffix = match.suffix();
    }

    upToDateContent += suffix;

    return String(upToDateContent);
  }

  template <typename T>
  String args(T substitution) {
    string upToDateContent = "";
    string suffix = "";

    regex percentSign("%([1-9]{1})");

    auto content_begin =
        std::sregex_iterator(_content.begin(), _content.end(), percentSign);
    auto content_end = std::sregex_iterator();

    for (std::sregex_iterator i = content_begin; i != content_end; ++i) {
      smatch match = *i;
      string match_str = match.str();

      int index = match_str[1] - '1';

      if (index == 0)
        upToDateContent += match.prefix().str() + std::to_string(substitution);
      else
        upToDateContent += match.prefix().str() + "%" + std::to_string(index);

      suffix = match.suffix();
    }

    upToDateContent += suffix;

    return String(upToDateContent);
  }

  template <class T, class... Args>
  String args(T head, Args... rest) {
    String result(_content);
    result = result.args(head);
    result = result.args(rest...);
    return result;
  }

  string to_string() { return _content; }
};

#endif  // USTRING_H_
